import genData

def readData():
	
	data_points = []

	with open("./data/DataPoints.txt","r") as file_handle:
		line = file_handle.readline()
		line = line.trim()
		parts = line.split(" ")
		x = parts[0]
		y = parts[1]
		data_points += [(x,y)]

	return data_points

def grahm_scan(data_points):
	pass


def jarvis_march(data_points):
	
	hull_points = []
	sorted_points = sorted(data_points,key=lambda x:x[0]) # sort by x coordinate

	if len(data_points) <= 3:
		hull_points = data_points

	else:	
		hull_points += [sorted_points[0]]
		

	while()

def main():
	genData()
	data_points = readData()
	option = input("Which convex hull is desired\n 1. Grahm Scan \n2. JarvisMarch\n")
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

if "__name__" == "__main__":
	main()
