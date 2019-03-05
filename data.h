#ifndef DATA
#define DATA
#include<bits/stdc++.h>
class Data{
private:
	std::string filePath;
	std::string delim;
	public:
	static const int DATA_LINE_SIZE = 20;
	int generateTestCases();
	std::string getDelim();
	std::string getFilePath();
	Data(std::string filePath,char delim=',');
};

#endif
