#ifndef ERREXIT_H
#define ERREXIT_H

#define ERROR_PROCESSING 1
/******************** errExit **************************************
  void errExit(const char szFmt[], ... )
Purpose:
    Prints an error message defined by the printf-like szFmt and the
    corresponding arguments to that function.  The number of 
    arguments after szFmt varies dependent on the format codes in
    szFmt.  
    It also exits the program.
Parameters:
    I   const char szFmt[]      This contains the message to be printed
                                and format codes (just like printf) for 
                                values that we want to print.
    I   ...                     A variable-number of additional arguments
                                which correspond to what is needed
                                by the format codes in szFmt. 
Returns:
    Exits the program with a return code of ERROR_PROCESSING (99).
Notes:
    - Prints "ERROR: " followed by the formatted error message specified 
      in szFmt. 
    - Requires including <stdarg.h>
**************************************************************************/
void errExit(const char szFmt[], ... );

#endif // ERREXIT_H
