#include <iostream>
#include <vector>
using namespace std;

// Function to max-heapify a subtree rooted at index i
void maxHeap(vector<int>& arr, int n, int i) {
    int largest = i; // Initialize largest as root
    int left = 2 * i + 1; // Left child
    int right = 2 * i + 2; // Right child
	// If left child is larger than root
    if (left < n && arr[left] > arr[largest])
        largest = left;
	// If right child is larger than largest so far
    if (right < n && arr[right] > arr[largest])
        largest = right;
	// If largest is not root
    if (largest != i) {
        swap(arr[i], arr[largest]);
        maxHeap(arr, n, largest);
    }
}
// Function to build a max heap
void buildMaxHeap(vector<int>& arr) {
    int n = arr.size();
	// Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        maxHeap(arr, n, i);
}
// Heap-Sort function
void heapSort(vector<int>& arr) {
    int n = arr.size();
    buildMaxHeap(arr);
	// One by one extract an element from heap
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]); // Move current root to the end
        maxHeap(arr, i, 0); // Restore heap property
    }
}

int main() {
    int n;
    cout << "Enter the number of elements: ";
	cin >> n;
	vector<int> arr(n);
	cout << "Enter the elements: ";
	for (int i = 0; i < n; i++)
		cin >> arr[i];
	// Sort the array - pass by reference to avoid copying
    heapSort(arr);
    cout << "Sorted array: ";
    for (int num : arr)
        cout << num << " ";
    cout << endl;

    return 0;
}
