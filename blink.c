/**
 * Copyright (c) 2022 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "btstack_run_loop.h"
#include "pico/stdlib.h"
#include "btstack_event.h"
#include "pico/cyw43_arch.h"
#include "pico/btstack_cyw43.h"
#include "hal_led.h"
#include "btstack.h"
#include "ble/gatt-service/nordic_spp_service_server.h"
#include "mygatt.h"

static hci_con_handle_t con_handle = HCI_CON_HANDLE_INVALID;
static btstack_context_callback_registration_t send_request;
static btstack_packet_callback_registration_t  hci_event_callback_registration;
static int led_on = true;

const uint8_t adv_data[] = {
    // Flags general discoverable, BR/EDR not supported
    2, BLUETOOTH_DATA_TYPE_FLAGS, 0x06, 
    // Name
    8, BLUETOOTH_DATA_TYPE_COMPLETE_LOCAL_NAME, 'n', 'R', 'F',' ', 'S', 'P', 'P',
    // UUID ...
    17, BLUETOOTH_DATA_TYPE_COMPLETE_LIST_OF_128_BIT_SERVICE_CLASS_UUIDS, 0x9e, 0xca, 0xdc, 0x24, 0xe, 0xe5, 0xa9, 0xe0, 0x93, 0xf3, 0xa3, 0xb5, 0x1, 0x0, 0x40, 0x6e,
};
const uint8_t adv_data_len = sizeof(adv_data);

static void hci_packet_handler (uint8_t packet_type, uint16_t channel, uint8_t *packet, uint16_t size){
    UNUSED(channel);
    UNUSED(size);

    if (packet_type != HCI_EVENT_PACKET) return;

    switch (hci_event_packet_get_type(packet)) {
        case HCI_EVENT_DISCONNECTION_COMPLETE:
            con_handle = HCI_CON_HANDLE_INVALID;
            break;
        default:
            break;
    }
}

static void nordic_spp_packet_handler(uint8_t packet_type, uint16_t channel, uint8_t *packet, uint16_t size){
    UNUSED(channel);
    switch (packet_type){
        case HCI_EVENT_PACKET:
            if (hci_event_packet_get_type(packet) != HCI_EVENT_GATTSERVICE_META) break;
            switch (hci_event_gattservice_meta_get_subevent_code(packet)){
                case GATTSERVICE_SUBEVENT_SPP_SERVICE_CONNECTED:
                    con_handle = gattservice_subevent_spp_service_connected_get_con_handle(packet);
                    printf("Connected with handle 0x%04x\n", con_handle);
                    break;
                case GATTSERVICE_SUBEVENT_SPP_SERVICE_DISCONNECTED:
                    con_handle = HCI_CON_HANDLE_INVALID;
                    break;
                default:
                    break;
            }
            break;
        case RFCOMM_DATA_PACKET:
       
          led_on = !led_on;
          // send small letter t to toggle led
          if (packet[0] == 0x74) cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, led_on);
 
            printf("RECV: ");
            printf_hexdump(packet, size);
            break;
        default:
            break;
    }
}

int main() {
    stdio_init_all();
 if (cyw43_arch_init()) {
        printf("failed to initialise cyw43_arch\n");
        return -1;
    }
  
  
    hci_event_callback_registration.callback = &hci_packet_handler;
    hci_add_event_handler(&hci_event_callback_registration);
    
    l2cap_init();
    sm_init();
    att_server_init(profile_data, NULL, NULL);
    nordic_spp_service_server_init(&nordic_spp_packet_handler);

    uint16_t adv_int_min = 0x0030;
    uint16_t adv_int_max = 0x0030;
    uint8_t adv_type = 0;
    bd_addr_t null_addr;
    memset(null_addr, 0, 6);
    gap_advertisements_set_params(adv_int_min, adv_int_max, adv_type, 0, null_addr, 0x07, 0x00);
    gap_advertisements_set_data(adv_data_len, (uint8_t*) adv_data);
    gap_advertisements_enable(1);
    

	hci_power_control(HCI_POWER_ON);
 
    btstack_run_loop_execute();
    return 0;
}
