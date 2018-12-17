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

void selectionsort(int arr[], int len) {
    int low;
    for (int i = 0; i < len; i++) {
        low = i;
        for (int j = i + 1; j < len; j++)
            if (arr[j] < arr[low])
                low = j;
        std::swap(arr[i], arr[low]);
    }
}

void bubblesort(int arr[], int len) {
    bool didswap;
    for (int i = 0; i < len - 1; i++) {
        didswap = false;
        for (int j = 0; j < len - i - 1; j++) {
            if (arr[j] > arr[j+1]) {
                std::swap(arr[j], arr[j+1]);
                didswap = true;
            }
        }
        if (didswap == false)
            return;
    }
}

void insertionsort(int arr[], int len) {
    int x, j;
    for (int i = 1; i < len; i++) {
        x = arr[i];
        for (j = i - 1; arr[j] > x && j >= 0; j--)
            arr[j+1] = arr[j];
        arr[j+1] = x;
    }
}

void print_arr(int arr[], int n, std::string s) {
    std::cout << "\n" << s << " ";
    for (int i = 0; i < n; i++)
        std::cout << arr[i] << " ";
}

int main() {
    std::srand(time(NULL));

    int x, arr1[10], arr2[10], arr3[10], arr4[10], arr5[10], arr6[10], arr7[10], arr8[10];
    for (int i = 0; i < 10; i++) {
        x = rand() % 10; arr1[i] = x; arr2[i] = x; arr3[i] = x; arr4[i] = x; arr5[i] = x,
        arr6[i] = x, arr7[i] = x; arr8[i] = x;
    }

    quicksort_LEG(arr2, 0, 10);
    quicksort_SN(arr3, 0, 10);
    quicksort_PQ(arr4, 0, 10);
    mergesort(arr5, 10);
    selectionsort(arr6, 10);
    bubblesort(arr7, 10);
    insertionsort(arr8, 10);

    print_arr(arr1, 10, "Random array  :");
    print_arr(arr2, 10, "Quicksort LEG :");
    print_arr(arr3, 10, "Quicksort SN  :");
    print_arr(arr4, 10, "Quicksort PQ  :");
    print_arr(arr5, 10, "Merge Sort    :");
    print_arr(arr6, 10, "Selection Sort:");
    print_arr(arr7, 10, "Bubble Sort   :");
    print_arr(arr8, 10, "Insertion Sort:");

    return 0;
}
