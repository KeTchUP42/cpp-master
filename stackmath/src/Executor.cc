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

#include <Executor.h>

#include <vector>
#include <cmath>

sm::Executor::Code sm::Executor::step()
{
    auto opSize = m_opcodes.size();
    auto memoryStackSize = m_stack_memory.size();

    if (opSize == 0) return Code::PC_OVERFLOW_ERROR;
    if (m_pc > opSize - 1) return Code::PC_OVERFLOW_ERROR;

    switch (m_opcodes[m_pc])
    {
        case Lexer::Opcode::DUP:
            if (memoryStackSize < 1)
                return Code::NO_ARGS_ERROR;
            else
            {
                m_stack_memory.push_back(m_stack_memory.back());
                ++m_pc;
            }
            break;


        case Lexer::Opcode::MUL:
            if (memoryStackSize < 2)
                return Code::NO_ARGS_ERROR;
            else
            {
                auto arg1 = m_stack_memory.back();
                m_stack_memory.pop_back();
                auto arg2 = m_stack_memory.back();
                //m_stack_memory.pop_back();
                m_stack_memory.back() = arg1 * arg2;

                //m_stack_memory.push_back(arg1 * arg2);
                ++m_pc;
            }
            break;


        case Lexer::Opcode::SWAP:
            if (memoryStackSize < 2)
                return Code::NO_ARGS_ERROR;
            else
            {
                std::swap(m_stack_memory[memoryStackSize - 1], m_stack_memory[memoryStackSize - 2]);
                ++m_pc;
            }
            break;


        case Lexer::Opcode::ADD:
            if (memoryStackSize < 2)
                return Code::NO_ARGS_ERROR;
            else
            {
                auto arg1 = m_stack_memory.back();
                m_stack_memory.pop_back();
                auto arg2 = m_stack_memory.back();
                //m_stack_memory.pop_back();
                m_stack_memory.back() = arg1 + arg2;

                //m_stack_memory.push_back(arg1 + arg2);
                ++m_pc;
            }
            break;


        case Lexer::Opcode::OVER:
            if (memoryStackSize < 2)
                return Code::NO_ARGS_ERROR;
            else
            {
                m_stack_memory.push_back(m_stack_memory[memoryStackSize - 2]);
                ++m_pc;
            }
            break;


        case Lexer::Opcode::SIN:
            if (memoryStackSize < 1)
                return Code::NO_ARGS_ERROR;
            else
            {
                auto arg1 = m_stack_memory.back();
                m_stack_memory.back() = std::sin(arg1);
                ++m_pc;
            }
            break;


        case Lexer::Opcode::COS:
            if (memoryStackSize < 1)
                return Code::NO_ARGS_ERROR;
            else
            {
                auto arg1 = m_stack_memory.back();
                m_stack_memory.back() = std::cos(arg1);
                ++m_pc;
            }
            break;


        case Lexer::Opcode::STOP:
            return Code::STOP_CODE;

        default:
            return Code::OPCODE_ERROR;
    }

    return Code::NO_ERROR;
}

sm::Executor::Code sm::Executor::execute()
{
    Code ret_code;
    while (true)
    {
        ret_code = step();
        if (ret_code != Code::NO_ERROR)
            return ret_code;
    }
}
