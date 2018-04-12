#pragma once

#include <vector>
#include <deque>

#include "digraph.hpp"

class Depth_first_order
{
public:
	std::vector<bool> marked;
	std::vector<int> pre;
	std::vector<int> post;
	std::deque<int> preorder;
	std::deque<int> postorder;
	int pre_counter;
	int post_counter;
	
	Depth_first_order(const Digraph & G);
	
	// run DFS in edge-weighted digraph G from vertex v and compute preorder/postorder
	void dfs(const Digraph & G, int v);
	
	//returns the pre/postorder number of vertex v
	int get_pre(int v) const { return pre[v]; }
	int get_post(int v) const { return post[v]; }
	
	bool check();
	void validate_vertex(int v);
};

