/**
 * @file rule.h
 */

#ifndef _FIREWALL_SRC_RULE_H
#define _FIREWALL_SRC_RULE_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "packet.h"

/**
 * @brief Enumeration descibes actions to packet.
 * ACCEPT Accept packet.
 * DROP Drop packet.
 */
enum fw_action {
  /**
   * @brief Accept packet.
   */
  ACCEPT,

  /**
   * @brief Drop packet.
   */
  DROP
};

/**
 * @struct fw_rule
 * @brief Store info about rule of firewall.
 * @var saddr Source ip address.
 * @var daddr Destination ip address.
 * @var next Pointer to next rule (Forward list).
 * @var sport Source port.
 * @var dport Destination port.
 * @var proto Protocol.
 * @var action Action for the rule.
 * @var smask Subnet mask for source ip address.
 * @var dmask Subnet mask for destination ip address.
 */
typedef struct fw_rule {
  /**
   * @brief Source ip address.
   */
  uint32_t saddr;

  /**
   * @brief Destination ip address.
   */
  uint32_t daddr;

  /**
   * @brief Pointer to next rule.
   */
  struct fw_rule *next;

  /**
   * @brief Source port.
   */
  uint16_t sport;

  /**
   * @brief Destination port.
   */
  uint16_t dport;

  /**
   * @brief Protocol.
   */
  enum fw_proto proto;

  /**
   * @brief Action for the rule.
   */
  enum fw_action action;

  /**
   * @brief Subnet mask for source ip address.
   */
  uint8_t smask;

  /**
   * @brief Subnet mask for destination ip address.
   */
  uint8_t dmask;
} fw_rule_t;

/**
 * @brief Function to make new rule. Allocates heap memory.
 *
 * @param src Source ip address in uint32_t representation.
 * @param smask Subnet mask for source ip address.
 * @param dst Destination ip address in uint32_t representation.
 * @param dmask Subnet mask for destination ip address.
 * @param sport Source port.
 * @param dport Destination port.
 * @param proto Protocol.
 * @param action Action for the rule.
 * @param next Pointer to the next rule.
 * @return fw_rule_t * New rule.
 */
fw_rule_t *fw_rule_new(uint32_t src, uint8_t smask, uint32_t dst, uint8_t dmask,
                       uint16_t sport, uint16_t dport, enum fw_proto proto,
                       enum fw_action action, fw_rule_t *next);

#endif //_FIREWALL_SRC_RULE_H
