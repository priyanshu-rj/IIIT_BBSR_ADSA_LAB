##  Defective Coin Finder (C Program)

This project implements a **C program** to find a **defective coin** (the one with the lowest weight/value) from a set of coins.  
We assume the array is **almost sorted** but contains one defective (lighter) coin.  
The goal is to identify that defective coin efficiently.

---

## ⚡ Features
- Uses **divide and conquer logic** to quickly locate the defective coin.
- Handles cases where the defective coin is at:
  - The beginning  
  - The middle  
  - The end of the array  
- Returns the **value of the defective coin** or `-1` if no defective coin is found.

---

## 📖 Code Explanation

### 🔹 Function: `find(int arr[], int n)`
- **Input:** array of integers (`arr`), number of elements (`n`).  
- **Process:**
  1. Uses `low` and `high` pointers to search.  
  2. Compares middle elements with neighbors.  
  3. If a coin is smaller than both left and right neighbors → it's defective.  
  4. Otherwise, keeps moving search window.  
- **Output:** Returns defective coin value, or `-1` if not found.

## ⏱️ Time Complexity (Why it is `O(log n)`)

We use a **binary-search-like** strategy: at each step we compare around a midpoint and **discard half** of the remaining search interval.
### 📊 Recurrence and Solution

Let $T(n)$ be the worst-case number of steps for an input of size $n$.  
Each step does $O(1)$ work (a few comparisons) and reduces the problem to **half** the size:

T(n) = T((n/2)) + O(1)

---

#### 🔹 Unrolling (repeated substitution)

T(n) = T((n/2)) + c  
     = T((n/4)) + 2c  
     = ...  
     = T((n/2^k)) + kc  

Stop when the subproblem size is 1:

(n / 2^k) = 1  ⇒  k = log₂ n  

Thus,

T(n) = T(1) + c log₂ n = O(log n)

---

#### 🔹 Base-change note

The base of the logarithm only changes the constant factor:

logₐ n = (log_b n) / (log_b a)

---

#### 🔹 Inductive view (interval halving)

After each iteration, the interval length halves:

n → n/2 → n/4 → ... → n/2^k  

After k = ⌈log₂ n⌉ iterations, the interval size is ≤ 1, so the search finishes.  
Hence, worst-case comparisons grow as:

Θ(log n)



### Space Complexity
The implementation is iterative and stores only a few indices (`low`, `high`, `mid`) → **O(1)** extra space.

> **Important:** To truly achieve `O(log n)`, each step must **discard half the search space** (adjusting `low`/`high` around `mid`). If you advance with `low++` linearly, the worst case becomes `O(n)`. Ensure your `find()` updates `low/high` by **halves**, not by single increments.



### 🔹 `main()`
1. Takes array size `n`.  
2. Reads `n` coin values.  
3. Calls `find()` to locate defective coin.  
4. Prints result.

---

## 🧑 Input / Output Examples

### INPUT:
Enter Elements N : 5
Enter Elements value : 4 4 4 3 4

### OUTPUT:
defective coin :3

