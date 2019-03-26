import matplotlib.pyplot as plt
from hulls import *
def main():
	data_points=readData()
	plt.style.use('seaborn-whitegrid')
	x = [item[0] for item in data_points]
	y = [item[1] for item in data_points]
	plt.scatter(x,y,color='green',marker='o')
	plt.show()

	results = []
	with open("./data/attempts.txt","r") as file_handle:
		for line in file_handle:
			line = line.strip()
			parts = line.split(" ")
			x = float(parts[0])
			y = float(parts[1])
			z = float(parts[2])
			a = float(parts[3])
			b = float(parts[4])
			results += [(x,y,z,a,b)]

	for result in results:
		
		if result[4] == 0:
			plt.plot(result[0:2],result[2:4],color='red')
		else:
			plt.plot(result[0:2],result[2:4],color='white')

	plt.show()
			
if __name__ == main():
	main()
