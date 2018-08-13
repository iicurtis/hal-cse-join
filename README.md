Consider a matrix A of size Rnd×nd, where each non-overlapping d×d block of the matrix, Dij, is a diagonal matrix. So the matrix consists of n2
such blocks. An example of such a matrix is shown below:

Construct an efficient data structure to represent such matrices and device algorithms to perform matrix operations, such as matrix multiplications and matrix inverse, on the data structure you designed. Provide a technical write-up of your solution along with associated code implementing your solution.


## Ideas

Use standard vectors internally. Use z-order curve otherwise.

This is known as a BLOCK MATRIX.

## Roadmap

- [ ] Get idea working with Eigen
- [ ] Implement tests
- [ ] Implement matrix storage
- [ ] Matrix multiplication
- [ ] Parallel programming + SIMD
- [ ] Matrix Inverse
