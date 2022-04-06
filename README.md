# libtrino

Status: In Development

An (attempt) at a Trino connection library for C++.

This project is built using CMake and it is has the following open-soruce dependencies:

- [cpr](https://github.com/libcpr/cpr) An awesome C++ requests library, modelled on the Python requests package
- [nlohmann::json](https://github.com/nlohmann/json) An awesome, easy to use JSON library for C++

## Code Sample

This is how you can run a simple query:

```c++
#include <iostream>

#include "abrisan/trino/Connection.h"

using namespace abrisan;

int main() {
    trino::Connection connection("localhost", 8080, trino::Scheme::HTTP, {}, "abrisan1");
    trino::Result result;
    connection.execute("SHOW CATALOGS", result);
    std::cout << result["Catalog"] << std::endl;
    return 0;
}

```

## Running Tests

You can run the tests using docker, by running `docker-compose run test`


## Development Environment

You should be able to open this project using [CLion](https://www.jetbrains.com/clion/) and develop with it.

Stay tuned for more updates!