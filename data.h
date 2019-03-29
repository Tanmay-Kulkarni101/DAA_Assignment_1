#ifndef DATA
#define DATA
#include<iostream>
class Data{
private:
	std::string filePath;
	std::string delim;
	public:
	static const int DATA_LINE_SIZE = 20;
	static const std::string DEFAULT_DELIM = " ";
	static const std::string DEFAULT_FILE_PATH = "./data/DataPoints.txt" 
	int generateTestCases();
	std::string getDelim();
	std::string getFilePath();
	Data(std::string filePath,std::string delim);
	Data();
};

#endif
