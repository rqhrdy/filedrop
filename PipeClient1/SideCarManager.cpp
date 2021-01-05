#include <windows.h> 
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <iostream>
#include <string>
#include "SideCarManager.h"

#define BUFSIZE MAX_PATH

SideCarManager::SideCarManager() {
    pipeHandle = NULL;
    isConnected = false;
    start();
}

SideCarManager::~SideCarManager() {
    CloseHandle(pipeHandle);
    closeProcess(processInfo);
}

int SideCarManager::start() {

    TCHAR buffer[BUFSIZE];

    DWORD directorySuccess = GetCurrentDirectory(BUFSIZE, buffer);
    if (directorySuccess == 0)
        return -1;
    try {
        std::wstring bufferW(&buffer[0]); //convert to wstring
        std::string bufferString(bufferW.begin(), bufferW.end()); //and convert to string.
        std::string pathForSidecar = "\\net5.0\\ZoomOSCSideCar.exe";
        bufferString = bufferString.substr(0, bufferString.find_last_of('\\')); //remove current extension
        bufferString = bufferString.append(pathForSidecar); //add on current directory path
        LPCSTR path = bufferString.c_str();
        processInfo = startup(path);
        return 0;
    }
    catch (int e) {
        return -2;
    }
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

PROCESS_INFORMATION SideCarManager::startup(LPCSTR lpApplicationName)
{
    // additional information
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;

    // set the size of the structures
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // start the program up
    CreateProcessA
    (
        lpApplicationName,   // the path
        NULL,                // Command line
        NULL,                   // Process handle not inheritable
        NULL,                   // Thread handle not inheritable
        FALSE,                  // Set handle inheritance to FALSE
        CREATE_NEW_CONSOLE,     // Opens file in a separate console
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory 
        &si,            // Pointer to STARTUPINFO structure
        &pi           // Pointer to PROCESS_INFORMATION structure
    );
    return pi;
    // Close process and thread handles. 

}

void SideCarManager::closeProcess(PROCESS_INFORMATION pi) {
    try {
        TerminateProcess(pi.hProcess, 0);
        TerminateProcess(pi.hThread, 0);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        return;
    }
    catch (int e) {
        return;
    }
}
