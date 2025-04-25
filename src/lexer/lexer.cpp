//
// Created by dte on 1/22/2025.
//

#include "lexer.hpp"

#include <iostream>
#include <optional>
#include <exceptions/expected_token.hpp>

iota::lexer::lexer(const std::string&& filename)
{
    stream.open(filename);
    if (not stream.is_open())
    {
        throw exceptions::file_not_found(filename);
    }
    lit = it = 0;
    line = col = 1;
}

iota::token iota::lexer::next_int_or_double()
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
    return token(type, std::move(value), line, col);
}

iota::token iota::lexer::next_string()
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
    return token(enums::TCHAR_ARRAY, std::move(value), line, col);
}

iota::token iota::lexer::next_and()
{
    std::string value = {it};
    auto type = enums::TERROR;
    getchar();
    if(it == '&')
    {
        type = enums::TAND;
        value+=it;
        getchar();
    }
    return token(type, std::move(value), line, col);
}

iota::token iota::lexer::next_or()
{
    std::string value = {it};
    auto type = enums::TERROR;
    getchar();
    if(it == '|')
    {
        type = enums::TAND;
        value+=it;
        getchar();
    }
    return token(type, std::move(value), line, col);
}

iota::token iota::lexer::next_equ_or_equal()
{
    std::string value = {it};
    auto type = enums::TEQU;
    getchar();
    if(it == '=')
    {
        type = enums::TEQUAL;
        value+=it;
        getchar();
    }
    return token(type, std::move(value), line, col);
}

iota::token iota::lexer::next_single(const enums::token_type&& type)
{
    std::string value = {it};
    getchar();
    return token(type, std::move(value), line, col);
}

iota::token iota::lexer::next_not_equal()
{
    std::string value = {it};
    auto type = enums::TERROR;
    getchar();
    if(it == '=')
    {
        type = enums::TNOT_EQUAL;
        value+=it;
        getchar();
    }
    return token(type, std::move(value), line, col);
}

iota::token iota::lexer::next_greater_or_greater_equal()
{
    std::string value = {it};
    auto type = enums::TGREATER;
    getchar();
    if(it == '=')
    {
        type = enums::TGREATER_OR_EQUAL;
        value+=it;
        getchar();
    }
    return token(type,std::move(value),line, col);
}

iota::token iota::lexer::next_lower_or_lower_equal()
{
    std::string value = {it};
    auto type = enums::TLOWER;
    getchar();
    if(it == '=')
    {
        type = enums::TLOWER_OR_EQUAL;
        value+=it;
        getchar();
    }
    return token(type, std::move(value), line, col);
}

iota::token iota::lexer::next_plus_or_plus_plus_or_plus_equal()
{
    std::string value = {it};
    auto type = enums::TPLUS;
    getchar();
    if(it == '=')
    {
        type = enums::TPLUS_EQU;
        value+=it;
        getchar();
    } else if(it == '+')
    {
        type = enums::TPLUS_PLUS;
        value+=it;
        getchar();
    }
    return token(type,std::move(value), line, col);
}

iota::token iota::lexer::next_minus_or_minus_minus_or_minus_equal()
{
    std::string value = {it};
    auto type = enums::TMINUS;
    getchar();
    if(it == '=')
    {
        type = enums::TMINUS_EQU;
        value+=it;
        getchar();
    } else if(it == '-')
    {
        type = enums::TMINUS_MINUS;
        value+=it;
        getchar();
    }

    return token(type, std::move(value), line, col);
}

iota::token iota::lexer::next_times_or_times_equal()
{
    std::string value = {it};
    auto type = enums::TTIMES;
    getchar();
    if(it == '=')
    {
        type = enums::TTIMES_EQU;
        value+=it;
        getchar();
    }
    return token(type, std::move(value), line, col);
}

iota::token iota::lexer::next_modulo_or_modulo_equal()
{
    std::string value = {it};
    auto type = enums::TMODULO;
    getchar();
    if(it == '=')
    {
        type = enums::TMODULO_EQU;
        value+=it;
        getchar();
    }
    return token(type, std::move(value), line, col);
}

