//
// Created by dte on 1/22/2025.
//

#include "token.hpp"

namespace spark {
    token::token(const enums::token_type & type, std::string && value): type(type)
    {
        if (not value.empty())
            this->value = std::move(value);
    }
} // spark