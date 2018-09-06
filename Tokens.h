#pragma once
#include <vector>
#include <istream>

std::vector<std::string> Tokens(const std::string_view &line);

std::vector<std::string> Tokens(std::istream &istream);