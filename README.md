A small library for ultra fast matrix multiplication of special diagonal block
matrices.

# Problem Statement

Consider a matrix $\mathbf{A}$ of size $\mathbb{R}^{nd\times nd}$, where each 
non-overlapping $d \times d$ block of the matrix, $\mathbf{D}_{ij}$, is a 
diagonal matrix. So the matrix consists of $n^2$
such blocks. An example of such a matrix is shown below:

\begin{bmatrix}
    \mathbf{D}_{11} & \mathbf{D}_{12} & \mathbf{D}_{13} & \cdots & \mathbf{D}_{1n} \\
    \mathbf{D}_{21} & \mathbf{D}_{22} & \mathbf{D}_{23} & \cdots & \mathbf{D}_{2n} \\
    \cdots & \cdots & \cdots & \cdots & \cdots \\
    \mathbf{D}_{n1} & \mathbf{D}_{n2} & \mathbf{D}_{n3} & \cdots & \mathbf{D}_{nn}
\end{bmatrix} 

Construct an efficient data structure to represent such matrices and device algorithms 
to perform matrix operations, such as matrix multiplications and matrix inverse, 
on the data structure you designed. Provide a technical write-up of your solution 
along with associated code implementing your solution.

# Usage

```
./diagblock n d
```
where n is the array size, and d is the size of the diagonal.

## Example

```
./diagblock 16 8
Initializing...    n: 16  d: 16

Generating initial blocks.
Done. Matrix size: 65536.

===EIGEN SPARSE===
  Building Eigen Sparse Matrix... Done.
  Matmul:        0 milliseconds

===EIGEN DENSE====
  Building Eigen Dense Matrix... Done.
  Matmul:        0 milliseconds

===GSL DENSE======
  Building GSL Dense Matrix... Done.
  Matmul:        1 milliseconds

===DiagBlock ======
  Building DiagBlock Dense Matrix... Done.
  Matmul:        0 milliseconds
```

# Compiling

Requires:
- CMake 3.5+
- GSL
- Eigen


# Roadmap

- [x] Get idea working with Eigen
- [ ] Implement tests
- [x] Implement matrix storage
- [x] Matrix multiplication
- [x] Parallel programming + SIMD
- [ ] Matrix Inverse
