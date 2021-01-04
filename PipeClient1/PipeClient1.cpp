#include <windows.h> 
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <iostream>
#include <string>
#include "SideCarManager.h"

#define BUFSIZE 512
 
int _tmain(int argc, TCHAR *argv[]) 
{ 
    SideCarManager scm;
    scm.openConnection();
    scm.sendMessage("hiiiiiiiiiiiiiii");
    std::string yonk = "";
    while (yonk.compare("exit") != 0) {
        std::cout << "Please input some input for me :" << std::endl;
        std::cin >> yonk;
        scm.sendMessage(yonk);
    }
    Sleep(20000);
    /*
    std::string message = "Default message from client";
    int wchars_num = MultiByteToWideChar(CP_UTF8, 0, message.c_str(), -1, NULL, 0);
    wchar_t* wstrMessage = new wchar_t[wchars_num];
    MultiByteToWideChar(CP_UTF8, 0, message.c_str(), -1, wstrMessage, wchars_num);
    std::string pipename = "\\\\.\\pipe\\psexecsvc";
    wchars_num = MultiByteToWideChar(CP_UTF8, 0, pipename.c_str(), -1, NULL, 0);
    wchar_t* wstrPipename = new wchar_t[wchars_num];
    MultiByteToWideChar(CP_UTF8, 0, pipename.c_str(), -1, wstrPipename, wchars_num);
   HANDLE hPipe; 
   LPTSTR lpvMessage = wstrMessage; // TEXT("Default message from client."); 
   TCHAR  chBuf[BUFSIZE]; 
   BOOL   fSuccess = FALSE; 
   DWORD  cbRead, cbToWrite, cbWritten, dwMode; 
   LPTSTR lpszPipename = wstrPipename; // TEXT("\\\\.\\pipe\\mynamedpipe");

   if( argc > 1 )
      lpvMessage = argv[1];
 
// Try to open a named pipe; wait for it, if necessary. 
 
   while (1) 
   { 
      hPipe = CreateFile( 
         lpszPipename,   // pipe name 
         GENERIC_READ |  // read and write access 
         GENERIC_WRITE, 
         0,              // no sharing 
         NULL,           // default security attributes
         OPEN_EXISTING,  // opens existing pipe 
         0,              // default attributes 
         NULL);          // no template file 
 
   // Break if the pipe handle is valid. 
 
      if (hPipe != INVALID_HANDLE_VALUE) 
         break; 
 
      // Exit if an error other than ERROR_PIPE_BUSY occurs. 
 
      if (GetLastError() != ERROR_PIPE_BUSY) 
      {
         _tprintf( TEXT("Could not open pipe. GLE=%d\n"), GetLastError() ); 
         return -1;
      }
 
      // All pipe instances are busy, so wait for 20 seconds. 
 
      if ( ! WaitNamedPipe(lpszPipename, 20000)) 
      { 
         printf("Could not open pipe: 20 second wait timed out."); 
         return -1;
      } 
   } 
 
// The pipe connected; change to message-read mode. 
 
   dwMode = PIPE_READMODE_MESSAGE; 
   fSuccess = SetNamedPipeHandleState( 
      hPipe,    // pipe handle 
      &dwMode,  // new pipe mode 
      NULL,     // don't set maximum bytes 
      NULL);    // don't set maximum time 
   if ( ! fSuccess) 
   {
      _tprintf( TEXT("SetNamedPipeHandleState failed. GLE=%d\n"), GetLastError() ); 
      return -1;
   }
 
// Send a message to the pipe server. 
    
   cbToWrite = (lstrlen(lpvMessage)+1)*sizeof(TCHAR);
   _tprintf( TEXT("Sending %d byte message: \"%s\"\n"), cbToWrite, lpvMessage); 

   fSuccess = WriteFile( 
      hPipe,                  // pipe handle 
      lpvMessage,             // message 
      cbToWrite,              // message length 
      &cbWritten,             // bytes written 
      NULL);                  // not overlapped 

   if ( ! fSuccess) 
   {
      _tprintf( TEXT("WriteFile to pipe failed. GLE=%d\n"), GetLastError() ); 
      return -1;
   }

   printf("\nMessage sent to server, receiving reply as follows:\n");
 
   do 
   { 
   // Read from the pipe. 
 
      fSuccess = ReadFile( 
         hPipe,    // pipe handle 
         chBuf,    // buffer to receive reply 
         BUFSIZE*sizeof(TCHAR),  // size of buffer 
         &cbRead,  // number of bytes read 
         NULL);    // not overlapped 
 
      if ( ! fSuccess && GetLastError() != ERROR_MORE_DATA )
         break; 
 
      _tprintf( TEXT("\"%s\"\n"), chBuf ); 
   } while ( ! fSuccess);  // repeat loop if ERROR_MORE_DATA 

   if ( ! fSuccess)
   {
      _tprintf( TEXT("ReadFile from pipe failed. GLE=%d\n"), GetLastError() );
      return -1;
   }
   std::string input = "Default input from client";
   std::cin >> input;
   wchars_num = MultiByteToWideChar(CP_UTF8, 0, input.c_str(), -1, NULL, 0);
   wchar_t* wstrInput = new wchar_t[wchars_num];
   MultiByteToWideChar(CP_UTF8, 0, input.c_str(), -1, wstrInput, wchars_num);
   //sending MY message
   LPTSTR lpvInput = wstrInput;
   cbToWrite = (lstrlen(lpvInput) + 1) * sizeof(TCHAR);
   _tprintf(TEXT("Sending %d byte message: \"%s\"\n"), cbToWrite, lpvInput);

   fSuccess = WriteFile(
       hPipe,                  // pipe handle 
       lpvInput,             // message 
       cbToWrite,              // message length 
       &cbWritten,             // bytes written 
       NULL);                  // not overlapped 

   if (!fSuccess)
   {
       _tprintf(TEXT("WriteFile to pipe failed. GLE=%d\n"), GetLastError());
       return -1;
   }
   printf("\n<End of message, press ENTER to terminate connection and exit>");
   _getch();
 
   CloseHandle(hPipe); 
   delete[] wstrMessage;
   delete[] wstrPipename;
   delete[] wstrInput;*/
   return 0; 
}