//
//  depth_first_order.hpp
//  Solver
//

#pragma once

#include <vector>
#include <deque>

#include "digraph.hpp"

using namespace std;

class Depth_first_order
{
public:
	vector<bool> marked;
	vector<int> pre;
	vector<int> post;
	deque<int> preorder;
	deque<int> postorder;
	int pre_counter;
	int post_counter;
	
	Depth_first_order(Digraph & G);
	
	// run DFS in edge-weighted digraph G from vertex v and compute preorder/postorder
	void dfs(Digraph & G, int v);
	
	//returns the pre/postorder number of vertex v
	int get_pre(int v);
	int get_post(int v);
	
	
	bool check();
	void validate_vertex(int v);
	
};

