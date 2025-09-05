# 📚 Heap Sort in C

This project implements the **Heap Sort algorithm** in C.  
Heap Sort is a **comparison-based sorting technique** based on a **Binary Heap** data structure.  
It sorts an array in-place with **O(n log n)** time complexity.

---

## ⚡ Features
- Implements **Heapify** (maintains max-heap property).  
- Efficient **in-place sorting** (no extra memory needed).  
- Works for arrays of any size.  
- Runs in **O(n log n)** time in all cases (best, average, worst).  

---

## 📖 Code Explanation

### 🔹 `heapify(int arr[], int n, int i)`
- Maintains the **max-heap property** for the subtree rooted at index `i`.  
- Compares node `i` with its left and right children (`2*i+1`, `2*i+2`).  
- Swaps with the largest child if needed, then recursively heapifies.

### 🔹 `heapSort(int arr[], int n)`
1. **Build max heap** from the input array.  
2. Repeatedly swap the root (largest element) with the last element.  
3. Reduce heap size and call `heapify()` on the root.  
4. Continue until the array is sorted.

### 🔹 `main()`
1. Reads `n` (number of elements).  
2. Reads array elements.  
3. Calls `heapSort()`.  
4. Prints sorted array.

---

## 🧑 Input / Output Examples

**Input**
5
12 11 13 5 6

**Output**
5 6 11 12 13
