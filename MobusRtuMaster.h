#ifndef __MODBUSRTUMASTER_h
#define __MODBUSRTUMASTER_h
#include <stdio.h>
#include <stdint.h>
#include <string.h>
void read_mudbus_holding_register_massage(uint8_t *sendbuf,uint16_t sendlen,uint8_t station,uint16_t address,uint16_t len);
void write_mudbus_holding_register_massage_uint16(uint8_t *sendbuf,uint16_t sendlen,uint8_t station,uint16_t address,uint16_t len,uint16_t *writebuf);
void write_mudbus_holding_register_massage_int32(uint8_t *sendbuf,uint16_t sendlen,uint8_t station,uint16_t address,uint16_t len,int32_t *writebuf);
void write_mudbus_holding_register_massage_char(uint8_t *sendbuf,uint16_t sendlen,uint8_t station,uint16_t address,uint16_t len,char *writebuf);
int write_mudbus_holding_register_reply(uint8_t *reply_buf,uint16_t reply_len,uint8_t station);
int analysis_read_recevice_to_uint16(uint8_t *rcv_buf,uint16_t rcv_len,uint8_t station,uint16_t *holding_register);
int analysis_read_recevice_to_int32(uint8_t *rcv_buf,uint16_t rcv_len,uint8_t station,int32_t *holding_register);
int analysis_read_recevice_to_char(uint8_t *rcv_buf,uint16_t rcv_len,uint8_t station,char *holding_register);


#endif