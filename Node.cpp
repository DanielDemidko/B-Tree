#include "Node.h"
#include "Tokens.h"
#include <string>

std::ostream &operator<<(std::ostream &s, const std::shared_ptr<Node> &p)
{
    if (!p)
    {
        s << "Empty node";
        return s;
    }
    s << "[ ";
    auto printChild = [&s, &vec = p->Children](const int &index)
    {
        if (index < size(vec) && vec[index])
        {
            s << vec[index];
        }
    };
    const int keysCount = size(p->Keys);
    for (size_t i = 0; i < keysCount; ++i)
    {
        printChild(i);
        s << p->Keys[i] << ' ';
    }
    printChild(keysCount);
    return s << "] ";
}

static std::shared_ptr<Node> CreateNode(
    std::vector<std::string>::const_iterator &i, const std::shared_ptr<Node> &parent)
{
    const auto res = std::make_shared<Node>();
    res->Parent = parent;
    for (++i; *i != "]"; ++i)
    {
        if (*i == "[")
        {
            res->Children.emplace_back(CreateNode(i, res));
        }
        else
        {
            res->Keys.emplace_back(std::stoi(*i));
        }
    }
    return res;
}

std::istream &operator>>(std::istream &s, std::shared_ptr<Node> &p)
{
    const auto vec = Tokens(s);
    if (!empty(vec))
    {
        auto i = cbegin(vec);
        p = CreateNode(i, nullptr);
    }
    return s;
}