#ifndef _FIREWALL_SRC_FIREWALL_DB_H
#define _FIREWALL_SRC_FIREWALL_DB_H

#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "packet.h"
#include "rule.h"

#define FW_DB_LINE_SRC_FORMAT "src: %15s%n"
#define FW_DB_LINE_SPORT_FORMAT "sport: %hd%n"
#define FW_DB_LINE_DST_FORMAT "dst: %15s%n"
#define FW_DB_LINE_DPORT_FORMAT "dport: %hd%n"
#define FW_DB_LINE_PROTO_FORMAT "proto: %3s%n"
#define FW_DB_LINE_ACTION_FORMAT "%6s"

#define FW_DB_LINE_REGEX                                                       \
  "( *src: *([0-9]{1,3}\\.){3}[0-9]{1,3}(\\/[0-9]{1,2})?)?( *sport: "          \
  "*[0-9]{1,5})?( *dst: *([0-9]{1,3}\\.){3}[0-9]{1,3}(\\/[0-9]{1,2})?)?( "     \
  "*dport: "                                                                   \
  "*[0-9]{1,5})?( *proto: (tc|ud)p)? *(=>)? *(DROP|ACCEPT) *\n?$"

fw_rule_t *fw_rule_from_file(const char *file);

enum fw_action fw_rule_process_packet(const fw_rule_t *rules,
                                      const fw_packet_t *packet);

void fw_rule_free(fw_rule_t *rules);

#endif //_FIREWALL_SRC_FIREWALL_DB_H
