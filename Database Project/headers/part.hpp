#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>

// part class, stores essential data. 
class part {
public:
	part(std::string id, std::string type, int quantity) {
		this->id = id;
		this->type = type;
		this->quantity = quantity;
	}

	std::string id;
	std::string type;
	int quantity;
};