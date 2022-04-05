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
