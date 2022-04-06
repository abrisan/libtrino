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