#include "matching_engine.h"
#include <cmath>
#include <cstring>
#include <climits>
#include <iostream>

using namespace std;

MatchingEngine::MatchingEngine() {
    order_capacity = 100;
    order_count = 0;
    orders = new DeliveryOrder[order_capacity];

    rider_capacity = 50;
    rider_count = 0;
    riders = new Rider[rider_capacity];
}

MatchingEngine::~MatchingEngine() {
    delete[] orders;
    delete[] riders;
}

void MatchingEngine::addOrder(DeliveryOrder order) {
    if (order_count >= order_capacity) {
        // 배열 확장 - 기존 데이터 복사
        int new_capacity = order_capacity * 2;
        DeliveryOrder* new_orders = new DeliveryOrder[new_capacity];
        memcpy(new_orders, orders, order_count * sizeof(DeliveryOrder));
        delete[] orders;
        orders = new_orders;
        order_capacity = new_capacity;
    }
    orders[order_count] = order;
    order_count++;
}

void MatchingEngine::addRider(Rider rider) {
    if (rider_count >= rider_capacity) {
        int new_capacity = rider_capacity * 2;
        Rider* new_riders = new Rider[new_capacity];
        memcpy(new_riders, riders, rider_count * sizeof(Rider));
        delete[] riders;
        riders = new_riders;
        rider_capacity = new_capacity;
    }
    riders[rider_count] = rider;
    rider_count++;
}

double MatchingEngine::calculateDistance(double lat1, double lng1, double lat2, double lng2) {
    double R = 6371.0;
    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLng = (lng2 - lng1) * M_PI / 180.0;
    double a = sin(dLat / 2) * sin(dLat / 2) +
               cos(lat1 * M_PI / 180.0) * cos(lat2 * M_PI / 180.0) *
               sin(dLng / 2) * sin(dLng / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    return R * c;
}

MatchResult* MatchingEngine::findBestMatch(int order_id) {
    DeliveryOrder* target = NULL;
    for (int i = 0; i < order_count; i++) {
        if (orders[i].id == order_id) {
            target = &orders[i];
            break;
        }
    }

    if (target == NULL) return NULL;

    double min_distance = 999999.0;
    int best_rider = -1;

    for (int i = 0; i < rider_count; i++) {
        if (riders[i].is_available) {
            double dist = calculateDistance(
                riders[i].current_lat, riders[i].current_lng,
                target->store_lat, target->store_lng
            );
            if (dist < min_distance) {
                min_distance = dist;
                best_rider = i;
            }
        }
    }

    if (best_rider == -1) return NULL;

    MatchResult* result = new MatchResult();
    result->order_id = order_id;
    result->rider_id = riders[best_rider].id;
    result->distance = min_distance;
    result->estimated_time = min_distance / 30.0 * 60.0;

    return result;
}

vector<MatchResult> MatchingEngine::matchAll() {
    vector<MatchResult> results;
    for (int i = 0; i < order_count; i++) {
        MatchResult* match = findBestMatch(orders[i].id);
        if (match != NULL) {
            results.push_back(*match);
            // 라이더를 사용 불가로 변경
            for (int j = 0; j < rider_count; j++) {
                if (riders[j].id == match->rider_id) {
                    riders[j].is_available = 0;
                    break;
                }
            }
            delete match;
        }
    }
    return results;
}

void MatchingEngine::clearAll() {
    order_count = 0;
    rider_count = 0;
}
