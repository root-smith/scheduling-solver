//
//  digraph.hpp
//

#ifndef digraph_hpp
#define digraph_hpp

#include <unordered_set>
#include <vector>

#include "json.hpp"

using namespace std;

using json = nlohmann::json;
using Bag = std::unordered_set<int>;

class Digraph
{
private:
	int V; 					//number of vertices
	int E;					//number of edges
	
public:
	Digraph(json j);
	Digraph(int n);
	Digraph();
	int getV();
	int getE();
	vector<Bag> adj; 		//adjacency list for vertex v
	vector<int> indegree;	//indegree[v] = indegree of vertex v
	void validateVertex(int v);
	void addEdge(int v, int w);
	size_t getOutdegree(int v);
	size_t getIndegree(int v);
	json to_json();
	bool edgeExists(int v, int w);
	
};

#endif /* digraph_hpp */
