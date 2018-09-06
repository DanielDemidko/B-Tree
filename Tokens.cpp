#include "Tokens.h"
#include <string>

std::vector<std::string> Tokens(const std::string_view &line)
{
    std::string buf;
    std::vector<std::string> res;
    auto move = [&buf, &res] 
    { 
        if (!empty(buf))
        {
            res.push_back(buf);
            buf.clear();
        }
    };
    for (const auto &i : line)
    {
        if (i == ' ')
        {
            move();
            continue;
        }
        if (i == '[' || i == ']')
        {
            move();
            res.emplace_back(1, i);
            continue;
        }
        buf.push_back(i);
    }
    move();
    return res;
}

std::vector<std::string> Tokens(std::istream &stream)
{
    std::vector<std::string> res;
    for (std::string line; getline(stream, line);)
    {
        const auto vec = Tokens(line);
        res.insert(end(res), cbegin(vec), cend(vec));
    }
    return res;
}
