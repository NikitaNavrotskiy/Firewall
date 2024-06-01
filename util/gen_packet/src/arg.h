/**
 * @file arg.h
 */

#ifndef _FIREWALL_SRC_UTIL_PACKET_GEN_ARG_H
#define _FIREWALL_SRC_UTIL_PACKET_GEN_ARG_H

#include <getopt.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "generator.h"

/**
 * @struct gen_opt
 * @brief Structure to store program options.
 * @var timeout Stores timeout between packets.
 * @var count Stores number of packets to generate.
 * @var arg_o Stores output file.
 */
typedef struct {
  /**
   * @brief Stores timeout between packets.
   */
  uint64_t timeout;

  /**
   * @brief Stores number of packets to generate.
   */
  uint64_t count;

  /**
   * @brief Stores output file.
   */
  char *arg_o;
} gen_opt_t;

/**
 * @brief Function to write program options to struct gen_opt
 * from argv.
 *
 * @param argc Argc param of main().
 * @param argv Argv param of main().
 * @param options struct gen_opt to write options.
 * @return Status code. 0 on success.
 */
int gen_opt_get(int argc, char **argv, gen_opt_t *options);

#endif //_FIREWALL_SRC_ARG_H
