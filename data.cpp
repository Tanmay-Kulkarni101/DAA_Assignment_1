#include <iostream>
#include <random>
#include <fstream>
#include <string>
#include  "data.h"

int Data::generateTestCases(int numberOfTestCases,double lower_bound,double upper_bound){
	fstream file;
	file.open(filePath,ios::out);
	std::default_random_engine generator;
	std::uniform_real_distribution<double> distribution(lower_bound,upper_bound);
	if(file.is_open()){
		std::cout<<"Opened the file successfully\n";
		for(int i=0;i<numberOfTestCases;i++){
			char[DATA_LINE_SIZE] record;
			double x = distribution(generator);
			double y = distribution(generator);
			record = sprintf("%lf%s%lf\n",x,delim.c_str(),y);
			file << record;
		}
	}
	else{
		std::cout<<"Could not find the file location\n";
	}
	
	return 0;
}
std::string Data::getDelim(){
	return delim;
}
std::string Data::getFilePath(){
	return filePath;
}
Data::Data(std::string filePath,std::string delim){
	this->filePath=filePath;
	this->delim=delim;
}
Data::Data(){
	this->filePath=DEFAULT_FILE_PATH;
	this->delim=DEFAUT_DELIM;
}
