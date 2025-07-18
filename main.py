import pandas as pd
import kmeans

data = [1.0, 2.0, 3.5, 10.0, 12.0, 11.5]
k = 2

clusters = kmeans.kMeansClustering(k, data)

for i, cluster in enumerate(clusters):
    print(f"Cluster {i}: {cluster}")

#df = pd.read_csv("data/mall_customers.csv")
#annual_incomes = df["Annual Income (k$)"]
