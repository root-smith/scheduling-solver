//
//  main.cpp
//  Solver


#include <iostream>
#include <fstream>
#include <string>

#include "digraph.hpp"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

int main()
{
	//load json file with list of graph edges
	std::ifstream i("graph.json");
	json jin;
	i >> jin;
	
	//create digraph object from json
	Digraph d(jin);
	
	for (int i = 0; i < 10; i++)
		d.addEdge(i, i+1);
	
	json jout = d.to_json();
	
	cout << "json output :" << '\n';
	cout << jout << '\n';
	
	ofstream o("output.json");
	o << std::setw(4) << jout << '\n';
	
	return 0;
}
