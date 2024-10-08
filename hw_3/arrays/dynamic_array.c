#include "dynamic_array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* private functions *********************************************************/

/* Position in the buffer of the array element at position index */
static int index_to_offset(const DynamicArray *da, int index)
{
    return index + da->origin;
}

/* Position of the element at buffer position 'offset' */
static int offset_to_index(const DynamicArray *da, int offset)
{
    return offset - da->origin;
}

/* Non-zero if and only if offset lies ouside the buffer */
static int out_of_buffer(DynamicArray *da, int offset)
{
    return offset < 0 || offset >= da->capacity;
}

/* Makes a new buffer that is twice the size of the old buffer,
   copies the old information into the new buffer, and deletes
   the old buffer */
static void extend_buffer(DynamicArray *da)
{

    double *temp = (double *)calloc(2 * da->capacity, sizeof(double));
    int new_origin = da->capacity - (da->end - da->origin) / 2,
        new_end = new_origin + (da->end - da->origin);

    for (int i = 0; i < DynamicArray_size(da); i++)
    {
        temp[new_origin + i] = DynamicArray_get(da, i);
    }

    free(da->buffer);
    da->buffer = temp;

    da->capacity = 2 * da->capacity;
    da->origin = new_origin;
    da->end = new_end;

    return;
}

/* public functions **********************************************************/

DynamicArray *DynamicArray_new(void)
{
    DynamicArray *da = (DynamicArray *)malloc(sizeof(DynamicArray));
    da->capacity = DYNAMIC_ARRAY_INITIAL_CAPACITY;
    da->buffer = (double *)calloc(da->capacity, sizeof(double));
    da->origin = da->capacity / 2;
    da->end = da->origin;
    return da;
}

void DynamicArray_destroy(DynamicArray *da)
{
    free(da->buffer);
    da->buffer = NULL;
    return;
}

int DynamicArray_size(const DynamicArray *da)
{
    assert(da->buffer != NULL);
    return da->end - da->origin;
}

char *DynamicArray_to_string(const DynamicArray *da)
{
    assert(da->buffer != NULL);
    char *str = (char *)calloc(20, DynamicArray_size(da)),
         temp[20];
    int j = 1;
    str[0] = '[';
    for (int i = 0; i < DynamicArray_size(da); i++)
    {
        if (DynamicArray_get(da, i) == 0)
        {
            snprintf(temp, 20, "0");
        }
        else
        {
            snprintf(temp, 20, "%.5lf", DynamicArray_get(da, i));
        }
        if (i < DynamicArray_size(da) - 1)
        {
            sprintf(str + j, "%s,", temp);
            j += strlen(temp) + 1;
        }
        else
        {
            sprintf(str + j, "%s", temp);
            j += strlen(temp);
        }
    }
    str[j] = ']';
    return str;
}

void DynamicArray_print_debug_info(const DynamicArray *da)
{

    char *s = DynamicArray_to_string(da);
    printf("  %s\n", s);
    printf("  capacity: %d\n  origin: %d\n  end: %d\n  size: %d\n\n",
           da->capacity,
           da->origin,
           da->end,
           DynamicArray_size(da));

    free(s);
}

void DynamicArray_set(DynamicArray *da, int index, double value)
{
    assert(da->buffer != NULL);
    assert(index >= 0);
    while (out_of_buffer(da, index_to_offset(da, index)))
    {
        extend_buffer(da);
    }
    da->buffer[index_to_offset(da, index)] = value;
    if (index >= DynamicArray_size(da))
    {
        da->end = index_to_offset(da, index + 1);
    }
}

double DynamicArray_get(const DynamicArray *da, int index)
{
    assert(da->buffer != NULL);
    assert(index >= 0);
    if (index >= DynamicArray_size(da))
    {
        return 0;
    }
    else
    {
        return da->buffer[index_to_offset(da, index)];
    }
}

void DynamicArray_push(DynamicArray *da, double value)
{
    DynamicArray_set(da, DynamicArray_size(da), value);
}

void DynamicArray_push_front(DynamicArray *da, double value)
{
    assert(da->buffer != NULL);
    while (da->origin == 0)
    {
        extend_buffer(da);
    }
    da->origin--;
    DynamicArray_set(da, 0, value);
}

double DynamicArray_pop(DynamicArray *da)
{
    assert(DynamicArray_size(da) > 0);
    double value = DynamicArray_get(da, DynamicArray_size(da) - 1);
    DynamicArray_set(da, DynamicArray_size(da) - 1, 0.0);
    da->end--;
    return value;
}

double DynamicArray_pop_front(DynamicArray *da)
{
    assert(DynamicArray_size(da) > 0);
    double value = DynamicArray_get(da, 0);
    da->origin++;
    return value;
}

DynamicArray *DynamicArray_map(const DynamicArray *da, double (*f)(double))
{
    assert(da->buffer != NULL);
    DynamicArray *result = DynamicArray_new();
    for (int i = 0; i < DynamicArray_size(da); i++)
    {
        DynamicArray_set(result, i, f(DynamicArray_get(da, i)));
    }
    return result;
}

