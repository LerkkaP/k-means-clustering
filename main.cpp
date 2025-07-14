#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

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
    std::vector<std::vector<double>> clusters = {{10.0}, {12.0}};
    int iterations { };

    for (double point : data) {
        double minDistance = std::numeric_limits<double>::max();
        int closestCluster { -1 };

        for (int i = 0; i <= 1; ++i) {
            double distance = abs(point - clusters[i][0]);
            if (distance < minDistance) {
                minDistance = distance;
                closestCluster = i;
            }
        } 
        clusters[closestCluster].push_back(point);
        std::cout << "The closest cluster for point " << point << " is " << closestCluster << '\n';

    }
    
    return clusters;
}
