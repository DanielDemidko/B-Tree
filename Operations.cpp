#include "Operations.h"

// Анонимное пространство имён не позволяет обьявить эти функции ещё где либо - 
// и таким образом полностью инкапсулирует их отовсюду кроме этого файла
namespace
{
    void Split(const std::shared_ptr<Node> &node, const int &t, std::shared_ptr<Node> &root);

    // Делаем иньекцию родительской ноде - 
    // прививаем ещё одного ребёнка возникшего в результате разделения дочерней
    void Inject(
        std::shared_ptr<Node> &parent, const int key, 
        const std::shared_ptr<Node> &child, const int &t, std::shared_ptr<Node> &root)
    {
        // Новый рут
        if (!parent)
        {
            parent = std::make_shared<Node>();
            parent->Keys.push_back(key);
            parent->Children.push_back(child);
            parent->Children.push_back(root);
            root = parent;
            return;
        }
        size_t index = 0;
        for (; index < size(parent->Keys); ++index)
        {
            if (parent->Keys[index] > key)
            {
                break;
            }
        }
        parent->Keys.insert(cbegin(parent->Keys) + index, key);
        parent->Children.insert(cbegin(parent->Children) + index, child);
        Split(parent, t, root);
    }

    // Разбиваем переполненную ноду на две
    void Split(const std::shared_ptr<Node> &node, const int &t, std::shared_ptr<Node> &root)
    {
        if (size(node->Keys) <= 2 * t - 1)
        {
            return;
        }
        const auto otherNode = std::make_shared<Node>();
        const auto grabeKeysFrom = cbegin(node->Keys);
        const auto grabeKeysTo = grabeKeysFrom + t;
        std::copy(grabeKeysFrom, grabeKeysTo, back_inserter(otherNode->Keys));
        node->Keys.erase(grabeKeysFrom, grabeKeysTo);
        const auto keyToOtherNode = node->Keys.front();
        node->Keys.erase(cbegin(node->Keys));
        if (!empty(node->Children))
        {
            const auto grabeChildsFrom = cbegin(node->Children);
            const auto grabeChildsTo = grabeChildsFrom + t + 1;
            std::copy(grabeChildsFrom, grabeChildsTo, back_inserter(otherNode->Children));
            node->Children.erase(grabeChildsFrom, grabeChildsTo);
        }
        Inject(node->Parent, keyToOtherNode, otherNode, t, root);
    }
}

namespace Operations
{
    // Возвращает результат поиска (найден ключ или нет), и последнюю ноду, в которой завершился поиск
    std::tuple<bool, std::shared_ptr<Node>> Contains(const std::shared_ptr<Node> &ptr, const int &key)
    {
        if (!ptr)
        {
            return { false, nullptr };
        }
        size_t i = 0;
        for (; i < size(ptr->Keys); ++i)
        {
            if (ptr->Keys[i] == key)
            {
                return { true, ptr };
            }
            if (ptr->Keys[i] > key)
            {
                break;
            }
        }
        if (i < size(ptr->Children) && ptr->Children[i])
        {
            return Contains(ptr->Children[i], key);
        }
        return { false, ptr };
    }

    // Добавление ключа: Принимает указатель на корень, ключ, и t-фактор
    void Add(std::shared_ptr<Node> &root, const int &key, const int &t)
    {
        if (!root)
        {
            root = std::make_shared<Node>();
            root->Keys.push_back(key);
            return;
        }
        auto[wasAdded, lastNode] = Contains(root, key);
        if (wasAdded)
        {
            return;
        }
        auto i = cbegin(lastNode->Keys);
        for (; i < cend(lastNode->Keys); ++i)
        {
            if (*i > key)
            {
                break;
            }
        }
        lastNode->Keys.insert(i, key);
        Split(lastNode, t, root);
    }
}