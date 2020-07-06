# Stylebase Translator

*Stylebase Translator* is a command line utility aims to transform the JSON output from the WYSIWYG
editor [Stylebase](https://github.com/simplify9/stylebase) into Blazor output. *Potentially more
formats in the future*

# Dependencies
* [Nlohmann's JSON](https://github.com/nlohmann/json) to read the JSON template

# Build
Make sure CMake and a suitable C++ compiler is available, then:

```
$ mkdir build
$ cd build/
$ cmake ../
$ cmake --build .
```

# Using
```
$ ./stylebaseTranslator PATHTOJSONTEMPLATE
```

