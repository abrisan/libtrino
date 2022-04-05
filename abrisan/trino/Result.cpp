//
// Created by Alexandru Brisan on 03/04/2022.
//

#include "Result.h"

using namespace abrisan::trino;

Row const &Result::operator[](size_t index) const {
    if (index >= _rows.size()) {
        throw std::out_of_range("Out of range!");
    }

    return _rows[index];
}

Column Result::operator[](std::string const &column) const {
    auto column_index_it = _columns.first.find(column);

    if (column_index_it == _columns.first.end()) {
        std::ostringstream error_message;
        error_message << "Column " << column << " does not exist in result set.";
        throw std::out_of_range(error_message.str());
    }

    auto column_index = column_index_it->second;

    Column return_value;
    for (auto const &row : _rows) {
        return_value.push_back(row[column_index]);
    }

    return return_value;
}