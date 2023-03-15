/* Copyright (C) 2023 Roman Bondarenko
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the “Software“), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED “AS IS“, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 * 
 */

#ifndef STACKMATH_TRIM_H
#define STACKMATH_TRIM_H

#include <algorithm>
#include <locale>

namespace sm {

    /**
     * Trim from start (in place)
     * @param str String to ltrim
     */
    static inline void ltrim(std::string &str) {
        str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](int ch) {
            return !std::isspace(ch);
        }));
    }

    /**
     * Trim from end (in place)
     * @param str String to rtrim
     */
    static inline void rtrim(std::string &str) {
        str.erase(std::find_if(str.rbegin(), str.rend(), [](int ch) {
            return !std::isspace(ch);
        }).base(), str.end());
    }

    /**
     * Trim from both ends (in place)
     * @param str String to trim
     */
    static inline void trim(std::string &str) {
        ltrim(str);
        rtrim(str);
    }

    /**
     * Trim from start (copying)
     * @param str String to ltrim_copy
     * @return
     */
    static inline std::string ltrim_copy(std::string str) {
        ltrim(str);
        return str;
    }

    /**
     * Trim from end (copying)
     * @param str String to rtrim_copy
     * @return
     */
    static inline std::string rtrim_copy(std::string str) {
        rtrim(str);
        return str;
    }
}

#endif //STACKMATH_TRIM_H

