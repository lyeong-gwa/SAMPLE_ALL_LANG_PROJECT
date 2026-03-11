#include "pos_interface.h"
#include <stdio.h>

int main() {
    printf("DeliveryHub POS Module v0.1.0\n\n");

    // POS 장치 연결
    PosDevice device;
    pos_connect(&device, "192.168.1.100", POS_PORT);

    // 주문 생성
    PosOrder* order = pos_create_order("홍길동", "맛있는치킨");
    pos_add_item(order, "후라이드치킨", 18000, 1);
    pos_add_item(order, "양념치킨", 19000, 1);
    pos_add_item(order, "콜라 1.5L", 2500, 2);

    // 주문 전송
    pos_send_order(&device, order);

    // 영수증 출력
    pos_print_receipt(order);

    // 상태 확인
    int status = pos_receive_status(&device, order->order_id);
    printf("주문 상태: %s\n", status == 1 ? "접수완료" : "대기중");

    // 정리
    pos_free_order(order);
    pos_disconnect(&device);

    return 0;
}
