//
// Created by Alexandru Brisan on 03/04/2022.
//

#ifndef TRINO_LIB_RESULT_H
#define TRINO_LIB_RESULT_H

#include <string>
#include <unordered_map>
#include <variant>
#include <vector>
#include <sstream>
#include "TrinoTypes.h"

namespace abrisan::trino {

    using Row = std::vector<TrinoValue>;
    using Column = std::vector<TrinoValue>;
    using Columns = std::pair<std::unordered_map<std::string, size_t>, std::vector<std::string>>;
    using OriginalTypes = std::unordered_map<std::string, SupportedTrinoTypes>;

    template<SupportedTrinoTypes type>
    typename TrinoTypesCppTraits<type>::CorrespondingType get_cell(TrinoValue const &c) {
        using CType = typename TrinoTypesCppTraits<type>::CorrespondingType;
        return std::get<CType>(c);
    };

    class Result {
        std::vector<Row> _rows;
        Columns _columns;
        OriginalTypes  _original_types;
    public:
        explicit Result() = default;
        Row const &operator[](size_t index) const;
        Column operator[](std::string const &column) const;
        std::vector<Row> &rows() { return this->_rows; }
        Columns &columns() { return this->_columns; }
        OriginalTypes &typeMappings() { return this->_original_types; }
    };
}

inline
std::ostream &operator<<(std::ostream &cout, abrisan::trino::Row const &row) {
    cout <<  "[";
    for (auto it = row.begin(); it != row.end() - 1 ; ++it) {
        std::visit([&](auto &&arg){ cout << arg << ", "; }, *it);
    }
    if (!row.empty()) {
        std::visit([&](auto &&arg){ cout << arg; }, row[row.size() - 1]);
    }
    cout << "]";
    return cout;
}

#endif //TRINO_LIB_RESULT_H
