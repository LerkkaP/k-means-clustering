#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <numeric>

int getClosestCluster(double point, const std::vector<double> &centroids);
double getNewCentroid(const std::vector<double> &cluster);
std::vector<std::vector<double>> kMeansClustering(const int k, const std::vector<double> &data);

int main()
{

    std::vector<double> data = {1.0, 2.0, 3.5, 10.0, 12.0, 11.5};
    const int k { 2 };

    std::vector<std::vector<double>> clusters { kMeansClustering(k, data) };

    // For debugging
    for (size_t i = 0; i < clusters.size(); ++i) {
        std::cout << "Cluster " << i << ": ";
        for (double val : clusters[i]) {
            std::cout << val << ' ';
        }
        std::cout << '\n';
    }
    return 0;
}

std::vector<std::vector<double>> kMeansClustering(const int k, const std::vector<double> &data)
{
    std::vector<double> centroids = {10.0, 12.0};
    std::vector<std::vector<double>> clusters(k);
    
    int iterations { };
    constexpr int max_iters { 10 };

    while (iterations <= max_iters) {
        // Start with empty clusters at each iteration
        clusters = std::vector<std::vector<double>>(k);

        // Assign point to nearest cluster
        for (double point : data) {
            int closestCluster = getClosestCluster(point, centroids);
            clusters[closestCluster].push_back(point);
        }

        // Update centroids
        centroids.clear();
        for (const std::vector<double> &cluster : clusters) {
            double newMean = getNewCentroid(cluster);
            centroids.push_back(newMean);
        }
        ++iterations;
    }
    return clusters;
}

int getClosestCluster(double point, const std::vector<double> &centroids) 
{
    double minDistance = std::numeric_limits<double>::max();
    int closestCluster { -1 };

    for (int i = 0; i < centroids.size(); ++i) {
        double distance = abs(point - centroids[i]);
        if (distance < minDistance) {
            minDistance = distance;
            closestCluster = i;
        }
    }
    return closestCluster;
}

double getNewCentroid(const std::vector<double> &cluster) {
    double newMean = std::reduce(cluster.begin(), cluster.end(), 0.0) / cluster.size();
    return newMean;
}