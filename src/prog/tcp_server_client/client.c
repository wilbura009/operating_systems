#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

#define CLT_NOTICE "[CLIENT] - NOTICE: Inputs greater than 2 chars for menu selection and 7 for empID will be truncated."

#define CLT_USR_PROMPT "[CLIENT] - Please select from the following: \n\n\
  1 - Get SALARY for an employee.\n\
  2 - STOP.\n\n\
[CLIENT] - "

#define CLT_USR_EMP_ID_PROMPT "[CLIENT] - Enter Employee ID: "

#define CLT_STAT_SEND_REQ "[CLIENT] - Sent request to server ->"
#define CLT_STAT_STOP     "[CLIENT] - Sent STOP request to the server. Exiting."
#define CLT_INVALID_INPUT "[CLIENT] - INVALID input:"
#define CLT_SIGINT_WAIT   "[CLIENT] - Waiting for SIGINT (Ctrl-C) ..."
#define CLT_SIGINT_RCV    "[CLIENT] - Received SIGINT (Ctrl-C). Continuing ..."
#define CLT_SIGHNDL_ERR   "[CLIENT] - FAILED to set up signal handler. Exiting."
#define CLT_ERROR         "[CLIENT] - ERROR:"

#define EMP_ID_MAX_SZ 7

// Flushes stdin after a fgets() call in case the input was longer than the buffer
void flush_stdin()
{
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
}

void sigint_handler(int sig)
{
  printf("\n%s\n", CLT_SIGINT_RCV); // \n because of the ^C
}

int sigint_init(sigset_t *sigset, struct sigaction *sigact)
{
  // Set up the signal handler
  sigemptyset(&sigact->sa_mask); // Clear the mask
  sigact->sa_flags = 0; // No flags
  sigact->sa_handler = sigint_handler; // Set the handler function
  int result = sigaction(SIGINT, sigact, NULL); // Set the handler for SIGINT
  printf("%s\n", CLT_SIGINT_WAIT); 

  return result;
}

int main(int argc, char **argv)
{ 
  struct  sockaddr_in sad; /* structure to hold an IP address     */
  int     clientSocket;    /* socket descriptor                   */ 
  struct  hostent  *ptrh;  /* pointer to a host table entry       */
  
  char    *host;           /* pointer to host name                */
  int     port;            /* protocol port number                */  
  
  char    svrResp[128]; 
  char    buff[128];
  int     n;
   
  if (argc != 3)
  {
    fprintf(stderr,"Usage: %s server-name port-number\n",argv[0]);
    exit(1);
  }

  // Print notice about input truncation
  printf("%s\n", CLT_NOTICE);
  
  /* Extract host-name from command-line argument */
  host = argv[1];   /* if host argument specified   */
  
  /* Extract port number  from command-line argument */
  port = atoi(argv[2]);   /* convert to binary */

  // Signal handling
  sigset_t sigset;
  struct sigaction sigact;

  int rc_sigint;
  if ( (rc_sigint = sigint_init(&sigset, &sigact)) == -1)
  {
    fprintf(stderr, "%s\n", CLT_SIGHNDL_ERR);
    exit(1);
  }
  sigsuspend(&sigset); // Wait for SIGINT to be received
  printf("\n");

  /* Create a socket. */
  clientSocket = socket(PF_INET, SOCK_STREAM, 0);
  if (clientSocket < 0)
  {
    fprintf(stderr, "%s socket(): %s\n", CLT_ERROR, strerror(errno));
    exit(1);
  }

  /* Connect the socket to the specified server. */
  memset((char *)&sad,0,sizeof(sad)); /* clear sockaddr structure */
  sad.sin_family = AF_INET;           /* set family to Internet     */
  sad.sin_port = htons((u_short)port);
  ptrh = gethostbyname(host); /* Convert host name to equivalent IP address and copy to sad. */
  if ( ((char *)ptrh) == NULL ) {
    fprintf(stderr,"%s gethostbyname(): %s - %s\n", CLT_ERROR, strerror(errno), host);
    exit(1);
  }
  memcpy(&sad.sin_addr, ptrh->h_addr, ptrh->h_length);
  
  if (connect(clientSocket, (struct sockaddr *)&sad, sizeof(sad)) < 0) {
    fprintf(stderr,"%s connect(): %s\n", CLT_ERROR, strerror(errno));
    exit(1);
  }

  // Get user input from selection menu
  int usrSelectionSz = 2, iUsrSelection;
  char usrSelection[usrSelectionSz];
  printf("%s", CLT_USR_PROMPT);
  fgets(usrSelection, usrSelectionSz, stdin);
  iUsrSelection = atoi(usrSelection);
  flush_stdin(); // clear stdin buffer

  if (iUsrSelection == 1) // Get SALARY for an employee
  {
    // Get user input for employee ID
    char empID[7];
    printf("%s", CLT_USR_EMP_ID_PROMPT);
    fgets(empID, EMP_ID_MAX_SZ, stdin);
    //flush_stdin(); // clear stdin buffer

    // Send the employee ID to the server
    write(clientSocket, empID, strlen(empID)+1);
    printf("%s %s\n", CLT_STAT_SEND_REQ, empID);

    // Get the Data from the server
    svrResp[0]='\0';
    n=read(clientSocket, buff, sizeof(buff));
    while(n > 0)
    {
      strncat(svrResp,buff,n);
      if (buff[n-1]=='\0') break;
      n=read(clientSocket, buff, sizeof(buff));
    }
    // Print the Data
    printf("\n%s\n", svrResp);
  }
  else if (iUsrSelection == 2) // STOP
  {
    write(clientSocket, "STOP", strlen("STOP")+1);
    printf("%s\n", CLT_STAT_STOP);
    close(clientSocket);
    exit(0);
  }
  else
  {
    fprintf(stderr, "%s\n", CLT_INVALID_INPUT);
  }
     
  // Close the socket.
  close(clientSocket);
}
