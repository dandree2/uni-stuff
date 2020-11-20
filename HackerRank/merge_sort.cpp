#include<iostream>
#include<vector>

void Merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temp arrays  
    std::vector<int> left_arr;
    std::vector<int> right_arr;

    // Copy data to temp arrays L[] and R[]  
    for (size_t i = 0; i < static_cast<size_t> (n1); i++)
        left_arr.emplace_back(arr[l + i]);
    for (size_t j = 0; j < static_cast<size_t> (n2); j++)
        right_arr.emplace_back(arr[m + 1 + j]);

    // Merge the temp arrays back into arr[l..r] 

    // Initial index of first subarray 
    size_t i = 0;

    // Initial index of second subarray 
    size_t j = 0;

    // Initial index of merged subarray 
    size_t k = l;
    
    while (i < n1 and j < n2)
    {
        if (left_arr[i] <= right_arr[j])
        {
            arr[k] = left_arr[i];
            i++;
        }
        else
        {
            arr[k] = right_arr[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of 
    // L[], if there are any  
    while (i < n1)
    {
        arr[k] = left_arr[i];
        i++;
        k++;
    }

    // Copy the remaining elements of 
    // R[], if there are any  
    while (j < n2)
    {
        arr[k] = right_arr[j];
        j++;
        k++;
    }
}

void MergeSort(int arr[], int l, int r) {
	if (l < r) {
		int m = l + (r - l) / 2;

		MergeSort(arr, l, m);
		MergeSort(arr, m + 1, r);

		Merge(arr, l, m, r);
	}
}

void printArray(int A[], int size)
{
    for (int i = 0; i < size; i++)
        std::cout << A[i] << " ";
}

int main() {

    int arr[] = { 12, 11, 13, 5, 6, 7 };
    int arr_size = sizeof(arr) / sizeof(arr[0]);

    std::cout << "Given array is \n";
    printArray(arr, arr_size);

    MergeSort(arr, 0, arr_size - 1);

    std::cout << "\nSorted array is \n";
    printArray(arr, arr_size);

	return 0;
}