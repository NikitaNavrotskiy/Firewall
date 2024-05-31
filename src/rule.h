#ifndef _FIREWALL_SRC_RULE_H
#define _FIREWALL_SRC_RULE_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "packet.h"

enum fw_action { ACCEPT, DROP };

typedef struct fw_rule {
  uint32_t saddr;
  uint32_t daddr;
  struct fw_rule *next;
  uint16_t sport;
  uint16_t dport;
  enum fw_proto proto;
  enum fw_action action;
  uint8_t smask;
  uint8_t dmask;
} fw_rule_t;

fw_rule_t *fw_rule_new(uint32_t src, uint8_t smask, uint32_t dst, uint8_t dmask,
                       uint16_t sport, uint16_t dport, enum fw_proto proto,
                       enum fw_action action, fw_rule_t *next);

#endif //_FIREWALL_SRC_RULE_H
