#ifndef RESOURCE_H
#define RESOURCE_H

#include <iostream>

class Resource {
public:
	std::string _dataPath;

	Resource(std::string dataPath);
	~Resource();

	void fileName(std::string name);
};

#endif