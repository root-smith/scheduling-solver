//
//  main.cpp
//  Solver


#include <iostream>
#include <fstream>
#include <string>

#include "digraph.hpp"
#include "json.hpp"
#include "BFS.hpp"

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
	
	json jout = d.to_json();
	
	cout << "json output :" << '\n';
	cout << jout << '\n';
	
	ofstream o("output.json");
	o << std::setw(4) << jout << '\n';
	
	int s = 0; //source
	BreadthFirstDirectedPaths g = BreadthFirstDirectedPaths(d, s);
	
	cout << "dist_to 3: " << g.get_dist_to(3) << '\n';
	
	//TODO: hasPathTo, distTo
	
	/*
	 
	 BreadthFirstDirectedPaths bfs = new BreadthFirstDirectedPaths(G, s);
	 
	 for (int v = 0; v < G.V(); v++) {
		 if (bfs.hasPathTo(v)) {
			 StdOut.printf("%d to %d (%d):  ", s, v, bfs.distTo(v));
			 for (int x : bfs.pathTo(v)) {
			 	if (x == s) StdOut.print(x);
		 		else        StdOut.print("->" + x);
		 }
		 StdOut.println();
	 }
	 
	 else {
	 StdOut.printf("%d to %d (-):  not connected\n", s, v);
	 }
	 
	*/
	
	return 0;
}
