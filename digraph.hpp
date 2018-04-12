#pragma once

#include <vector>
#include <utility>
#include <string>
#include <sstream>
#include <map>
#include <iostream>
//#include "vertex.hpp"
//#include "edge.hpp"
#include "json.hpp"

using json = nlohmann::json;

class Digraph
{
private:
	int V; 					//number of vertices
	int E;					//number of edges
	int next_id;			//next vertex ID

	struct Vertex
	{
		Digraph * parent;
		int UID;
		int next_id;
		std::string public_id;
		
		//Vertex() = delete;
		Vertex()
		: parent(nullptr) {}
		
		Vertex(Digraph & G, const std::string & public_id)
		: parent(&G), UID(parent->next_id++), public_id(public_id)
		{
			++(parent->V);
			parent->adj.resize(parent->V);
			parent->indegree.resize(parent->V);
			parent->vertex_map.insert(std::make_pair(public_id, UID));
			parent->vertex_list.resize(parent->V);
			parent->vertex_list[UID] = *this;
		}
		Vertex(Digraph & G)
		: Vertex(G, std::string("")) {}
		
		//copy ctor
		Vertex(const Vertex & other)
		: UID(other.UID), public_id(other.public_id)
		{
		}
		
		//copy assignment
		Vertex & operator=(const Vertex & rhs)
		{
			parent = rhs.parent;
			UID = rhs.UID;
			public_id = rhs.public_id;
			return *this;
		}
		
		//dtor
		~Vertex()
		{
			//don't delete parent
		}
		
	};
	
	struct Edge
	{
		Digraph * parent;
		int from_n;
		int to_n;
		double weight;
		
		//Edge() = delete;	//Edge needs to be attached to a parent digraph
		Edge()
		: parent(nullptr) {}
		
		Edge(Digraph & G, std::string from_n, std::string to_n, double weight)
		: parent(&G), weight(weight)
		{
			if (!parent->vertex_exists(from_n))
				new Vertex(G, from_n);
			int id_from = parent->vertex_map[from_n];
			
			if (!parent->vertex_exists(to_n))
				new Vertex(G, to_n);
			int id_to = parent->vertex_map[to_n];
			
			if( !parent->edge_exists(from_n,to_n) )
			{
				std::cout << "new edge, from " << from_n << " to " << to_n << '\n';
				parent->indegree[id_to]++;
				parent->E++;
				parent->adj[id_from].emplace_back(*this);
			}
		}
		
		Edge(Digraph & G, int from_n, int to_n, double weight)
			: Edge(G, std::to_string(from_n), std::to_string(to_n), weight) {}
		Edge(Digraph & G, int from_n, int to_n)
			: Edge(G, std::to_string(from_n), std::to_string(to_n), 0.00) {}
		
		//copy ctor
		Edge(const Edge & other)
		: from_n(other.from_n), to_n(other.to_n), weight(other.weight)
		{
		}
		
		//copy assignment
		Edge& operator=(const Edge & rhs)
		{
			parent = rhs.parent;
			from_n = rhs.from_n;
			to_n = rhs.to_n;
			weight = rhs.weight;
			return *this;
		}
		~Edge()
		{
			//don't delete parent
		}
	};
	
public:
	Digraph();
	Digraph(const json& j);
	
	std::vector<std::vector<Edge>> adj;						//adjacency list for vertex v
	std::vector<int> indegree;								//indegree[v] = indegree of vertex v
	std::vector<Vertex> vertex_list;
	std::map<std::string, int> vertex_map;					//maps vertex public id to private id
	
	int get_v() const { return V; }
	int get_e() const { return E; }
	double get_weight(Edge e) const { return e.weight; };
	double get_weight(int v, int w) const;						//returns edge weight based on two vertex IDs
	size_t get_outdegree(int v) const;
	size_t get_indegree(int v) const;
	
	bool map_insert(std::string, int);
	void add_edge(int v, int w);
	void add_edge(int v, int w, double weight);
	void add_edge(const std::string & s1, const std::string & s2);
	void add_edge(const std::string & s1, const std::string & s2, double weight);
	
	void add_vertex(const std::string & s);
	void add_vertex(int i);
	
	bool edge_exists(int v, int w) const;
	bool edge_exists(const std::string & s1, const std::string & s2) const;
	
	bool vertex_exists(std::string s) const;
	bool vertex_exists(int v) const;
	
	json to_json() const;
	std::vector<std::vector<int>> get_adj_list() const;
	std::vector<std::pair<int, int>> get_edge_list() const;
	std::string edge_list_to_string() const;
	
	bool graph_is_valid() const;
	bool equals(Digraph& other) const;
	
	std::stringstream describe() const;
	std::vector<int> get_vertex_list() const;

	bool operator== (Digraph & other) const
	{
		return (this == &other);
	}
	
};

bool is_valid_path(const Digraph & G, const std::vector<int> v);
