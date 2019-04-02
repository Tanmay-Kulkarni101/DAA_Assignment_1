#ifndef DATA
#define DATA
#include <iostream>
#include <vector>
#include "node.h"
/**
 * @brief 
 * This class is used to facilitate all the transactions between the dataset in a file and the execution apparatus
 */
class Data{
private:
	std::string filePath;
	std::string delim;
	public:
	static const int DATA_LINE_SIZE;
	static const std::string DEFAULT_DELIM;
	static const std::string DEFAULT_FILE_PATH;
	int generateTestCases(long long,double,double);
	std::vector<std::string> split(const char *str, char delim );
	std::vector<Node> get_data_from_file();
	std::string getDelim();
	std::string getFilePath();
	Data(std::string filePath,std::string delim);
	Data();
};


#endif
