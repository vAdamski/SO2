/*
### Program 1A
###### Program po wywołaniu bez argumentów kończy się, wyświetlając jedynie komunikat, że został 
wywołany bez argumentów.
W przypadku wywołania z liczbą argumentów większą niż 1, tworzy taką liczbę procesów potomnych, 
ile było argumentów, a każdy z procesów wyświetla na ekranie jeden argument.
##### *Gdy pierwszym argumentem jest "c", wykorzystana zostanie funkcja *clone(...)*, 
jeżeli jest to inny znak, używany jest *fork()*.
 
Cel: zapoznanie się z funkcjami tworzącymi procesy, pojęcie PID, funkcja getpid(), 
wykorzystanie argumentów wywołania przekazywanych funkcji *main(...)*, odczyt zmiennych środowiskowych.
 
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

int cloneFunc(void *args)
{
    std::cout << "Clone: " <<(char*)args << std::endl;
    return 0;
}
 
int main(int argc, char **argv, char **envp)
{
    if(argc <= 1)
    {
        printf("Program zakonczyl sie bez argumentow.\n");
        return 0;
    }

    if(strcmp(argv[1], "c") == 0)
    {
        void* space = malloc(1024);

        for(int i = 2; i < argc; i++)
        {
            pid_t pid = clone(cloneFunc, space, CLONE_PARENT | SIGCHLD, (void*)argv[i]);
            //printf("Clone pid: %d\n", pid);
        }
        
        return 0;
    }
    else
    {
        for (int i = 1; i < argc; i++)
        {
            pid_t id = fork();
            if(id == 0)
            {
                printf("Fork: %s\n", argv[i]);
                return 0;
            }
        }
    }

    return 0;
}