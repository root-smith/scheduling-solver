#pragma once

#include <vector>
#include <utility>
#include <string>
#include "json.hpp"

using json = nlohmann::json;

class Vertex{
private:
	std::string id;
	static int newUID;
	const int UID;
public:
	Vertex()
		: UID(newUID++)
	{
	}
	Vertex(const std::string & newid)
		: UID(newUID++), id(newid)
	{
	}
};
