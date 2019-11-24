#ifndef SENSOR_H
#define SENSOR_H

#include "nrf24l01.h"
#include "tinyudp.h"
#include "utils.h"

#define server_ip 1
#define port_sensor_data 0

struct sensor_info
{
    uint8_t nr;
    uint8_t type;
    uint8_t size;
    uint32_t min;
    uint32_t max;
    char name[10];
};

struct sensor_info_packet : public TinyUDP::Packet
{
    sensor_info info;
};

// Sensor types (st)
enum {
    st_raw = 0,
    st_debug = 1,
    st_temperature = 2,
    st_humidity = 3,
    st_pressure = 4,
    st_light = 5,
    st_sound = 6,
    st_gas = 7,
    st_fan = 8,
    st_voltage = 9,
    st_scanner = 10,
    st_printer = 11,
    st_current = 12,
    st_power = 13,
    st_energy = 14,
    st_unixtime = 15,
    st_seconds = 16,
};

// Sensor size (ss)
enum {
    ss_uint8 = 1,
    ss_int8 = 2,
    ss_uint16 = 3,
    ss_int16 = 4,
    ss_uint32 = 5,
    ss_int32 = 6,
    ss_float = 7,
    ss_double = 8
};

// Sensor scale (sc)
enum {
    sc_1 = 0,
    sc_0_1 = 1,
    sc_0_01 = 2,
    sc_0_001 = 3,
    sc_0_0001 = 4,
    sc_10 = 5,
    sc_100 = 6,
    sc_1000 = 7,
    sc_10000 = 8
};

#define sinfo(nr, type, size, scale, name) {nr, type, ((size) | ((scale) << 4)), 0, 0, name}
#define cinfo(nr, type, size, scale, min, max, name) {(nr+0x40), type, ((size) | ((scale) << 4)), min, max, name}
#define ginfo(num_sensors, num_controls, name) {0xff, num_sensors, num_controls, 0, 0, name}

static inline void send_sensor_info_P(const sensor_info *msg)
{
    sensor_info_packet p;
    p.flags = 1;
    p.set_payload_size(sizeof(sensor_info));
    memcpy_P(&p.info, msg, sizeof(sensor_info));
    TinyUDP::send(p, server_ip, port_sensor_data);
}

static inline void send_sensor_data(TinyUDP::Packet &packet)
{
    TinyUDP::send(packet, server_ip, port_sensor_data);
}

#endif // SENSOR_H
