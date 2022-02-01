/*
Bazując na dostarczonym kodzie (L2.zip), zawierającym program tworzący osobne wątki z wykorzystaniem biblioteki
pthreads, zrealizuj program, który tworzy N (w zakresie 3…100) osobnych wątków, które powinny zakończyć się w
określonej kolejności, zależnie od argumentów podanych przy wywołaniu.
program N direction
gdzie N to liczba wątków, a direction może oznaczać rosnącą lub malejącą kolejność ich zakończenia
Przykładowe wywołanie i opis działania:
a.exe 10 inc
Tworzonych jest 10 wątków, kończą się w kolejności rosnącego ID.
a.exe 3 dec
Tworzone są 3 wątki, kończą się w kolejności malejącego ID.
a.exe 1
Program wyświetla komunikat o nieprawidłowo podanych argumentach.
Wątki przy uruchamianiu powinny otrzymać ID oznaczające kolejność ich startu, następnie przez pewien czas pracują
współbieżnie i kończą się w określonej kolejności, np. kolejność rosnąca oznacza, że powinien najpierw zakończyć się
wątek nr 1, oczekuje na to wątek nr 2, po którego zakończeniu kończy się wątek nr 3, itd
Pamiętaj, że dostarczony kod może zawierać błędy, uważnie go przeanalizuj i uporządkuj. Rozważ zastosowanie jednego z
mechanizmów/algorytmu poznanych na wykładzie, np. algorytmu Lamporata czy odpowiednio skonfigurowanego semafora…

To samo ale na WinAPI
*/

#include <windows.h>
#include <strsafe.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

DWORD WINAPI MyThreadFunction( LPVOID lpParam );

_Atomic int globalId;
int flag; //0 -> inc / 1 -> dec
HANDLE ghMutex;

struct threadInfo
{
    DWORD ThreadId;
    int numerek;
};

int main(int argc, char **argv, char **envp)
{
    long countOfThreads;

    if (argc != 3)
    {
        printf("Bad input data");
        exit(0);
    }

    countOfThreads = strtol(argv[1], NULL, 10);

    if(countOfThreads  <= 0)
    {
        printf("Bad input data");
        exit(0);
    }

    if (strcmp(argv[2], "inc") == 0)
    {
        globalId = 0;
        flag = 0;
    }
    else if (strcmp(argv[2], "dec") == 0)
    {
        globalId = countOfThreads - 1;
        flag = 1;
    }
    else
    {
        printf("Bad input data");
        exit(0);
    }

    struct threadInfo *threadInf = malloc(sizeof(struct threadInfo) * countOfThreads);
    HANDLE  *hThreadArray = malloc(sizeof(HANDLE) * countOfThreads);
    ghMutex = CreateMutex(
            NULL,              // default security attributes
            FALSE,             // initially not owned
            NULL);

    //Initialize queue
    for (int i = 0; i < countOfThreads; i++)
    {
        (threadInf + i)->numerek = i;

        *(hThreadArray + i) = CreateThread(
                NULL,
                0,
                MyThreadFunction,
                &threadInf[i],
                0,
                &(threadInf+i)->ThreadId
        );
    }

    for (int i = 0; i < countOfThreads; i++)
    {
        WaitForSingleObject(hThreadArray+i, INFINITE);
        Sleep(100);
    }

    for (int i = 0; i < countOfThreads; i++)
    {
        CloseHandle(hThreadArray+i);
    }

    free(threadInf);
    CloseHandle(ghMutex);
}

DWORD WINAPI MyThreadFunction( LPVOID arg )
{
    DWORD dwWaitResult;
    struct threadInfo *threadInf = arg;

    //START CS
    dwWaitResult = WaitForSingleObject(
            ghMutex,
            INFINITE);

    printf("Wykonuje sie watek = %d\n", (int)threadInf->numerek);

    ReleaseMutex(ghMutex);
    //END CS

    while(threadInf->numerek != globalId)
    {
        Sleep(100);
    }

    printf("Zakonczyl sie watek nr = %d\n", (int)threadInf->numerek);

    if (flag == 0)
    {
        globalId++;
    }
    else if (flag == 1)
    {
        globalId--;
    }

    Sleep(1000);
}



/*
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdatomic.h>
#include <stdio.h>

_Atomic int globalId;
int flag; //0 -> inc / 1 -> dec
pthread_mutex_t mutex;

struct threadInfo
{
    pthread_t ThreadId;
    int numerek;
};

void* threadFunc(void *arg)
{
    struct threadInfo *threadInf = arg;

    //START CS
    pthread_mutex_lock(&mutex);

    printf("Wykonuje sie watek = %d\n", threadInf->numerek);

    pthread_mutex_unlock(&mutex);
    //END CS

    while(threadInf->numerek != globalId)
    {
        //Waitng
    }

    printf("Zakonczyl sie watek nr = %d\n", threadInf->numerek);

    if (flag == 0)
    {
        globalId++;
    }
    else if (flag == 1)
    {
        globalId--;
    }

    sleep(1);

    return NULL;
}

int main(int argc, char **argv, char **envp)
{
    long countOfThreads = strtol(argv[1], NULL, 10);

    if (argc != 3 || countOfThreads <= 0)
    {
        // cout << "Bad input data" << endl;
    }

    if (strcmp(argv[2], "inc") == 0)
    {
        globalId = 0;
        flag = 0;
    }
    else if (strcmp(argv[2], "dec") == 0)
    {
        globalId = countOfThreads - 1;
        flag = 1;
    }
    else
    {
        // cout << "Bad input data" << endl;
    }

    struct threadInfo *threadInf = malloc(sizeof(struct threadInfo) * countOfThreads);
    pthread_mutex_init(&mutex, NULL);

    //Initialize queue
    for (int i = 0; i < countOfThreads; i++)
    {
        pthread_t IdThread;
        int error;

        (threadInf + i)->numerek = i;

        error = pthread_create(&threadInf->ThreadId, NULL, threadFunch, &treadInf[i]);
    }

    for (int i = 0; i < countOfThreads; i++)
    {
        pthread_join(threadInf[i].ThreadId, NULL);
    }


    return 0;
}
 */