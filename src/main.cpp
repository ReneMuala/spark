#include <iostream>
#include "lexer/lexer.hpp"
#include "parser/parser.hpp"
std::vector<iota::token> tokens;

int main(int argc, char** argv) try {
    iota::lexer lexer("main.iota");
    while (auto token = lexer.next())
    {
        // fmt::println(">> {}: '{}'", static_cast<int>(token->type), token->value);
        ILC::chain.push_back(token->type);
        tokens.emplace_back(token.value());
    }
    ILC::chain_size = ILC::chain.size();
    if (parse())
    {
        std::cout << "Success" << std::endl;
    } else
    {
        std::cout << "Failed " << std::endl;
    }
    return 0;
} catch (std::exception& e)
{
    std::cerr << e.what() << std::endl;
}
