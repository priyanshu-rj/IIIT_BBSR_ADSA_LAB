# 🔍 Binary Search vs Ternary Search – Comparison in C

This project implements and compares **Binary Search** and **Ternary Search** algorithms in C by measuring the number of comparisons required to find a given key.  

The program asks the user for an array (sorted) and a key to search, then performs both searches and prints:  
- The index where the key was found.  
- The number of comparisons made in each search.  

---

## ⚡ Features
- Implements **Ternary Search** and **Binary Search** iteratively.
- Tracks and prints the **number of comparisons** for each search.
- Helps understand which algorithm is more efficient in practice.
- Easy-to-use interactive program (takes input for array and key).

---

## 📚 Algorithm Explanation

### 🔹 Binary Search
- Divides the array into **two halves** at each step.
- Compares the key with the **middle element**.
- Time Complexity: **O(log₂ n)**  
- Space Complexity: **O(1)** (iterative).

### 🔹 Ternary Search
- Divides the array into **three parts** at each step (using `mid1` and `mid2`).
- Compares the key with two midpoints.
- Time Complexity: **O(log₃ n)**  
- Space Complexity: **O(1)** (iterative).

---

## 📊 Comparison

| Criterion           | Binary Search | Ternary Search |
|---------------------|---------------|----------------|
| **Divisions**       | 2 parts       | 3 parts        |
| **Comparisons per step** | 1           | 2              |
| **Time Complexity** | O(log₂ n)     | O(log₃ n)      |
| **Practical Use**   | Faster (fewer comparisons) | Slower (extra comparison overhead) |

➡️ Although Ternary Search reduces the array into smaller parts (log base 3), it performs **more comparisons per step** than Binary Search.  
In practice, **Binary Search is more efficient**.

---

## 🖥️ Sample Input/Output

## INPUT:
Enter Size of Array: 20
Enter Array Elements: 5 10 15 20 25 30 35 40 45 50 55 60 65 70 75 80 85 90 95 100
Enter value of key: 95
## OUTPUT:
Index Found at Index : 18
TernarySearch Comparisons : 4

Key found at Index: 18
BinarySearch Comparisons: 5

