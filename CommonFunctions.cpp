#include "CommonFunctions.h"

bool IsProcessRunning(const wstring& processName)
{
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot != INVALID_HANDLE_VALUE)
    {
        PROCESSENTRY32 pe32{};
        pe32.dwSize = sizeof(PROCESSENTRY32);
        if (Process32First(hSnapshot, &pe32))
        {
            do
            {
                if (pe32.szExeFile == processName)
                    return true;
            } while (Process32Next(hSnapshot, &pe32));
        }
        CloseHandle(hSnapshot);
    }
    return false;
}

int ReadArgument(LPSTR lpAnsiStr) {
    try {
        return stoi(lpAnsiStr);
    }
    catch (const exception& e) {
        return 100;
    }
}
