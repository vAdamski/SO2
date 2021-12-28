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

int main(int argc, char **argv, char **envp)
{
    while(1)
    {

    }
}