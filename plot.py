import matplotlib.pyplot as plt
import numpy as np

def plot_clusters_1d(k, clusters):
    plt.ylim(-1, 1)
    for i in range(k):
        plt.scatter(clusters[i], np.zeros(len(clusters[i])))
    plt.savefig("clusters.png")
    plt.close()