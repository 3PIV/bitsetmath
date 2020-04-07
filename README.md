# bitsetmath

Bitsetmath is a simple, header-only solution for integer math operations to extend the std::bitset data structure.

### Prerequisites

```
C++11 Compliant Compiler
```

To build the rsa test executable:
```
CMake >= 3.12
```

### Installing

In the directory you wish to build:
```
cmake /path/to/bitsetmath && make
```

### Testing

To test how the library works a toy rsa program was implemented as well as a small assert test package.
After building the rsa program, it may be ran as follows:
```
echo 'encrypt fileOfIntegers.txt done' | rsa
```
Which will produce `encrypted.txt`.
To decrypt:
```
echo 'decrypt encrypted.txt done' | rsa
```

## Authors

* **Preston Provins** - *Initial work* - [3PIV](https://github.com/3PIV)
