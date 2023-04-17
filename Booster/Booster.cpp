// Booster.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <windows.h>
#include <stdio.h>
#include "../PriorityBooster/PriorityBoosterCommon.h"


int Error(const char* msg);

int main(int argc, const char* argv[])
{
	if (argc < 3)
	{
		printf("Usage: Booster <ThreadId> <Priority> \n");
		return 0;
	}

	HANDLE hDevice = CreateFile(L"\\\\.\\PriorityBooster", GENERIC_WRITE, FILE_SHARE_WRITE, nullptr, OPEN_EXISTING, 0, nullptr);
	if (hDevice == INVALID_HANDLE_VALUE)
	{
		return Error("Failed to open device");
	}


	ThreadData data;
	data.ThreadId = atoi(argv[1]);
	data.Priority = atoi(argv[2]);

	DWORD returned;
	BOOL success = DeviceIoControl(
		hDevice,
		IOCTL_PRIORITY_BOOSTER_SET_PRIORITY,
		&data, sizeof(data),
		nullptr, 0,
		&returned, nullptr
	);
	if (success)
	{
		printf("Priority change succeeded!\n");
	}
	else
	{
		Error("Priority change failed!");
	}

	CloseHandle(hDevice);

    return 0;
}

int Error(const char* msg) {
	printf("%s (error=%d)\n", msg, GetLastError());
	return 1;
}