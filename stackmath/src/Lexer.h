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

#ifndef STACKMATH_LEXER_H
#define STACKMATH_LEXER_H

#include <istream>
#include <vector>
#include <optional>

#include <string_view>
#include <unordered_map>

namespace sm
{

    class Lexer
    {
      public:
        /**
         * @brief ALL lexer opcodes.
         */
        enum class Opcode
        {
            DUP,
            MUL,
            SWAP,
            ADD,
            OVER,
            SIN,
            COS,
            STOP
        };

        /**
         * @brief Type of input opcodes table.
         */
        using opcodes_table_type = std::unordered_map<std::string_view, sm::Lexer::Opcode>;

        /**
         * @brief Lexer gets some input-stream. It can be file or std::cin.
         */
        Lexer(std::istream& stream, const opcodes_table_type& table) : m_input(stream), m_opcodes_table(table) {}

        /**
         * @brief Reads ONE opcode form input stream. Throws sm::LexerException if can't find instruction name.
         *
         * @return std::nullopt on EOF.
         */
        std::optional<Opcode> readOne();

        /**
         * @brief Reads ALL possible opcodes from input stream.
         *
         * @return All read op-codes.
         */
        std::vector<Opcode> readAll();

        auto getLinesNum() const { return m_nlines; }

      private:
        /**
         * @brief Number of successfully read lines.
         */
        size_t m_nlines = 0;

        std::istream& m_input;
        const opcodes_table_type& m_opcodes_table;
    };
}

#endif //STACKMATH_LEXER_H
