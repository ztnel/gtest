# C Integration Utils

[![ci](https://github.com/ztnel/gtest/actions/workflows/ci.yaml/badge.svg)](https://github.com/ztnel/gtest/actions/workflows/ci.yaml)
[![codecov](https://codecov.io/gh/ztnel/gtest/branch/master/graph/badge.svg?token=FW5QOZV3HS)](https://codecov.io/gh/ztnel/gtest)

Modified: 2022-01

Scalable templating for C project development with `gtest` and `gcov` and `codecov.io`. This repository merges utility from [bilke/cmake-modules](https://github.com/bilke/cmake-modules) and [jhbell/cmake-gcov](https://github.com/jhbell/cmake-gcov).

## Quickstart
Install `gcovr` util for xml generation
```bash
python3 -m pip install gcovr
```

Build with CMake
```bash
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
make -j2
```

Run tests and generate coverage report
```bash
make cov
```

