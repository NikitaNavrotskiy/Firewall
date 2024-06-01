#include "rule.h"

fw_rule_t *
fw_rule_new (uint32_t src, uint8_t smask, uint32_t dst, uint8_t dmask,
             uint16_t sport, uint16_t dport, enum fw_proto proto,
             enum fw_action action, fw_rule_t *next)
{
  fw_rule_t *inst = (fw_rule_t *)malloc (sizeof (fw_rule_t));

  inst->saddr = src;
  inst->smask = smask;
  inst->daddr = dst;
  inst->dmask = dmask;
  inst->sport = sport;
  inst->dport = dport;
  inst->proto = proto;
  inst->action = action;
  inst->next = next;

  return inst;
}
