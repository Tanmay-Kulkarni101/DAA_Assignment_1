import matplotlib.pyplot as plt
import numpy as np
def main():
	hull_points = []
	graph_points = []
	with open("output.txt","r") as file_handle:
		for line in file_handle:
			line = line.strip()
			parts = line.split(",")
			x = float(parts[0])
			y = float(parts[1])
			hull_points.append([x,y])

	with open("data/DataPoints.txt","r") as file_handle:
		for line in file_handle:
			line = line.strip()
			parts = line.split(" ")
			x = float(parts[0])
			y = float(parts[1])
			graph_points.append([x,y])

	hull_points = np.array(hull_points)
	graph_points = np.array(graph_points)
	print(hull_points[:,0])
	plt.scatter(graph_points[:,0],graph_points[:,1],zorder=1)
	plt.scatter(hull_points[:,0],hull_points[:,1],color='black',zorder=2)
	plt.plot(hull_points[:,0],hull_points[:,1],color='red',zorder=2)
	# res = [[0.001420,6.100933],
	# [0.001852,2.614026],
	# [0.004346,3.191505],
	# [0.002183,4.935350],
	# [0.001708,4.791094],
	# [0.011080,0.622821]]
	# res = np.array(res)
	# p_max = [[0.001420,6.100933],
	# [0.011080,0.622821],
	# [0.001708 , 4.791094],
	# [0.001852 , 2.614026],
	# [0.001420,6.100933]]
	# p_max = np.array(p_max)
	# plt.scatter(res[:,0],res[:,1])
	# plt.scatter(p_max[:,0],p_max[:,1],color='red')
	plt.show()

if __name__ == '__main__':
	main()