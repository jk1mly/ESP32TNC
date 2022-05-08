#include <stdio.h>
#include <string.h>
#include "driver/i2c.h"
#include "sdkconfig.h"
#include "esp_log.h"
#include "bk4802p.h"

static const char TAG[] = "bk4802p";

void writeReg(uint8_t addr, uint8_t data1, uint8_t data2)
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, ((BK4802_ADDRESS << 1) & 0xFE) | WRITE_BIT, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, addr, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, data1, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, data2, ACK_CHECK_EN);
    i2c_master_stop(cmd);
    i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 1 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
}

void trx_freq(void)
{

}

void trx_init(void)
{
    ESP_LOGI(TAG, "trx_init");

    i2c_config_t conf;
 
    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = I2C_MASTER_SDA_IO;
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    conf.scl_io_num = I2C_MASTER_SCL_IO;
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
    conf.master.clk_speed = I2C_MASTER_FREQ_HZ;
 
    i2c_param_config(I2C_MASTER_NUM, &conf);
    i2c_driver_install(I2C_MASTER_NUM, conf.mode, 0, 0, 0);
//    i2c_set_timeout(I2C_MASTER_NUM, 0xFFFFF);
    vTaskDelay(100 / portTICK_PERIOD_MS);

    trx_freq();
    trx_recv();
}

void trx_send(void)
{
    ESP_LOGI(TAG, "trx_send");

    const uint16_t snd_reg[24] = {
        0x518a,     // REG0 433.18M
        0x2e05,
        0x0000,
        0x0000,
        0x7c00,
        0x0004,     // REG5
        0xf140,
        0xed00,
        0x17e0,
        0xe0e4,
        0x8543,     // REG10 
        0x0700,
        0xa066,
        0xffff,
        0xffe0,
        0x061f,     // REG15
        0x9e3c,
        0x1f00,
        0xd1c1,
        0x200f,
        0x01ff,     // REG20
        0xe000,
        0x0340,
        0xaed0
    };

// set reg
    for(uint8_t lp = 4; lp < 24; lp++){
        uint8_t addr = (uint8_t)(lp & 0xFF);
        uint8_t data1 = (uint8_t)((snd_reg[lp] >> 8) & 0xFF);
        uint8_t data2 = (uint8_t)(snd_reg[lp] & 0xFF);
        writeReg(addr, data1, data2);
    }
// set freq
    for(uint8_t lp = 0; lp < 3; lp++){
        uint8_t addr = (uint8_t)(lp & 0xFF);
        uint8_t data1 = (uint8_t)((snd_reg[lp] >> 8) & 0xFF);
        uint8_t data2 = (uint8_t)(snd_reg[lp] & 0xFF);
        writeReg(addr, data1, data2);
    }
}

void trx_recv(void)
{
    ESP_LOGI(TAG, "trx_recv");

    const uint16_t rcv_reg[24] = {
        0x5183,     // REG0 433.18M
        0x93f6,
        0x0000,
        0x0000,
        0x0300,
        0x0c04,     // REG5
        0xf140,
        0xed00,
        0x17e0,
        0xe0e4,     
        0x8543,     // REG10
        0x0700,
        0xa066,
        0xffff,
        0xffe0,
        0x061f,     // REG15
        0x9e3c,
        0x1f00,
        0xd1d1,
        0x200f,
        0x01ff,     // REG20
        0xe000,
        0x1800,        
        0xacd0
    };

// set reg
    for(uint8_t lp = 4; lp < 24; lp++){
        uint8_t addr = (uint8_t)(lp & 0xFF);
        uint8_t data1 = (uint8_t)((rcv_reg[lp] >> 8) & 0xFF);
        uint8_t data2 = (uint8_t)(rcv_reg[lp] & 0xFF);
        writeReg(addr, data1, data2);
    }
// set freq
    for(uint8_t lp = 0; lp < 3; lp++){
        uint8_t addr = (uint8_t)(lp & 0xFF);
        uint8_t data1 = (uint8_t)((rcv_reg[lp] >> 8) & 0xFF);
        uint8_t data2 = (uint8_t)(rcv_reg[lp] & 0xFF);
        writeReg(addr, data1, data2);
    }
}
