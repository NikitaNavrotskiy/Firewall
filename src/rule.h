#ifndef _FIREWALL_SRC_RULE_H
#define _FIREWALL_SRC_RULE_H

#include <stdint.h>

#include "packet.h"

enum fw_action { ACCEPT, DROP };

typedef struct fw_rule {
  char daddr[16];
  char saddr[16];
  uint16_t dport;
  uint16_t sport;
  enum fw_proto proto;
  enum fw_action action;
  struct fw_rule *next;
} fw_rule_t;

#endif //_FIREWALL_SRC_RULE_H
