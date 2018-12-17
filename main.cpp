#include <chrono>
#include <ctime>
#include <iostream>
#include <random>
#include <string>

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

void mergesort(int arr[], int start, int len) {
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

void selectionsort(int arr[], int start, int len) {
    int low;
    for (start = 0; start < len; start++) {
        low = start;
        for (int j = start + 1; j < len; j++)
            if (arr[j] < arr[low])
                low = j;
        std::swap(arr[start], arr[low]);
    }
}

void time_sort(void x(int[], int, int), std::string name, int arr[], int start, int fin) {
    auto t1 = std::chrono::high_resolution_clock::now();
    x(arr, start, fin);
    auto t2 = std::chrono::high_resolution_clock::now();
    auto q = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
    std::cout << name << ": " << q << " ms\n";
}

int main() {
    std::srand(time(NULL));

    int x, arr[10], arr2[10], arr3[10], arr4[10], arr5[10], arr6[10];
    for (int i = 0; i < 10; i++) {
        x = rand() % 10; arr[i] = x; arr2[i] = x; arr3[i] = x; arr4[i] = x; arr5[i] = x, arr6[i] = x;
    }

    quicksort_LEG(arr2, 0, 10);
    quicksort_SN(arr3, 0, 10);
    quicksort_PQ(arr4, 0, 10);
    mergesort(arr5, 0, 10);
    selectionsort(arr6, 0, 10);

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
    std::cout << "\nSelection sort: ";
    for (int i = 0; i < 10; i++)
        std::cout << arr6[i] << " ";

    int n1, n2, n3;
    std::cout << "\n\nNumber of integers to test (100,000 recommended): ";
    std::cin >> n1;
    std::cout << "Lower bound: ";
    std::cin >> n2;
    std::cout << "Upper bound: ";
    std::cin >> n3;

    int * b1 = new int[n1], * b2 = new int[n1], * b3 = new int[n1], * b4 = new int[n1],
    * b5 = new int[n1];
    for (int i = 0; i < n1; i++) {
        x = rand() % n3 + n2; b1[i] = x; b2[i] = x; b3[i] = x; b4[i] = x; b5[i] = x;
    }

    time_sort(quicksort_LEG, "Quicksort LEG", b1, 0, n1);
    time_sort(mergesort, "Mergesort", b2, 0, n1);
    time_sort(quicksort_PQ, "Quicksort PQ", b3, 0, n1);
    time_sort(quicksort_SN, "Quicksort SN", b4, 0, n1);
    time_sort(selectionsort, "Selection Sort", b5, 0, n1);

    return 0;
}
