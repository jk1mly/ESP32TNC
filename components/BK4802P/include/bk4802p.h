#include <stdio.h>
#include <string.h>
#include "driver/i2c.h"
#include "sdkconfig.h"

#define I2C_MASTER_SCL_IO 22			/*!< gpio number for I2C master clock */
#define I2C_MASTER_SDA_IO 21			/*!< gpio number for I2C master data  */
#define I2C_MASTER_NUM I2C_NUM_1		/*!< I2C port number for master dev */
#define I2C_MASTER_FREQ_HZ 100000		/*!< I2C master clock frequency */
#define I2C_MASTER_TX_BUF_DISABLE 0             /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE 0             /*!< I2C master doesn't need buffer */

#define WRITE_BIT I2C_MASTER_WRITE              /*!< I2C master write */
#define READ_BIT I2C_MASTER_READ                /*!< I2C master read */
#define ACK_CHECK_EN 0x1                        /*!< I2C master will check ack from slave*/
#define ACK_CHECK_DIS 0x0                       /*!< I2C master will not check ack from slave */
#define ACK_VAL 0x0                             /*!< I2C ack value */
#define NACK_VAL 0x1                            /*!< I2C nack value */

#define BK4802_ADDRESS 0x48

/*
 * BK4802P init
 */
void trx_init(void);

/*
 * BK4802P recv
 */
void trx_recv(void);

/*
 * BK4802P send
 */
void trx_send(void);

