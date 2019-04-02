#include "data.h"
#include "graph.h"
#include <chrono>
/*! \mainpage Convex Hull Algorithms
 *
 * \section intro Introduction
 *
 * The objective of this code is to run convex hull algorithms and understand and analuyze their execution times.
 * In addition, we have plotted the working of the program as an mp4 file to help visualize the working of each.
 * Here we have made use of three algorithms:
 * 	- Graham Scan
 * 	- Jarvis March
 * 	- Kirk-Patrick Sidele Algorithm
 * \section install Installation
 *	There are two folders
 *   - Refactored Code
 *   - Vizard_Vizon
 *
 * The first contains the optimized code for testing the run time of each the second contains the additional code for visualization
 * \subsection step1 Testing the performance:
 * Navigate to the Refactored code folder.<br>
 * To test the performance run the command-<br>
 * <b>bash script</b><br>
 * Take user input from the terminal.
 * The performace for each will be displayed on the terminal output.<br>
 * <b>Note: This currently supports up to 10^7 data points</b>
 * \subsection step2 Testing the Visualization:
 * Navigate to the Vizard_Vizon folder.<br>
 * To test the performance run the command-<br>
 * <b>bash script</b><br>
 * Take user input from the terminal.<br>
 * After the execution is complete, there will be an animated plot of the working depending on the option that has been taken.<br>
 * In addition, there will be gifs generated, so that we do not have to run the algorithm one more time.<br>
 * \subsection step3 Conclusions:
 * Jarvis march performs better on an average, however, the difference between them is not significant, in the sense that they both run in the same order of time.<br>
 * However, Kirkpartik-Sidel does not seem to scale up to that factor due to the fact that the use of vectors is not efficient due to the large number of memory operations.
 */

/**
 * @brief
 * This is the dirver function that runs the whole program
 */
const double mean = 0;
const double variance = 10;
int main(){

	Data data; // calls default constructor

	long long  number_of_test_cases;
	cout << "Enter number of points\n";
	cin >> number_of_test_cases;

	data.generateTestCases(number_of_test_cases,mean,variance);
	Graph graph = Graph(data);

	for (int i=0;i<3;i++){

		Graph graph = Graph(data);
		if(i == 0){
			puts("KPS");
			auto start = std::chrono::system_clock::now();
			graph.kirk_patrick_seidel();
			auto end = std::chrono::system_clock::now();
			auto elapsed = end - start;
			std::cout << "KPS: "<< elapsed.count() << '\n';
		}
		else if(i == 1){
			puts("GS");
			auto start = std::chrono::system_clock::now();
			graph.graham_scan();
			auto end = std::chrono::system_clock::now();
			auto elapsed = end - start;
			std::cout<< "GS: " << elapsed.count() << '\n';
		}
		else if(i == 2){
			puts("JM");
			auto start = std::chrono::system_clock::now();
			graph.jarvis_march();
			auto end = std::chrono::system_clock::now();
			auto elapsed = end - start;
			std::cout<< "JM: " << elapsed.count() << '\n';
		}
	}

	return 0;
}
