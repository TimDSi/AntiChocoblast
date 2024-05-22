#include "../CommonFunctions.h"

// Get the text from the clipboard
static wstring GetClipboardText()
{
    wstring clipboardText;
    
    if (OpenClipboard(nullptr))
    {
        HANDLE hClipboardData = GetClipboardData(CF_UNICODETEXT);
        if (hClipboardData != nullptr)
        {
            wchar_t* pszText = static_cast<wchar_t*>(GlobalLock(hClipboardData));
            if (pszText != nullptr)
            {
                clipboardText = pszText;
                GlobalUnlock(hClipboardData);
            }
        }
        CloseClipboard();
    }

    return clipboardText;
}

// Detect clipboard upadtes
static void ClipboardListener(int refreshRate)
{
    // save the current clipboard 
    const wstring clipboardText = GetClipboardText();

    // detect clipboard changes
    while (true)
    {
        if (clipboardText != GetClipboardText()) 
        {
			ExitProcess(0); 
		}
        Sleep(refreshRate); 
    }
}

int main(int refreshRate)
{
    //Waiting for Chocolatine to start
    while (!IsProcessRunning(L"Chocolatine.exe")) 
    {
        Sleep(refreshRate);
    }

    // Create a thread for clipboard listener
    thread clipboardThread(ClipboardListener, refreshRate); 

    //Waiting for Chocolatine to stop
    while (IsProcessRunning(L"Chocolatine.exe")) 
    {
        Sleep(refreshRate);
    }

    // Lock the computer
    LockWorkStation();

    // end the process
    ExitProcess(0);

    return 0;
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    main(ReadArgument(lpCmdLine));
    return 0;
}
