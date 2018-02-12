//
//  depth_first_order.cpp
//  Solver
//

#include <iostream>

#include "depth_first_order.hpp"

Depth_first_order::Depth_first_order(Digraph & G)
{
	pre.resize(G.get_v());
	post.resize(G.get_v());
	marked.resize(G.get_v());
	
	for (int v = 0; v < G.get_v(); v++)
		if (!marked[v]) dfs(G, v);
}

void Depth_first_order::dfs(Digraph & G, int v)
{
	marked[v] = true;
	pre[v] = pre_counter++;
	preorder.push_front(v);
	for ( int w : G.adj[v] ) {
		if (!marked[w]) {
			dfs(G, w);
		}
	}
	postorder.push_front(v);
	post[v] = post_counter++;
}

int Depth_first_order::get_pre(int v) { return pre[v]; }
int Depth_first_order::get_post(int v) { return post[v]; }

bool Depth_first_order::check()
{
	// check that post(v) is consistent with post()
	int r = 0;
	for (int v : postorder) {
		if (get_post(v) != r) {
			std::cout << "post(v) and post() inconsistent\n";
			return false;
		}
		r++;
	}
	
	// check that pre(v) is consistent with pre()
	r = 0;
	for (int v : preorder) {
		if (get_pre(v) != r) {
			std::cout << "pre(v) and pre() inconsistent\n";
			return false;
		}
		r++;
	}
	
	return true;
}

void Depth_first_order::validate_vertex(int v)
{
	auto V = marked.size();
	if (v < 0 || v >= V)
		cout << "error\n";
}

/*
 class Depth_first_order
 {
 vector<bool> marked;
 vector<int> pre;
 vector<int> post;
 queue<int> preorder;
 queue<int> postorder;
 int pre_counter;
 int post_counter;
 
 *Depth_first_order(Digraph & G);
 
 // run DFS in edge-weighted digraph G from vertex v and compute preorder/postorder
 *void dfs(Digraph & G, int v);
 
 //returns the pre/postorder number of vertex v
 int get_pre(int v);
 int get_post(int v);
 
 // check that pre() and post() are consistent with pre(v) and post(v)
 bool check();
 
 void validate_vertex(int v);
 
 };

 
 */

