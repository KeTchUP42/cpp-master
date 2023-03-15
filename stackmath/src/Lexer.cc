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

#include <Lexer.h>

#include <iostream>
#include <exception>
#include <string>

#include <trim.h>
#include <LexerException.h>

std::optional<sm::Lexer::Opcode> sm::Lexer::readOne()
{
    std::string opcode; //I don't care about "all time" string memory alloc because of SSO.
    if (std::getline(m_input, opcode))
    {
        trim(opcode);

        sm::Lexer::Opcode iopcode;
        try
        {
            iopcode = m_opcodes_table.at(std::string_view(opcode.c_str()));
        }
        catch (const std::out_of_range& e)
        {
            //Avoiding one memory allocation.
            throw LexerException(std::move(std::to_string(m_nlines + 1).insert(0, "SYNTAX ERROR IN LINE: ")));
        }
        ++m_nlines;
        return iopcode;
    }

    return std::nullopt;
}

std::vector<sm::Lexer::Opcode> sm::Lexer::readAll()
{
    std::optional<Lexer::Opcode> opcode;
    std::vector<Opcode> opcodes;

    while (true)
    {
        opcode = readOne();

        if (!opcode.has_value()) break;
        opcodes.push_back(opcode.value());
    }

    return opcodes;
}
