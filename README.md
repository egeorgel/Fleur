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
### Installing
1. Download the repo
```sh
    git clone https://github.com/egeorgel/Fleur.git
```
2. You are ready to go
## How to use 
The syntax is SQL like in order to be easy to take in charge
Some key word :
* SELECT + css selector
* FROM + url or name of your ressource
* USE + your component ex: twitter by default it will use the HTML component 
### Example
```fql
    SELECT html FROM "http://httpbin.org/html";
    SELECT html (title) FROM "http://www.dynsim.fr";
```
## Contributing
Feel free to add any new component to this project.

## Authors
Edgar Georgel - Philppe Dupart - Arthur Busser - Anthony Da Mota - Valentin Mercier
