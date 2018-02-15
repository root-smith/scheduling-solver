//
//  main.cpp
//  Solver

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>

#include "digraph.hpp"
#include "json.hpp"
#include "BFS.hpp"
#include "depth_first_order.hpp"
#include "topological.hpp"

using namespace std;
using json = nlohmann::json;

int main()
{
	//load json file with list of graph edges
	std::ifstream i("graph.json");
	json jin;
	i >> jin;
	
	ofstream backup("backup.json");
	backup << std::setw(4) << jin << '\n';
	
	//create digraph object from json
	Digraph d(jin);
	
	//create depth first order
	int w = 6;
	Depth_first_order dfs = Depth_first_order(d);
	cout << setw(w) << 'v' << setw(w) << "pre" << setw(w) << "post" << '\n';
	cout << "--------------------\n";
	for (int v = 0; v < d.get_v(); v++) {
		cout << setw(w) << v << setw(w) << dfs.preorder[v] << setw(w) << dfs.postorder[v] << '\n';
	}
	cout << '\n';
	
	//create a topological sort
	/*
	Topological ts = Topological(d);
	cout << "Topological sort: \n";
	for (int i = 0; i < ts.order.size(); i++)
	{
		if (i != 0)
			cout << " => ";
		cout << ts.order[i];
	}
	cout << '\n';
	*/
	
	vector<vector<int>> all_tsorts = all_topological_sorts(d);
	
	cout << '\n';
	
	cout << all_tsorts.size() << " unique topological sorts generated.\n";
	
	/*
	 OUTPUT
	json jout = d.to_json();
	
	cout << jout << '\n';
	
	ofstream o("graph.json");
	o << std::setw(w) << jout << '\n';
	*/

	return 0;
}
