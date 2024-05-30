#include "firewall_db.h"

static inline enum fw_proto __fw_rule_proto_from_str(const char *proto_str) {
  if (strncmp(proto_str, "tcp", 3) == 0)
    return TCP;
  return UDP;
}

static inline enum fw_action __fw_rule_action_from_str(const char *action_str) {
  if (strncmp(action_str, "ACCEPT", 6) == 0)
    return ACCEPT;
  return DROP;
}

static bool __fw_rule_str_regex_check(const char *str) {
  regex_t regex = {0};
  int res;
  bool ret = false;

  res = regcomp(&regex, FW_DB_LINE_REGEX, REG_EXTENDED);

  if (res) // regex compile error
    return true;

  res = regexec(&regex, str, 0, NULL, 0);

  switch (res) {
  case 0:
    ret = true;
    break;
  case REG_NOMATCH:
    ret = false;
    break;
  default:
    ret = false;
    regerror(res, &regex, NULL, 0);
  }

  regfree(&regex);

  return ret;
}

static void __fw_rule_make_offset(const char **str, int *last_offset) {
  (*str) += *last_offset;

  while (**str == ' ')
    (*str)++;

  *last_offset = 0;
}

static fw_rule_t *__fw_rule_getline(fw_rule_t *last, const char *line) {
  if (__fw_rule_str_regex_check(line) == false)
    return last;

  int status = 0;
  int offset = 0;

  fw_rule_t *new_rule = NULL;
  char src_addr[16] = {0};
  char dst_addr[16] = {0};
  uint16_t dport = 0;
  uint16_t sport = 0;
  char proto[4] = {0};
  char action[7] = {0};

  enum fw_proto enum_proto;
  enum fw_action enum_action;

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
    enum_proto = __fw_rule_proto_from_str(proto);
    enum_action = __fw_rule_action_from_str(action);

    new_rule = fw_rule_new(src_addr, dst_addr, sport, dport, enum_proto,
                           enum_action, NULL);

    if (last != NULL)
      last->next = new_rule;
  } else
    new_rule = last;

  return new_rule;
}

static bool __fw_rule_packet_match(const fw_rule_t *rule,
                                   const fw_packet_t *packet) {
  return rule->saddr == packet->saddr && rule->daddr == packet->daddr &&
         rule->sport == packet->sport && rule->dport == packet->dport &&
         rule->proto == packet->proto;
}

fw_rule_t *fw_rule_from_file(const char *file) {
  FILE *fd;
  fw_rule_t *last = NULL;
  fw_rule_t *head = NULL;
  char *line = NULL;
  size_t len = 0;

  fd = fopen(file, "r");

  if (!fd)
    return NULL;

  if (getline(&line, &len, fd) != -1) {
    last = __fw_rule_getline(NULL, line);
    head = last;
  }

  while (getline(&line, &len, fd) != -1)
    last = __fw_rule_getline(last, line);

  if (line)
    free(line);
  fclose(fd);

  return head;
}

enum fw_action fw_rule_process_packet(const fw_rule_t *rules,
                                      const fw_packet_t *packet);

void fw_rule_free(fw_rule_t *rules) {
  fw_rule_t *cur = rules;

  while (cur) {
    fw_rule_t *cur_next = cur->next;
    free(cur);
    cur = cur_next;
  }
}
