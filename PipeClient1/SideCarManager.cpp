#include <windows.h> 
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <iostream>
#include <string>
#include "SideCarManager.h"

SideCarManager::SideCarManager() {
    pipeHandle = NULL;
    isConnected = false;
}

SideCarManager::~SideCarManager() {
    CloseHandle(pipeHandle);
}

int SideCarManager::sendMessage(std::string message) {
    if (!isConnected)
        return -1;
    BOOL   fSuccess = FALSE;
    DWORD  cbRead, cbToWrite, cbWritten, dwMode;
    wchar_t* wstrMessage = strToWstr(message);
    LPTSTR lpvMessage = wstrMessage;
    cbToWrite = (lstrlen(lpvMessage) + 1) * sizeof(TCHAR);
    //_tprintf(TEXT("Sending %d byte message: \"%s\"\n"), cbToWrite, lpvMessage);

    fSuccess = WriteFile(
        pipeHandle,                  // pipe handle 
        lpvMessage,             // message 
        cbToWrite,              // message length 
        &cbWritten,             // bytes written 
        NULL);                  // not overlapped 

    if (!fSuccess)
    {
        //failed to write to pipe
        return -2;
    }

    printf("\nMessage sent to server, receiving reply as follows:\n");
}

int SideCarManager::openConnection() {

    wchar_t* wstrPipe = strToWstr(pipeName);

    LPTSTR lpszPipename = wstrPipe;

    // Try to open a named pipe; wait for it, if necessary. 

    while (1)
    {
        pipeHandle = CreateFile(
            lpszPipename,   // pipe name 
            GENERIC_READ |  // read and write access 
            GENERIC_WRITE,
            0,              // no sharing 
            NULL,           // default security attributes
            OPEN_EXISTING,  // opens existing pipe 
            0,              // default attributes 
            NULL);          // no template file 

      // Break if the pipe handle is valid. 

        if (pipeHandle != INVALID_HANDLE_VALUE) {
            isConnected = true;
            delete[] wstrPipe;
            return 1;
        }

        // Exit if an error other than ERROR_PIPE_BUSY occurs. 

        if (GetLastError() != ERROR_PIPE_BUSY)
        {
            delete[] wstrPipe;
            isConnected = true;
            //failed to open pipe
            return -1;
        }

        // All pipe instances are busy, so wait for 20 seconds. 

        if (!WaitNamedPipe(lpszPipename, 20000))
        {
            delete[] wstrPipe;
            //Couldn't find pipe
            return -2;
        }
    }

}

wchar_t* SideCarManager::strToWstr(std::string text) {
    int wchars_num;
    //CHANGE TO "ZoomOSC" once everything is finalized
    wchars_num = MultiByteToWideChar(CP_UTF8, 0, text.c_str(), -1, NULL, 0);
    wchar_t* wstr = new wchar_t[wchars_num];
    MultiByteToWideChar(CP_UTF8, 0, text.c_str(), -1, wstr, wchars_num);
    return wstr;
}