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
 * The above copyright notice and this permission notice shall be included in
 all
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

#ifndef TRINO_LIB_RESULT_H
#define TRINO_LIB_RESULT_H

#include "TrinoTypes.h"
#include <sstream>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

namespace abrisan::trino {

    using Row = std::vector<TrinoValue>;
    using Column = std::vector<TrinoValue>;
    using Columns = std::pair<std::unordered_map<std::string, size_t>,
            std::vector<std::string>>;
    using OriginalTypes = std::unordered_map<std::string, SupportedTrinoTypes>;

    template<SupportedTrinoTypes type>
    typename TrinoTypesCppTraits<type>::CorrespondingType
    get_cell(TrinoValue const &c) {
        using CType = typename TrinoTypesCppTraits<type>::CorrespondingType;
        return std::get<CType>(c);
    };

    class Result {
        std::vector<Row> _rows;
        Columns _columns;
        OriginalTypes _original_types;

    public:
        explicit Result() = default;

        Row const &operator[](size_t index) const;

        Column operator[](std::string const &column) const;

        std::vector<Row> &rows() { return this->_rows; }

        Columns &columns() { return this->_columns; }

        OriginalTypes &typeMappings() { return this->_original_types; }
    };
} // namespace abrisan::trino

inline std::ostream &operator<<(std::ostream &cout,
                                abrisan::trino::Row const &row) {
    cout << "[";
    for (auto it = row.begin(); it != row.end() - 1; ++it) {
        std::visit([&](auto &&arg) { cout << arg << ", "; }, *it);
    }
    if (!row.empty()) {
        std::visit([&](auto &&arg) { cout << arg; }, row[row.size() - 1]);
    }
    cout << "]";
    return cout;
}

#endif // TRINO_LIB_RESULT_H
