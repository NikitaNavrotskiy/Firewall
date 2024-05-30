#include "rule.h"

fw_rule_t *
fw_rule_new (const char saddr[16], const char daddr[16], uint16_t sport,
             uint16_t dport, enum fw_proto proto, enum fw_action action,
             fw_rule_t *next)
{
  fw_rule_t *inst = (fw_rule_t *)malloc (sizeof (fw_rule_t));

  strncpy (inst->saddr, saddr, 16);
  strncpy (inst->daddr, daddr, 16);
  inst->sport = sport;
  inst->dport = dport;
  inst->proto = proto;
  inst->action = action;
  inst->next = next;

  return inst;
}
