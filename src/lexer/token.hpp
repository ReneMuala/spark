//
// Created by dte on 1/22/2025.
//

#pragma once
#include "enums/token_type.hpp"
#include <string>

namespace spark {
    class token {
        public:
        enums::token_type type;
        std::string value;
        explicit token(const enums::token_type& type, std::string&& value = "");
    };
} // spark