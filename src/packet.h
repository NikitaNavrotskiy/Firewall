/**
 * @file packet.h
 */

#ifndef _FIREWALL_SRC_PACKET_H
#define _FIREWALL_SRC_PACKET_H

#include <stdint.h>

#include "convert.h"

/**
 * @brief Enumeration descibes protocols.
 * NONE Any protocol.
 * TCP Tcp protocol.
 * UDP Udp protocol.
 */
enum fw_proto {
  /**
   * @brief Any protocol.
   */
  NONE = 0,

  /**
   * @brief Tcp protocol.
   */
  TCP = 6,

  /**
   * @brief Udp protocol.
   */
  UDP = 17
};

/**
 * @struct fw_packet
 * @brief Structure to store info about packet.
 * @var saddr Source ip address.
 * @var daddr Destination ip address.
 * @var sport Source port.
 * @var dport Destination port.
 * @var proto Protocol (6 - TCP, 17 - UDP).
 */
typedef struct fw_packet {
  /**
   * @brief Source ip address.
   */
  uint32_t saddr;

  /**
   * @brief Destination ip address.
   */
  uint32_t daddr;

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
} fw_packet_t;

/**
 * @brief Function to fill struct fw_packet.
 *
 * @param packet struct fw_packet to store data.
 * @param saddr C-string source ip address.
 * @param daddr C-string destination ip address.
 * @param sport Source port.
 * @param dport Destination port.
 * @param proto Protocol.
 */
void fw_packet_fill(fw_packet_t *packet, const char *saddr, const char *daddr,
                    int sport, int dport, int proto);

#endif //_FIREWALL_SRC_PACKET_H
