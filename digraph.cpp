#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <map>
#include <unordered_set>
#include <typeinfo>

#include "digraph.hpp"

using namespace std;
using json = nlohmann::json;

//initalizes an empty digraph
Digraph::Digraph()
{
	V = 0;
	E = 0;
	next_id = 0;
}

Digraph::Digraph(const json& j)
{
	next_id = 0;
	
	int cnt_vert = 0;
	for (auto & vert : j["nodes"])
	{
		string s = vert["data"]["id"];
		vertex_list.emplace_back(Vertex(*this, s));
		//cout << s << '\n';
		++cnt_vert;
	}
	cout << "Count of vertices is " << cnt_vert << '\n';
	
	int cnt_edges = 0;
	for (auto & edge : j["edges"])
	{
		if (edge["data"].find("source") != edge["data"].end()
			&& edge["data"].find("target") != edge["data"].end() )
		{
			string s_source = edge["data"]["source"];
			string s_target = edge["data"]["target"];
			
			int from_n = stoi(s_source);
			int to_n = stoi(s_target);
			
			if ( edge["data"].find("weight") != edge["data"].end() )
			{
				string temp = edge["data"]["weight"];
				double weight = stoi(temp);
				new Edge(*this, from_n, to_n, weight);
			}
			else
			{
				new Edge(*this, from_n, to_n);
			}
			++cnt_edges;
		}
	}
	cout << "Count of edges from json is " << cnt_edges << '\n';
	cout << "Count of edges from digraph is " << get_e() << '\n';
}

bool Digraph::map_insert(std::string s, int i)
{
	auto res = vertex_map.insert( std::make_pair(s, i) );
	return res.second;
}

double Digraph::get_weight(int v, int w) const
{
	auto it = find_if( begin(adj[v]), end(adj[v]),
					  [&w](const Edge & e){ return e.to_n == w;} );
	return (*it).to_n;
}

bool Digraph::vertex_exists(string s) const
{
	auto it = find_if( begin(vertex_list), end(vertex_list),
					  [&s](const Vertex & v){ return v.public_id == s;} );
	
	return (it != vertex_list.end());
}

bool Digraph::vertex_exists(int i) const
{
	return vertex_exists(std::to_string(i));
}

bool Digraph::edge_exists(const string & s1, const string & s2) const
{
	if ( !vertex_exists(s1) || !vertex_exists(s2) )
		return false;

	int id_from = vertex_map.at(s1);
	int id_to = vertex_map.at(s2);
	
	auto it = find_if( begin(adj[id_from]), end(adj[id_from]),
					[&id_to](const Edge & e)
					{
						return e.to_n == id_to;
					} );
	//if not unfound, return true
	return ( it != end(adj[id_from]) );
}

bool Digraph::edge_exists(int v, int w) const
{
	return edge_exists(to_string(v), to_string(w));
}

size_t Digraph::get_outdegree(int v) const
{
	return adj[v].size();
}

size_t Digraph::get_indegree(int v) const
{
	return indegree[v];
}

void Digraph::add_edge(const string & s1, const string & s2, double weight)
{
	if (!edge_exists(s1,s2))
		new Edge(*this, s1, s2, weight);
}

void Digraph::add_edge(int v, int w)
{
	add_edge(to_string(v), to_string(w), 0.0);
}

void Digraph::add_edge(int v, int w, double weight)
{
	add_edge(to_string(v), to_string(w), weight);
}

void Digraph::add_vertex(const string & s)
{
	if (!vertex_exists(s))
		new Vertex(*this, s);
}

void Digraph::add_vertex(int i)
{
	add_vertex(to_string(i));
}



json Digraph::to_json() const
{

	int cnt_edge = 0;
	const auto edge_list = Digraph::get_edge_list();
	map<string, pair<int, int>> m;
	
	for (auto i : edge_list)
		m.emplace(to_string(cnt_edge++), i );
	
	//generate vertex list from edge list
	vector<int> vertex_list;
	for (auto i : edge_list)
	{
		vertex_list.push_back(i.first);
		vertex_list.push_back(i.second);
	}
	
	json j;
	j["edge_list"] = m;
	j["edges"] = cnt_edge;
	j["vertices"] = vertex_list.size();
	
	//cout << "j: " << j << '\n';
	
	return j;	
}

vector<pair<int, int>> Digraph::get_edge_list() const
{

	vector<pair<int, int>> edge_list;
	
	//cout << "Edge list: \n";
	
	//adj is std::vector<std::vector<Edge>>
	for (auto v : adj)
		for(auto e : v)
			edge_list.emplace_back(pair<int,int>{e.from_n, e.to_n});
	
	return edge_list;
}

string Digraph::edge_list_to_string() const
{
	auto edge_list = Digraph::get_edge_list();
	string s;
	
	for (auto vertex: edge_list)
	{
		s.append( "<" + to_string(vertex.first) + "," + to_string(vertex.second) + ">\n");
	}
	return s;
}

bool Digraph::graph_is_valid() const
{
	auto edge_list = get_edge_list();
	vector<int> vertex_list;
	
	for (auto i : edge_list)
	{
		vertex_list.push_back(i.first);
		vertex_list.push_back(i.second);
	}
	
	if (edge_list.size() == E && vertex_list.size() == adj.size() && adj.size() == V)
		return true;
	else
		return false;
}
vector<int> Digraph::get_vertex_list() const
{
	//generate vertex list from edge list
	auto edge_list = get_edge_list();
	vector<int> vertex_list;
	
	for (auto i : edge_list)
	{
		vertex_list.push_back(i.first);
		vertex_list.push_back(i.second);
	}
	return vertex_list;
}
	
stringstream Digraph::describe() const
{
	stringstream ss;
	
	auto vertex_list = get_vertex_list();
	auto edge_list = get_edge_list();
	
	ss << "graph_is_valid: " << graph_is_valid() << '\n';
	ss << "edge_list:\n" << edge_list_to_string() << '\n';
	ss << "edge_list.size(): " << edge_list.size() << '\n';
	ss << "Edges: " << get_e() << '\n';
	ss << "Vertices: " << get_v() << '\n';
	ss << "vertex_list.size(): " << vertex_list.size() << '\n';
	ss << "adj.size(): " << adj.size() << '\n';
	ss << "adj list: \n";
	
	for (auto v : adj)
	{
		for (Edge e : v)
			cout << e.to_n;
		cout << '\n';
	}
	
	return ss;
}

vector<vector<int>> Digraph::get_adj_list() const
{
	//returns internal vector<vector<Edge>> as vector<vector<int>>
	//where int is adjacent node IDs
	vector<vector<int>> ret;
	
	cout << "Get adj list: \n";
	
	for (auto v : adj)
	{
		vector<int> t;
		for (Edge e : v)
			t.emplace_back(e.to_n);
		ret.push_back(t);
	}
	return ret;
}

bool is_valid_path(const Digraph & G, const std::vector<int> v)
{
	bool flag = true;
		
	for (size_t i = 0; i < v.size()-1; i++)
		if (!G.edge_exists(v[i],v[i+1]))
			flag = false;
	return flag;
}


