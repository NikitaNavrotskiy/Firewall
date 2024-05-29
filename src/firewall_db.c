#include "firewall_db.h"

static fw_rule_t *__fw_rule_getline(fw_rule_t *last, const char *line) {
  return NULL;
}

static bool __fw_rule_packet_match(const fw_rule_t *rule,
                                   const fw_packet_t *packet) {
  return false;
}

fw_rule_t *fw_rule_from_file(const char *file) { return NULL; }

enum fw_action fw_rule_process_packet(const fw_rule_t *rules,
                                      const fw_packet_t *packet);

void fw_rule_free(fw_rule_t *rules) {
  fw_rule_t *cur = rules;

  while (cur) {
    fw_rule_t *cur_next = cur->next;
    free(cur);
  }
}
