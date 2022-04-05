//
// Created by Alexandru Brisan on 03/04/2022.
//

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
