#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <numeric>

int getClosestCluster(double point, std::vector<double> centroids);
double getNewCentroid(std::vector<double> cluster);
std::vector<std::vector<double>> kMeansClustering(const int k, const std::vector<double> &data);

int main()
{

    std::vector<double> data = {1.0, 2.0, 3.5, 10.0, 12.0, 11.5};
    const int k { 2 };

    std::vector<std::vector<double>> clusters { kMeansClustering(k, data) };

    for (int i = 0; i <= 1; ++i) {
        std::cout << clusters[i][0];
    }

    return 0;
}

std::vector<std::vector<double>> kMeansClustering(const int k, const std::vector<double> &data)
{
    std::vector<double> centroids = {10.0, 12.0};
    std::vector<std::vector<double>> clusters(k);
    int iterations { };
    constexpr int MAX_ITERS { 10 };

    while (iterations <= MAX_ITERS) {
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

int getClosestCluster(double point, std::vector<double> centroids) 
{
    double minDistance = std::numeric_limits<double>::max();
    int closestCluster { -1 };

    for (int i = 0; i <= 1; ++i) {
        double distance = abs(point - centroids[i]);
        if (distance < minDistance) {
            minDistance = distance;
            closestCluster = i;
        }
    }
    return closestCluster;
}

double getNewCentroid(std::vector<double> cluster) {
    double newMean = std::reduce(cluster.begin(), cluster.end(), 0.0) / cluster.size();
    return newMean;
}