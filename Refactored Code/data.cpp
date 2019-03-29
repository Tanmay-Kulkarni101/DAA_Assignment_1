#include <iostream>
#include <random>
#include <fstream>
#include <string>
#include <cstdlib>
#include  "data.h"

const std::string Data::DEFAULT_DELIM = " ";
const std::string Data::DEFAULT_FILE_PATH = "./data/DataPoints.txt";
int Data::generateTestCases(int numberOfTestCases,double lower_bound,double upper_bound){
	std::fstream file;
	file.open(filePath,std::ios::out);
	std::default_random_engine generator;
	std::uniform_real_distribution<double> distribution(lower_bound,upper_bound);
	if(file.is_open()){
		std::cout<<"Opened the file successfully\n";
		for(int i=0;i<numberOfTestCases;i++){
			char record[DATA_LINE_SIZE];
			double x = distribution(generator);
			double y = distribution(generator);
			sprintf(record,"%lf%s%lf\n",x,delim.c_str(),y);
			file << record;
		}
		std::cout<<"The file has been written successfully\n";
	}
	else{
		std::cout<<"Could not find the file location\n";
	}
	
	return 0;
}
std::vector<std::string> Data::split(const char *str, char delim )
{
    std::vector<std::string> result;

    do
    {
        const char *begin = str;

        while(*str != delim && *str)
            str++;

        result.push_back(std::string(begin, str));
    } while (0 != *str++); // First check then update

    return result;
}
std::vector<Node> Data::get_data_from_file(){
	std::fstream file;
	file.open(filePath,std::ios::in);

	std::vector<Node> values;
	if(file.is_open()){
		std::cout<<"File found, extracting the data\n";
		std::string line;
		while(std::getline(file,line)){
			std::vector<std::string> temp = split(line.c_str(),delim.at(0));
			char* term;
			double x = strtod(temp[0].c_str(),&term);
			if(term!=NULL){
				std::cout<<"Not a double\n";
				exit(EXIT_FAILURE);
			}
			double y = strtod(temp[1].c_str(),&term);
			if(term!=NULL){
				std::cout<<"Not a double\n";
				exit(EXIT_FAILURE);
			}

			Node temp_node = Node(x,y);
			values.push_back(temp_node);
		}
	}
	else{
		std::cout<<"The file is not found, either the file is not generated or the path provided "<<filePath<< " is incorrect\n";
		exit(EXIT_FAILURE);
	}

	return values;
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
	this->delim=DEFAULT_DELIM;
}
