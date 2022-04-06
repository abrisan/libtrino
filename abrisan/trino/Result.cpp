/*
 * MIT License

 * Copyright (c) 2022 Alexandru Brisan
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */


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