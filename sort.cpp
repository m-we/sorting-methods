#include <ctime>
#include <iostream>
#include <random>
#include <string>

/*
Time: n log n
Partition: | < | = | > | unexplored |
               L   E   G
Other: Fastest partition method when dealing w/ lots of repeat values,
       e.g. 100,000 integers between 0 and 100.
*/
void quicksort_leg(int arr[], int start, int fin) {
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

    quicksort_leg(arr, start, L);
    quicksort_leg(arr, E, fin);
}

/*
Time: n log n
Partition: | < | >= | unexplored |p|
               S    N
*/
void quicksort_sn(int arr[], int start, int fin) {
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
    quicksort_sn(arr, start, S);
    quicksort_sn(arr, S+1, fin);
}

/*
Time: n log n
Partition: | <= | unexplored | >= |p|
                P            Q
*/
void quicksort_pq(int arr[], int start, int fin) {
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
    quicksort_pq(arr, start, P);
    quicksort_pq(arr, P+1, fin);
}

/*
Time: n log n
*/
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

/*
Time: n^2
*/
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

/*
Time: n^2
*/
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

/*
Time: n^2
*/
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

    int x, arr[8][10];
    for (int i = 0; i < 10; i++) {
        x = rand() % 10;
        for (int j = 0; j < 10; j++) {
            arr[j][i] = x;
        }
    }

    quicksort_leg(arr[1], 0, 10);
    quicksort_sn(arr[2], 0, 10);
    quicksort_pq(arr[3], 0, 10);
    mergesort(arr[4], 10);
    selectionsort(arr[5], 10);
    bubblesort(arr[6], 10);
    insertionsort(arr[7], 10);

    print_arr(arr[0], 10, "Random array  :");
    print_arr(arr[1], 10, "Quicksort LEG :");
    print_arr(arr[2], 10, "Quicksort SN  :");
    print_arr(arr[3], 10, "Quicksort PQ  :");
    print_arr(arr[4], 10, "Merge Sort    :");
    print_arr(arr[5], 10, "Selection Sort:");
    print_arr(arr[6], 10, "Bubble Sort   :");
    print_arr(arr[7], 10, "Insertion Sort:");

    return 0;
}
