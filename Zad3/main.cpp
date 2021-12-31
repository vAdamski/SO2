/*
Program 1A
Program po wywołaniu bez argumentów kończy się, wyświetlając jedynie komunikat, że został wywołany bez
argumentów.
W przypadku wywołania z liczbą argumentów większą niż 1, tworzy taką liczbę procesów potomnych, ile było argumentów, a
każdy z procesów wyświetla na ekranie jeden argument.
*Gdy pierwszym argumentem jest "c", wykorzystana zostanie funkcja *clone(…)*, jeżeli jest to inny znak, używany jest
*fork()*.
 
Program 3A
Zachowanie programu jest takie jak w wersji IX/POSIX, z pominięciem opcji wywołanie "c", ale został napisany z
wykorzystaniem wyłącznie WinAPI (windows.h*).
Wskazówka: CreateProcess(…)
*/
 
#include <windows.h>
#include <cwchar>
#include <iostream>
 
using namespace std;
 
void zeroMemory(PROCESS_INFORMATION* pi, STARTUPINFO* si)
{
    ZeroMemory(pi, sizeof(*pi));
    ZeroMemory(si, sizeof(*si));
}
 
int main(int argc, char** argv) {
    PROCESS_INFORMATION pi;
    STARTUPINFO si;
    CreateMutex(NULL, false, (LPCSTR)"myMutex");
 
 
 
 
    int err = GetLastError();
    bool isMainProcess = false;
 
    if (!err)
    {
        isMainProcess = true;
    }
 
    zeroMemory(&pi, &si);
 
    si.cb = sizeof(si);
 
    if (argc == 1)
    {
        if (isMainProcess)
        {
            cout << "Brak parametrów" << endl;
        }
 
        return 1;
    }
 
 
    for (int i = 1; i < argc ; i++)
    {
        int newProcess = CreateProcess(argv[0],
                                       argv[i],
                                       NULL,
                                       NULL,
                                       NULL,
                                       0,
                                       NULL,
                                       NULL,
                                       &si,
                                       &pi);
 
        if (!newProcess)
        {
            return 1;
        }
        cout << "Process: "<<argv[i] << endl;
 
 
        WaitForSingleObject(pi.hProcess, INFINITE);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
 
    return 0;
}