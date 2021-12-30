/*
### Program 1B
##### Program po uruchomieniu nie kończy się, nie robi nic ;) Pozwala jednak na uruchomienie tylko
jednej swojej kopii. W przypadku próby uruchomienia kolejnej wersji, nowouruchamiana instancja powinna 
wyświetlić komunikat, że jest już uruchomiony i się zakończyć. 
Jeżeli w zmiennych systemowych znajduję się zmienna SO2=NEW, "stara" instacja (pracująca wcześniej) 
powinna zostać zakończona, a pracuje tylko ta ostatnio uruchomiona.
*/

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
