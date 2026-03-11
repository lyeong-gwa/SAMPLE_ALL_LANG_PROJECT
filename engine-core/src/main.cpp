#include <iostream>
#include <cstring>
#include "matching_engine.h"
#include "route_optimizer.h"

using namespace std;

int main() {
    cout << "DeliveryHub Engine v0.1.0" << endl;

    MatchingEngine engine;

    // 테스트 데이터
    DeliveryOrder order1;
    order1.id = 1;
    order1.store_lat = 37.5665;
    order1.store_lng = 126.9780;
    order1.dest_lat = 37.5700;
    order1.dest_lng = 126.9820;
    order1.priority = 1;
    strcpy(order1.customer_name, "홍길동");
    strcpy(order1.store_name, "맛있는치킨");

    engine.addOrder(order1);

    Rider rider1;
    rider1.id = 1;
    rider1.current_lat = 37.5660;
    rider1.current_lng = 126.9770;
    rider1.is_available = 1;
    strcpy(rider1.name, "라이더1");
    rider1.total_deliveries = 150;

    engine.addRider(rider1);

    MatchResult* result = engine.findBestMatch(1);
    if (result != NULL) {
        cout << "매칭 완료 - 주문: " << result->order_id
             << " -> 라이더: " << result->rider_id
             << " (거리: " << result->distance << "km)" << endl;
        delete result;
    }

    return 0;
}
