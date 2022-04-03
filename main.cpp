#include <iostream>

#include "abrisan/trino/Request.h"
#include "abrisan/trino/Query.h"
#include <chrono>

using namespace abrisan;

std::ostream &operator<<(std::ostream &cout, std::vector<std::vector<std::string>> const &value) {
    cout << "[";
    for (auto const &row : value) {
        cout << "[";
        for (auto const &col: row) {
            cout << col << ",";
        }
        cout << "]\n";
    }
    cout << "]\n";
    return cout;
}

std::ostream &operator<<(std::ostream &cout, trino::Data const &value) {
    cout << "[\n";
    for (auto const &row : value) {
        cout << "   {\n";
        for (auto const &col: row) {
            cout << "       " << col.first << ": " << col.second << ",\n";
        }
        cout << "   }\n";
    }
    cout << "]\n";
}

int main() {
    auto before = std::chrono::high_resolution_clock::now();
    trino::Request request("localhost", 8080, "abrisan",{});
    trino::Query query(request, "SHOW SCHEMAS FROM tpcds");
    query.execute();
    std::cout << query.get_data();
    return 0;
}
