#ifndef _FIREWALL_SRC_PACKET_H
#define _FIREWALL_SRC_PACKET_H

#include <stdint.h>

#include "convert.h"

enum fw_proto { NONE = 0, TCP = 6, UDP = 17, ANY = 18 };

typedef struct {
  uint32_t saddr;
  uint32_t daddr;
  uint16_t dport;
  uint16_t sport;
  enum fw_proto proto;
} fw_packet_t;

void fw_packet_fill(fw_packet_t *packet, const char *saddr, const char *daddr,
                    int sport, int dport, int proto);

#endif //_FIREWALL_SRC_PACKET_H
