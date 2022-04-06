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


#ifndef TRINO_LIB_REQUEST_H
#define TRINO_LIB_REQUEST_H

#include <string>
#include <optional>
#include <sstream>
#include <unordered_map>
#include <iostream>
#include "cpr/cpr.h"
#include "TrinoJsonWrapper.h"

namespace abrisan {
    namespace trino {

        template<CompatibleHttpClient HttpClient>
        class Request {
            std::string host;
            int port;
            std::string user;
            std::unordered_map<std::string, std::string> http_headers;
        private:
            [[nodiscard]] std::string make_statement_url() const;
        public:
            Request(std::string host, int port, std::string user, std::unordered_map<std::string, std::string> http_headers = {}):
                    host(std::move(host)), port(port), user(std::move(user)), http_headers(std::move(http_headers)) {

            };
            typename HttpClient::Response post(std::string const &sql, std::unordered_map<std::string, std::string> const &additional_headers = {});
            static typename HttpClient::Response get(std::string const &url);
        };

        template<CompatibleHttpClient HttpClient>
        std::string Request<HttpClient>::make_statement_url() const {
            std::ostringstream output;
            output << "http://" << this->host <<  ":" << this->port << "/v1/statement";
            return output.str();
        }

        template<CompatibleHttpClient HttpClient>
        typename HttpClient::Response Request<HttpClient>::post(std::string const &sql, std::unordered_map<std::string, std::string> const &additional_headers) {
            std::unordered_map<std::string, std::string> _headers = http_headers;
            _headers.insert(additional_headers.begin(), additional_headers.end());


            std::string url = this->make_statement_url();

            return HttpClient::post(url, sql, _headers, user);
        }

        template<CompatibleHttpClient HttpClient>
        typename HttpClient::Response Request<HttpClient>::get(std::string const &url) {
            return HttpClient::get(url);
        }
    }
}


#endif //TRINO_LIB_REQUEST_H
