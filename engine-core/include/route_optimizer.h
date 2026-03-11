#ifndef ROUTE_OPTIMIZER_H
#define ROUTE_OPTIMIZER_H

#include <vector>

struct Location {
    double lat;
    double lng;
    char name[100];
};

struct Route {
    std::vector<int> waypoint_indices;
    double total_distance;
    double estimated_minutes;
};

class RouteOptimizer {
public:
    RouteOptimizer();
    ~RouteOptimizer();

    Route optimize(std::vector<Location>& locations);
    double calculateTotalDistance(std::vector<Location>& locations, std::vector<int>& order);

private:
    double haversine(double lat1, double lng1, double lat2, double lng2);
    Route nearestNeighbor(std::vector<Location>& locations);
};

#endif
