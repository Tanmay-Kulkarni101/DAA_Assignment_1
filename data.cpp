#include <iostream>
#include  "data.h"

static const int DATA_LINE_SIZE = 20; 
int Data::generateTestCases(){
	return 0;
}
std::string Data::getDelim(){
	return delim;
}
std::string Data::getFilePath(){
	return filePath;
}
Data::Data(std::string filePath,char delim){
	this->filePath=filePath;
	this->delim=delim;
}

