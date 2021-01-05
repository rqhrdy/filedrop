#pragma once

#include <windows.h> 
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <iostream>
#include <string>

class SideCarManager {
private:
	bool isConnected;
	HANDLE pipeHandle;
	//CHANGE TO "ZoomOSC" once everything is finalized
	std::string pipeName = "\\\\.\\pipe\\psexecsvc";
	int start();
	PROCESS_INFORMATION startup(LPCSTR lpApplicationName);
	PROCESS_INFORMATION processInfo;
	wchar_t* strToWstr(std::string text);
	void closeProcess(PROCESS_INFORMATION pi);

public:
	SideCarManager();
	~SideCarManager();
	int sendMessage(std::string message);
	int openConnection();
	//int start();
};