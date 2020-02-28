# DAA_Assignment_1
The objective of this assignment is to implement convex hull algorithms and visualize them with the help of python

## Basic Structures
It consists of two main packages
- Refactored Code: Optimized code to monitor performance
- Vizard Vision: The same code without performance gimmicks to visualize the performance of algorithms.

## Algorithms Implemented
- Performance for Graham Scan
![Graham Scan](https://github.com/Tanmay-Kulkarni101/DAA_Assignment_1/blob/master/Graham%20Scan.png)
- Performance for Jarvis March
![Jarvis March](https://github.com/Tanmay-Kulkarni101/DAA_Assignment_1/blob/master/Jarvis%20March.png)
- Performance for Kirkpatrik Siedel
![Kirkpatrik Seidel](https://github.com/Tanmay-Kulkarni101/DAA_Assignment_1/blob/master/Kirkpatrick%20Seidel.png)

## Instructions to run
The entry point for each packages is the corresponding ```main.cpp```

Use the following command to compile

```g++ main.cpp graph.cpp edge.cpp data.cpp node.cpp```

taken from [Dependency.txt](https://github.com/Tanmay-Kulkarni101/DAA_Assignment_1/blob/master/Vizard_Vizon/Dependencies.txt)

### Run Visualization
You can run the Visualizations with the help of [Vizard_Vizon/script.sh](https://github.com/Tanmay-Kulkarni101/DAA_Assignment_1/blob/master/Vizard_Vizon/script.sh)

```
  
#! /usr/bin/bash
g++ main.cpp graph.cpp edge.cpp data.cpp node.cpp
./a.out
python3 das_plotz.py
```

### Test the Performance
You can test the performance with the help of [Refactored Code/script.sh](https://github.com/Tanmay-Kulkarni101/DAA_Assignment_1/blob/master/Refactored%20Code/script.sh)

```
#! /bin/bash
g++ main.cpp graph.cpp edge.cpp data.cpp node.cpp
./a.out
```
Link to the [Performance Report](https://github.com/Tanmay-Kulkarni101/DAA_Assignment_1/blob/master/Timings.html)


## Authors
- Tanmay Kulkarni
- Aditya Srikanth
- Vishal Chokala
