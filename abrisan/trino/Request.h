//
// Created by Alexandru Brisan on 03/04/2022.
//

#ifndef TRINO_LIB_REQUEST_H
#define TRINO_LIB_REQUEST_H

#include <string>
#include <optional>
#include <sstream>
#include <unordered_map>
#include <iostream>
#include "cpr/cpr.h"
#include "Status.h"
#include "TrinoJsonWrapper.h"

namespace abrisan {
    namespace trino {

        class Request {
            std::string host;
            int port;
            std::string user;
            std::optional<std::unordered_map<std::string, std::string>> http_headers;
            std::string next_uri;
        private:
            [[nodiscard]] std::string make_statement_url() const;
        public:
            Request(std::string host, int port, std::string user, std::optional<std::unordered_map<std::string, std::string>> http_headers = {}):
                    host(std::move(host)), port(port), user(std::move(user)), http_headers(std::move(http_headers)) {

            };
            cpr::Response post(std::string const &sql, std::optional<std::unordered_map<std::string, std::string>> const &additional_headers = {});
            static cpr::Response get(std::string const &url);
            Status process(cpr::Response const &response);
            [[nodiscard]] std::string get_next_uri() const { return this->next_uri; }
        };

        std::string Request::make_statement_url() const {
            std::ostringstream output;
            output << "http://" << this->host <<  ":" << this->port << "/v1/statement";
            return output.str();
        }

        cpr::Response Request::post(std::string const &sql, std::optional<std::unordered_map<std::string, std::string>> const &additional_headers) {
            cpr::Header headers;
            if (http_headers) {
                auto _http_headers = this->http_headers.value();
                headers.insert(_http_headers.begin(), _http_headers.end());
            }
            if (additional_headers) {
                auto _http_headers = additional_headers.value();
                headers.insert(_http_headers.begin(), _http_headers.end());
            }

            std::string url = this->make_statement_url();
            cpr::Response r = cpr::Post(cpr::Url{url},
                                        cpr::Body{sql},
                                        headers,
                                        cpr::Authentication{user, ""});
            return r;
        }

        cpr::Response Request::get(std::string const &url) {
            return cpr::Get(cpr::Url(url));
        }

        Status Request::process(cpr::Response const &response) {
            auto data_as_json = json::parse(response.text);

            if (data_as_json["nextUri"].is_null()) {
                this->next_uri = "";
            }
            else {
                this->next_uri = data_as_json["nextUri"];
            }


            return {data_as_json["id"], data_as_json["infoUri"], this->next_uri, data_as_json["data"], data_as_json["columns"]};
        }
    }
}


#endif //TRINO_LIB_REQUEST_H
