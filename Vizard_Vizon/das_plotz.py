import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np

hull_points = np.empty((0,2))
candidates = []
graph_points = []

fig,ax = plt.subplots()
plot, = ax.plot([],[],color='blue',animated=True)

def init():
	return plot,

def animate(i):
	ax.cla()
	global hull_points		
	if i == 0:
		hull_points = np.reshape(np.array(candidates[i,:]),(1,2))
	elif candidates[i] in hull_points and i != len(candidates) - 1:
		index = np.where((candidates[i] == hull_points).all(axis=1))[0][0]
		hull_points = np.delete(hull_points,index,axis=0)
	else:
		hull_points = np.vstack((hull_points,np.reshape(candidates[i,:],(1,2))))
	print(i)
	ax.scatter(graph_points[:,0],graph_points[:,1])
	ax.scatter(hull_points[:,0],hull_points[:,1],color='black')
	ax.plot(hull_points[:,0],hull_points[:,1],color='red')
	return plot,


def main():
	global candidates
	global graph_points
	with open("data/DataPoints.txt","r") as file_handle:
		for line in file_handle:
			line = line.strip()
			parts = line.split(" ")
			x = float(parts[0])
			y = float(parts[1])
			graph_points.append([x,y])

	

	file = int(input("Enter file to run:\n1: Graham Scan\n2: Jarvis March\n3:KPS\n"))
	if file == 1:
		with open('./visualizations/grahm_scan.txt','r') as file_handle:
			for line in file_handle:
				line = line.strip()
				parts = line.split(",")
				x = float(parts[0])
				y = float(parts[1])
				candidates.append([x,y])
	elif file == 2:
		with open('./visualizations/jarvis_march.txt','r') as file_handle:
			for line in file_handle:
				line = line.strip()
				parts = line.split(",")
				x = float(parts[0])
				y = float(parts[1])
				candidates.append([x,y])
	elif file == 3:
		with open('./visualizations/kps.txt','r') as file_handle:
			for line in file_handle:
				line = line.strip()
				parts = line.split(",")
				x = float(parts[0])
				y = float(parts[1])
				candidates.append([x,y])
	candidates = np.array(candidates)
	graph_points = np.array(graph_points)
	
	lowest_x,highest_x = (min(graph_points[:,0]),max(graph_points[:,0]))
	lowest_y,highest_y = (min(graph_points[:,1]),max(graph_points[:,1]))
	ax.set_xlim(lowest_x-10,highest_x+10)
	ax.set_ylim(lowest_y-10,highest_y+10)

	ax.scatter(graph_points[:,0],graph_points[:,1],color='red',zorder=1)
	ani = animation.FuncAnimation(fig, animate, init_func=init, frames=np.arange(0,len(candidates),1))
	Writer = animation.writers['ffmpeg']
	writer = Writer(fps=30, metadata=dict(artist='Me'), bitrate=1800)
	ani.save('gs.mp4',writer = writer)
	plot.set_data(candidates[:,0],candidates[:,1])
	plt.show()

if __name__ == '__main__':
	main()