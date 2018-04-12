#include <iostream>
#include <limits>

#include "topological.hpp"
#include "digraph.hpp"
#include "minimum_topo_path.hpp"

using namespace std;

vector<int> minimum_complete_path(const Digraph & G)
{
	vector<vector<int>> all_tsorts = all_topological_sorts(G);
	
	vector<int> min_path;
	double min_cost = numeric_limits<double>::max();
	
	for (const vector<int> & v : all_tsorts)
	{
		double cost = 0;
		bool valid_path = true;
		
		for (size_t i = 0; i < v.size()-1 && valid_path == true; i++)
		{
			if (!G.edge_exists(v[i],v[i+1]))
			{
				valid_path = false;
				cost = numeric_limits<double>::max();
				break;
			}
			else
				cost += G.get_weight(i,i+1);
		}
		if (cost < min_cost)
		{
			min_path = v;
		}
	}
	
	return min_path;
}


vector<vector<int>> get_complete_paths(const Digraph & G)
{
	vector<vector<int>> all_tsorts = all_topological_sorts(G);
	
	vector<vector<int>> ret;
	int reject = 0;
	
	for (const vector<int> & v : all_tsorts)
	{
		if ( is_valid_path(G,v) )
			ret.push_back(v);
		else
			++reject;
	}
	cout << "Invalid paths: " << reject << '\n';
	return ret;
}

//bool is_valid_path(const Digraph & G, const std::vector<int> v);

