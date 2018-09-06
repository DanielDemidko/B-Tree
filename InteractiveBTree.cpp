#include "InteractiveBTree.h"
#include <iostream>
#include <fstream>
#include "Operations.h"

void InteractiveBTree::Sync()
{
    std::cout << Root << std::endl;
    std::ofstream(DBPath) << Root;
}

void InteractiveBTree::Print() const
{
    std::cout << Root << std::endl;
}

void InteractiveBTree::Add(const int & key)
{
    Operations::Add(Root, key, TFactor);
    Sync();
}

void InteractiveBTree::Contains(const int & key) const
{
    std::cout << std::get<0>(Operations::Contains(Root, key)) << std::endl;
}

void InteractiveBTree::Clear()
{
    Root = nullptr;
    Sync();
}

InteractiveBTree::InteractiveBTree(const int &t) : TFactor(t)
{
    // Восстанавливаем из DB
    std::cout << "The tree was automatically restored from the database." << std::endl;
    std::ifstream(DBPath) >> Root;
}