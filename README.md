## LBFGS-blaze

A header-only L-BFGS unconstrained optimizer with the power of `blaze-lib`, [website](https://bitbucket.org/blaze-lib/blaze/src/master/).
`LBFGS-blaze` is modified from `LBFGS-Lite`, [GitHub Repo](https://github.com/ZJU-FAST-Lab/LBFGS-Lite).
The detailed features please refer to `LBFGS-Lite`.

### Requirement

You will need the header Matrix C++ library, `blaze` to use this library.
We only tested on `blaze` 3.8.2. If you found any problems, please report issues.

### Example

You may refer [this file](./src/lbfgs_example.cpp) for the example code.

### Extension

We also provide a plug-in for `Rcpp`. Please refer to [the repository](https://github.com/ChingChuan-Chen/RcppLbfgsBlaze).

### License

`LBFGS-blaze` is modified from [LBFGS-Lite](https://github.com/ZJU-FAST-Lab/LBFGS-Lite) by `ZJU FAST Lab` which is modified based on [the C version](https://github.com/chokkan/liblbfgs) by Okazaki and extended from [the original Fortran version](https://doi.org/10.1007/BF01589116) by Nocedal. Thus, we follow the same LICENSE. Please refer to LICENSE file in the distribution.
