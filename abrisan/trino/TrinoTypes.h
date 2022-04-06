//
// Created by Alexandru Brisan on 03/04/2022.
//

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
