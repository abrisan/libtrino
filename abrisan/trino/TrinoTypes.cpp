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

#include "TrinoTypes.h"

namespace abrisan::trino {

    SupportedTrinoTypes parseTypeSignature(std::string const &raw_type) {
        if (raw_type == "varchar") {
            return SupportedTrinoTypes::VARCHAR;
        }
        return SupportedTrinoTypes::VARCHAR;
    }

    TrinoValue convert_to_cpp_type(std::string const &value,
                                   SupportedTrinoTypes type) {
        switch (type) {
            case (SupportedTrinoTypes::BOOLEAN):
                return TrinoTypesCppTraits<SupportedTrinoTypes::BOOLEAN>::parse(value);
            case SupportedTrinoTypes::TINYINT:
                return TrinoTypesCppTraits<SupportedTrinoTypes::TINYINT>::parse(value);
            case SupportedTrinoTypes::SMALLINT:
                return TrinoTypesCppTraits<SupportedTrinoTypes::SMALLINT>::parse(value);
            case SupportedTrinoTypes::INTEGER:
                return TrinoTypesCppTraits<SupportedTrinoTypes::INTEGER>::parse(value);
            case SupportedTrinoTypes::BIGINT:
                return TrinoTypesCppTraits<SupportedTrinoTypes::BIGINT>::parse(value);
            case SupportedTrinoTypes::REAL:
                return TrinoTypesCppTraits<SupportedTrinoTypes::REAL>::parse(value);
            case SupportedTrinoTypes::DOUBLE:
                return TrinoTypesCppTraits<SupportedTrinoTypes::DOUBLE>::parse(value);
            case SupportedTrinoTypes::VARCHAR:
                return TrinoTypesCppTraits<SupportedTrinoTypes::VARCHAR>::parse(value);
            case SupportedTrinoTypes::CHAR:
                return TrinoTypesCppTraits<SupportedTrinoTypes::CHAR>::parse(value);
            case SupportedTrinoTypes::VARBINARY:
                return TrinoTypesCppTraits<SupportedTrinoTypes::VARBINARY>::parse(value);
        }
    }
} // namespace abrisan::trino
