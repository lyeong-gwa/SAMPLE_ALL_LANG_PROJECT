#ifndef MATCHING_ENGINE_H
#define MATCHING_ENGINE_H

#include <string>
#include <vector>

struct DeliveryOrder {
    int id;
    double store_lat;
    double store_lng;
    double dest_lat;
    double dest_lng;
    int priority;
    char customer_name[50];
    char store_name[50];
};

struct Rider {
    int id;
    double current_lat;
    double current_lng;
    int is_available;
    char name[50];
    int total_deliveries;
};

struct MatchResult {
    int order_id;
    int rider_id;
    double distance;
    double estimated_time;
};

class MatchingEngine {
public:
    MatchingEngine();
    ~MatchingEngine();

    void addOrder(DeliveryOrder order);
    void addRider(Rider rider);
    MatchResult* findBestMatch(int order_id);
    std::vector<MatchResult> matchAll();
    double calculateDistance(double lat1, double lng1, double lat2, double lng2);
    void clearAll();

private:
    DeliveryOrder* orders;
    int order_count;
    int order_capacity;
    Rider* riders;
    int rider_count;
    int rider_capacity;
};

#endif
