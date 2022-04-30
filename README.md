# Compilation Instructions
## Using Cmake
A CmakeList.txt is included in the archive. Compile the attack
with
```bash
cmake .
make
```
# Included binaries
Two binaries are included:
* `attack` which takes an integer d as an argument and appends 2^d collisions to results.out
* `test_col` which tests the `find_col` function. Returns on stdout a collision and their value.

