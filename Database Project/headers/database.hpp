#include "part.hpp"

class database {
public:
	std::string filepath;
	std::vector<part> parts;
	std::string dbText;

	// constrcutor for database class
	database(std::string file) {
		this->filepath = file;
	}

	// std::find doesn't work, so a function to find the index of the part matching the id passed into the function is necessary
	int findPart(std::string partID) {
		int count = 0;
		for (int i = 0; i < parts.size(); ++i) {
			if (parts[i].id == partID) {
				count = i;
				break;
			}
		}
		return count;
	}

	// initializes the database, runs download.py to get the latest version of data.csv from firebase. 
	void init(void) {
		system("cd C:\\Users\\Pranav\\Desktop\\Database Project\\ && python -u download.py");

		std::ifstream in(filepath);

		std::string temp;

		// pushes the current data into the vector parts for easy manipulation and writing. 
		while (!in.eof()) {
			std::string tempPart[3];

			std::getline(in, temp);

			std::istringstream ss(temp);
			std::string temp2;

			int i = 0;

			while (std::getline(ss, temp2, ',')) {
				tempPart[i] = temp2;
				++i;
			}

			parts.push_back(part(tempPart[0], tempPart[1], std::atoi(tempPart[2].c_str())));
		}
		in.close();
	}

	void addPart(part newPart) {
		parts.push_back(newPart);
	}

	// edits the quantity of the part that matches the id passed into the function. 
	void editPart(std::string id, int newQuantity) {
		parts[findPart(id)].quantity = newQuantity;
	}

	void deletePart(std::string id) {
		parts.erase(parts.begin() + findPart(id) - 1);
	}

	// writes all data from the vector into data.csv, uploads data.csv to firebase. 
	void close(void) {
		std::ofstream out(filepath, std::ofstream::out | std::ofstream::trunc);
		for (int i = 0; i < parts.size(); ++i) {
			if (i != parts.size() - 1)
				out << parts[i].id << "," << parts[i].type << "," << std::to_string(parts[i].quantity) << std::endl;
			else
				out << parts[i].id << "," << parts[i].type << "," << std::to_string(parts[i].quantity);
		}
		out.close();

		system("cd C:\\Users\\Pranav\\Desktop\\Database Project\\ && python -u upload.py");
	}

	void inputCmd(std::string input) {
		if (input.substr(0, 7) == "addPart") { // works
			std::cout << "ADD WORKING" << std::endl;
			std::cout << input << std::endl;
			dbText.clear();
			input = input.substr(8, input.length() - 7);
			input = input.substr(0, input.size() - 1);
			std::cout << input << std::endl;
			std::vector<std::string> temp;
			std::istringstream ss(input);
			std::string i;
			while(std::getline(ss, i, ',')) {
				temp.push_back(i);
				std::cout << i << std::endl;
			}
			part Part(temp[0], temp[1], std::atoi(temp[2].c_str()));
			addPart(Part);
			dbText = "Part Added!";
		}
		else if (input.substr(0, 8) == "editPart") { // works
			std::cout << "EDIT WORKING" << std::endl;
			
			dbText.clear();
			input = input.substr(9, input.size() - 8);
			input = input.substr(0, input.size() - 1);
			std::istringstream ss(input);
			std::string i, store[2];
			int k = 0;
			while(std::getline(ss, i, ',')) {
				store[k] = i;
				std::cout << i;
				++k;
			}
			editPart(store[0], std::atoi(store[1].c_str()));
			close();
			dbText = store[0] + " has been updated to reflect new count of " + store[1];
		}
		else if (input.substr(0, 10) == "deletePart") { // deletes random part?????? idk (fix this one) 
			dbText.clear();
			input = input.substr(11, 10);
			input = input.substr(0, input.size() - 1);
			deletePart(input);
		}
		else if (input.substr(0, 10) == "updateData") { // works
			close();
		}
		else if (input.substr(0, 10) == "displayAll") { // works
			dbText.clear();
			for (int i = 0; i < parts.size(); ++i) {
				dbText += parts[i].id + " " + parts[i].type + " " + std::to_string(parts[i].quantity) + "\n";
			}
		}
		else if (input.substr(0, 11) == "displayPart") { // works
			dbText.clear();
			input = input.substr(12, input.size() - 11);
			input = input.substr(0, input.size() - 1);
			part temp = parts[findPart(input)];
			dbText = temp.id + " " + temp.type + " " + std::to_string(temp.quantity) + "\n";
		}
		else if (input.substr(0, 4) == "exit") { // works
			dbText.clear();
			dbText = "EXITING, ALL CHANGES WILL BE UPLOADED";
			close();
			exit(0);
		}
		
	}
};