DynamicArray *DynamicArray_subarray(DynamicArray *da, int a, int b)
{

    assert(da->buffer != NULL);
    assert(b >= a);

    DynamicArray *result = DynamicArray_new();

    for (int i = a; i < b; i++)
    {
        DynamicArray_push(result, DynamicArray_get(da, i));
    }

    return result;
}

double DynamicArray_min(const DynamicArray *da)
{
    assert(da->end > 0);
    int size = DynamicArray_size(da);
    if (size <= 0)
    {
        return 0.0;
    }
    double min = da->buffer[0];
    for (int i = 1; i < size; ++i)
    {
        if (da->buffer[i] < min)
        {
            min = da->buffer[i];
        }
    }
    return min;
}

double DynamicArray_max(const DynamicArray *da)
{
    assert(da->end > 0);
    int size = DynamicArray_size(da);
    if (size <= 0)
    {
        return 0.0;
    }
    double max = da->buffer[0];
    for (int i = 1; i < size; ++i)
    {
        if (da->buffer[i] > max)
        {
            max = da->buffer[i];
        }
    }
    return max;
}

double DynamicArray_mean(const DynamicArray *da)
{
    assert(da->end > 0);
    int size = DynamicArray_size(da);
    if (size <= 0)
    {
        return 0.0;
    }
    double mean = 0.0;
    for (int i = 0; i < size; ++i)
    {
        mean += da->buffer[i];
    }
    return mean / size;
}

/// quick selection
void quicksort(double arr[], int low, int high)
{
    if (low < high)
    {
        int pivot = partition(arr, low, high);
        quicksort(arr, low, pivot - 1);
        quicksort(arr, pivot + 1, high);
    }
}
/// partition
int partition(double arr[], int low, int high)
{
    double pivot = arr[low];
    while (low < high)
    {
        while (low < high && arr[high] >= pivot)
        {
            high--;
        }
        arr[low] = arr[high];

        while (low < high && arr[low] <= pivot)
        {
            low++;
        }
        arr[high] = arr[low];
    }
    arr[low] = pivot;
    return low;
}

double DynamicArray_median(const DynamicArray *da)
{
    assert(da->end > 0);
    quicksort(da->buffer, 0, da->end);

    double median;
    if (da->end % 2 == 0)
    {
        int mid = da->end >> 1;
        median = (da->buffer[mid - 1] + da->buffer[mid]) / 2.0;
    }
    else
    {
        median = da->buffer[da->end >> 1];
    }
    return median;
}

double DynamicArray_sum(const DynamicArray *da)
{
    int size = DynamicArray_size(da);
    if (size <= 0)
    {
        return 0.0;
    }
    double sum = 0.0;
    for (int i = 0; i < size; ++i)
    {
        sum += da->buffer[i];
    }
    return sum;
}

double DynamicArray_last(const DynamicArray *da)
{
    assert(da->end > 0);
    return da->buffer[da->end - 1];
}

double DynamicArray_first(const DynamicArray *da)
{
    assert(da->end > 0);
    return da->buffer[0];
}

DynamicArray *DynamicArray_copy(const DynamicArray *da)
{
    DynamicArray *ans = (DynamicArray *)malloc(sizeof(DynamicArray));
    int size = DynamicArray_size(da);
    ans->capacity = da->capacity;
    ans->buffer = (double *)calloc(size, sizeof(double));
    ans->origin = da->origin;
    ans->end = da->end;
    for (int i = 0; i < size; ++i)
    {
        ans->buffer[i] = da->buffer[i];
    }

    return ans;
}

DynamicArray *DynamicArray_range(double a, double b, double step)
{
    int size = (int)((b - a) / step) + 1;
    DynamicArray *ans = (DynamicArray *)malloc(sizeof(DynamicArray));
    ans->origin = 0;
    ans->end = size;
    ans->buffer = (double *)calloc(size, sizeof(double));
    for (double val = a; val <= b; val += step)
    {
        ans->buffer[ans->end++] = val;
    }

    return ans;
}

DynamicArray *DynamicArray_concat(const DynamicArray *a, const DynamicArray *b)
{
    int size = DynamicArray_size(a) + DynamicArray_size(b);
    DynamicArray *ans = (DynamicArray *)malloc(sizeof(DynamicArray));
    ans->origin = 0;
    ans->end = size;
    ans->buffer = (double *)calloc(size, sizeof(double));
    for (int i = 0; i < a->end; ++i)
    {
        ans->buffer[ans->end++] = a->buffer[i];
    }
    for (int i = 0; i < b->end; ++i)
    {
        ans->buffer[ans->end++] = b->buffer[i];
    }

    return ans;
}

DynamicArray *DynamicArray_take(const DynamicArray *a, int num)
{
    int a_size = DynamicArray_size(a);
    int size = abs(num);
    DynamicArray *ans = (DynamicArray *)calloc(size, sizeof(int));
    if (num > 0)
    {
        for (int i = 0; i < a_size && i < size; ++i)
        {
            ans->buffer[i] = a->buffer[i];
        }
    }
    else
    {
        if (size > a_size)
        {
            for (int i = 0; i < a_size; ++i)
            {
                ans->buffer[i] = a->buffer[i];
            }
        }
        else
        {
            for (int i = 0; i < size; ++i)
            {
                ans->buffer[i] = a->buffer[i + a_size - size];
            }
        }
    }

    return ans;
}
