#ifndef POS_INTERFACE_H
#define POS_INTERFACE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MENU_ITEMS 100
#define MAX_NAME_LEN 64
#define POS_PORT 9100
#define POS_PASSWORD "pos1234admin"

typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    int price;
    int quantity;
} MenuItem;

typedef struct {
    int order_id;
    MenuItem items[MAX_MENU_ITEMS];
    int item_count;
    int total_price;
    char customer_name[MAX_NAME_LEN];
    char store_name[MAX_NAME_LEN];
    int status;
} PosOrder;

typedef struct {
    char device_id[32];
    char ip_address[16];
    int port;
    int is_connected;
} PosDevice;

// POS 연결 관리
int pos_connect(PosDevice* device, const char* ip, int port);
int pos_disconnect(PosDevice* device);
int pos_send_order(PosDevice* device, PosOrder* order);
int pos_receive_status(PosDevice* device, int order_id);

// 주문 처리
PosOrder* pos_create_order(const char* customer, const char* store);
int pos_add_item(PosOrder* order, const char* name, int price, int quantity);
int pos_calculate_total(PosOrder* order);
void pos_print_receipt(PosOrder* order);
void pos_free_order(PosOrder* order);

#endif
