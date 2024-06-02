#include "firewall_db.h"

/**
 * @brief Function to recognize protocol from c-string.
 *
 * @param proto_str C-string protocol.
 * @return Protocol as fw_proto enumeration.
 */
static inline enum fw_proto __fw_rule_proto_from_str(const char *proto_str) {
  if (strncmp(proto_str, "tcp", 3) == 0)
    return TCP;
  else if (strncmp(proto_str, "udp", 3) == 0)
    return UDP;
  return NONE;
}

/**
 * @brief Function to recognize action from c-string.
 *
 * @param action_str C-string action.
 * @return Action as fw_action enumeration.
 */
static inline enum fw_action __fw_rule_action_from_str(const char *action_str) {
  if (strncmp(action_str, "ACCEPT", 6) == 0)
    return ACCEPT;
  return DROP;
}

/**
 * @brief Function to check validity of input rule as c-string.
 *
 * @param str C-string rule.
 * @param Compiled regex_t instance.
 * @return true if correct, false otherwise
 */
static bool __fw_rule_str_regex_check(const char *str, regex_t *regex) {
  int res;
  bool ret = false;

  res = regexec(regex, str, 0, NULL, 0);

  switch (res) {
  case 0:
    ret = true;
    break;
  case REG_NOMATCH:
    ret = false;
    break;
  default:
    ret = false;
    regerror(res, regex, NULL, 0);
  }

  return ret;
}

/**
 * @brief Function to remove extra spaces in the start
 * of the string for correct sscanf call.
 *
 * @param str Double char pointer to the string to move pointer in this
 * Function.
 * @param last_offset %n specifier output of the last sscanf call to get offset
 * of last format occurence.
 */
static void __fw_rule_make_offset(const char **str, int *last_offset) {
  (*str) += *last_offset;

  while (**str == ' ')
    (*str)++;

  *last_offset = 0;
}

/**
 * @brief Function to retrieve ip and mask (if mask was set) from c-string.
 *
 * @param addr C-string to parse ip where.
 * @param ip uint32_ pointer to write the ip in decimal format where.
 * @param mask uint8_t pointer to write the mask where. If mask is not set,
 * mask will be equal to 32.
 */
static void __fw_rule_retrieve_ip_net(char addr[19], uint32_t *ip,
                                      uint8_t *mask) {
  char *ip_token = strtok(addr, "/");
  char *mask_token = strtok(NULL, "/");

  *ip = fw_convert_ip_str_to_int(ip_token);

  if (mask_token == NULL)
    *mask = 32;
  else
    *mask = (uint8_t)atoi(mask_token);
}

/**
 * @brief Function to process c-string line after getline call.
 * Checks on regex, parses and calls fw_rule's constructor.
 *
 * @param last Pointer to the last rule in rules list.
 * @param line C-string line after getline call.
 * @param regex Compiled regex_t instance.
 * @return On success returns new rule's pointer,
 * on failure - the last rule's pointer before __fw_rule_getline call.
 */
static fw_rule_t *__fw_rule_getline(fw_rule_t *last, const char *line,
                                    regex_t *regex) {
  if (__fw_rule_str_regex_check(line, regex) == false)
    return last;

  int status = 0;
  int offset = 0;

  fw_rule_t *new_rule = NULL;
  char src_addr[19] = {0};
  char dst_addr[19] = {0};
  uint32_t src_ip = 0;
  uint32_t dst_ip = 0;
  uint16_t dport = 0;
  uint16_t sport = 0;
  char proto[4] = {0};
  char action[7] = {0};
  uint8_t smask = 0;
  uint8_t dmask = 0;

  __fw_rule_make_offset(&line, &offset);
  sscanf(line, FW_DB_LINE_SRC_FORMAT, src_addr, &offset);
  __fw_rule_make_offset(&line, &offset);
  sscanf(line, FW_DB_LINE_SPORT_FORMAT, &sport, &offset);
  __fw_rule_make_offset(&line, &offset);
  sscanf(line, FW_DB_LINE_DST_FORMAT, dst_addr, &offset);
  __fw_rule_make_offset(&line, &offset);
  sscanf(line, FW_DB_LINE_DPORT_FORMAT, &dport, &offset);
  __fw_rule_make_offset(&line, &offset);
  sscanf(line, FW_DB_LINE_PROTO_FORMAT, proto, &offset);
  __fw_rule_make_offset(&line, &offset);

  status = sscanf(line, FW_DB_LINE_ACTION_FORMAT, action);

  if (status != 0) {
    enum fw_proto enum_proto = __fw_rule_proto_from_str(proto);
    enum fw_action enum_action = __fw_rule_action_from_str(action);

    if (strlen(src_addr) > 0)
      __fw_rule_retrieve_ip_net(src_addr, &src_ip, &smask);

    if (strlen(dst_addr) > 0)
      __fw_rule_retrieve_ip_net(dst_addr, &dst_ip, &dmask);

    new_rule = fw_rule_new(src_ip, smask, dst_ip, dmask, sport, dport,
                           enum_proto, enum_action, NULL);

    if (last != NULL)
      last->next = new_rule;
  } else
    new_rule = last;

  return new_rule;
}

