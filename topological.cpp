//
//  topological.cpp
//  Solver
//

#include <iostream>
#include "topological.hpp"
#include "depth_first_order.hpp"

vector<int> order;
vector<int> rank;

Topological::Topological(Digraph & G)
{
	//TODO: check for directed cycles
	
	Depth_first_order dfs = Depth_first_order(G);
	size_t size = dfs.postorder.size();
	
	if ( size > INT_MAX )
		throw std::overflow_error("Postorder size is larger than INT_MAX");
		//TODO: catch this somewhere
	int i = static_cast<int>(size);
	
	for (auto it = end(dfs.postorder) - 1; it != begin(dfs.postorder) - 1; --it )
	{
		order.push_back(*it);
		rank.push_back(--i);
	}
}

bool Topological::has_order() { return order.size() != 0; }

int Topological::get_rank(int v)
{
	if (has_order())
		return rank[v];
	else
		return -1;
}
void Topological::validate_vertex(int v)
{
	auto V = rank.size();
	if (v < 0 || v >= V)
		std::cout << "vertex " << v << " is not between 0 and " << (V-1) << '\n';
}



void all_topological_util(vector<int> res, vector<int> visited, vector<int>& indegree, const vector<vector<int>>& adj)
{
	bool flag = false;
	
	for (int i = 0; i < visited.size(); i++)
	{
		//  If indegree is 0 and not yet visited then
		//  only choose that vertex
		if (indegree[i] == 0 && !visited[i])
		{
			// decrement indegree of adjacent vertices
			for (auto j : adj[i])
				indegree[j]--;

			//  add to result
			res.push_back(i);
			visited[i] = true;
			all_topological_util(res, visited, indegree, adj);
			
			// resetting visited, res and indegree for
			// backtracking
			visited[i] = false;
			res.erase(res.end() - 1);
			for (auto j = adj[i].begin(); j != adj[i].end(); j++)
				indegree[*j]++;
			
			flag = true;
		}
	}

	//  Print solution
	if (!flag)
	{
		for (int i = 0; i < res.size(); i++)
			cout << res[i] << " ";
		cout << '\n';
	}
}

void all_topological_sorts(Digraph & G)
{
	
	// Mark all the vertices as not visited
	vector<int> visited;
	visited.resize(G.get_v());
	for (auto i : visited)
		visited[i] = false;
	
	vector<int> indegree = G.indegree;
	const vector<vector<int>> adj = G.adj;
	
	vector<int> res;
	all_topological_util(res, visited, indegree, adj);
}


/*
 
 All topological sorts:
 For each vertex, make temp indegree vector
 Find all vertices where indegree is 0. "Top"
 	For each Top
 		If not visited
 			Reduce indegree of adjacent vertices
 			add vertex to res
 			mark visited true
 			alltopologicalSortUtil(res, visited);
 
 
//  Main recursive function to print all possible
//  topological sorts
void Graph::alltopologicalSortUtil(vector<int>& res,
								   bool visited[])
{
	// To indicate whether all topological are found
	// or not
	bool flag = false;
	
	for (int i = 0; i < V; i++)
	{
		//  If indegree is 0 and not yet visited then
		//  only choose that vertex
		if (indegree[i] == 0 && !visited[i])
		{
			//  reducing indegree of adjacent vertices
			list<int>:: iterator j;
			for (j = adj[i].begin(); j != adj[i].end(); j++)
				indegree[*j]--;
			
			//  including in result
			res.push_back(i);
			visited[i] = true;
			alltopologicalSortUtil(res, visited);
			
			// resetting visited, res and indegree for
			// backtracking
			visited[i] = false;
			res.erase(res.end() - 1);
			for (j = adj[i].begin(); j != adj[i].end(); j++)
				indegree[*j]++;
			
			flag = true;
		}
	}
	
	//  We reach here if all vertices are visited.
	//  So we print the solution here
	if (!flag)
	{
		for (int i = 0; i < res.size(); i++)
			cout << res[i] << " ";
		cout << endl;
	}
}
 
 ////
 
 //  The function does all Topological Sort.
 //  It uses recursive alltopologicalSortUtil()
 void Graph::alltopologicalSort()
 {
	 // Mark all the vertices as not visited
	 bool *visited = new bool[V];
	 for (int i = 0; i < V; i++)
	 visited[i] = false;
 
	 vector<int> res;
	 alltopologicalSortUtil(res, visited);
 }
*/

