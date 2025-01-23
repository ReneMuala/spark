//
// Created by dte on 1/22/2025.
//

#include "lexer.hpp"

#include <iostream>
#include <optional>
#include <exceptions/expected_token.hpp>

spark::lexer::lexer(const std::string&& filename)
{
    stream.open(filename);
    if (not stream.is_open())
    {
        throw exceptions::file_not_found(filename);
    }
    lit = it = 0;
    line = col = 1;
}

spark::token spark::lexer::next_int_or_double()
{
    std::string value;
    auto type = enums::TINT_NUM;
    restart:
    do
    {
        value += it;
        getchar();
    } while (isdigit(it));
    if (it == '.' and type == enums::TINT_NUM)
    {
        type = enums::TDOUBLE_NUM;
        goto restart;
    }
    return token(type, std::move(value));
}

spark::token spark::lexer::next_string()
{
    std::string value;
    do
    {
        getchar();
        if (stream.eof())
            throw exceptions::expected_token("\"", line, col);
        if (lit == '\\')
        {
            value.pop_back();
            if (it == 'n')
                value += '\n';
            else if (it == 't')
                value += '\t';
            else if (it == 'r')
                value += '\r';
            else if (it == '\\')
            {
                value += '\\';
                it = 0; // avoid lit being == '\\'
            }
            else if (it == '"')
                value += '"';
        } else
            value += it;
    } while (it != '"' or  lit == '\\');
    getchar();
    value.pop_back();
    return token(enums::TCHAR_ARRAY, std::move(value));
}

spark::token spark::lexer::next_equ_or_equal()
{
    auto type = enums::TEQU;
    getchar();
    if(it == '=')
    {
        type = enums::TEQUAL;
        getchar();
    }
    return token(type);
}

spark::token spark::lexer::next_single(const enums::token_type&& type)
{
    getchar();
    return token(type);
}

spark::token spark::lexer::next_not_equal()
{
    std::string value;
    auto type = enums::TERROR;
    value += it;
    getchar();
    if(it == '=')
    {
        type = enums::TNOT_EQUAL;
        getchar();
    }
    return type == enums::TERROR ? token(type, std::move(value)) : token(type);
}

spark::token spark::lexer::next_greater_or_greater_equal()
{
    auto type = enums::TGREATER;
    getchar();
    if(it == '=')
    {
        type = enums::TGREATER_OR_EQUAL;
        getchar();
    }
    return token(type);
}

spark::token spark::lexer::next_lower_or_lower_equal()
{
    auto type = enums::TLOWER;
    getchar();
    if(it == '=')
    {
        type = enums::TLOWER_OR_EQUAL;
        getchar();
    }
    return token(type);
}

spark::token spark::lexer::next_plus_or_plus_plus_or_plus_equal()
{
    auto type = enums::TPLUS;
    getchar();
    if(it == '=')
    {
        type = enums::TPLUS_EQU;
        getchar();
    } else if(it == '+')
    {
        type = enums::TPLUS_PLUS;
        getchar();
    }
    return token(type);
}

spark::token spark::lexer::next_minus_or_minus_minus_or_minus_equal()
{
    std::string value;
    auto type = enums::TMINUS;
    getchar();
    if(it == '=')
    {
        type = enums::TMINUS_EQU;
        getchar();
    } else if(it == '-')
    {
        type = enums::TMINUS_MINUS;
        getchar();
    }

    return token(type);
}

spark::token spark::lexer::next_times_or_times_equal()
{
    auto type = enums::TTIMES;
    getchar();
    if(it == '=')
    {
        type = enums::TTIMES_EQU;
        getchar();
    }
    return token(type);
}

spark::token spark::lexer::next_modulo_or_modulo_equal()
{
    auto type = enums::TMODULO;
    getchar();
    if(it == '=')
    {
        type = enums::TMODULO_EQU;
        getchar();
    }
    return token(type);
}

spark::token spark::lexer::next_slash_or_slash_equal_or_comment()
{
    auto type = enums::TSLASH;
    getchar();
    if(it == '=')
    {
        type = enums::TSLASH_EQU;
        getchar();
    } else if (it == '/')
    {
        type = enums::TCOMMENT;
        do
            getchar();
        while(it != '\n' and not stream.eof());
    } else if (it == '*')
    {
        int depth = 1;
        type = enums::TCOMMENT;
        do
        {
            getchar();
            if (stream.eof())
                throw exceptions::expected_token("*/", line, col);
            if (lit == '/' and it == '*') depth++;
            else if (lit == '*' and it == '/') depth--;
        } while(depth);
        getchar();
    }
    return token(type);
}

