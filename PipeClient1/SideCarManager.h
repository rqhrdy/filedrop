#pragma once

#include <windows.h> 
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <iostream>
#include <string>

class SideCarManager {
private:
	wchar_t* strToWstr(std::string text);
	bool isConnected;
	//CHANGE TO "ZoomOSC" once everything is finalized
	std::string pipeName = "\\\\.\\pipe\\psexecsvc";
	HANDLE pipeHandle;

public:
	SideCarManager();
	~SideCarManager();
	int sendMessage(std::string message);
	int openConnection();
};