/*
   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <esp_log.h>
#include <stdlib.h>
#include <string.h>

#include <esp_matter.h>
#include <driver/uart.h>

#include "app_priv.h"

using namespace chip::app::Clusters;
using namespace esp_matter;

static const char *TAG = "app_driver";
extern uint16_t projector_endpoint_id;
bool current_power = false;

/* Do any conversions/remapping for the actual value here */
static esp_err_t app_driver_projector_set_power(esp_matter_attr_val_t *val)
{
    bool power = val->val.b;
    // if (power == current_power) {
    //     return ESP_ERR_INVALID_ARG;
    // }

    if (power) {
            ESP_LOGI(TAG, "Set power: on");
        uart_write_bytes(UART_NUM_1, optoma_on, OPTOMA_DATA_LEN);
    } else {

            ESP_LOGI(TAG, "Set power: off");
        uart_write_bytes(UART_NUM_1, optoma_off, OPTOMA_DATA_LEN);
    }

    current_power = power;

    return ESP_OK;
}

esp_err_t app_driver_attribute_update(uint16_t endpoint_id, uint32_t cluster_id,
                                      uint32_t attribute_id, esp_matter_attr_val_t *val)
{
    ESP_LOGI(TAG, "app_driver_attribute_update");
    esp_err_t err = ESP_OK;
    if (endpoint_id == projector_endpoint_id) {
        if (cluster_id == OnOff::Id) {
            if (attribute_id == OnOff::Attributes::OnOff::Id) {
                err = app_driver_projector_set_power(val);
            }
        }
    }
    return err;
}

esp_err_t app_driver_projector_set_defaults(uint16_t endpoint_id)
{
    esp_err_t err = ESP_OK;
    node_t *node = node::get();
    endpoint_t *endpoint = endpoint::get(node, endpoint_id);
    cluster_t *cluster = NULL;
    attribute_t *attribute = NULL;
    esp_matter_attr_val_t val = esp_matter_invalid(NULL);

    /* Setting power */
    cluster = cluster::get(endpoint, OnOff::Id);
    attribute = attribute::get(cluster, OnOff::Attributes::OnOff::Id);
    attribute::get_val(attribute, &val);
    err |= app_driver_projector_set_power(&val);

    return err;
}

void app_driver_projector_init()
{
    // Configure UART parameters
    uart_config_t uart_config = {
        .baud_rate = UART_BAUD_RATE,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };

    // Configure UART pins
    uart_param_config(UART_NUM_1, &uart_config);
    uart_set_pin(UART_NUM_1, TXD_PIN, RXD_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);

    // Install UART driver using an event queue to send/receive data
    uart_driver_install(UART_NUM_1, 1024, 0, 0, NULL, 0);
    return;
}

