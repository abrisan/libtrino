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

#ifndef TRINO_LIB_CONNECTION_H
#define TRINO_LIB_CONNECTION_H

#include "Result.h"
#include <string>
#include <utility>
#include <cpr/cpr.h>
#include <optional>

namespace abrisan {
    namespace trino {

        using HttpHeaders = std::unordered_map<std::string, std::string>;

        enum Scheme {
            HTTP,
            HTTPS
        };

        class Connection {
            std::string host;
            int port;
            Scheme scheme;
            std::unordered_map<std::string, std::string>  http_headers;
            std::string user;
        private:
            static std::optional<std::string> processPartialResponse(cpr::Response const &partialResponse, Result &result);
        public:
            Connection(std::string host, int port, Scheme scheme, HttpHeaders http_headers, std::string user) :
                    host(std::move(host)), port(port), scheme(scheme), http_headers(std::move(http_headers)), user(std::move(user)) {};

            void execute(std::string const &sql, Result &result, HttpHeaders const &additionalHeaders = {});
        };
    }
}



#endif //TRINO_LIB_CONNECTION_H
