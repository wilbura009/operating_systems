#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <wait.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

#define SVR_STAT_LISTEN        "[SERVER] - Listening for client on port:"
#define SVR_STAT_CONN_SUCCESS  "[SERVER] - Accepted client connection from:"
#define SVR_STAT_CONN_FAIL     "[SERVER] - FAILED to accept client connection from:"
#define SVR_STAT_FORK_FAIL     "[SERVER] - FAILED to fork child proc."
#define SVR_STAT_SEND_RESP     "[SERVER] - Sent response to client ->"
#define SVR_STAT_EMP_NOT_FOUND "[SERVER] - Employee not found."
#define SVR_STAT_CLT_REQ       "[SERVER] - Received client request:"
#define SVR_STAT_STOP          "[SERVER] - Received STOP command from client."
#define SVR_STAT_FORK_CHILD    "[SERVER] - Forked child proc. to handle client request, PID:"
#define SVR_STAT_FORK_PARENT   "[SERVER] - Parent proc. continuing to listen for client requests, PID:"
#define SVR_STAT_CHILD_EXIT    "[SERVER] - Child proc. exited with status:"
#define SVR_STAT_CHILD_TERM    "[SERVER] - Child proc. terminated with signal:"
#define SVR_STAT_CHILD_UNEXP   "[SERVER] - Child proc. terminated unexpectedly."
#define SVR_ERROR              "[SERVER] - ERROR:"

typedef struct employee_info {
  char ID[7];
  char name[10];
  double salary;
} Employee;

void flush_stdin()
{
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
}

char *employee_to_string(Employee e)
{
  char *str = malloc(sizeof(char) * 128);
  sprintf(str, "[SERVER] - %s %.2f", e.name, e.salary);
  return str;
}

/* Return the index for the employee or -1 if not found */
int employee_get_index_by_id(Employee DB[], char *ID)
{
  int i;

  if (strcmp(ID, "STOP") == 0)
    return -2; // STOP command

  for (i = 0; i < 10; i++)
  {
    if (strcmp(DB[i].ID, ID) == 0)
      return i; // ID found at index i
  }
  return -1; // ID not found
}

void read_client_request(int socket, char* request, char* buff)
{
  int n;
  request[0]='\0'; // clear clientRequest buffer
  n=read(socket, buff, sizeof(buff));
  while(n > 0)
  {
    strncat(request,buff,n);
    if (buff[n-1]=='\0') break;
    n=read(socket,buff,sizeof(buff));
  }
}

void handle_client_request(int connSock, char* clientRequest, Employee DB[])
{
  // Write response to client
  int index = employee_get_index_by_id(DB, clientRequest);
  if (index == -2) // STOP command
  {
    printf("\n%s", SVR_STAT_STOP);
  }
  else if (index == -1) // ID not found
  {
    printf("%s\n", SVR_STAT_EMP_NOT_FOUND);
    write(connSock, SVR_STAT_EMP_NOT_FOUND, strlen(SVR_STAT_EMP_NOT_FOUND)+1);
  }
  else // ID found
  {
    printf("%s %s\n", SVR_STAT_SEND_RESP, employee_to_string(DB[index]));
    write(connSock, employee_to_string(DB[index]), sizeof(Employee));
  }
  close(connSock); // TODO: print a message that the connection was closed
  exit(EXIT_SUCCESS);
}

void handle_child_exit(int status)
{
  if (WIFEXITED(status))
    printf("\n%s %d\n", SVR_STAT_CHILD_EXIT, WEXITSTATUS(status));
  else if (WIFSIGNALED(status))
    printf("\n%s %d\n", SVR_STAT_CHILD_TERM, WTERMSIG(status));
  else
   printf("\n%s\n", SVR_STAT_CHILD_UNEXP);
}