/**
 * @brief Function to check if ip from the packet is corresponds
 * to the rule.
 *
 * @param ip uint32_t ip respresentation of the packet.
 * @param net_addr uint32_t net ip respresentation of the rule.
 * @param subnet Subnet for the rule's ip.
 * @return true if matches, false otherwise.
 */
static bool __fw_rule_ip_match(uint32_t ip, uint32_t net_addr, uint8_t subnet) {
  if (net_addr == 0)
    return true;
  return (net_addr & (0xFFFFFFFF << (32 - subnet))) ==
         (ip & (0xFFFFFFFF << (32 - subnet)));
}

/**
 * @brief Function to check if port from the packet is corresponds
 * to the rule's port.
 *
 * @param checking_port Port number of the packet.
 * @param rule_port Port number of the rule.
 * @return true if matches, false otherwise.
 */

static bool __fw_rule_port_match(uint16_t checking_port, uint16_t rule_port) {
  if (rule_port == 0)
    return true;
  return checking_port == rule_port;
}

/**
 * @brief Function to check if protocol from the packet is corresponds
 * to the rule's protocol.
 *
 * @param checking_proto Protocol number of the packet.
 * @param rule_proto Protocol number of the rule.
 * @return true if matches, false otherwise.
 */
static bool __fw_rule_proto_match(enum fw_proto checking_proto,
                                  enum fw_proto rule_proto) {
  if (rule_proto == NONE)
    return true;
  return checking_proto == rule_proto;
}

/**
 * @brief Function to check if packet is corresponds to
 * the rule.
 *
 * @param rule Pointer to the current rule of the rules list.
 * @param packet Packet ot check.
 * @return true if matches, false otherwise.
 */
static bool __fw_rule_packet_match(const fw_rule_t *rule,
                                   const fw_packet_t *packet) {
  return __fw_rule_ip_match(packet->saddr, rule->saddr, rule->smask) &&
         __fw_rule_ip_match(packet->daddr, rule->daddr, rule->dmask) &&
         __fw_rule_port_match(packet->sport, rule->sport) &&
         __fw_rule_port_match(packet->dport, rule->dport) &&
         __fw_rule_proto_match(packet->proto, rule->proto);
}

fw_rule_t *fw_rule_from_file(const char *file) {
  regex_t regex = {0};
  FILE *fd;
  fw_rule_t *last = NULL;
  fw_rule_t *head = NULL;
  char *line = NULL;
  size_t len = 0;
  int res = 0;

  res = regcomp(&regex, FW_DB_LINE_REGEX, REG_EXTENDED | REG_NEWLINE);

  if (res) // regex compile error
    return NULL;

  fd = fopen(file, "r");

  if (!fd)
    return NULL;

  while (head == NULL) { // getting head
    getline(&line, &len, fd);
    last = __fw_rule_getline(NULL, line, &regex);
    head = last;
  }

  while (getline(&line, &len, fd) != -1)
    last = __fw_rule_getline(last, line, &regex);

  if (line)
    free(line);

  regfree(&regex);

  fclose(fd);

  return head;
}

enum fw_action fw_rule_process_packet(const fw_rule_t *rules,
                                      const fw_packet_t *packet) {
  for (fw_rule_t *cur = (fw_rule_t *)rules; cur; cur = cur->next) {
    if (__fw_rule_packet_match(cur, packet)) {
      return cur->action;
    }
  }

  return FW_DEFAULT_ACTION;
}

void fw_rule_free(fw_rule_t *rules) {
  fw_rule_t *cur = rules;

  while (cur) {
    fw_rule_t *cur_next = cur->next;
    free(cur);
    cur = cur_next;
  }
}
