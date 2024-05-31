#ifndef _FIREWALL_SRC_FIREWALL_DB_H
#define _FIREWALL_SRC_FIREWALL_DB_H

#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "convert.h"
#include "packet.h"
#include "rule.h"

#define FW_DEFAULT_ACTION DROP

#define FW_DB_LINE_SRC_FORMAT "src: %18s%n"
#define FW_DB_LINE_SPORT_FORMAT "sport: %hd%n"
#define FW_DB_LINE_DST_FORMAT "dst: %18s%n"
#define FW_DB_LINE_DPORT_FORMAT "dport: %hd%n"
#define FW_DB_LINE_PROTO_FORMAT "proto: %3s%n"
#define FW_DB_LINE_ACTION_FORMAT "%6s"

#define FW_DB_LINE_REGEX                                                       \
  "^(\\s*src:\\s*"                                                             \
  "((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(25[0-5]|2[0-4][0-9]|[01]?["  \
  "0-9][0-9]?)(\\/((3[0-2])|([1-2][0-9])|([1-9])))?)?(\\s*sport:\\s*"          \
  "((6553[0-5])|(655[0-2][0-9])|(65[0-4][0-9]{2})|(6[0-4][0-9]{3})|([1-5][0-"  \
  "9]{4})|([0-5]{0,5})|([0-9]{1,4})))?(\\s*dst:\\s*"                           \
  "((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(25[0-5]|2[0-4][0-9]|[01]?["  \
  "0-9][0-9]?)(\\/((3[0-2])|([1-2][0-9])|([1-9])))?)?(\\s*"                    \
  "dport:\\s*"                                                                 \
  "((6553[0-5])|(655[0-2][0-9])|(65[0-4][0-9]{2})|(6[0-4][0-9]{3})|([1-5][0-"  \
  "9]{4})|([0-5]{0,5})|([0-9]{1,4})))?(\\s*proto:\\s*(tc|ud)p)?\\s*(=>)? *"    \
  "(DROP|ACCEPT)\\s*\n?$"

fw_rule_t *fw_rule_from_file(const char *file);

enum fw_action fw_rule_process_packet(const fw_rule_t *rules,
                                      const fw_packet_t *packet);

void fw_rule_free(fw_rule_t *rules);

#endif //_FIREWALL_SRC_FIREWALL_DB_H
