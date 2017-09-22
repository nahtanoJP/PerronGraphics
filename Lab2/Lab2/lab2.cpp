#include <shlobj.h>
#include <Windows.h>
#include <direct.h>
#include <iostream>

#if defined(_DEBUG)
# define GCC_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#else
# define GCC_NEW new
#endif

using namespace std;

class DirectXGame {};

int main(void) {
	DirectXGame* d = nullptr;

	//Check for instance.
	//==================================
	if (d != NULL) {
		cout << "There is an instance already open!" << endl;
		return(0);
	}
	else {
		d = new DirectXGame();
		cout << "Instance created." << endl;
	}
	DirectXGame* game = d;
	//==================================
	//Check for free space.
	__int64 available, total, totalfree;
	GetDiskFreeSpaceEx(NULL, (PULARGE_INTEGER)&available, (PULARGE_INTEGER)&total, (PULARGE_INTEGER)&totalfree);
	if ((available / (1024 * 1024)) < 300) {
		cout << "There is not enough free space. :(" << endl;
	}
	else {
		cout << "There is enough free space! :)" << endl;
	}
	//==================================
	//Check for free RAM (memory).
	MEMORYSTATUSEX status;
	status.dwLength = sizeof(status);
	GlobalMemoryStatusEx(&status);
	cout << "Installed Memory = " << ((status.ullTotalPhys / 1024) / 1024) << "MB\n";
	cout << "Available Memory = " << ((status.ullAvailVirtual / 1024) / 1024) << "MB\n";

	if (status.ullTotalPhys < 300000) { 
		cout << "CheckMemory Failure: Not enough physical memory." << endl;
		return false;
	}
	else {
		cout << "Physical Memory: Check." << endl;
	}

	if (status.ullAvailVirtual < 600000) {
		cout << "CheckMemory Failure: Not enough virtual memory." << endl;
		return false;
	}
	else {
		cout << "Virtual Memory: Check." << endl;
	}

	char *buff = GCC_NEW char[6000000];
	if (buff) {
		delete[] buff;
	}
	else {
		cout << "CheckMemory Failure: Not enough contiguous memory." << endl;
		return false;
	}
	//==================================
	//Check CPU speed.
	DWORD BufSize = sizeof(DWORD);
	DWORD dwMHz = 0;
	DWORD type = REG_DWORD;
	HKEY hKey;

	//Open the key where the proc speed is hidden:
	long lError = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0, KEY_READ, &hKey);

	if (lError == ERROR_SUCCESS) {
		//Query the key:
		RegQueryValueEx(hKey, "~MHz", NULL, &type, (LPBYTE)&dwMHz, &BufSize);
	}

	//Convert to Ghz on the way out.
	cout << "CPU clock speed: " << (dwMHz / 1000.0f) << "Ghz." << endl;
	//==================================

	system("PAUSE");
}
