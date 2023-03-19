/*
   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#pragma once

#include <esp_err.h>
#include <esp_matter.h>

#define TXD_PIN 17
#define RXD_PIN 16
#define UART_BAUD_RATE 9600

#define OPTOMA_DATA_LEN 8
static const uint8_t optoma_on[OPTOMA_DATA_LEN] = {
    0x7E, 0x30, 0x30, 0x30, 0x30, 0x20, 0x31, 0x0D
};

static const uint8_t optoma_off[OPTOMA_DATA_LEN] = {
    0x7E, 0x30, 0x30, 0x30, 0x30, 0x20, 0x30, 0x0D
};

/** Initialize the projector driver
 *
 * This initializes the projector driver associated with the selected board.
 */
void app_driver_projector_init();

/** Driver Update
 *
 * This API should be called to update the driver for the attribute being updated.
 * This is usually called from the common `app_attribute_update_cb()`.
 *
 * @param[in] endpoint_id Endpoint ID of the attribute.
 * @param[in] cluster_id Cluster ID of the attribute.
 * @param[in] attribute_id Attribute ID of the attribute.
 * @param[in] val Pointer to `esp_matter_attr_val_t`. Use appropriate elements as per the value type.
 *
 * @return ESP_OK on success.
 * @return error in case of failure.
 */
esp_err_t app_driver_attribute_update(uint16_t endpoint_id, uint32_t cluster_id,
                                      uint32_t attribute_id, esp_matter_attr_val_t *val);

/** Set defaults for projector driver
 *
 * Set the attribute drivers to their default values from the created data model.
 *
 * @param[in] endpoint_id Endpoint ID of the driver.
 *
 * @return ESP_OK on success.
 * @return error in case of failure.
 */
esp_err_t app_driver_projector_set_defaults(uint16_t endpoint_id);
