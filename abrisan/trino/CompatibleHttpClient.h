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

#ifndef LIBTRINO_COMPATIBLEHTTPCLIENT_H
#define LIBTRINO_COMPATIBLEHTTPCLIENT_H

#include <concepts>
#include <unordered_map>

namespace abrisan::trino {

    template<typename T>
    concept CompatibleHttpClient = requires(
            std::string const &url, std::string const &sql, std::string const &user,
            std::unordered_map<std::string, std::string> const &headers) {

        typename T::Response;

        { T::post(url, sql, headers, user) } -> std::same_as<typename T::Response>;
        { T::get(url) } -> std::same_as<typename T::Response>;
    };

} // namespace abrisan::trino

#endif // LIBTRINO_COMPATIBLEHTTPCLIENT_H
