## comments section

CC = g++ 	# compiler to use
TARGET = output # where all the code compiles

all: 
	$(CC)   data.cpp edge.cpp graph.cpp mujeHullMilGaya.cpp node.cpp stack.cpp utilities.cpp -o $(TARGET)

clear: rm $(TARGET)	
