#ifndef _FIREWALL_SRC_PROCESS_H
#define _FIREWALL_SRC_PROCESS_H

#include <regex.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "arg.h"
#include "convert.h"
#include "firewall_db.h"
#include "packet.h"
#include "rule.h"

#define FW_REGEX_IP                                                            \
  "^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(25[0-5]|2[0-4][0-9]|[01]?[" \
  "0-9][0-9]?)$"

#define FW_PROCESS_FORMAT "%15s %15s %5d %5d %2d"

#define FW_PROCESS_LOG_FORMAT                                                  \
  "INFO\tsrc: %15s:%-5hu\tdst: %15s:%-5hu\tproto: %3s\tstatus: %6s\n"

int fw_process_input(fw_opt_t *options, fw_rule_t *rules);

#endif
