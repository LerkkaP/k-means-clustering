#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <numeric>

std::vector<std::vector<double>> kMeansClustering(const int k, const std::vector<double> &data);

int main()
{

    std::vector<double> data = {1.0, 2.0, 3.5, 10.0, 12.0, 11.5};
    const int k { 2 };

    std::vector<std::vector<double>> clusters { kMeansClustering(k, data) };

    return 0;
}

std::vector<std::vector<double>> kMeansClustering(const int k, const std::vector<double> &data)
{
    std::vector<double> centroids = {10.0, 12.0};
    std::vector<std::vector<double>> clusters(2);
    int iterations { };
    constexpr int MAX_ITERS { 10 };

    while (iterations <= MAX_ITERS) {
        for (double point : data) {
            double minDistance = std::numeric_limits<double>::max();
            int closestCluster { -1 };

            for (int i = 0; i <= 1; ++i) {
                double distance = abs(point - centroids[i]);
                if (distance < minDistance) {
                    minDistance = distance;
                    closestCluster = i;
                }
            } 
            clusters[closestCluster].push_back(point);
        }
        centroids = {};
        for (std::vector<double> cluster : clusters) {
            double mean = std::reduce(cluster.begin(), cluster.end(), 0.0) / cluster.size();
            centroids.push_back(mean);
        }
        ++iterations;
    }
    return clusters;
}
