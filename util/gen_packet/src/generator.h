/**
 * @file generator.h
 */

#ifndef _FIREWALL_SRC_UTIL_PACKET_GEN_GENERATOR_H
#define _FIREWALL_SRC_UTIL_PACKET_GEN_GENERATOR_H

#include <limits.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "../../../src/convert.h"
#include "../../../src/packet.h"

/**
 * @brief Format to fprintf packet.
 */
#define GEN_FORMAT "%-15s %-15s %-5hu %-5hu %-2d\n"

/**
 * @brief Default number of packets to generate.
 */
#define GEN_COUNT_DEFAULT 10

/**
 * @brief Function to generate random ip address
 * in uint32_t representation.
 *
 * @return Ip address in uint32_t representation.
 */
uint32_t gen_generate_ip();

/**
 * @brief Function to generate random port number.
 *
 * @return Port number.
 */
uint16_t gen_generate_port();

/**
 * @brief Function to generate random protocol.
 *
 * @return Protocol.
 */
enum fw_proto gen_generate_proto();

/**
 * @brief Function that generates packets to fd_out.
 *
 * @param fd_out File to store generated packets.
 * @param count Number of packets to generate.
 * @param milsec_timeout Timeout between packets in
 * milleseconds.
 */
void gen_generator_proc(FILE *fd_out, uint64_t count, uint64_t milsec_timeout);

#endif
