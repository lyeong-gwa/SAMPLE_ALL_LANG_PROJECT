#include "route_optimizer.h"
#include <cmath>
#include <algorithm>
#include <climits>

using namespace std;

RouteOptimizer::RouteOptimizer() {}
RouteOptimizer::~RouteOptimizer() {}

double RouteOptimizer::haversine(double lat1, double lng1, double lat2, double lng2) {
    double R = 6371.0;
    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLng = (lng2 - lng1) * M_PI / 180.0;
    double a = sin(dLat / 2) * sin(dLat / 2) +
               cos(lat1 * M_PI / 180.0) * cos(lat2 * M_PI / 180.0) *
               sin(dLng / 2) * sin(dLng / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    return R * c;
}

double RouteOptimizer::calculateTotalDistance(vector<Location>& locations, vector<int>& order) {
    double total = 0.0;
    for (int i = 0; i < order.size() - 1; i++) {
        total += haversine(
            locations[order[i]].lat, locations[order[i]].lng,
            locations[order[i + 1]].lat, locations[order[i + 1]].lng
        );
    }
    return total;
}

Route RouteOptimizer::nearestNeighbor(vector<Location>& locations) {
    int n = locations.size();
    vector<bool> visited(n, false);
    Route route;
    route.waypoint_indices.push_back(0);
    visited[0] = true;

    for (int step = 1; step < n; step++) {
        int current = route.waypoint_indices.back();
        double min_dist = 999999.0;
        int nearest = -1;

        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                double dist = haversine(
                    locations[current].lat, locations[current].lng,
                    locations[i].lat, locations[i].lng
                );
                if (dist < min_dist) {
                    min_dist = dist;
                    nearest = i;
                }
            }
        }

        if (nearest != -1) {
            route.waypoint_indices.push_back(nearest);
            visited[nearest] = true;
        }
    }

    route.total_distance = calculateTotalDistance(locations, route.waypoint_indices);
    route.estimated_minutes = route.total_distance / 30.0 * 60.0;
    return route;
}

Route RouteOptimizer::optimize(vector<Location>& locations) {
    if (locations.size() <= 1) {
        Route route;
        if (locations.size() == 1) route.waypoint_indices.push_back(0);
        route.total_distance = 0;
        route.estimated_minutes = 0;
        return route;
    }
    return nearestNeighbor(locations);
}
