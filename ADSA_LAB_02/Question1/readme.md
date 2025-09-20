# 📘 Strassen Matrix Multiplication in C

This repository contains a C implementation of **Strassen’s Matrix Multiplication Algorithm**, one of the earliest and most famous algorithms that improved upon the classical cubic-time matrix multiplication.  

Strassen’s method reduces the number of multiplications in recursive steps, making it **asymptotically faster** than the standard \(O(n^3)\) algorithm.  
This implementation demonstrates how divide-and-conquer recursion works in practice.

---

## 📌 Why Strassen’s Algorithm?

Matrix multiplication is a fundamental operation in computer science, used in:
- Scientific computing 🧪  
- Graphics and image processing 🎨  
- Machine learning & neural networks 🤖  
- Cryptography 🔐  

The **naive algorithm** for multiplying two \(n \times n\) matrices requires:
\[
O(n^3)
\]

Strassen’s insight was that by cleverly combining submatrices, we can reduce **8 multiplications** into **7 multiplications** (with some additional additions/subtractions).  
This reduces complexity to:
\[
O(n^{\log_2 7}) \approx O(n^{2.807})
\]

For very large matrices, this reduction is significant!

---

## ✨ Features

- Recursive **divide-and-conquer** implementation  
- Works for square matrices of size \(2^k \times 2^k\)  
- Matrix **addition** and **subtraction** utilities  
- Base case with **2x2 matrices** multiplication  
- Configurable size with `#define MAX` (default: 8)  
- Simple **C99 standard code** (portable across Linux, Windows, MacOS)  

---

## 🛠️ Installation & Usage

1. **Clone the repository**
   ```bash
   git clone <your-repo-url>
   cd strassen-matrix-multiplication
