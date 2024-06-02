/**
 * @file process.h
 */

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

/**
 * @brief Regular expression for ip address.
 */
#define FW_REGEX_IP                                                            \
  "^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(25[0-5]|2[0-4][0-9]|[01]?"  \
  "["                                                                          \
  "0-9][0-9]?)$"

/**
 * @brief Format string to sscanf packet.
 */
#define FW_PROCESS_FORMAT "%15s %15s %5d %5d %2d"

/**
 * @brief Format string for fprintf to write log.
 */
#define FW_PROCESS_LOG_FORMAT                                                  \
  "INFO\tsrc: %-s:%-10hu\tdst: %-s:%-10hu\tproto: %3s\tstatus: %6s\n"

/**
 * @brief Function that process input packets.
 *
 * @param options Program options stored in struct fw_opt.
 * @param rules Pointer to head of forward list with rules.
 * @return Status code.
 */
int fw_process_input(fw_opt_t *options, fw_rule_t *rules);

#endif
