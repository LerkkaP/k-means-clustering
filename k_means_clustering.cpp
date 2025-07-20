#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <vector>
#include <cmath>
#include <limits>
#include <numeric>
#include <random>
#include <iostream>
#include <unordered_set>

int getClosestCluster(double point, const std::vector<double> &centroids);
double getNewCentroid(const std::vector<double> &cluster);
std::vector<std::vector<double>> kMeansClustering(const int k, const std::vector<double> &data);
std::vector<double> initializeCentroids(const int k, const std::vector<double> &data);

std::vector<std::vector<double>> kMeansClustering(const int k, const std::vector<double> &data)
{
    /*for (double point : data) {
        std::cout << point << '\n';
    }*/
    
    std::vector<double> centroids{initializeCentroids(k, data)};
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

std::vector<double> initializeCentroids(const int k, const std::vector<double> &data)
{
    std::vector<double> centroids{};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, data.size() - 1);
    std::unordered_set<int> used_indices;

    while (centroids.size() < k) {
        int index = dis(gen);
        if (used_indices.insert(index).second) {
            centroids.push_back(data[index]);
        }
    }
    return centroids;
}

PYBIND11_MODULE(kmeans, m) {
    m.def("kMeansClustering", &kMeansClustering, "Run k-means clustering",
          pybind11::arg("k"), pybind11::arg("data"));
}