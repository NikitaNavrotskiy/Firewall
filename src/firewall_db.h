#ifndef _FIREWALL_SRC_FIREWALL_DB_H
#define _FIREWALL_SRC_FIREWALL_DB_H

#include <stdbool.h>
#include <stdlib.h>

#include "packet.h"
#include "rule.h"

fw_rule_t *fw_rule_from_file(const char *file);

enum fw_action fw_rule_process_packet(const fw_rule_t *rules,
                                      const fw_packet_t *packet);

void fw_rule_free(fw_rule_t *rules);

#endif //_FIREWALL_SRC_FIREWALL_DB_H
