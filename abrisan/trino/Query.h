//
// Created by Alexandru Brisan on 03/04/2022.
//

#ifndef TRINO_LIB_QUERY_H
#define TRINO_LIB_QUERY_H

#include <memory>
#include <ranges>
#include "Request.h"

namespace abrisan {
    namespace trino {

        using Row = std::unordered_map<std::string, std::string>;
        using Data = std::vector<Row>;

        class Query : public std::enable_shared_from_this<Query> {
            Request request;
            std::string sql;
            bool finished;
            Data data;
        private:
            std::pair<json, json> fetch();

            void process_results(std::vector<json> const &columns, std::vector<json> const &rows);

        public:
            Query(Request request, std::string sql) : request(std::move(request)), sql(std::move(sql)), finished(false) {};

            void execute(std::unordered_map<std::string, std::string> const &additional_headers = {});

            Data const &get_data() const {return this->data;}
        };

        void Query::execute(std::unordered_map<std::string, std::string> const &additional_headers) {
            cpr::Response response = this->request.post(this->sql, additional_headers);
            auto status = this->request.process(response);
            if (status.get_next_uri().empty()) {
                this->finished = true;
            }
            std::vector<json> _rows{status.get_data()};
            std::vector<json> _columns{status.get_columns()};

            while (!this->finished) {
                auto next = this->fetch();
                _rows.push_back(next.first);
                _columns.push_back(next.second);
            }
            this->process_results(_columns, _rows);
        }

        std::pair<json, json> Query::fetch() {
            auto response = this->request.get(this->request.get_next_uri());
            auto status = this->request.process(response);
            if (status.get_next_uri().empty()) {
                this->finished = true;
            }
            return std::make_pair(status.get_data(), status.get_columns());
        }

        void Query::process_results(std::vector<json> const &columns, const std::vector<json> &rows) {

            auto cols = std::find_if(columns.begin(), columns.end(), [](json const &col) {return !col.is_null();});
            if (cols == columns.end()) {
                std::cout << "Query did not return the set of columns. Cannot process" << std::endl;
                return;
            }

            for (auto const &partial_result : rows) {
                if (partial_result.is_null()) {
                    continue;
                }
                if (!partial_result.is_array()) {
                    std::cout << "Found a partial result that is not an array, it is " << partial_result << std::endl;
                    return;
                }
                for (auto const &row : partial_result) {
                    if (row.size() != cols->size()) {
                        std::cout << "Mismatch between column count and number of columns in row " << row << std::endl;
                        return;
                    }
                    Row transformed_row;
                    for (size_t idx = 0 ; idx < row.size() ; ++idx) {
                        transformed_row[to_string((*cols)[idx]["name"])] = to_string(row[idx]);
                    }
                    data.push_back(transformed_row);
                }
            }

        }
    }
}



#endif //TRINO_LIB_QUERY_H
