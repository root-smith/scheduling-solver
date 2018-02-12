//
//  digraph.hpp
//

#pragma once

#include <vector>
#include <utility>
#include <unordered_set>
#include "json.hpp"

using json = nlohmann::json;

class Digraph
{
private:
	int V; 					//number of vertices
	int E;					//number of edges
	
public:
	Digraph(const json& j);
	Digraph(int n);
	Digraph();
	int get_v();
	int get_e();
	std::vector<std::vector<int>> adj; 		//adjacency list for vertex v
	std::vector<int> indegree;				//indegree[v] = indegree of vertex v
	void validate_vertex(int v);
	void add_edge(int v, int w);
	size_t get_outdegree(int v);
	size_t get_indegree(int v);
	json to_json();
	bool edge_exists(int v, int w);
	bool vertex_exists(int v);
	std::vector<std::pair<int, int>> get_edge_list();
	std::string edge_list_to_string();
	bool graph_is_valid();
	bool equals(Digraph& other);
	void describe();
	std::unordered_set<int> get_vertex_list();
	
	/*
	bool operator == (Digraph& other) const
	{
		if(this == &other) return true;
		else return false;
	}
	 */
	
};
