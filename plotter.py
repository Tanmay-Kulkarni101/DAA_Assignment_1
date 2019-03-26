import matplotlib.pyplot as plt

def main():
    data_points=readData()
    plt.style.use('seaborn-whitegrid')
    plt.plot(data_points[:][0],data_points[:][1])
if __name__ == main():
    main()
