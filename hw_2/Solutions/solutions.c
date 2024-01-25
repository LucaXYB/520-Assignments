#include "solutions.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Constantly calculate the sum of input value
static int sum = 0;
int running_total(int val) {
    sum += val;
    return sum;
}

// Revereve the input array, return a new array
int* reverse(int* arr, int num) {
    int* res = (int*) malloc(num * sizeof(int));
    for (int i = 0; i < num; ++i) {
        res[i] = arr[num-1-i];
    }
    return res;
}

// Reverse and update the input array
void reverse_in_place(int* arr, int num) {
    int left = 0, right = num - 1;
    while (left < right) {
        int temp = arr[left];
        arr[left] = arr[right];
        arr[right] = temp;
        left++;
        right--;
    }
}

int num_occurences(int* arr, int num, int val) {
    int ans = 0;
    for (int i = 0; i < num; ++i) {
        if (arr[i] == val) {
            ans++;
        }
    }
    return ans;
}