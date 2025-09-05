# 📊 Growth Rate Comparison of Mathematical Functions in C

This project implements a **C program** that compares the growth rates of different mathematical functions by calculating their average values over a given range of `n`. It then sorts and prints the functions in **increasing order of their average growth**.

---

## ⚡ Features
- Implements **12 different mathematical functions** (logarithmic, polynomial, root-based, exponential).
- Computes the **average value** of each function over the range `n = 2` to `256` (step size = 2).
- **Sorts the functions** based on their average values.
- Displays the functions in **increasing order of growth**.
- Demonstrates **asymptotic growth analysis** in a simple, practical way.

---

## 🧮 Functions Implemented

| Function Label | Formula | Type |
|----------------|---------|------|
| `1/n` | \( \frac{1}{n} \) | Reciprocal |
| `log2(n)` | \( \log_2(n) \) | Logarithmic |
| `12*sqrt(n)` | \( 12 \cdot \sqrt{n} \) | Root |
| `50*sqrt(n)` | \( 50 \cdot \sqrt{n} \) | Root |
| `n^0.51` | \( n^{0.51} \) | Polynomial (sublinear) |
| `n*log(n)` | \( n \cdot \log_2(n) \) | Polynomial-Log |
| `n^2 - 324` | \( n^2 - 324 \) | Quadratic |
| `100n^2 + 6n` | \( 100n^2 + 6n \) | Quadratic (scaled) |
| `2n^3` | \( 2n^3 \) | Cubic |
| `n^log(n)` | \( n^{\log_2(n)} \) | Super-polynomial |
| `3^n` | \( 3^n \) | Exponential |
| `2^n` | \( 2^n \) | Exponential | 


## 🖥 Why We Fixed 2^32 · n to 2^n 
Originally, the code used: 
f12(n) = 2^32 · n

But this is *not exponential* — it’s just a linear function with a very large constant.  
Asymptotically, 2^32·n is *Θ(n), which will **never surpass n·log(n), n², or n³*.  

The intended comparison was with an *exponential function*.  
Therefore, we corrected it to:

f12(n) = 2^n

---

## 🖥️ Code Overview
- **Function Definitions:** Each growth function is implemented separately (`f1` to `f12`).
- **Computation:** For each `n` in the range, values are calculated and accumulated.
- **Averaging:** Average values are computed for fair comparison.
- **Sorting:** Functions are sorted in ascending order using a simple comparison swap.
- **Output:** Functions are displayed in increasing order of average growth.

---

## 📋 Sample Output

When you run the program, you’ll see an output like this:
1/n < log2(n) < 12*sqrt(n) < 50*sqrt(n) < n^0.51 < n*log(n) < n^2 - 324 < 100n^2 + 6n < 2n^3 < n^log(n) < 2^n < 3^n

