//
//  digraph.cpp
//

#include <iostream>
#include <string>
#include <map>
#include <algorithm>

#include "digraph.hpp"

using namespace std;
using json = nlohmann::json;

//initalizes an empty digraph with V vertices
Digraph::Digraph()
{
	V = 1;
	E = 0;
	indegree.resize(1);
	adj.resize(1);
}

Digraph::Digraph(int n) : V(n)
{
	E = 0;
	indegree.resize(n);
	adj.resize(n);
}

// Getters
int Digraph::get_v() { return V; }
int Digraph::get_e() { return E; }

void Digraph::validate_vertex(int v)
{
	if (v < 0 ) {
		cout << "Invalid vertex" << '\n';
	}
	if (v > V) {
		cout << "Increasing V from " << V << '\n';
		V++;
		indegree.resize(V);
		adj.resize(V);
	}
}

bool Digraph::vertex_exists(int v)
{
	//TODO: check for missing vertices
	if (v < adj.size())
		return true;
	return false;
}

bool Digraph::edge_exists(int v, int w)
{
	if ( find(adj[v].begin(), adj[v].end(), w) != adj[v].end() )
		return true;
	else
		return false;
}

void Digraph::add_edge(int v, int w)
{
	validate_vertex(v);
	validate_vertex(w);
	
	if( !edge_exists(v,w) )
	{
		indegree[w]++;
		E++;
		adj[v].push_back(w);
		//cout << "adding edge " << v << " to " << w << "; E is " << E << '\n';
	}
}

size_t Digraph::get_outdegree(int v)
{
	validate_vertex(v);
	return adj[v].size();
}

size_t Digraph::get_indegree(int v)
{
	validate_vertex(v);
	return indegree[v];
}

Digraph::Digraph(const json& j)
{
	if ( j.find("edges") != j.end() && j.find("vertices") != j.end() && j.find("edge_list") != j.end())
	{
		//E = j["edges"];
		E = 0; //TODO: E is set from the edge list, not the json data
		V = j["vertices"];
		
		indegree.resize(V);
		adj.resize(V);
		
		for (auto& edge : j["edge_list"])
			add_edge(edge[0],edge[1]);
	} else
		cout << "Error parsing data from json file\n";
	if(!graph_is_valid())
		cout << "Json file does not contain valid graph\n";
		
}

json Digraph::to_json() {

	int cnt_edge = 0;
	const auto edge_list = Digraph::get_edge_list();
	map<string, pair<int, int>> m;
	
	for (auto i : edge_list)
		m.emplace(to_string(cnt_edge++), i );
	
	//generate vertex list from edge list
	unordered_set<int> vertex_list;
	for (auto i : edge_list)
	{
		vertex_list.insert(i.first);
		vertex_list.insert(i.second);
	}
	
	json j;
	j["edge_list"] = m;
	j["edges"] = cnt_edge;
	j["vertices"] = vertex_list.size();
	
	//cout << "j: " << j << '\n';
	
	return j;	
}

vector<pair<int, int>> Digraph::get_edge_list() {

	vector<pair<int, int>> edge_list;
	
	//QUESTION: is there a better way to do this?
	//adj is a vector<vector<int>>
	//trying to make a vector<pair<int, int>> that contains all edges
	for (int i = 0; i < adj.size(); i++)
	{
		for (auto it = begin(adj[i]); it != end(adj[i]); it++)
		{
			pair<int, int> new_pair = {i, *it};
			edge_list.push_back(new_pair);
		}
	}
	return edge_list;
}

string Digraph::edge_list_to_string() {
	auto edge_list = Digraph::get_edge_list();
	string s;
	
	for (auto vertex: edge_list)
	{
		s.append( "<" + to_string(vertex.first) + "," + to_string(vertex.second) + ">\n");
	}
	return s;
}

bool Digraph::graph_is_valid()
{
	auto edge_list = get_edge_list();
	unordered_set<int> vertex_list;
	
	for (auto i : edge_list)
	{
		vertex_list.insert(i.first);
		vertex_list.insert(i.second);
	}
	
	if (edge_list.size() == E && vertex_list.size() == adj.size() && adj.size() == V)
		return true;
	else
		return false;
}
unordered_set<int> Digraph::get_vertex_list(){
	//generate vertex list from edge list
	auto edge_list = get_edge_list();
	std::unordered_set<int> vertex_list;
	
	for (auto i : edge_list)
	{
		vertex_list.insert(i.first);
		vertex_list.insert(i.second);
	}
	return vertex_list;
}
	
void Digraph::describe()
{
	
	auto vertex_list = get_vertex_list();
	auto edge_list = get_edge_list();
	
	cout << "graph_is_valid: " << graph_is_valid() << '\n';
	cout << "edge_list:\n" << edge_list_to_string() << '\n';
	cout << "edge_list.size(): " << edge_list.size() << '\n';
	cout << "Edges: " << get_e() << '\n';
	cout << "Vertices: " << get_v() << '\n';
	cout << "vertex_list.size(): " << vertex_list.size() << '\n';
	cout << "adj.size(): " << adj.size() << '\n';
}

/*
 Tests:
 No duplicate edges
 Acyclic
 contiguous
 Create small graph and verify
 
 Fail on:
 negative vertex
 create edge that already exists
 
 TODO:
 Deep copy graph
 DFS
 Topological sort
 List of all topological sorts
 
*/
