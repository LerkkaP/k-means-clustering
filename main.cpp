#include <iostream>
#include <vector>

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

    for (double point: data) {
        std::cout << point;
    }
    return clusters;
}
