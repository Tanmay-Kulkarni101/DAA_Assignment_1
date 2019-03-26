from genData import *

def readData():

	data_points = []

	with open("./data/DataPoints.txt","r") as file_handle:

		for line in file_handle:
			line = line.strip()
			parts = line.split(" ")
			x = float(parts[0])
			y = float(parts[1])
			data_points += [(x,y)]

	return data_points

def get_orientation(point1,point2,point3):
	# PQ x QR

	result = ( (point2[0]-point1[0])*(point3[1]-point2[1]) - (point3[0]-point2[0])*(point2[1]-point1[1]) )

	if result > 0:
	 	return True
	else:
		return False


def grahm_scan(data_points):
	file_handle=open("./data/attempts.txt","w")
	print("Running grahm scan\n")
	print(data_points)
	hull_points = []
	sorted_points = sorted(data_points,key=lambda x:x[0]) # sort by x coordinate

	if len(data_points) <= 3:
		hull_points = data_points

	else:
		hull_points += [sorted_points[0]]

		stack = [sorted_points[0]]
		file_handle.write("{0} {1} 0\n".format(sorted_points[0][0],sorted_points[0][1]))
		stack += [sorted_points[1]]

		for i in range(2,len(sorted_points)):
			if len(stack)>1 and get_orientation(stack[-2],stack[-1],sorted_points[i]) is False :
				file_handle.write("{0} {1} -1\n".format(stack[-1][0],stack[-1][1]))
				stack.pop()
			else:
				file_handle.write("{0} {1} 0\n".format(stack[-1][0],stack[-1][1]))
				stack += [sorted_points[i]]

		if len(stack)<=2:
			print("No Hull found")
		else:
			hull_points=stack
			print("The hull is made up of")
			print(hull_points)

	file_handle.close()



def jarvis_march(data_points):
	pass


def main():
	generateData()
	data_points = readData()
	option = input("Which convex hull is desired\n 1. Grahm Scan \n 2. JarvisMarch\n")
	try:
		option = int(option)
		if option == 1 :
			grahm_scan(data_points)

		elif option == 2 :
			jarvis_march(data_points)

		else:
			print("Invalid option Terminating program, this option does not exist")

	except ValueError:
		print("Invalid option Terminating program, input is not an integer")

if __name__ == "__main__":
	main()
