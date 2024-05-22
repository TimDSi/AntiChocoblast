#include "../CommonFunctions.h"

int main(int refreshRate)
{
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
