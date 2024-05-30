#ifndef _FIREWALL_SRC_PACKET_H
#define _FIREWALL_SRC_PACKET_H

#include <stdint.h>

enum fw_proto { TCP = 6, UDP = 17, ANY = 18 };

typedef struct {
  char daddr[16];
  char saddr[16];
  uint16_t dport;
  uint16_t sport;
  enum fw_proto proto;
} fw_packet_t;

#endif //_FIREWALL_SRC_PACKET_H
