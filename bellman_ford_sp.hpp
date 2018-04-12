//
//  bellman_ford_sp.hpp
//  Solver
//

#pragma once

#include <vector>
#include <queue>
#include <limits>
#include <utility>

#include "digraph.hpp"

class bellman_ford_sp {
	std::vector<double> dist_to;              		// distTo[v] = distance  of shortest s->v path
	std::vector<std::pair<int,int>> edge_to;        // edgeTo[v] = last edge on shortest s->v path
	std::vector<bool> on_queue;             		// onQueue[v] = is v currently on the queue?
	std::queue<int> q;         						// queue of vertices to relax
	int cost;                     					// number of calls to relax()
	
	//private Iterable<DirectedEdge> cycle;
	// negative cycle (or null if no such cycle)
	
public:
	bellman_ford_sp(Digraph & G, int s);
	
	void relax(Digraph & G, int v);
	bool has_negative_cycle();
	void find_negative_cycle();
	double get_dist_to(int v);
	bool has_path_to(int v);
	
	std::vector<int> pathTo(int v);
	bool check(Digraph G, int s);
	void validateVertex(int v);
};
