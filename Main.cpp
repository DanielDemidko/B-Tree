#include <iostream>
#include "InteractiveBTree.h"
#include "Tokens.h"

std::vector<std::string> ToUpper(const std::vector<std::string> &vec)
{
    std::vector<std::string> result(size(vec));
    std::transform(cbegin(vec), cend(vec), begin(result), [](const std::string &i)
    {
        std::string res(size(i), {});
        std::transform(cbegin(i), cend(i), begin(res), toupper);
        return res;
    });
    return result;
}

int main()
{
    std::cout <<
        "Interactive BTree 1.0\n"
        "You can use the commands: add [number], find [number], print, clear."
        << std::endl;
    std::cout << "T-Factor: ";
    int tfactor;
    std::cin >> tfactor;
    InteractiveBTree tree(tfactor);
    // Цикл обработки команд
    for (std::string line; std::getline(std::cin, line);)
    {
        const auto toks = ToUpper(Tokens(line));
        if (size(toks) == 1)
        {
            if (toks.front() == "PRINT")
            {
                tree.Print();
                continue;
            }
            if (toks.front() == "CLEAR")
            {
                tree.Clear();
                continue;
            }
            std::cout << "Unknown command!" << std::endl;
        }
        if (size(toks) == 2)
        {
            if (toks.front() == "FIND")
            {
                tree.Contains(stoi(toks[1]));
                continue;
            }
            if (toks.front() == "ADD")
            {
                tree.Add(stoi(toks[1]));
                continue;
            }
            std::cout << "Unknown command!" << std::endl;
        }
    }
}
