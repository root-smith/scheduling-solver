//
//  digraph.cpp
//

#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "digraph.hpp"
#include "json.hpp"

using namespace std;
using Bag = std::unordered_set<int>;
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
	for (int i = 0; i < n; i++)
		adj[i] = *new Bag();
}

// Getters
int Digraph::getV() { return V; }
int Digraph::getE() { return E; }

void Digraph::validateVertex(int v)
{
	//TODO: add actual error checking here
	if (v < 0 || v >= V) {
		cout << "Invalid vertex" << '\n';
	}
}

bool Digraph::edgeExists(int v, int w)
{
	//TODO: add function
	return false;
}

void Digraph::addEdge(int v, int w)
{
	validateVertex(v);
	validateVertex(w);
	
	if( !edgeExists(v,w) )
	{
		indegree[w]++;
		E++;
		adj[v].insert(w);
	}
}

size_t Digraph::getOutdegree(int v)
{
	Digraph::validateVertex(v);
	return adj[v].size();
}

size_t Digraph::getIndegree(int v)
{
	validateVertex(v);
	return indegree[v];
}

Digraph::Digraph(json j)
{
	if ( j.find("edges") != j.end() && j.find("vertices") != j.end() && j.find("edge_list") != j.end())
	{
		E = j["edges"];
		V = j["vertices"];
		
		indegree.resize(V);
		adj.resize(V);
		for (int i = 0; i < V; i++)
			adj[i] = *new Bag();
		
		for (auto& edge : j["edge_list"])
			addEdge(edge[0],edge[1]);
	} else
		cout << "Error parsing data from json file";
}

json Digraph::to_json() {

	int cnt_edge = 0;
	map<string, pair<int, int>> edge_list;
	
	//generate list of every edge based on adjacency list
	for (int b = 0; b < adj.size(); b++)
	{
		for (auto it = begin(adj[b]); it != end(adj[b]); it++)
		{
			pair<int, int> new_pair = {b, *it};
			edge_list.emplace(to_string(cnt_edge), new_pair);
			cnt_edge++;
		}
	}
	
	json j;
	j["edge_list"] = edge_list;
	j["edges"] = cnt_edge;
	j["vertices"] = adj.size();
	
	cout << "j: " << j << '\n';
	
	return j;
	
	/*
	 Saving to ask a question about iterators:
	 
	 for (int b = 0; b < adj.size(); b++)
	 {
		for (auto it = begin(adj[b]); it != end(adj[b]); it++)
	 	{
		 //trailing comma
		 if (it != begin(adj[b])) edge_list.append(", ");
	 
		 //generate list of tuples
		 string from_v = to_string(b);
		 string to_v = to_string(*it);
		 edge_list.append('"' + to_string(cnt_edge) + "\": " + '[' + from_v + ',' + to_v + "]");
		 cnt_edge++;
		}
		edge_list.append(" ");
	 }
	 
	 cout << "edge_list: " << edge_list << '\n';
	 
	 */
	
}
