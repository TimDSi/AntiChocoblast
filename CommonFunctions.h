#pragma once

#include <windows.h>
#include <tlhelp32.h>
#include <string>

using namespace std;

bool IsProcessRunning(const wstring& processName);
int ReadArgument(LPSTR lpAnsiStr);
