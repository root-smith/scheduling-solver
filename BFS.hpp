//
//  BFS.hpp
//

#ifndef BFS_hpp
#define BFS_hpp

#include <stdio.h>
#include <limits>
#include <stack>

class BreadthFirstDirectedPaths
{
private:
	int int_max = std::numeric_limits<int>::max();
	vector<bool> marked;
	vector<int> dist_to;
	vector<int> edge_to;
	Digraph* G;
	
	void bfs(Digraph & G, int s);	// BFS from single source
	void bfs(Digraph & G, vector<int> sources); // BFS from multiple sources
	void validate_vertex(int v);
	void validate_vertices(vector<int> vertices);
	
public:
	//Computes the shortest path from s and every other vertex in graph
	BreadthFirstDirectedPaths(Digraph & G, int s);
	
	//Computes the shortest path from any one of the source vertices
	//in sources to every other vertex in graph
	BreadthFirstDirectedPaths(Digraph & G, vector<int> sources);
	
	bool has_path_to(int v);
	int get_dist_to(int v);
	stack<int> path_to(int v);
};

	

#endif /* BFS_hpp */
