//
//  main.cpp
//  Solver

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_set>

#include "digraph.hpp"
#include "json.hpp"
#include "BFS.hpp"
#include "directed_dfs.hpp"
#include "topological.hpp"
#include "util.hpp"
#include "minimum_topo_path.hpp"

using namespace std;
using json = nlohmann::json;

template <typename T>
void print_vec_of_vec(const vector<T> & x)
{
	for (auto i : x)
	{
		for (auto j : i)
			cout << j << ' ';
		cout << '\n';
	}
}

int main()
{
	//load json file with list of graph edges
	std::ifstream i("new_graph.json");
	
	json jin;
	i >> jin;
	
	replace( jin.begin(), jin.end(), '[', '{' );
	replace( jin.begin(), jin.end(), ']', '}' );
	
	//create digraph object from json
	Digraph d(jin);
	
	//create depth first order
	int w = 6;
	directed_dfs dfs = directed_dfs(d);
	cout << setw(w) << 'v' << setw(w) << "pre" << setw(w) << "post" << '\n';
	cout << "--------------------\n";
	for (int v = 0; v < d.get_v(); v++) {
		cout << setw(w) << v << setw(w) << dfs.preorder[v] << setw(w) << dfs.postorder[v] << '\n';
	}
	cout << '\n';
	
	cout << "E: " << d.get_e() << "; V: " << d.get_v() << '\n';
	cout << '\n';
	
	for (auto x : d.indegree)
		cout << x << ' ';
	cout << '\n';
	
	dfs.check();
	
	cout << "Preorder / pre: \n";
	
	for (auto x : dfs.preorder)
		cout << x << ' ';
	cout << '\n';
	
	for (auto x : dfs.pre)
		cout << x << ' ';
	cout << '\n';
	cout << '\n';
	cout << "Postorder / post: \n";
	for (auto x : dfs.postorder)
		cout << x << ' ';
	cout << '\n';
	
	for (auto x : dfs.post)
		cout << x << ' ';
	cout << '\n';

	//create a topological sort
	
	Topological ts = Topological(d);
	cout << "Topological sort: \n";
	for (int i = 0; i < ts.order.size(); i++)
	{
		if (i != 0)
			cout << " => ";
		cout << ts.order[i];
	}
	cout << '\n';
	
	//create all topological sorts
	vector<vector<int>> all_tsorts = all_topological_sorts(d);
	
	cout << '\n';
	
	cout << all_tsorts.size() << " unique topological sorts generated.\n";
	
	if (all_tsorts.size() > 10)
	{
		cout << "Listing first 10 topological sorts: \n";
		for (auto i : Range<0, 10>())
		{
			for (auto j : all_tsorts[i])
				cout << j << ' ';
			cout << '\n';
		}
	}
	else
	{
		print_vec_of_vec(all_tsorts);
	}
	cout << '\n';
	
	vector<vector<int>> complete_paths = get_complete_paths(d);
	print_vec_of_vec(complete_paths);
	
	for (const vector<int> & v : all_tsorts)
	{
		for (int i=0; i < v.size()-1; i++)
		{
			cout << "Testing edge from: " << v[i] << " to: " << v[i+1] << '\n';
			if (d.edge_exists(v[i],v[i+1]))
				cout << "edge exists\n";
			else
				cout << "edge does not exist\n";
		}
		if ( is_valid_path(d,v) )
			cout << "****path is valid****\n";
		else
			cout << "path does not exist\n";
	}
	
	/*
	 OUTPUT
	json jout = d.to_json();
	
	cout << jout << '\n';
	
	ofstream o("graph.json");
	o << std::setw(w) << jout << '\n';
	*/
	
	return 0;
}
