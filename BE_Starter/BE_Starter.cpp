#include "BE_Starter.hpp"

int main()
{
	VirtualizerStart();
	BOOL IsWow64 = 0;
	STARTUPINFOA si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	char Client_BE[MAX_PATH], Client[MAX_PATH], Client64[MAX_PATH], Proxy[MAX_PATH];
	ZeroMemory(Client_BE, MAX_PATH);
	ZeroMemory(Client, MAX_PATH);
	ZeroMemory(Client64, MAX_PATH);
	ZeroMemory(Proxy, MAX_PATH);
	if (!IsElevated())
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
		std::cout << "[>>] [ERROR] : Administrative rights are needed for this bypass!" << std::endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		goto END;
	}

	if (!GetFullPathNameA("Client_BE.exe", MAX_PATH, Client_BE, 0) || //only 32 bit
		!GetFullPathNameA("Client_Game.exe", MAX_PATH, Client, 0) ||
		!GetFullPathNameA("Client_Game_x64.exe", MAX_PATH, Client64, 0) ||
		!GetFullPathNameA("ProxyManager.exe", MAX_PATH, Proxy, 0))
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
		std::cout << "[ERROR] : GetFullPathNameA failed with errorcode " << GetLastError() << std::endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		goto END;

	}
	if (!IsWow64Process(GetCurrentProcess(), &IsWow64)) // 确定指定进程是否运行在64位操作系统的32环境（Wow64）下。
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
		std::cout << "[ERROR] : IsWow64Process failed with errorcode " << GetLastError() << std::endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		goto END;
	}
	/*
	if (!CreateProcessA(0, Proxy, 0, 0, 0, 0, 0, 0, &si, &pi))
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
		std::cout << "[ERROR] : CreateProcessA_1 failed with errorcode " << GetLastError() << std::endl;
		std::cout << "[ERROR] : Path " << Proxy << std::endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		goto END;
	}
	*/
	Sleep(300);
	if (!IsWow64) // !IsWow64 = Is64    Wow64 = 64位操作系统的32环境
	{
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		ZeroMemory(&pi, sizeof(pi));
		if (!CreateProcessA(0, Client64, 0, 0, 0, 0, 0, 0, &si, &pi))
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
			std::cout << "[ERROR] : CreateProcessA_2 failed with errorcode " << GetLastError() << std::endl;
			std::cout << "[ERROR] : Path " << Client64 << std::endl;
			goto END;
		}
		
		std::cout << "64 bit operation system detected." << std::endl;
	}
	else
	{
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		ZeroMemory(&pi, sizeof(pi));
		if (!CreateProcessA(0, Client, 0, 0, 0, 0, 0, 0, &si, &pi))
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
			std::cout << "[ERROR] : CreateProcessA_3 failed with errorcode " << GetLastError() << std::endl;
			std::cout << "[ERROR] : Path " << Client << std::endl;
			goto END;
		}
		std::cout << "32 bit operation system detected." << std::endl;
	}
	Sleep(100);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	if (!CreateProcessA(0, Client_BE, 0, 0, 0, 0, 0, 0, &si, &pi))
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
		std::cout << "[ERROR] : CreateProcessA_4 failed with errorcode " << GetLastError() << std::endl;
		std::cout << "[ERROR] : Path " << Client_BE << std::endl;
		goto END;
	}
END:
	std::cout << "Starter: Exit..." << std::endl;
#if _DEBUG
	getchar();
#else
	Sleep(2000);
#endif
	VirtualizerEnd();
	return 1;
}

bool IsElevated()
{
	BOOL fRet = FALSE;
	HANDLE hToken = NULL;
	TOKEN_ELEVATION Elevation;
	DWORD cbSize = sizeof(TOKEN_ELEVATION);
	ZeroMemory(&Elevation, sizeof(Elevation));
	if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken))
	{
		if (GetTokenInformation(hToken, TokenElevation, &Elevation, sizeof(Elevation), &cbSize))
			fRet = Elevation.TokenIsElevated;
	}
	if (hToken)
		CloseHandle(hToken);
	return fRet;
}