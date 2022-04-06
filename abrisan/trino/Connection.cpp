//
// Created by Alexandru Brisan on 04/04/2022.
//

#include "Connection.h"
#include "Request.h"


using namespace abrisan::trino;

void Connection::execute(std::string const &sql, Result &out, HttpHeaders const &additional_headers) {
    Request request(this->host, this->port, this->user, this->http_headers);
    cpr::Response response = request.post(sql, additional_headers);
    auto next_uri = Connection::processPartialResponse(response, out);
    while (next_uri.has_value()) {
        response = request.get(next_uri.value());
        next_uri = Connection::processPartialResponse(response, out);
    }
}

void parseColumns(json const &columns, Result &result) {
    if (columns.is_null() || !result.columns().first.empty()) {
        return;
    }
    for (size_t idx = 0 ; idx < columns.size() ; ++idx) {
        auto as_string = columns[idx]["name"];
        result.columns().first[as_string] = idx;
        result.columns().second.push_back(as_string);
        result.typeMappings()[as_string] = parseTypeSignature(columns[idx]["typeSignature"]["rawType"]);
    }
}

void parseRows(json const &rows, Result &result) {
    if (rows.is_null()) {
        return;
    }
    if (!rows.is_array()) {
        std::cout << "Found a row set that is not an array. It is " << rows << std::endl;
        return;
    }

    for (auto const &row : rows) {
        if (row.size() != result.columns().first.size()) {
            std::cout << "Mismatch between column count and number of columns in row " << row << std::endl;
            return;
        }
        Row transformed_row;
        size_t idx = 0;
        for (auto const &value : row) {
            std::string as_string = value;
            auto trino_type = result.typeMappings()[result.columns().second[idx]];
            transformed_row.push_back(convert_to_cpp_type(as_string, trino_type));
            ++idx;
        }
        result.rows().push_back(transformed_row);
    }
}

std::optional<std::string> Connection::processPartialResponse(const cpr::Response &partialResponse, Result &result) {
    std::optional<std::string> return_value;

    auto data_as_json = json::parse(partialResponse.text);

    if (!data_as_json["nextUri"].is_null()) {
        return_value = data_as_json["nextUri"];
    }

    parseColumns(data_as_json["columns"], result);
    parseRows(data_as_json["data"], result);

    return return_value;
}