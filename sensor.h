#ifndef SENSOR_H
#define SENSOR_H

#include "nrf24l01.h"

//TODO: Write sensor info compiler
struct sensor_info
{
    uint8_t nr;
    uint8_t type;
    uint8_t size;
    uint32_t min;
    uint32_t max;
    char name[10];
};

struct sensor_info_packet : public tiny_udp_packet
{
    sensor_info info;
};


#define sinfo(nr, type, size, scale, name) {nr, type, ((size) | ((scale) << 4)), 0, 0, name}
#define cinfo(nr, type, size, scale, min, max, name) {(nr+0x40), type, ((size) | ((scale) << 4)), min, max, name}

extern const sensor_info info_messages[];

inline void send_sensor_info(uint8_t nr)
{
    sensor_info_packet p;
    p.flags = 1;
    p.size = sizeof(sensor_info);
    memcpy_P(&p.info, &(info_messages[nr]), sizeof(sensor_info));
    send_udp_packet(p, server_ip, port_sensor_data);
}


#endif // SENSOR_H
