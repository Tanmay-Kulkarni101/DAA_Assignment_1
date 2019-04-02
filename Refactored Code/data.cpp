#include <iostream>
#include <random>
#include <fstream>
#include <string>
#include <cstdlib>
#include  "data.h"

/**
 * @brief 
 * default size of a record in the file
 */
const int Data::DATA_LINE_SIZE = 20;
/**
 * @brief 
 * the default delimiter to differentiate between entries within the file
 */
const std::string Data::DEFAULT_DELIM = " ";
/**
 * @brief 
 * The default file path within the project to store files
 */
const std::string Data::DEFAULT_FILE_PATH = "./data/DataPoints.txt";
/**
 * @brief 
 * This function takes the number of test cases,the mean of the normal distribution as well as the variance
 * Alternatively we can use it with a uniform distribution by changing the function call used in the code
 * @param numberOfTestCases 
 * It is the number of data points on which the algorithm has to run
 * @param mean 
 * It is the mean of the sampling distribution
 * @param variance 
 * It is the variance of the sampling distribution
 * @return int 
 * Returns 0 on successful execution, can be used for buffer overflows if the input is too large
 */
int Data::generateTestCases(long long numberOfTestCases,double mean,double variance){
	std::fstream file;
	file.open(filePath,std::ios::out);
	std::default_random_engine generator;
	// std::uniform_real_distribution<double> distribution(lower_bound,upper_bound);
	std::normal_distribution<double> distribution(mean,variance);
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

	file.close();
	return 0;
}
/**
 * @brief 
 * This is used to split the character array input based on a delimiter.
 * @param str 
 * The input character array
 * @param delim 
 * The delimiter that is used to divide the char array into parts
 * @return std::vector<std::string> 
 * It returns a vector of the string parts delimited by the delimiter character
 */
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
/**
 * @brief 
 * This function extracts the data stored in a text file and returns a vector of nodes
 * @return std::vector<Node> 
 */
std::vector<Node> Data::get_data_from_file(){
	std::fstream file;
	file.open(filePath,std::ios::in);

	std::vector<Node> values;
	if(file.is_open()){
		std::cout<<"File found, extracting the data\n";
		std::string line;
		while(std::getline(file,line)){
			std::vector<std::string> temp = split(line.c_str(),delim.at(0));
			// std::cout<<temp[0]<<","<<temp[1]<<"\n";
			char* term;
			double x = strtod(temp[0].c_str(),&term);
			if(*term!=0){
				std::cout<<"Not a double\n";
				exit(EXIT_FAILURE);
			}
			double y = strtod(temp[1].c_str(),&term);
			if(*term!=0){
				std::cout<<"Not a double\n";
				exit(EXIT_FAILURE);
			}

			Node temp_node = Node(x,y);
			values.push_back(temp_node);
		}
		std::cout<<"Data extracted successfully\n";
	}
	else{
		std::cout<<"The file is not found, either the file is not generated or the path provided "<<filePath<< " is incorrect\n";
		exit(EXIT_FAILURE);
	}

	return values;
}
/**
 * @brief 
 * The delimiter used to separate points
 * @return std::string 
 */
std::string Data::getDelim(){
	return delim;
}
/**
 * @brief 
 * The file path used to store the data points for which the convex hull is to be found
 * @return std::string 
 */
std::string Data::getFilePath(){
	return filePath;
}
/**
 * @brief Construct a new Data:: Data object
 * Constructor to create a data object that stores data in the location specified by filePath
 * @param filePath 
 * The path at which we can find the data points for the convex hull
 * @param delim 
 * The delimiter that separates the data points within the file
 */
Data::Data(std::string filePath,std::string delim){
	this->filePath=filePath;
	this->delim=delim;
}
/**
 * @brief Construct a new Data:: Data object
 * This is the default constructor that stores the hardcoded values for path and delimiter
 */
Data::Data(){
	this->filePath=DEFAULT_FILE_PATH;
	this->delim=DEFAULT_DELIM;
}
