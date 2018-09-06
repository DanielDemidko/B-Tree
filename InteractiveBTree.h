#pragma once
#include <filesystem>
#include "Node.h"

class InteractiveBTree
{
private:
    const int TFactor;
    std::shared_ptr<Node> Root;
    const std::filesystem::path DBPath = "DB.txt";

    //Синхронизируемся с DB
    void Sync();

public:
    void Print() const;

    void Add(const int &key);

    void Contains(const int &key) const;

    void Clear();

    InteractiveBTree(const int &t);
};
