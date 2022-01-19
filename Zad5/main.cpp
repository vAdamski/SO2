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