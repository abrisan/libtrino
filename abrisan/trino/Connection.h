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

#ifndef TRINO_LIB_CONNECTION_H
#define TRINO_LIB_CONNECTION_H

#include "CompatibleHttpClient.h"
#include "DefaultHttpClient.h"
#include "Request.h"
#include "Result.h"
#include <cpr/cpr.h>
#include <optional>
#include <string>
#include <utility>

namespace abrisan {
    namespace trino {

        using HttpHeaders = std::unordered_map<std::string, std::string>;

        enum Scheme {
            HTTP, HTTPS
        };

        template<CompatibleHttpClient HttpClient = DefaultHttpClient>
        class Connection {
            static_assert(CompatibleHttpClient<HttpClient>);

            std::string host;
            int port;
            Scheme scheme;
            std::unordered_map<std::string, std::string> http_headers;
            std::string user;

        private:
            using Response = typename HttpClient::Response;

            static void parseColumns(json const &columns, Result &result) {
                if (columns.is_null() || !result.columns().first.empty()) {
                    return;
                }
                for (size_t idx = 0; idx < columns.size(); ++idx) {
                    auto as_string = columns[idx]["name"];
                    result.columns().first[as_string] = idx;
                    result.columns().second.push_back(as_string);
                    result.typeMappings()[as_string] =
                            parseTypeSignature(columns[idx]["typeSignature"]["rawType"]);
                }
            }

            static void parseRows(json const &rows, Result &result) {
                if (rows.is_null()) {
                    return;
                }
                if (!rows.is_array()) {
                    std::cout << "Found a row set that is not an array. It is " << rows
                              << std::endl;
                    return;
                }

                for (auto const &row: rows) {
                    if (row.size() != result.columns().first.size()) {
                        std::cout
                                << "Mismatch between column count and number of columns in row "
                                << row << std::endl;
                        return;
                    }
                    Row transformed_row;
                    size_t idx = 0;
                    for (auto const &value: row) {
                        std::string as_string = value;
                        auto trino_type = result.typeMappings()[result.columns().second[idx]];
                        transformed_row.push_back(convert_to_cpp_type(as_string, trino_type));
                        ++idx;
                    }
                    result.rows().push_back(transformed_row);
                }
            }

            static std::optional<std::string>
            processPartialResponse(Response const &partialResponse, Result &result) {
                std::optional<std::string> return_value;

                auto data_as_json = json::parse(partialResponse.text);

                if (!data_as_json["nextUri"].is_null()) {
                    return_value = data_as_json["nextUri"];
                }

                Connection<HttpClient>::parseColumns(data_as_json["columns"], result);
                Connection<HttpClient>::parseRows(data_as_json["data"], result);

                return return_value;
            }

        public:
            Connection(std::string host, int port, Scheme scheme,
                       HttpHeaders http_headers, std::string user)
                    : host(std::move(host)), port(port), scheme(scheme),
                      http_headers(std::move(http_headers)), user(std::move(user)) {};

            void execute(std::string const &sql, Result &result,
                         HttpHeaders const &additionalHeaders = {}) {
                static_assert(CompatibleHttpClient<HttpClient>);
                Request<HttpClient> request(this->host, this->port, this->user,
                                            this->http_headers);
                Response response = request.post(sql, additionalHeaders);
                auto next_uri = Connection::processPartialResponse(response, result);
                while (next_uri.has_value()) {
                    response = request.get(next_uri.value());
                    next_uri = Connection::processPartialResponse(response, result);
                }
            }
        };
    } // namespace trino
} // namespace abrisan

#endif // TRINO_LIB_CONNECTION_H
