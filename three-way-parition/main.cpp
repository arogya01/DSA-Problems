#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class ThreeWayPartition {
public:
    // Main three-way partition function
    static void partition(vector<int>& arr, int pivot) {
        int low = 0;      // Boundary for elements < pivot
        int mid = 0;      // Current element being processed
        int high = arr.size() - 1;  // Boundary for elements > pivot
        
        while (mid <= high) {
            if (arr[mid] < pivot) {
                // Element belongs in the "less than" section
                swap(arr[low], arr[mid]);
                low++;
                mid++;
            }
            else if (arr[mid] == pivot) {
                // Element is already in correct position
                mid++;
            }
            else {  // arr[mid] > pivot
                // Element belongs in the "greater than" section
                swap(arr[mid], arr[high]);
                high--;
                // Don't increment mid - we need to process the swapped element
            }
        }
    }
    
    // Variant: Return the boundaries of the equal section
    static pair<int, int> partitionWithBounds(vector<int>& arr, int pivot) {
        int low = 0;
        int mid = 0;
        int high = arr.size() - 1;
        
        while (mid <= high) {
            if (arr[mid] < pivot) {
                swap(arr[low], arr[mid]);
                low++;
                mid++;
            }
            else if (arr[mid] == pivot) {
                mid++;
            }
            else {
                swap(arr[mid], arr[high]);
                high--;
            }
        }
        
        // Return [start, end] of the equal section
        return {low, high + 1};
    }
    
    // Utility function to print array
    static void printArray(const vector<int>& arr) {
        for (int x : arr) {
            cout << x << " ";
        }
        cout << endl;
    }
    
    // Test function with detailed tracing
    static void demonstrateWithTrace(vector<int> arr, int pivot) {
        cout << "Original array: ";
        printArray(arr);
        cout << "Pivot: " << pivot << "\n\n";
        
        int low = 0, mid = 0, high = arr.size() - 1;
        int step = 1;
        
        while (mid <= high) {
            cout << "Step " << step++ << ": ";
            cout << "low=" << low << ", mid=" << mid << ", high=" << high;
            cout << ", arr[mid]=" << arr[mid] << endl;
            
            if (arr[mid] < pivot) {
                cout << "  arr[mid] < pivot: swap arr[" << low << "] with arr[" << mid << "]" << endl;
                swap(arr[low], arr[mid]);
                low++;
                mid++;
            }
            else if (arr[mid] == pivot) {
                cout << "  arr[mid] == pivot: just move mid forward" << endl;
                mid++;
            }
            else {
                cout << "  arr[mid] > pivot: swap arr[" << mid << "] with arr[" << high << "]" << endl;
                swap(arr[mid], arr[high]);
                high--;
            }
            
            cout << "  Result: ";
            printArray(arr);
            cout << endl;
        }
        
        cout << "Final partitioned array: ";
        printArray(arr);
    }
};

// Specialized version for the classic "Sort 0s, 1s, 2s" problem
class DutchFlagSort {
public:
    static void sort012(vector<int>& arr) {
        ThreeWayPartition::partition(arr, 1);  // Using 1 as pivot
    }
};

int main() {
    // Example 1: Basic demonstration
    cout << "=== Basic Three-Way Partitioning ===\n";
    vector<int> arr1 = {2, 0, 2, 1, 1, 0};
    cout << "Before: ";
    ThreeWayPartition::printArray(arr1);
    
    ThreeWayPartition::partition(arr1, 1);
    cout << "After partitioning around pivot 1: ";
    ThreeWayPartition::printArray(arr1);
    cout << endl;
    
    // Example 2: Detailed trace
    cout << "=== Detailed Step-by-Step Trace ===\n";
    vector<int> arr2 = {2, 0, 2, 1, 1, 0};
    ThreeWayPartition::demonstrateWithTrace(arr2, 1);
    cout << endl;
    
    // Example 3: Edge cases
    cout << "=== Edge Cases ===\n";
    
    // All elements equal to pivot
    vector<int> arr3 = {5, 5, 5, 5};
    cout << "All equal to pivot: ";
    ThreeWayPartition::printArray(arr3);
    ThreeWayPartition::partition(arr3, 5);
    cout << "After partitioning: ";
    ThreeWayPartition::printArray(arr3);
    
    // No elements equal to pivot
    vector<int> arr4 = {1, 3, 7, 9};
    cout << "No elements equal to pivot 5: ";
    ThreeWayPartition::printArray(arr4);
    ThreeWayPartition::partition(arr4, 5);
    cout << "After partitioning: ";
    ThreeWayPartition::printArray(arr4);
    
    // Dutch National Flag (0s, 1s, 2s)
    cout << "\n=== Dutch National Flag Problem ===\n";
    vector<int> arr5 = {2, 0, 1, 2, 1, 0, 2, 1, 0};
    cout << "Unsorted 0s, 1s, 2s: ";
    ThreeWayPartition::printArray(arr5);
    DutchFlagSort::sort012(arr5);
    cout << "After sorting: ";
    ThreeWayPartition::printArray(arr5);
    
    return 0;
}