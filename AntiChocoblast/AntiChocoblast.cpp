#include "../CommonFunctions.h"
#include <fstream>
#include "Resource.h"

// Extract executable from resource and save it to disk
static bool ExtractResource(int resourceID, const wchar_t* outputPath)
{
    // find the specified resource.
    HRSRC hResource = FindResource(NULL, MAKEINTRESOURCE(resourceID), L"EXE");
    if (!hResource) return false;

    // load the resource into memory.
    HGLOBAL hLoadedResource = LoadResource(NULL, hResource);
    if (!hLoadedResource) return false;

    // lock the loaded resource and get its size.
    LPVOID pLockedResource = LockResource(hLoadedResource);
    DWORD dwResourceSize = SizeofResource(NULL, hResource);
    if (!pLockedResource || dwResourceSize == 0) return false;

    // open the output file for writing in binary mode.
    ofstream outputFile(outputPath, ios::binary);
    if (!outputFile) return false;

    // write the contents of the resource to the output file.
    outputFile.write((const char*)pLockedResource, dwResourceSize);

    // close the output file.
    outputFile.close();

    return true;
}

// Main function
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    // temp Paths
    wchar_t tempPath[MAX_PATH];
    GetTempPath(MAX_PATH, tempPath);
    wchar_t chocolatinExePath[MAX_PATH];
    wchar_t painAuChocolatExePath[MAX_PATH];
    wsprintf(chocolatinExePath, L"%sChocolatine.exe", tempPath);
    wsprintf(painAuChocolatExePath, L"%sPainAuChocolat.exe", tempPath);

    // executables extraction
    if (!ExtractResource(IDR_CHOCOLATINE, chocolatinExePath)) {
        MessageBox(NULL, L"Failed to extract Chocolatine.exe", L"Error", MB_OK | MB_ICONERROR);
        return 1;
    }
    if (!ExtractResource(IDR_PAINAUCHO, painAuChocolatExePath)) {
        MessageBox(NULL, L"Failed to extract PainAuChocolat.exe", L"Error", MB_OK | MB_ICONERROR);
        return 1;
    }

    // start executables
    ShellExecute(NULL, L"open", chocolatinExePath, to_wstring(ReadArgument(lpCmdLine)).c_str(), NULL, SW_SHOWNORMAL); 
    ShellExecute(NULL, L"open", painAuChocolatExePath, to_wstring(ReadArgument(lpCmdLine)).c_str(), NULL, SW_SHOWNORMAL); 

    return 0; 
}
