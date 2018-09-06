#pragma once
#include <memory>
#include <vector>
#include <ostream>

struct Node
{
    std::vector<int> Keys;
    std::vector<std::shared_ptr<Node>> Children;
    std::shared_ptr<Node> Parent;
};

std::ostream &operator<<(std::ostream &s, const std::shared_ptr<Node> &p);

std::istream &operator>>(std::istream &s, std::shared_ptr<Node> &p);

