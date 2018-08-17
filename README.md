A small library for ultra fast matrix multiplication of special diagonal block
matrices.

# Usage

```
./diagblock n d
```
where __n__ is the array size, and __d__ is the size of the diagonal.

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

Simply create a build directory and use cmake.

```
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make
```


# Roadmap

- [x] Get idea working with Eigen
- [ ] Implement tests
- [x] Implement matrix storage
- [x] Matrix multiplication
- [x] Parallel programming + SIMD
- [ ] Matrix Inverse
