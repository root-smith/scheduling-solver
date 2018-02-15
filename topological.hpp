//
//  topological.hpp
//  Solver
//

#pragma once

#include <vector>
#include "digraph.hpp"

using namespace std;

class Topological
{
public:
	vector<int> order;
	vector<int> rank;
	
	Topological(Digraph & G);
	bool has_order();
	int get_rank(int v);
	void validate_vertex(int v);
	
};

vector<vector<int>> all_topological_sorts(Digraph & G);
