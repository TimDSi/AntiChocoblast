#include "../CommonFunctions.h"

// Detect keyboard input
static void KeyboardListener(int refreshRate)
{
    while (true) 
    {
        for (int i = 8; i <= 255; i++) 
        {
            if (GetAsyncKeyState(i) & 0x8000) 
            {
                ExitProcess(0);
            }
        }
        Sleep(refreshRate);
    }
}

int main(int refreshRate)
{
    //Waiting for PainAuChocolat to start
    while (!IsProcessRunning(L"PainAuChocolat.exe")) 
    {
        Sleep(refreshRate);
    }

    // Create a thread for keyboard listener
    thread keyboardThread(KeyboardListener, refreshRate);

    //Waiting for PainAuChocolat to stop
    while (IsProcessRunning(L"PainAuChocolat.exe")) 
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
