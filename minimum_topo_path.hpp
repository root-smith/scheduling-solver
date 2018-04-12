#pragma once

#include <vector>
#include "digraph.hpp"

std::vector<std::vector<int>> get_complete_paths(const Digraph & G);
std::vector<int> minimum_complete_path(const Digraph & G);

