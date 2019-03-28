
import numpy as np
import os

def generateData():
	number_of_points = 20

	if os.path.isdir("./data") is False:
		os.mkdir("./data")

		data_points=[]
		for i in range(0,number_of_points):
			x=np.random.uniform(0,10)
			y=np.random.uniform(0,10)
			data_points += [(x,y)]

		with open("./data/DataPoints.txt","w") as file_handle:
			for i in range(0,number_of_points):
				file_handle.write("{0} {1}\n".format(data_points[i][0],data_points[i][1]) )


	print("Data Generated\n")


def main():
	generateData()
if __name__ == '__main__':
	main()
