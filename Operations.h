#pragma once
#include "Node.h"

namespace Operations
{
    // Возвращает результат поиска (найден ключ или нет), и последнюю ноду, в которой завершился поиск
    std::tuple<bool, std::shared_ptr<Node>> Contains(const std::shared_ptr<Node> &ptr, const int &key);

    // Добавление ключа: Принимает указатель на корень, ключ, и t-фактор
    void Add(std::shared_ptr<Node> &root, const int &key, const int &t);
}
