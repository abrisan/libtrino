#include <gtest/gtest.h>
#include "abrisan/trino/Connection.h"

using namespace abrisan;

TEST(libtrino_integration_tests, can_get_result) {
    // GIVEN
    trino::Connection conn("trino", 8080, trino::Scheme::HTTP, {}, "user");
    trino::Result res;

    // WHEN
    conn.execute("SHOW CATALOGS", res);

    // THEN
    std::vector<trino::Row> expected_rows = {
            { trino::TrinoValue("jmx") },
            { trino::TrinoValue("memory") },
            { trino::TrinoValue("system") },
            { trino::TrinoValue("tpcds") },
            { trino::TrinoValue("tpch") }
    };
    EXPECT_EQ(res.rows(), expected_rows);
}