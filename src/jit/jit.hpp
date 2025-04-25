//
// Created by dte on 3/4/2025.
//

#pragma once
#include <asmjit/asmjit.h>
#include <unordered_map>
#include <variant>
#include <stack>
#include <string>
#include <supernova/src/jit/function.hpp>

namespace jit
{
    using namespace supernova::jit;
    typedef std::variant<asmjit::x86::Gp, XmmWrapper> value_t;
    struct scope_t
    {
        std::string name;
        std::unordered_map<std::string, value_t> variables;
        std::unordered_map<std::string, value_t> constants;
    };

    extern std::stack<value_t> stack;
    extern std::stack<std::shared_ptr<function_builder>> builders;
    extern std::stack<scope_t> scopes;

    void init();
    inline std::shared_ptr<function_builder> builder();
    inline scope_t& scope();
    inline void push_builder(const std::string& name, const asmjit::FuncSignature& signature);
    inline void pop_builder();

    inline void insn_mult();
    inline void insn_div();
    inline void insn_add();
    inline void insn_sub();
}