int main(int argc, char **argv) {
  struct    sockaddr_in sad; /* structure to hold server's address  */
  int       port;            /* protocol port number                */

  struct    sockaddr_in cad; /* structure to hold client's address  */
  socklen_t alen;            /* length of address                   */

  int       welcomeSocket, connectionSocket; /* socket descriptors  */

  char      clientRequest[128]; 
  char      serverResponse[128]; 
  char      buff[128];
  int       i, n;

  Employee DB[10] = {
    {"afg994","Britt",72000.0},
    {"uti804","Hugh",54432.0},
    {"ofp667","Robbi",9508.0},
    {"diy852","Miguel",14638.0},
    {"bfg277","Marna",26617.0},
    {"bff954","Delcie",26772.0},
    {"grp116","Sam",18480.0},
    {"mee065","Tiny",3027.0},
    {"yuo826","Vanita",12064.0},
    {"zed219","Karren",22428.0}
  };

  /* Check command-line argument for protocol port and extract   */
  /* port number if one is specified. Otherwise, give error      */
  if (argc > 1)                 /* if argument specified        */
    port = atoi(argv[1]); /* convert argument to binary   */
  else
  { 
    fprintf(stderr,"Usage: %s port-number\n",argv[0]);
    exit(1);
  }

  /* Create a socket */
  welcomeSocket = socket(PF_INET, SOCK_STREAM, 0); /* CREATE SOCKET */
  if (welcomeSocket < 0)
  {
    fprintf(stderr, "socket creation failed\n");
    exit(1);
  }

  /* Bind a local address to the socket */
  memset((char *)&sad,0,sizeof(sad)); /* clear sockaddr structure   */
  sad.sin_family = AF_INET;           /* set family to Internet     */
  sad.sin_addr.s_addr = INADDR_ANY;   /* set the local IP address   */
  sad.sin_port = htons((u_short)port);/* set the port number        */ 

  if (bind(welcomeSocket, (struct sockaddr *)&sad, sizeof(sad)) < 0)
  {
    fprintf(stderr,"bind failed\n");
    exit(1);
  }

  /* Specify the size of request queue */
  if (listen(welcomeSocket, 10) < 0)
  {
    fprintf(stderr,"listen failed\n");
    exit(1);
  }
  printf("%s %d ...\n", SVR_STAT_LISTEN, port);

  /* Main server loop - accept and handle requests */
  while (1)
  {
    alen = sizeof(cad); // length of address
    if ( (connectionSocket=accept(welcomeSocket, (struct sockaddr *)&cad, &alen)) < 0)
    {
      fprintf(stderr, "%s %s, port %d\n", SVR_STAT_CONN_FAIL, inet_ntoa(cad.sin_addr), ntohs(cad.sin_port));
      fprintf(stderr, "%s accept failed: %s\n", SVR_ERROR, strerror(errno));
      exit(1);
    }
    else {
      printf("%s %s, port %d\n\n", SVR_STAT_CONN_SUCCESS, inet_ntoa(cad.sin_addr), ntohs(cad.sin_port));
    }

    pid_t pid;
    switch (pid = fork())
    {
      case -1: // Fork failed
        fprintf(stderr, "%s\n", SVR_STAT_FORK_FAIL);
        exit(EXIT_FAILURE);

      case 0: // Child (client) process DB request
        printf("%s %d\n", SVR_STAT_FORK_CHILD, getpid());
        read_client_request(connectionSocket, clientRequest, buff);
        printf("\n%s %s\n", SVR_STAT_CLT_REQ, clientRequest); // Print client request
        handle_client_request(connectionSocket, clientRequest, DB); // exit(EXIT_SUCCESS) in this function

      default: // parent (server) - waits for other clients to connect
        printf("%s %d\n", SVR_STAT_FORK_PARENT, getpid());
        int status;
        if (waitpid(pid, &status, 0) == -1)
        {
          fprintf(stderr, "%s waitpid failed: %s\n", SVR_ERROR, strerror(errno));
          exit(EXIT_FAILURE);
        }
        handle_child_exit(status);
        printf("%s %d\n", SVR_STAT_FORK_PARENT, getpid());
        continue;
    }
  }

  return 0;
}
