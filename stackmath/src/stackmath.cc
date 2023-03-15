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

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstring>
#include <fstream>

#include <Lexer.h>
#include <LexerException.h>
#include <opcodes.h>
#include <Executor.h>

int main (int argc, const char* argv[])
{
    if (argc < 2)
    {
        std::cout << "No enough args! Try -h or --help to see docs.\n";
        return EXIT_FAILURE;
    }

    if ((std::strcmp(argv[1], "-h") == 0) || (std::strcmp(argv[1], "--help") == 0))
    {
        std::cout << "How to use:\n"
                  << "stackmath [-h/--help] INIT_VALUE - if you want type commands by yourself.\n"
                  << "stackmath [-h/--help] INIT_VALUE < formule.sm - if you want read them from file.\n\n"
                  << "If INIT_VALUE cannot be read correctly, it will be taken as ZERO!\n";
        return EXIT_SUCCESS;
    }

    auto inputValue = std::strtof(argv[1], nullptr);

    try
    {
        sm::Lexer lx(std::cin, sm::OpcodeTable::basic());
        sm::Executor exe(lx.readAll());

        exe.getMemory().push_back(inputValue);

        if (exe.execute() != sm::Executor::Code::STOP_CODE)
        {
            std::cout << "RUNTIME ERROR[PC:" << exe.getPC() << "]\n";
            return EXIT_FAILURE;
        }

        auto& memory = exe.getMemory();

        if (memory.size() != 0)
            std::cout << "STACK-MEMORY TOP: " << memory.back() << '\n';

        return EXIT_SUCCESS;
    }
    catch (const sm::LexerException& e)
    {
        std::cout << e.what() << '\n';
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << '\n';
    }
    catch (...)
    {
        std::cout << "PROGRAM PANIC!\n";
    }

    return EXIT_FAILURE;
}
