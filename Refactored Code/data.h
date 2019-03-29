#ifndef DATA
#define DATA
#include <iostream>
#include <vector>
#include "node.h"
class Data{
private:
	std::string filePath;
	std::string delim;
	public:
	static const int DATA_LINE_SIZE;
	static const std::string DEFAULT_DELIM;
	static const std::string DEFAULT_FILE_PATH;
	int generateTestCases(int,double,double);
	std::vector<std::string> split(const char *str, char delim );
	std::vector<Node> get_data_from_file();
	std::string getDelim();
	std::string getFilePath();
	Data(std::string filePath,std::string delim);
	Data();
};


#endif
