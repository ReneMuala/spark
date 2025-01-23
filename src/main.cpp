#include <iostream>
#include "lexer/lexer.hpp"
int main(int argc, char** argv) try {
    spark::lexer lexer("main.spark");

    while (auto token = lexer.next())
    {
        fmt::println(">> {}: '{}'", static_cast<int>(token->type), token->value);
    }
    return 0;
} catch (std::exception& e)
{
    std::cerr << e.what() << std::endl;
}
