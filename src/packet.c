#include "packet.h"

void
fw_packet_fill (fw_packet_t *packet, const char *saddr, const char *daddr,
                int sport, int dport, int proto)
{
  packet->saddr = fw_convert_ip_str_to_int ((char *)saddr);
  packet->daddr = fw_convert_ip_str_to_int ((char *)daddr);
  packet->sport = (uint16_t)sport;
  packet->dport = (uint16_t)dport;
  packet->proto = proto;
}
