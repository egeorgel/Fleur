# Ƒ|eµℝ
 An API request tool for developpers, our main goal is to create a unify request language for all the API
## Tech
Ƒ|eµℝ uses a number of open source projects to work properly:
* [C++ Requests](https://github.com/whoshuu/cpr) - Simple wrapper around libcurl
* [Gumbo-query](https://github.com/lazytiger/gumbo-query) - Library that provides jQuery-like selectors
* [Google Test](https://github.com/google/googletest) - Google's C++ test framework!
* [Spirit](http://www.boost.org/doc/libs/1_62_0/libs/spirit/doc/html/index.html) - Practical parsing tool
## Getting Started
### Prerequisities
1. Install [Boost](http://www.boost.org/doc/libs/1_61_0/more/getting_started/unix-variants.html)
2. Install Curl
3. Install Gumbo
### Installing
1. Download the repo
```sh
    git clone https://github.com/egeorgel/Fleur.git
    git submodule update --init --recursive
```
2. Init Cmake
```sh
    cd Fleur
    mkdir tmp && cd tmp
    cmake -DCMAKE_BUILD_TYPE=Release ..
```

3. Build and/or install Fleur's static library
```sh
    make fleur_static
    # Files will be in Fleur/build/lib
    
    make fleur_static-install
    # Files will be in /usr/local/include/fleur.h and /usr/local/include/libfleur.a
```

4. Build and/or install Fleur's Command Line
```sh
    make fleur_cli
    # File will be in Fleur/build/bin
    
    make fleur_static-install
    # File will be in /usr/local/bin/fleur
 ```
 

## Fleur Query Language
## How to use the CLI
## Contributing
Feel free to add any new component to this project.

## Authors
Edgar Georgel - Philippe Dupart - Arthur Busser - Anthony Da Mota - Valentin Mercier
