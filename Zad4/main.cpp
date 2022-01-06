/*
Program 1B
Program po uruchomieniu nie kończy się, ale nie robi nic ;) Pozwala jednak na uruchomienie tylko jednej swojej kopii.
W przypadku próby uruchomienia kolejnej wersji, nowo-uruchamiana instancja powinna wyświetlić komunikat, że
proces jest już uruchomiony i się zakończyć.
Jeżeli w zmiennych systemowych znajduję się zmienna SO2=NEW, "stara" instacja (pracująca wcześniej) powinna zostać
zakończona, a pracuje tylko ta ostatnio uruchomiona.
Rozwiązanie możliwe jest na kilka sposobów, można wykorzystać tzw. blokadę plikową, semafor nazwany, gniazdo sieciowe itd.


Program 3B
Zachowanie programu jest takie jak w wersji IX/POSIX, z pominięciem opcji wywołanie "c", ale został napisany z
wykorzystaniem wyłącznie WinAPI (windows.h*).
*Wskazówka: *CreateMutex (…)* lub EnumProcesses(…) lub CreateEvent(…)

*/

#include <windows.h>
#include <fileapi.h>
#include <iostream>
#include <string>
#include <cstring>
#include <psapi.h>

using namespace std;

int main(int argc, char **argv, char **envp) {
    HANDLE mutex = CreateMutexA(NULL, TRUE, "PID");
    int flag = 0;

    if (mutex == NULL) {
        cout << "Nie udało się utworzyć mutex'a" << endl;
        return 0;
    }

    if (GetLastError() == ERROR_ALREADY_EXISTS)
    {
        for(char **env = envp; *env != 0; env++)
        {
            char *thisEnv = *env;
            if(strcmp(thisEnv, "SO2=NEW") == 0)
            {
                //cout << "Zabijam proces" << endl;
                char procesPIDToKill[15];
                int procesPIDToKillInt;

                HANDLE file = CreateFile(
                        "SO2.txt",
                        GENERIC_READ,
                        NULL,
                        NULL,
                        OPEN_EXISTING,
                        NULL,
                        NULL
                );

                if (file == NULL)
                {
                    cout << "Plik z PIDEM nie istanieje" << endl;
                    return 0;
                }

                DWORD tmp;
                ReadFile(
                        file,
                        &procesPIDToKill,
                        14,
                        &tmp,
                        NULL
                        );

                CloseHandle(file);

                procesPIDToKillInt = stoi(procesPIDToKill);

                cout << "PID in file = " << procesPIDToKillInt << "   "<< endl;

                // Get the list of process identifiers.

                DWORD aProcesses[1024], cbNeeded, cProcesses;
                unsigned int i;

                if ( !EnumProcesses( aProcesses, sizeof(aProcesses), &cbNeeded ) )
                {
                    return 1;
                }

                // Calculate how many process identifiers were returned.

                cProcesses = cbNeeded / sizeof(DWORD);

                // Print the name and process identifier for each process.

                for ( i = 0; i < cProcesses; i++ )
                {
                    if( aProcesses[i] == procesPIDToKillInt)
                    {
                        HANDLE hProcess = OpenProcess( PROCESS_TERMINATE |
                                                       FALSE,
                                                       FALSE,
                                                       procesPIDToKillInt
                                                       );
                        TerminateProcess(hProcess, 0);

                        WaitForSingleObject(mutex, INFINITE);

                        flag = 1;
                        break;
                    }
                }
            }
        }
        if(flag == 0)
        {
            cout << "Inny proces uruchomiony bark SO2=NEW" << endl;
            exit(1);
        }
    }


    DWORD dwProcessId = GetCurrentProcessId();
    char procID[15];
    sprintf(procID, "%d", dwProcessId);
    DWORD tmp;

    cout << "Create file with id = " << procID << endl;

    HANDLE file = CreateFile(
            "SO2.txt",
            GENERIC_WRITE,
            NULL,
            NULL,
            CREATE_ALWAYS,
            NULL,
            NULL
    );

    WriteFile(
            file,
            procID,
            strlen(procID),
            &tmp,
            NULL
            );

    CloseHandle(file);

    while(1)
    {

    }
    return 0;
}



/*

### Program 1B
##### Program po uruchomieniu nie kończy się, nie robi nic ;) Pozwala jednak na uruchomienie tylko
jednej swojej kopii. W przypadku próby uruchomienia kolejnej wersji, nowouruchamiana instancja powinna
wyświetlić komunikat, że jest już uruchomiony i się zakończyć.
Jeżeli w zmiennych systemowych znajduję się zmienna SO2=NEW, "stara" instacja (pracująca wcześniej)
powinna zostać zakończona, a pracuje tylko ta ostatnio uruchomiona.


#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char **argv, char **envp)
{
    const string PATH = "/var/run/lock/so2.txt";
    string number;
    fstream file;


    for(char **env = envp; *env != 0; env++)
    {
        char *thisEnv = *env;
        if(strcmp(thisEnv, "SO2=NEW") == 0)
        {
            //cout << "Zabijam proces" << endl;
            string procesPIDToKill;
            int procesPIDToKillInt;


            file.open(PATH, ios::in);
            file >> procesPIDToKill;
            procesPIDToKillInt = stoi(procesPIDToKill);
            file.close();

            if(kill(procesPIDToKillInt, SIGTERM) == 0)
            {
                file.open(PATH, ios::out);
                file << "";
                file.close();

                break;
            }
        }
    }

    file.open(PATH, ios::in);
    file >> number;
    file.close();

    //cout << "Text w pliku = " << number << endl;

    if(number.empty())
    {
        //cout << "Zapisuje PID = " << getpid() << endl;
        file.open(PATH, ios::out);
        file << (int)getpid();
        file.close();
    }
    else
    {
        cout << "Program jest juz uruchomiony" << endl;
        return 0;
    }

    //cout << "Program zostaje uruchomiony w nieskoncoznej petli" << endl;

    while(1)
    {

    }
}

 */