[![Build Status](https://travis-ci.org/egeorgel/Fleur.svg?branch=master)](https://travis-ci.org/egeorgel/Fleur)

# Ƒ|eµℝ
 An API request tool for developpers, our main goal is to create a unify request language for all the APIs.

- [Tech](#Tech)
- [Getting Started](#Getting-Started)
  - [Prerequisities](#Prerequisities)
  - [Installing](#Installing)
- [Fleur Query Language Documentation](#Fleur-Query-Language-Documentation)
    - [HTTP Module](#HTTP-Module)
    - [Twitter Module](#Twitter-Module)
    - [Wikipedia Module](#Wikipedia-Module)
    - [WolframeAlpha Module](#WolframeAlpha-Module)
- [How to use the CLI](#How-to-use-the-CLI)
- [Contributing](#Contributing)
- [Authors](#Authors)

## Tech
Ƒ|eµℝ uses a number of open source projects to work properly:
* [C++ Requests](https://github.com/whoshuu/cpr) - Simple wrapper around libcurl
* [Gumbo-query](https://github.com/lazytiger/gumbo-query) - Library that provides jQuery-like selectors
* [Google Test](https://github.com/google/googletest) - Google's C++ test framework!
* [Spirit](http://www.boost.org/doc/libs/1_62_0/libs/spirit/doc/html/index.html) - Practical parsing tool

## Getting Started
### Prerequisities
* Install [Boost](http://www.boost.org/doc/libs/1_61_0/more/getting_started/unix-variants.html)
* Install Curl
* Install Readline
* Install Gumbo

### Installing
* Download the repo
```sh
    git clone https://github.com/egeorgel/Fleur.git
    cd Fleur/
    git submodule update --init --recursive
```
* Init Cmake
```sh
    mkdir cmake && cd cmake
    cmake -DCMAKE_BUILD_TYPE=Release ..
```

* Build and/or install Fleur's static library
```sh
    make fleur_static
    # Files will be in Fleur/build/lib
    
    make fleur_static-install
    # Files will be in /usr/local/include/fleur.h and /usr/local/include/libfleur.a
```

* Build and/or install Fleur's Command Line
```sh
    make fleur_cli
    # File will be in Fleur/build/bin
    
    make fleur_static-install
    # File will be in /usr/local/bin/fleur
```
 
 * Uninstall
```sh
     make fleur_cli-uninstall
     make fleur_static-uninstall
 ```
 
## Fleur Query Language Documentation 
Fleur comprend différent module en plus des fonctionnalité du module de base.
Chaque module comporte quelques spécificité syntaxique que vous pouvez trouver ci-dessous.
### HTTP Module
The syntax is SQL like in order to be easy to take in charge
* SELECT + html/* or json or xml + Optional: (css selector) + FROM + url or name of your ressource + Optional: GET/POST/Header (param1=val1, param2=val2)
```fql
    use http;  
    SELECT html FROM "http://httpbin.org/html";
    SELECT html (title) FROM "http://www.dynsim.fr";
    
    select json from "http://denis.fr" get (name=denis, age=12, date=12/12/12) header (tokenID=E223DEF, time=4);
    select html (p) from "http://denis.fr" get (name=denis, age=12, date=12/12/12) header (tokenID=E223DEF, time=4);
```

###Twitter Module
In order to start the Twitter Module you have to type:
```fql
    use twitter;
    (_consumerKey, _consumerSecret, _tokenKey, _tokenSecret);
```
* syntax : GET + */tweets or mention or trends + from twitter/. or anyother personn + Optional : limit to X
```fql
get tweets from twitter;                           #Get all your tweet from twitter limit to 200
get * from .;                                               #Same request
get tweets from ProductHunt limit 2;    #Get the 2 first tweets from ProductHunt   
get * from ProductHunt limit 2;              #Same request
```
* syntax: SEARCH + text + FROM + twitter
```fql
    search Java from wiki;            #Search all article with the key word Java
    search "text" from * limit 2;   #Same request but only take the 2 first
```
* syntax: POST + text
```fql
    post "new tweet";
```
* syntax: DELETE + post_id
```fql
   delete 934839843522;
```
###Wikipedia Module
In order to start the Twitter Module you have to type:
```fql
    use wikipedia;
```
* syntax: GET + (html or header or txt) article_name + FROM + wikipedia + Optional: limit to X
```fql
    get (header) java from wiki;     #get the first part of the java article 
    get (html) java from wiki;          #get the full html of the java arcticle
    get java from wiki;                     #same as HTML
    get (txt) java from wiki;             #retreive the full content of the article in text format
```

* syntax: SEARCH + article_name + FROM + wikipedia + Optional: limit to X
```fql
    search Java from wiki;              #Get all article id, name, header from the Java search
    search Java from wiki limit 4;  #Get the 4 first result of the previous search
```
###WolframeAlpha Module
In order to start the WolframeAlpha Module you have to type:
```fql
    use wolframealpha;
    appId;
```
* syntax : evaluate + string_to_evaluate_in_walframe_alpha;
```fql
    evaluate x + 3 = 4;
    evaluate string to search in Walframe Alpha
```
 


## How to use the CLI
```sh
    fleur -h or fleur --help
    fleur -v or fleur --version
    fleur -e QUERY or fleur --execute QUERY
    INPUT | fleur
```
 
## Contributing
Feel free to add any new component to this project.

## Authors
Edgar Georgel - Valentin Mercier - Philippe Dupart - Arthur Busser - Anthony Da Mota
