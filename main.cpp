#include <chrono>
#include <ctime>
#include <iostream>
#include <random>

/*
|  <  | = |  >  |  unexplored  |
      L   E     G
*/
void quicksort_LEG(int arr[], int start, int fin) {
    if (start >= fin)
        return;
    int L = start, E = start+1, G = start+1, pivot = (start+fin)/2;
    std::swap(arr[L], arr[pivot]);
    while (G < fin) {
        if (arr[G] > arr[L])
            G++;
        else if (arr[G] == arr[L]) {
            std::swap(arr[G], arr[E]);
            G++; E++;
        } else {
            std::swap(arr[L], arr[G]);
            std::swap(arr[G], arr[E]);
            G++; E++; L++;
        }
    }

    quicksort_LEG(arr, start, L);
    quicksort_LEG(arr, E, fin);
}

/*
|  <  |  >=  |  unexplored  |p|
      S      N
*/
void quicksort_SN(int arr[], int start, int fin) {
    if (start >= fin - 1)
        return;
    int S = start, N = start, pivot = (start+fin)/2;
    std::swap(arr[pivot], arr[fin-1]);
    while (N < fin - 1) {
        if (arr[N] >= arr[fin-1])
            N++;
        else {
            std::swap(arr[S], arr[N]);
            S++; N++;
        }
    }
    std::swap(arr[S], arr[fin-1]);
    quicksort_SN(arr, start, S);
    quicksort_SN(arr, S+1, fin);
}

/*
|  <=  |  unexplored  |  >=  |p|
       P              Q
*/
void quicksort_PQ(int arr[], int start, int fin) {
    if (start >= fin)
        return;
    int pivot = (start+fin)/2, P = start, Q = fin - 1;
    std::swap(arr[pivot], arr[fin-1]);
    while (P < Q) {
        while (arr[P] <= arr[fin-1] && P < Q)
            P++;
        while (arr[Q] >= arr[fin-1] && P < Q)
            Q--;
        std::swap(arr[P], arr[Q]);
    }
    std::swap(arr[P], arr[fin-1]);
    quicksort_PQ(arr, start, P);
    quicksort_PQ(arr, P+1, fin);
}

void mergesort(int arr[], int len) {
    for (int chunksize = 1; chunksize < len; chunksize *= 2) {
        for (int astart = 0; true; astart += 2*chunksize) {
            int aend = astart + chunksize - 1, bstart = aend + 1, bend = bstart + chunksize - 1;
            if (bstart >= len)
                break;
            if (bend >= len)
                bend = len - 1;

            int p = astart, q = bstart, index = 0, sz = bend - astart + 1, * sorted = new int[sz];
            while (index < sz) {
                if (p > aend) {
                    sorted[index] = arr[q];
                    q++;
                } else if (q > bend) {
                    sorted[index] = arr[p];
                    p++;
                } else {
                    if (arr[p] <= arr[q]) {
                        sorted[index] = arr[p];
                        p++;
                    } else {
                        sorted[index] = arr[q];
                        q++;
                    }
                }
                index++;
            }
            for (int i = 0; i < index; i++)
                arr[astart+i] = sorted[i];
            delete[] sorted;
        }
    }
}

int main() {
    std::srand(time(NULL));

    int arr[10], arr2[10], arr3[10], arr4[10], arr5[10];
    for (int i = 0; i < 10; i++) {
        arr[i] = rand() % 10;
        arr2[i] = arr[i];
        arr3[i] = arr[i];
        arr4[i] = arr[i];
        arr5[i] = arr[i];
    }

    quicksort_LEG(arr2, 0, 10);
    quicksort_SN(arr3, 0, 10);
    quicksort_PQ(arr4, 0, 10);
    mergesort(arr5, 10);

    std::cout << "*** Verification that each of the methods works ***\n";
    std::cout << "Random array  : ";
    for (int i = 0; i < 10; i++)
        std::cout << arr[i] << " ";
    std::cout << "\nQuicksort LEG : ";
    for (int i = 0; i < 10; i++)
        std::cout << arr2[i] << " ";
    std::cout << "\nQuicksort SN  : ";
    for (int i = 0; i < 10; i++)
        std::cout << arr3[i] << " ";
    std::cout << "\nQuicksort PQ  : ";
    for (int i = 0; i < 10; i++)
        std::cout << arr4[i] << " ";
    std::cout << "\nMergesort     : ";
    for (int i = 0; i < 10; i++)
        std::cout << arr5[i] << " ";

    std::cout << "\n\n*** Timing ***\n";
    int b1[100000], b2[100000], b3[100000], b4[100000];
    for (int i = 0; i < 100000; i++) {
        b1[i] = rand() % 100;
        b2[i] = b1[i];
        b3[i] = b1[i];
        b4[i] = b1[i];
    }

    auto t1 = std::chrono::high_resolution_clock::now();
    quicksort_LEG(b1, 0, 100000);
    auto t2 = std::chrono::high_resolution_clock::now();
    auto q = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
    std::cout << "Quicksort LEG: " << q << " ms\n";

    t1 = std::chrono::high_resolution_clock::now();
    quicksort_SN(b2, 0, 100000);
    t2 = std::chrono::high_resolution_clock::now();
    q = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
    std::cout << "Quicksort SN: " << q << " ms\n";

    t1 = std::chrono::high_resolution_clock::now();
    quicksort_PQ(b3, 0, 100000);
    t2 = std::chrono::high_resolution_clock::now();
    q = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
    std::cout << "Quicksort PQ: " << q << " ms\n";

    t1 = std::chrono::high_resolution_clock::now();
    mergesort(b4, 100000);
    t2 = std::chrono::high_resolution_clock::now();
    q = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
    std::cout << "Mergesort: " << q << " ms\n";

    return 0;
}
