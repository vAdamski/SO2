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
*/

#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

using namespace std;

void* threadFunc(void *arg)
{
    int *idThread = arg;

    cout << "Thread number " << idThread << "is running" << endl;
    sleep(1);

    return;
}

int main(int argc, char **argv, char **envp)
{
    int countOfThreads = stoi(argv[1]);

    if (argc != 3 || countOfThreads <= 0)
    {
        cout << "Bad input data" << endl;
    }

    if (strcmp(argv[2], "inc") == 0)
    {
        cout << "INC" << endl;
    }
    else if (strcmp(argv[2], "dec") == 0)
    {
        cout << "DEC" << endl;
    }
    else
    {
        cout << "Bad input data" << endl;
    }

    int queue[countOfThreads];

    //Initialize queue
    for (int i = 0; i < countOfThreads - 1; i++)
    {
        queue[i] = i;
    }

    //Show queue
    cout << "--==QUEUE==--" << endl;
    for (int i = 0; i < countOfThreads - 1; i++)
    {
        cout << i << "." << queue[i] << endl;
    }

    for (int i = 0; i < countOfThreads - 1; i++)
    {
        cout << "Run thread number: " << i << endl;

        pthread_t IdThread;

        int error;

        error = pthread_create(&IdThread, NULL, threadFunc, &i);
        error = pthread_join(IdThread, NULL);

        cout << "Run thread number " << i << "has been end." << endl;
    }

    return 0;
}