spark::token spark::lexer::next_id_or_keyword()
{
    std::string value;
    auto type = enums::TID;
    do
    {
        value+=it;
        getchar();
    } while (isalnum(it));

    // for, while, if, else, fun, type, mut, yield, when, init, this, object
    if (value.length() >= 2 and value.length() <= 5)
    {
        if (value == "and")
            type = enums::TKEY_AND;
        else if (value == "or")
            type = enums::TKEY_OR;
        else if (value == "not")
            type = enums::TKEY_NOT;
        else if (value == "for")
            type = enums::TKEY_FOR;
        else if (value == "while")
            type = enums::TKEY_WHILE;
        else if (value == "if")
            type = enums::TKEY_IF;
        else if (value == "else")
            type = enums::TKEY_ELSE;
        else if (value == "fun")
            type = enums::TKEY_FUN;
        else if (value == "type")
            type = enums::TKEY_TYPE;
        else if (value == "mut")
            type = enums::TKEY_MUT;
        else if (value == "yield")
            type = enums::TKEY_YIELD;
        else if (value == "when")
            type = enums::TKEY_WHEN;
        else if (value == "init")
            type = enums::TKEY_INIT;
        else if (value == "this")
            type = enums::TKEY_THIS;
        else if (value == "object")
            type = enums::TKEY_OBJECT;
        else if (value == "true")
            type = enums::TKEY_TRUE;
        else if (value == "false")
            type = enums::TKEY_FALSE;
        else if (value == "is")
            type = enums::TKEY_IS;
    }
    return type == enums::TID ? token(type, std::move(value)) : token(type);
}

spark::token spark::lexer::next_error()
{
    std::string value;
    do
    {
        value+=it;
        getchar();
    } while (not isspace(it) and not stream.eof());
    return token(enums::TERROR, std::move(value));
}

void spark::lexer::getchar()
{
    lit = it;
    if (it == '\n' or it == '\r')
    {
        line++;
        col = 1;
    } else
    {
        col++;
    }
    it = static_cast<char>(stream.get());
}

std::optional<spark::token> spark::lexer::next()
{
    begin:
    while (std::isspace(it) or it == 0)
        getchar();
    if (stream.eof())
        return std::nullopt;
    if (isdigit(it))
        return next_int_or_double();
    if (isalpha(it))
        return next_id_or_keyword();
    if (it == '{')
        return next_single(enums::TBRACES_OPEN);
    if (it == '}')
        return next_single(enums::TBRACES_CLOSE);
    if (it == '[')
        return  next_single(enums::TBRACKETS_OPEN);
    if (it == ']')
        return next_single(enums::TBRACKETS_CLOSE);
    if (it == '(')
        return next_single(enums::TPARENTHESIS_OPEN);
    if (it == ')')
        return next_single(enums::TPARENTHESIS_CLOSE);
    if (it == '.')
        return next_single(enums::TDOT);
    if (it == ',')
        return next_single(enums::TCOMMA);
    if (it == '?')
        return next_single(enums::TQUESTION);
    if (it == ':')
        return next_single(enums::TCOLON);
    if (it == '$')
        return next_single(enums::TDOLLAR);
    if (it == '"')
        return next_string();
    if (it == '=')
        return next_equ_or_equal();
    if (it == '!')
    {
        auto && token = next_not_equal();
        if (token.type == enums::TCOMMENT)
            goto begin;
        return token;
    }
    if (it == '>')
        return next_greater_or_greater_equal();
    if (it == '<')
        return next_lower_or_lower_equal();
    if (it == '+')
        return next_plus_or_plus_plus_or_plus_equal();
    if (it == '-')
        return next_minus_or_minus_minus_or_minus_equal();
    if (it == '*')
        return next_times_or_times_equal();
    if (it == '%')
        return next_modulo_or_modulo_equal();
    if (it == '/')
    {
        auto && token = next_slash_or_slash_equal_or_comment();
        if (token.type == enums::TCOMMENT)
            goto begin;
        return token;
    }
    return next_error();
}
