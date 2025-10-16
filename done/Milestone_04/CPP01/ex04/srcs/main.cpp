#include <iostream>
#include <fstream>
#include <string>

std::string replaceS(std::string line, std::string find, std::string replace){
	std::string result;
	int pos = 0;
	if (find.empty())
		return (line);
	int found = line.find(find, pos);
	while (found != -1){
		result += line.substr(pos, found - pos);
		result += replace;
		pos = found + find.length();
		found = line.find(find, pos);
	}
	result += line.substr(pos);
	return (result);
}

int main(int ac, char **av) {
	if (ac != 4){
		std::cout << "Invalid. filename and string to find and string to replace" << std::endl;
		return 1;
	}
	std::ifstream infile(av[1]);
	if (!infile){
		std::cerr << "failed to open infile" << std::endl;
		return 1;
	}
	std::string name = std::string(av[1]) + ".replace";
	std::ofstream outfile(name.c_str());
	if (!outfile){
		std::cerr << "failed to open outfile" << std::endl;
		return 1;
	}
	std::string line;
	std::string s1 = av[2];
	std::string s2 = av[3];
	while (std::getline(infile, line)){
		std::string mod = replaceS(line, s1, s2);
		outfile << mod << std::endl;
	}


	return 0;
}
