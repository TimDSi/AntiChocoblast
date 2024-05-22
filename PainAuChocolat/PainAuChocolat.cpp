#include "../CommonFunctions.h"

// Detect clipboard copy
static void ClipboardListener(int refreshRate)
{
    // clear the clipboard
    if (OpenClipboard(nullptr))
    {
        EmptyClipboard();
        CloseClipboard();
    }

    // detect if clipboard has been filled
    while (true)
    {
        if (OpenClipboard(nullptr)) 
        {
            if (GetClipboardData(CF_UNICODETEXT) != nullptr) 
            {
                ExitProcess(0); 
            }
            CloseClipboard(); 
        }
        Sleep(refreshRate); 
    }
}

int main(int refreshRate)
{
    // Create a thread for clipboard listener
    thread clipboardThread(ClipboardListener, refreshRate);

    //Waiting for Chocolatine to start
    while (!IsProcessRunning(L"Chocolatine.exe")) 
    {
        Sleep(refreshRate);
    }

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
