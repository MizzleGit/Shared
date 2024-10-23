#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// Swap utility
void swap(long int *a, long int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// Bubble sort
void bubbleSort(long int a[], long int n)
{
    for (long int i = 0; i < n - 1; i++)
    {
        for (long int j = 0; j < n - 1 - i; j++)
        {
            if (a[j] > a[j + 1])
            {
                swap(&a[j], &a[j + 1]);
            }
        }
    }
}

// Insertion Sort
void insertionSort(long int arr[], long int n)
{
    long int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// Selection sort
void selectionSort(long int arr[], long int n)
{
    long int i, j, midx;
    for (i = 0; i < n - 1; i++)
    {
        midx = i;
        for (j = i + 1; j < n; j++)
            if (arr[j] < arr[midx])
                midx = j;
        swap(&arr[midx], &arr[i]);
    }
}

void merge(long int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1, n2 = r - m;
    int L[n1], R[n2];
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    i = 0; j = 0; k = l;
    while (i < n1 && j < n2){
        if (L[i] <= R[j]){
            arr[k] = L[i]; i++;
        }
        else{
            arr[k] = R[j]; j++;
        } k++;
    }
    while (i < n1){
        arr[k] = L[i];
        i++; k++;
    }
    while (j < n2){
        arr[k] = R[j];
        j++; k++;
    }
}

// Merge sort
void mergeSort(long int arr[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}


int partition(long int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

// Quick sort
void quickSort(long int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Counting sort
void countSort(long int inputArray[], int N)
{
    int M = 0;
    for (int i = 0; i < N; i++)
        if (inputArray[i] > M)
            M = inputArray[i];
    int *countArray = (int *)calloc(M + 1, sizeof(int));
    for (int i = 0; i < N; i++)
        countArray[inputArray[i]]++;
    for (int i = 1; i <= M; i++)
        countArray[i] += countArray[i - 1];
    int *outputArray = (int *)malloc(N * sizeof(int));
    for (int i = N - 1; i >= 0; i--)
    {
        outputArray[countArray[inputArray[i]] - 1] = inputArray[i];
        countArray[inputArray[i]]--;
    }

    for (int i = 0; i < N; i++)
        inputArray[i] = outputArray[i];
    free(countArray);
    free(outputArray);
}

int main(){
    FILE *fichierOutput = fopen("sort.txt", "w");
    if (fichierOutput == NULL) return -1;
    long int n = 10000; int it = 0;
    double tim1[10], tim2[10], tim3[10], tim4[10], tim5[10], tim6[10];
    fprintf(fichierOutput,"Taille de tableau, Bubble, Insertion, Selection, Merge, Quick, Counting\n");
    printf("Taille de tableau, Bubble, Insertion, Selection, Merge, Quick, Counting\n");
    while (it++ < 10){
        long int a[n], b[n], c[n], d[n], e[n], f[n];
        for (int i = 0; i < n; i++){ long int no = rand() % n + 1; a[i] = no; b[i] = no; c[i] = no; d[i] = no; e[i] = no; f[i] = no;}
        clock_t start, end;
        start = clock(); bubbleSort(a, n); end = clock();
        tim1[it] = ((double)(end - start) / CLOCKS_PER_SEC) * 1000000;
        start = clock(); insertionSort(b, n); end = clock();
        tim2[it] = ((double)(end - start) / CLOCKS_PER_SEC) * 1000000;
        start = clock(); selectionSort(c, n); end = clock();
        tim3[it] = ((double)(end - start) / CLOCKS_PER_SEC) * 1000000;
        start = clock(); mergeSort(d, 0, n - 1); end = clock();
        tim4[it] = ((double)(end - start) / CLOCKS_PER_SEC) * 1000000;
        start = clock(); quickSort(e, 0, n - 1); end = clock();
        tim5[it] = ((double)(end - start) / CLOCKS_PER_SEC) * 1000000;
        start = clock(); countSort(f, n); end = clock();
        tim6[it] = ((double)(end - start) / CLOCKS_PER_SEC) * 1000000;
        fprintf(fichierOutput, "%li, %li, %li, %li, %li, %li, %li\n",
               n,
               (long int)tim1[it], (long int)tim2[it], (long int)tim3[it], (long int)tim4[it], (long int)tim5[it], (long int)tim6[it]);
        printf("%li, %li, %li, %li, %li, %li, %li\n",
               n,
               (long int)tim1[it], (long int)tim2[it], (long int)tim3[it], (long int)tim4[it], (long int)tim5[it], (long int)tim6[it]);
        n += 10000;
    }
    fclose(fichierOutput);
    int choix;
    printf("\n\nType de graphe: [1] Pour normale, [2] Pour temps logarithmique, [3] Pour les deux:  ");
    scanf("%d", &choix);
    printf("\nAttendez 3 secondes...");
    sleep(3);
    if (choix == 1){
        system("gnuplot -p -e \"set title \\\"Performance d\'algorithmes de tri\\\"; set xlabel \'Taille de tableau\'; set ylabel \'Temps en microseconds\'; set grid; set key outside; set xtics rotate by -90; plot \'sort.txt\' using 1:2 with lines title \'A bulles\', \'sort.txt\' using 1:3 with lines title \'Insertion\', \'sort.txt\' using 1:4 with lines title \'Selection\', \'sort.txt\' using 1:5 with lines title \'Fusion\', \'sort.txt\' using 1:6 with lines title \'Rapide\', \'sort.txt\' using 1:7 with lines title \'Denombrement\'\"");
    }
    else if (choix == 2){
        system("gnuplot -p -e \"set title \\\"Performance d\'algorithmes de tri\\\"; set xlabel \'Taille de tableau\'; set ylabel \'Temps en microseconds\'; set grid; set key outside; set logscale y; set xtics rotate by -90; plot \'sort.txt\' using 1:2 with lines title \'A bulles\', \'sort.txt\' using 1:3 with lines title \'Insertion\', \'sort.txt\' using 1:4 with lines title \'Selection\', \'sort.txt\' using 1:5 with lines title \'Fusion\', \'sort.txt\' using 1:6 with lines title \'Rapide\', \'sort.txt\' using 1:7 with lines title \'Denombrement\'\"");
    }
    else{
        system("gnuplot -p -e \"set title \\\"Performance d\'algorithmes de tri\\\"; set xlabel \'Taille de tableau\'; set ylabel \'Temps en microseconds\'; set grid; set key outside; set xtics rotate by -90; plot \'sort.txt\' using 1:2 with lines title \'A bulles\', \'sort.txt\' using 1:3 with lines title \'Insertion\', \'sort.txt\' using 1:4 with lines title \'Selection\', \'sort.txt\' using 1:5 with lines title \'Fusion\', \'sort.txt\' using 1:6 with lines title \'Rapide\', \'sort.txt\' using 1:7 with lines title \'Denombrement\'\"");
        system("gnuplot -p -e \"set title \\\"Performance d\'algorithmes de tri\\\"; set xlabel \'Taille de tableau\'; set ylabel \'Temps en microseconds\'; set grid; set key outside; set logscale y; set xtics rotate by -90; plot \'sort.txt\' using 1:2 with lines title \'A bulles\', \'sort.txt\' using 1:3 with lines title \'Insertion\', \'sort.txt\' using 1:4 with lines title \'Selection\', \'sort.txt\' using 1:5 with lines title \'Fusion\', \'sort.txt\' using 1:6 with lines title \'Rapide\', \'sort.txt\' using 1:7 with lines title \'Denombrement\'\"");
    }
    return 0;
}


