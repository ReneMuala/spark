//
// Created by dte on 3/4/2025.
//
#include "jit.hpp"

namespace jit
{
    std::shared_ptr<asmjit::JitRuntime> rt = std::make_shared<asmjit::JitRuntime>();
    std::stack<value_t> stack;
    std::stack<std::shared_ptr<function_builder>> builders;
    std::stack<scope_t> scopes;

    void init()
    {
        builders.push(function_builder::create(rt, asmjit::FuncSignature::build<void>()));
    }

    std::shared_ptr<function_builder> builder()
    {
        return builders.top();
    }

    scope_t& scope()
    {
        return scopes.top();
    }

    void push_builder(const std::string& name, const asmjit::FuncSignature& signature)
    {
        builders.push(function_builder::create(rt, signature));
        scopes.emplace(scope_t{.name = name});
    }

    void pop_builder()
    {
        builders.pop();
        scopes.pop();
    }

    void insn_mult()
    {
        const auto rhs = stack.top();
        stack.pop();
        const auto lhs = stack.top();
        stack.pop();
        if (rhs.index() == lhs.index())
        {
            if (std::holds_alternative<jit::XmmWrapper>(lhs))
            {
                auto r = builder()->f64();
                builder()->mul(r, std::get<decltype(r)>(lhs), std::get<decltype(r)>(rhs));
                stack.emplace(r);
            } else if (std::holds_alternative<asmjit::x86::Gp>(lhs))
            {
                auto r = builder()->i32();
                builder()->mul(r, std::get<decltype(r)>(lhs), std::get<decltype(r)>(rhs));
                stack.emplace(r);
            }
        }
    }

    void insn_div()
    {
        const auto rhs = stack.top();
        stack.pop();
        const auto lhs = stack.top();
        stack.pop();
        if (rhs.index() == lhs.index())
        {
            if (std::holds_alternative<jit::XmmWrapper>(lhs))
            {
                auto r = builder()->f64();
                builder()->div(r, std::get<decltype(r)>(lhs), std::get<decltype(r)>(rhs));
                stack.emplace(r);
            } else if (std::holds_alternative<asmjit::x86::Gp>(lhs))
            {
                auto r = builder()->i32();
                builder()->div(r, std::get<decltype(r)>(lhs), std::get<decltype(r)>(rhs));
                stack.emplace(r);
            }
        }
    }

    void insn_add()
    {
        const auto rhs = stack.top();
        stack.pop();
        const auto lhs = stack.top();
        stack.pop();
        if (rhs.index() == lhs.index())
        {
            if (std::holds_alternative<jit::XmmWrapper>(lhs))
            {
                auto r = builder()->f64();
                builder()->add(r, std::get<decltype(r)>(lhs), std::get<decltype(r)>(rhs));
                stack.emplace(r);
            } else if (std::holds_alternative<asmjit::x86::Gp>(lhs))
            {
                auto r = builder()->i32();
                builder()->add(r, std::get<decltype(r)>(lhs), std::get<decltype(r)>(rhs));
                stack.emplace(r);
            }
        }
    }

    void insn_sub()
    {
        const auto rhs = stack.top();
        stack.pop();
        const auto lhs = stack.top();
        stack.pop();
        if (rhs.index() == lhs.index())
        {
            if (std::holds_alternative<jit::XmmWrapper>(lhs))
            {
                auto r = builder()->f64();
                builder()->sub(r, std::get<decltype(r)>(lhs), std::get<decltype(r)>(rhs));
                stack.emplace(r);
            } else if (std::holds_alternative<asmjit::x86::Gp>(lhs))
            {
                auto r = builder()->i32();
                builder()->sub(r, std::get<decltype(r)>(lhs), std::get<decltype(r)>(rhs));
                stack.emplace(r);
            }
        }
    }
}