iota::token iota::lexer::next_slash_or_slash_equal_or_comment()
{
    std::string value = {it};
    auto type = enums::TSLASH;
    getchar();
    if(it == '=')
    {
        type = enums::TSLASH_EQU;
        value+=it;
        getchar();
    } else if (it == '/')
    {
        type = enums::TCOMMENT;
        do
        {
            if (value.size() == 10)
            {
                value += "...";
            } else if (value.size() < 10)
            {
                value += it;
            }
            getchar();
        } while(it != '\n' and not stream.eof());
    } else if (it == '*')
    {
        int depth = 1;
        type = enums::TCOMMENT;
        do
        {
            if (value.size() == 10)
            {
                value += "...";
            } else if (value.size() < 10)
            {
                value += it;
            }
            getchar();
            if (stream.eof())
                throw exceptions::expected_token("*/", line, col);
            if (lit == '/' and it == '*') depth++;
            else if (lit == '*' and it == '/') depth--;
        } while(depth);
        getchar();
    }
    return token(type, std::move(value), line, col);
}

iota::token iota::lexer::next_id_or_keyword()
{
    std::string value;
    auto type = enums::TID;
    do
    {
        value+=it;
        getchar();
    } while (isalnum(it) or it == '_');

    // for, while, if, else, fun, type, mut, yield, when, init, this, object
    if (value.length() >= 2 and value.length() <= 9)
    {
        if (value == "for")
            type = enums::TKEYWORD_FOR;
        else if (value == "while")
            type = enums::TKEYWORD_WHILE;
        else if (value == "if")
            type = enums::TKEYWORD_IF;
        else if (value == "else")
            type = enums::TKEYWORD_ELSE;
        else if (value == "function" or value == "func")
            type = enums::TKEYWORD_FUNCTION;
        else if (value == "type")
            type = enums::TKEYWORD_TYPE;
        else if (value == "mutable")
            type = enums::TKEYWORD_MUTABLE;
        else if (value == "yield")
            type = enums::TKEYWORD_YIELD;
        else if (value == "when")
            type = enums::TKEYWORD_WHEN;
        else if (value == "init")
            type = enums::TKEYWORD_INIT;
        else if (value == "this")
            type = enums::TKEYWORD_THIS;
        else if (value == "true")
            type = enums::TKEYWORD_TRUE;
        else if (value == "false")
            type = enums::TKEYWORD_FALSE;
        else if (value == "break")
            type = enums::TKEYWORD_BREAK;
        else if (value == "continue")
            type = enums::TKEYWORD_CONTINUE;
        else if (value == "return")
            type = enums::TKEYWORD_RETURN;
        else if (value == "as")
            type = enums::TKEYWORD_AS;
        else if (value == "any")
            type = enums::TKEYWORD_ANY;
        else if (value == "string")
            type = enums::TKEYWORD_STRING;
        else if (value == "number")
            type = enums::TKEYWORD_NUMBER;
        else if (value == "undefined")
            type = enums::TKEYWORD_UNDEFINED;
        else if (value == "null")
            type = enums::TKEYWORD_NULL;
        else if (value == "switch")
            type = enums::TKEYWORD_SWITCH;
        else if (value == "case")
            type = enums::TKEYWORD_CASE;
        else if (value == "var")
            type = enums::TKEYWORD_VAR;
        else if (value == "const")
            type = enums::TKEYWORD_CONST;
    }
    return token(type, std::move(value), line, col);
}

iota::token iota::lexer::next_error()
{
    std::string value;
    do
    {
        value+=it;
        getchar();
    } while (not isspace(it) and not stream.eof());
    return token(enums::TERROR, std::move(value), line, col);
}

void iota::lexer::getchar()
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

std::optional<iota::token> iota::lexer::next()
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
    if (it == ';')
        return next_single(enums::TSEMICOLON);
    if (it == '$')
        return next_single(enums::TDOLLAR);
    if (it == '"')
        return next_string();
    if (it == '=')
        return next_equ_or_equal();
    if (it == '&')
        return next_and();
    if (it == '|')
        return next_or();
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
