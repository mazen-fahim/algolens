void sort(int *arr, int size, void sort_type()) { sort_type(arr,size); } 
void search(int *arr, int size, int element, void search_typr()) { search_typr(arr, size, element);}

/*SORT*/
void selection_sort(int *arr, int size)
{
    int temp;
    for(int i = 0; i < size-1; i++)
        for(int k = i+1; k < size; k++)
            if(arr[k] < arr[i])
            {
                temp = arr[i];
                arr[i] = arr[k];
                arr[k] = temp;
            }
}

void bubble_sort(int *arr, int size)
{
    for (int i = 0; i < size-1; i++)
        for(int k = 0; k < size-1-i; k++)
            if(arr[k] > arr[k+1])
            {
                int temp = arr[k+1];
                arr[k+1] = arr[k];
                arr[k] = temp;
            }
}

void bubble_sort_rec(int *arr, int size)
{
    if(size == 1)
        return;
    for(int i = 0; i < size - 1; i++)
        if(arr[i] > arr[i+1])
        {
            int temp = arr[i+1];
            arr[i+1] = arr[i];
            arr[i] = temp;
        }
    bubble_sort_rec(arr, size-1);
}

void insertion_sort(int *arr, int size)
{
    int key;
    for(int i = 1; i < size; i++)
    {
        key = arr[i];
        for(int k = 0; k < i; k++)
        {
            if(key < arr[i-k-1] && i-k-1 == 0)
            {
                arr[i-k] = arr[i-k-1];
                arr[i-k-1] = key;
            }
            else if (key < arr[i-k-1])
                arr[i-k] = arr[i-k-1];
            else 
            {
                arr[i-k] = key;
                break;
            }
        }
    }
}

void merge(int *arr, int l, int m, int r)
{
    
}
void merge_sort(int *arr, int l, int r)
{
    if(l<r)
    {
        int m = l+(r-l)/2;
        merge_sort(arr, l,m);
        merge_sort(arr, m+1,r);
        merge(arr, l, m ,r);
    }
}
// merge_sort(0, 6)
// {10, 7, 8, 19, 1, 4, 8}
//  ^   ^  ^  ^   ^  ^  ^
//  0   1  2  3   4  5  6
//            ^
//            m
// -----------------------
// merge_sort(0, 3)
// {10, 7, 8, 19, 1, 4, 8}
//  ^   ^  ^  ^   ^  ^  ^
//  0   1  2  3   4  5  6
//      ^
//      m
// -----------------------
// merge_sort(0, 1)             merge_sort(0,0)
// {10, 7, 8, 19, 1, 4, 8}      return; <<<<<<<<<<<
//  ^   ^  ^  ^   ^  ^  ^
//  0   1  2  3   4  5  6
//  ^
//  m
// merge_sort(1, 1)
//      return;
// merge(0,0,1)
//



/*SEARCH*/

int binary_search(int *arr, int size, int element)
{
    int first = 0;
    int last = size -1;
    int mid = 0;
    while(1)
    {
        mid = first+last/2;
        if(arr[mid] == element)
            return mid;
        else if(arr[mid] < element)
            first = mid+1;
        else
            last = mid -1;
    }
}
