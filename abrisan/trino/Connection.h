//
// Created by Alexandru Brisan on 03/04/2022.
//

#ifndef TRINO_LIB_CONNECTION_H
#define TRINO_LIB_CONNECTION_H

#include <string>
#include <utility>

namespace abrisan {
    namespace trino {
        class Connection {
            std::string host;
            int port;
        public:
            Connection(std::string host, int port) :
                    host(std::move(host)), port(port) {};

        };
    }
}



#endif //TRINO_LIB_CONNECTION_H
