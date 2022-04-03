//
// Created by Alexandru Brisan on 03/04/2022.
//

#ifndef TRINO_LIB_STATUS_H
#define TRINO_LIB_STATUS_H

#include <string>
#include "TrinoJsonWrapper.h"

namespace abrisan {
    namespace trino {
        class Status {
            std::string id;
            std::string info_uri;
            std::string next_uri;
            json data;
            json columns;
        public:
            Status(std::string id, std::string info_uri, std::string next_uri, json data, json columns):
                    id(std::move(id)), info_uri(std::move(info_uri)), next_uri(std::move(next_uri)), data(std::move(data)), columns(std::move(columns)) {};

            [[nodiscard]] std::string const &get_id() const {return this->id;}
            [[nodiscard]] std::string const &get_info_uri() const {return this->info_uri;}
            [[nodiscard]] std::string const &get_next_uri() const {return this->next_uri;}
            [[nodiscard]] json const &get_data() const {return this->data;}
            [[nodiscard]] json const &get_columns() const {return this->columns;}
        };
    }
}



#endif //TRINO_LIB_STATUS_H
