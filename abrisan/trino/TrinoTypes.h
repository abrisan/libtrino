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


#ifndef TRINO_LIB_TRINOTYPES_H
#define TRINO_LIB_TRINOTYPES_H

#include <string>
#include <variant>

namespace abrisan::trino {

    using TrinoValue = std::variant<bool, long long, float, double, std::string>;

    enum SupportedTrinoTypes {
        BOOLEAN,
        TINYINT,
        SMALLINT,
        INTEGER,
        BIGINT,
        REAL,
        DOUBLE,
        VARCHAR,
        CHAR,
        VARBINARY
    };

    SupportedTrinoTypes parseTypeSignature(std::string const &raw_type);

    TrinoValue convert_to_cpp_type(std::string const &value, SupportedTrinoTypes type);

    template<SupportedTrinoTypes type>
    struct TrinoTypesCppTraits {
    public:
        template<typename CType>
        using CorrespondingType = CType;

        template<typename CType>
        static CorrespondingType<CType> parse(std::string const &value);
    };

    template<>
    struct TrinoTypesCppTraits<SupportedTrinoTypes::BOOLEAN> {
    public:
        using CorrespondingType = bool;

        static bool parse(std::string const &value) {
            return value == "true";
        }
    };

    template<>
    struct TrinoTypesCppTraits<SupportedTrinoTypes::TINYINT> {
    public:
        using CorrespondingType = long long;

        static long long parse(std::string const &value) {
            return std::stoll(value);
        }
    };

    template<>
    struct TrinoTypesCppTraits<SupportedTrinoTypes::SMALLINT> {
    public:
        using CorrespondingType = long long;

        static long long parse(std::string const &value) {
            return std::stoll(value);
        }
    };

    template<>
    struct TrinoTypesCppTraits<SupportedTrinoTypes::INTEGER> {
    public:
        using CorrespondingType = long long;

        static long long parse(std::string const &value) {
            return std::stoll(value);
        }
    };

    template<>
    struct TrinoTypesCppTraits<SupportedTrinoTypes::BIGINT> {
    public:
        using CorrespondingType = long long;

        static long long parse(std::string const &value) {
            return std::stoll(value);
        }
    };

    template<>
    struct TrinoTypesCppTraits<SupportedTrinoTypes::REAL> {
    public:
        using CorrespondingType = float;

        static float parse(std::string const &value) {
            return std::stof(value);
        }
    };

    template<>
    struct TrinoTypesCppTraits<SupportedTrinoTypes::DOUBLE> {
    public:
        using CorrespondingType = double;

        static double parse(std::string const &value) {
            return std::stod(value);
        }
    };

    template<>
    struct TrinoTypesCppTraits<SupportedTrinoTypes::VARCHAR> {
    public:
        using CorrespondingType = std::string;

        static std::string parse(std::string const &value) {
            return value;
        }
    };

    template<>
    struct TrinoTypesCppTraits<SupportedTrinoTypes::CHAR> {
    public:
        using CorrespondingType = std::string;

        static std::string parse(std::string const &value) {
            return value;
        }
    };

    template<>
    struct TrinoTypesCppTraits<SupportedTrinoTypes::VARBINARY> {
    public:
        using CorrespondingType = std::string;

        static std::string parse(std::string const &value) {
            return value;
        }
    };
}


#endif //TRINO_LIB_TRINOTYPES_H
