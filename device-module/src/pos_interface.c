#include "pos_interface.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int next_order_id = 1;

int pos_connect(PosDevice* device, const char* ip, int port) {
    if (device == NULL) return -1;

    strncpy(device->ip_address, ip, sizeof(device->ip_address) - 1);
    device->ip_address[sizeof(device->ip_address) - 1] = '\0';
    device->port = port;
    device->is_connected = 1;
    sprintf(device->device_id, "POS-%s-%d", ip, port);

    printf("[POS] 연결됨: %s:%d\n", ip, port);
    return 0;
}

int pos_disconnect(PosDevice* device) {
    if (device == NULL) return -1;
    device->is_connected = 0;
    printf("[POS] 연결 해제: %s\n", device->device_id);
    return 0;
}

PosOrder* pos_create_order(const char* customer, const char* store) {
    PosOrder* order = (PosOrder*)malloc(sizeof(PosOrder));
    if (order == NULL) {
        printf("[POS] 메모리 할당 실패\n");
        return NULL;
    }
    order->order_id = next_order_id++;
    order->item_count = 0;
    order->total_price = 0;
    order->status = 0;
    strncpy(order->customer_name, customer, MAX_NAME_LEN - 1);
    order->customer_name[MAX_NAME_LEN - 1] = '\0';
    strncpy(order->store_name, store, MAX_NAME_LEN - 1);
    order->store_name[MAX_NAME_LEN - 1] = '\0';
    return order;
}

int pos_add_item(PosOrder* order, const char* name, int price, int quantity) {
    if (order->item_count >= MAX_MENU_ITEMS) {
        printf("[POS] 메뉴 항목 초과\n");
        return -1;
    }

    MenuItem* item = &order->items[order->item_count];
    item->id = order->item_count + 1;
    strncpy(item->name, name, MAX_NAME_LEN - 1);
    item->name[MAX_NAME_LEN - 1] = '\0';
    item->price = price;
    item->quantity = quantity;
    order->item_count++;

    return 0;
}

int pos_calculate_total(PosOrder* order) {
    int total = 0;
    int i;
    for (i = 0; i < order->item_count; i++) {
        total = total + order->items[i].price * order->items[i].quantity;
    }
    order->total_price = total;
    return total;
}

int pos_send_order(PosDevice* device, PosOrder* order) {
    if (!device->is_connected) {
        printf("[POS] 연결되지 않음\n");
        return -1;
    }

    pos_calculate_total(order);
    order->status = 1;

    printf("[POS] 주문 전송 - ID: %d, 고객: %s, 금액: %d원\n",
           order->order_id, order->customer_name, order->total_price);

    return 0;
}

int pos_receive_status(PosDevice* device, int order_id) {
    if (!device->is_connected) return -1;
    // 시뮬레이션: 항상 성공 반환
    return 1;
}

void pos_print_receipt(PosOrder* order) {
    printf("\n========== 영수증 ==========\n");
    printf("주문번호: %d\n", order->order_id);
    printf("고객: %s\n", order->customer_name);
    printf("가맹점: %s\n", order->store_name);
    printf("----------------------------\n");

    int i;
    for (i = 0; i < order->item_count; i++) {
        printf("%-20s x%d  %d원\n",
               order->items[i].name,
               order->items[i].quantity,
               order->items[i].price * order->items[i].quantity);
    }

    printf("----------------------------\n");
    printf("총 금액: %d원\n", order->total_price);
    printf("============================\n\n");
}

void pos_free_order(PosOrder* order) {
    free(order);
}
