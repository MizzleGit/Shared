#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

// Insertion sort
void insertionSort(long int arr[], long int n)
{
    long int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;

        // Move elements of arr[0..i-1], that are
        // greater than key, to one position ahead
        // of their current position
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

        // Find the minimum element in unsorted array
        midx = i;

        for (j = i + 1; j < n; j++)
            if (arr[j] < arr[midx])
                midx = j;

        // Swap the found minimum element
        // with the first element
        swap(&arr[midx], &arr[i]);
    }
}

void merge(long int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temp arrays
    int L[n1], R[n2];

    // Copy data to temp arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Merge the temp arrays back into arr[l..r
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[],
    // if there are any
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[],
    // if there are any
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// l is for left index and r is right index of the
// sub-array of arr to be sorted
void mergeSort(long int arr[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

// Partition function
int partition(long int arr[], int low, int high)
{

    // Choose the pivot
    int pivot = arr[high];

    // Index of smaller element and indicates
    // the right position of pivot found so far
    int i = low - 1;

    // Traverse arr[low..high] and move all smaller
    // elements to the left side. Elements from low to
    // i are smaller after every iteration
    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    // Move pivot after smaller elements and
    // return its position
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

// The QuickSort function implementation
void quickSort(long int arr[], int low, int high)
{
    if (low < high)
    {

        // pi is the partition return index of pivot
        int pi = partition(arr, low, high);

        // Recursion calls for smaller elements
        // and greater or equals elements
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void countSort(long int inputArray[], int N)
{

    // Finding the maximum element of
    // array inputArray[]
    int M = 0;
    for (int i = 0; i < N; i++)
        if (inputArray[i] > M)
            M = inputArray[i];

    // Initializing countArray[] with 0
    int *countArray = (int *)calloc(M + 1, sizeof(int));

    // Mapping each element of inputArray[]
    // as an index of countArray[] array
    for (int i = 0; i < N; i++)
        countArray[inputArray[i]]++;

    // Calculating prefix sum at every index
    // of array countArray[]
    for (int i = 1; i <= M; i++)
        countArray[i] += countArray[i - 1];

    // Creating outputArray[] from countArray[] array
    int *outputArray = (int *)malloc(N * sizeof(int));
    for (int i = N - 1; i >= 0; i--)
    {
        outputArray[countArray[inputArray[i]] - 1] = inputArray[i];
        countArray[inputArray[i]]--;
    }

    // Copying sorted elements back to inputArray[]
    for (int i = 0; i < N; i++)
        inputArray[i] = outputArray[i];

    // Freeing dynamically allocated memory
    free(countArray);
    free(outputArray);
}

// Driver code
int main()
{
    long int n = 10000;
    int it = 0;

    // Arrays to store time duration
    // of sorting algorithms
    double tim1[10], tim2[10], tim3[10], tim4[10], tim5[10], tim6[10];

    printf("A_size, Bubble, Insertion, Selection, Merge, Quick, Counting\n");

    // Performs 10 iterations
    while (it++ < 10)
    {
        long int a[n], b[n], c[n], d[n], e[n], f[n];

        // generating n random numbers
        // storing them in arrays a, b, c
        for (int i = 0; i < n; i++)
        {
            long int no = rand() % n + 1;
            a[i] = no;
            b[i] = no;
            c[i] = no;
            d[i] = no;
            e[i] = no;
            f[i] = no;
        }

        // using clock_t to store time
        clock_t start, end;

        // Bubble sort
        start = clock();
        bubbleSort(a, n);
        end = clock();

        tim1[it] = ((double)(end - start));

        // Insertion sort
        start = clock();
        insertionSort(b, n);
        end = clock();

        tim2[it] = ((double)(end - start));

        // Selection sort
        start = clock();
        selectionSort(c, n);
        end = clock();

        tim3[it] = ((double)(end - start));

        // Merge sort
        start = clock();
        mergeSort(d, 0, n - 1);
        end = clock();

        tim4[it] = ((double)(end - start));

        // Quick sort
        start = clock();
        quickSort(e, 0, n - 1);
        end = clock();

        tim5[it] = ((double)(end - start));

        // Counting sort
        start = clock();
        countSort(f, n);
        end = clock();

        tim6[it] = ((double)(end - start));
        // type conversion to long int
        // for plotting graph with integer values
        printf("%li, %li, %li, %li, %li, %li, %li\n",
               n,
               (long int)tim1[it],
               (long int)tim2[it],
               (long int)tim3[it],
               (long int)tim4[it],
               (long int)tim5[it],
               (long int)tim6[it]);

        // increases the size of array by 10000
        n += 10000;
    }

    return 0;
}
