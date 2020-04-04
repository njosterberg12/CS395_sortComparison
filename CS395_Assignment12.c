/****************************************************************************************************************
 * Id: oste1799
 * Purpose:
 *  This program compares sort times of Selection Sort, Instertion Sort, and QuickSort.
 * Input:
 *  ./assignment12
 * Output:
 *  time of each sort for 100, 1000, and 10000 elements
 * Compile:
 *  ex. gcc -Wall -o assignment12 assignment12.c
 ****************************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
void printTimes(int *, int *, int *);
void selectionSort(int *, int);
int hoarePartition(int *, int, int);
void quickSort(int *, int, int);
void insertionSort(int *, int);
int main(int argc, char *argv[]){
   int i;
   int x = 1000;
   int y = 10000;
   int z = 100000;
   int shortArray[x];
   int midArray[y];
   int longArray[z];
   srand(time(NULL));
   for(i = 0; i < x; i++)
   {
      shortArray[i] = rand();
   }
   for(i = 0; i < y; i++)
   {
      midArray[i] = rand();
   }
   for(i = 0; i < z; i++)
   {
      longArray[i] = rand();
   }
   printTimes(shortArray, midArray, longArray);
   return 0;
}
// this function does a selection sort to organize the array
void selectionSort(int *arr, int size){
   int i, j;
   int temp;
   for(i = 0; i < size-1; i++)
   {
      int minVal = i; // min val set equal to first array val
      arr[minVal] = arr[i];
      for(j = i+1; j < size; j++)
      {
         if(arr[j] < arr[minVal]) // compares minval to next element which is at the jth position
         {
            minVal = j; // if arr[j] is less than arr[minVal], minVal is set to j value
         }
      }
      temp = arr[i]; // temp variable set to hold current array val at position i so swap can happen
      arr[i] = arr[minVal]; // arr[i] is set to arr[minVal]
      arr[minVal] = temp; // minVal becomes the saved temp Val
   }
}
// this function does a Hoare Partition of array values
int hoarePartition(int *arr, int low, int high){
   int temp;
   int pivot = arr[low]; // pivot is shifted to the right as the values below low val are ordered.
   int i = low;
   int j = high + 1;
   do
   {
      do
      {
         i++;
      }while(arr[i] < pivot);
      do
      {
         j--;
      }while(arr[j] > pivot);
      temp = arr[i]; // temp value to hold the i value about to be swapped
      arr[i] = arr[j]; // swap of the i and j vals
      arr[j] = temp; // j returned to i value
   }while(i < j);
   // swap i, j
   temp = arr[i];
   arr[i] = arr[j];
   arr[j] = temp;
   // swap low, j
   temp = arr[low];
   arr[low] = arr[j];
   arr[j] = temp;
   return (j);
}
// this function uses the Hoare algorihtm to do a quicksort of the array
void quickSort(int *arr, int low, int high){
   int s; // split position
   if(high > low)
   {
      s = hoarePartition(arr, low, high);
      quickSort(arr, low, s - 1);
      quickSort(arr, s + 1, high);
   }
}
// this function does an insertion sort
void insertionSort(int *arr, int vals){
   int i;
   int v;
   int j;
   int sortCount = 0;
   for(i = 0; i < vals; i++)
   {
      v = arr[i];
      j = i - 1;
      while(j >= 0 && arr[j] > v)
      {
         arr[j+1] = arr[j];
         j = j-1;
      }
      arr[j+1] = v;
      sortCount++;
   }
}
// this function runs the algorithms and prints the times for each sort
void printTimes(int *shortArr, int *midArr, int *longArr){
   struct timeval start, stop;
   int i;
   int x = 1000;
   int y = 10000;
   int z = 100000;
   // shortArray duplicates to preserve original data
   int shortSelDup[x];
   int midSelDup[y];
   int longSelDup[z];
   // midArray duplicates to preserve original data
   int shortInsDup[x];
   int midInsDup[y];
   int longInsDup[z];
   // longArray duplicates to preserve orig data
   int shortQuickDup[x];
   int midQuickDup[y];
   int longQuickDup[z];
   for(i = 0; i < x; i++)
   {
      shortSelDup[i] = shortArr[i];
      shortInsDup[i] = shortArr[i];
      shortQuickDup[i] = shortArr[i];
   }
   for(i = 0; i < y; i++)
   {
      midSelDup[i] = midArr[i];
      midInsDup[i] = midArr[i];
      midQuickDup[i] = midArr[i];
   }
   for(i = 0; i < z; i++)
   {
      longSelDup[i] = longArr[i];
      longInsDup[i] = longArr[i];
      longQuickDup[i] = longArr[i];
   }
   // shortIns clock
   gettimeofday(&start, NULL);
   insertionSort(shortInsDup, x);
   gettimeofday(&stop, NULL);
   int timeInsShort = (double)(stop.tv_sec - start.tv_sec) * 1000 + (double)(stop.tv_usec - start.tv_usec) / 1000;
   // midIns clock
   gettimeofday(&start, NULL);
   insertionSort(midInsDup, y);
   gettimeofday(&stop, NULL);
   int timeInsMid = (double)(stop.tv_sec - start.tv_sec) * 1000 + (double)(stop.tv_usec - start.tv_usec) / 1000;
   // longIns clock
   gettimeofday(&start, NULL);
   insertionSort(longInsDup, z);
   gettimeofday(&stop, NULL);
   int timeInsLong = (double)(stop.tv_sec - start.tv_sec) * 1000 + (double)(stop.tv_usec - start.tv_usec) / 1000;
   // shortSel clock
   gettimeofday(&start, NULL);
   selectionSort(shortSelDup, x);
   gettimeofday(&stop, NULL);
   int timeSelShort = (double)(stop.tv_sec - start.tv_sec) * 1000 + (double)(stop.tv_usec - start.tv_usec) / 1000;
   // midSel clock
   gettimeofday(&start, NULL);
   selectionSort(midSelDup, y);
   gettimeofday(&stop, NULL);
   int timeSelMid = (double)(stop.tv_sec - start.tv_sec) * 1000 + (double)(stop.tv_usec - start.tv_usec) / 1000;
   // longSel clock
   gettimeofday(&start, NULL);
   selectionSort(longSelDup, z);
   gettimeofday(&stop, NULL);
   int timeSelLong = (double)(stop.tv_sec - start.tv_sec) * 1000 + (double)(stop.tv_usec - start.tv_usec) / 1000;
   // shortQuick clock
   gettimeofday(&start, NULL);
   quickSort(shortQuickDup, 0, x-1);
   gettimeofday(&stop, NULL);
   int timeQuickShort = (double)(stop.tv_sec - start.tv_sec) * 1000 + (double)(stop.tv_usec - start.tv_usec) / 1000;
   // midQuick clock
   gettimeofday(&start, NULL);
   quickSort(midQuickDup, 0, y-1);
   gettimeofday(&stop, NULL);
   int timeQuickMid = (double)(stop.tv_sec - start.tv_sec) * 1000 + (double)(stop.tv_usec - start.tv_usec) / 1000;
   // longQuick clock
   gettimeofday(&start, NULL);
   quickSort(longQuickDup, 0, z-1);
   gettimeofday(&stop, NULL);
   int timeQuickLong = (double)(stop.tv_sec - start.tv_sec) * 1000 + (double)(stop.tv_usec - start.tv_usec) / 1000;
   // print speed output
   printf("//+-----------------------+-----------------+----------------+------------+\n");
   printf("//|    Number of Elements |  Selection Sort | Insertion sort |  Quicksort |\n");
   printf("//+-----------------------+-----------------+----------------+------------+\n");
   printf("//|                   1000|              %i +             %i +         %i +\n", timeSelShort, timeInsShort, timeQuickShort);
   printf("//|                  10000|              %i +             %i +         %i +\n", timeSelMid, timeInsMid, timeQuickMid);
   printf("//|                 100000|               %i+             %i +         %i +\n", timeSelLong, timeInsLong, timeQuickLong);
   printf("//+-----------------------+-----------------+----------------+------------+\n");
}
// Attempt1
////+-----------------------+-----------------+----------------+------------+
////|    Number of Elements |  Selection Sort | Insertion sort |  Quicksort |
////+-----------------------+-----------------+----------------+------------+
////|                   1000|               1 +              0 +          0 +
////|                  10000|             149 +             83 +          1 +
////|                 100000|           14938 +           8220 +         14 +
////+-----------------------+-----------------+----------------+------------+
//
// Attempt2
////+-----------------------+-----------------+----------------+------------+
////|    Number of Elements |  Selection Sort | Insertion sort |  Quicksort |
////+-----------------------+-----------------+----------------+------------+
////|                   1000|               1 +              0 +          0 +
////|                  10000|             149 +             81 +          1 +
////|                 100000|           14901 +           8259 +         14 +
////+-----------------------+-----------------+----------------+------------+
//
// Attempt3
////+-----------------------+-----------------+----------------+------------+
////|    Number of Elements |  Selection Sort | Insertion sort |  Quicksort |
////+-----------------------+-----------------+----------------+------------+
////|                   1000|               1 +              0 +          0 +
////|                  10000|             149 +             82 +          1 +
////|                 100000|           14904 +           8239 +         14 +
////+-----------------------+-----------------+----------------+------------+
                                    