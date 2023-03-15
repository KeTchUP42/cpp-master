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

#ifndef STACKMATH_EXECUTOR_H
#define STACKMATH_EXECUTOR_H

#include <optional>
#include <vector>

#include <Lexer.h>

namespace sm
{

    class Executor
    {
      public:
        using memory_cell_type = float;
        using pc_type = size_t;

        enum class Code
        {
            NO_ERROR,
            NO_ARGS_ERROR,
            PC_OVERFLOW_ERROR,
            STOP_CODE,
            OPCODE_ERROR
        };

        explicit Executor(const std::vector<Lexer::Opcode>& opcodes) : m_opcodes(opcodes) {}
        explicit Executor(std::vector<Lexer::Opcode>&& opcodes) : m_opcodes(std::move(opcodes)) {}

        /**
         * @brief Execute ONLY ONE instruction.
         *
         * @return Result status-code.
         */
        Code step();

        /**
         * @brief Execute ALL instructions.
         *
         * @return Result status-code.
         */
        Code execute();

        /**
         * @brief This function gives FULL control over the memory.
         *
         * @return l-value ref to memory.
         */
        auto& getMemory() { return m_stack_memory; }

        void setMemory(const std::vector<memory_cell_type>& memory) { m_stack_memory = memory; }
        void setMemory(std::vector<memory_cell_type>&& memory) { m_stack_memory = std::move(memory); }


        /**
         * @brief This function gives FULL control over the opcodes memory.
         *
         * @return l-value ref to opcodes memory.
         */
        auto& getOpcodes() { return m_opcodes; }


        /**
         * @brief m_pc getter.
         *
         * @return
         */
        pc_type getPC() const { return m_pc; }

        /**
         * @brief m_pc setter.
         *
         * @param pc
        */
        void setPC(pc_type pc) { m_pc = pc; }

      private:
        std::vector<Lexer::Opcode> m_opcodes;
        pc_type m_pc = 0;
        std::vector<memory_cell_type> m_stack_memory;
    };
}

#endif //STACKMATH_EXECUTOR_H
