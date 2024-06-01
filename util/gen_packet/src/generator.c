#include "generator.h"

uint32_t
gen_generate_ip ()
{
  uint32_t res = 0;
  int is_double = rand () % 2;

  res = (uint32_t)rand ();

  if (is_double)
    res <<= 1;

  return res;
}

uint16_t
gen_generate_port ()
{
  return rand () % 65535 + 1;
}

enum fw_proto
gen_generate_proto ()
{
  return rand () % 2 == 0 ? TCP : UDP;
}

static void
__gen_proc_line (FILE *fd_out)
{
  char src_ip[16] = { 0 };
  char dst_ip[16] = { 0 };
  uint16_t sport = gen_generate_port ();
  uint16_t dport = gen_generate_port ();
  enum fw_proto proto = gen_generate_proto ();

  fw_convert_ip_int_to_str (gen_generate_ip (), src_ip);
  fw_convert_ip_int_to_str (gen_generate_ip (), dst_ip);

  fprintf (fd_out, GEN_FORMAT, src_ip, dst_ip, sport, dport, proto);
}

void
gen_generator_proc (FILE *fd_out, uint64_t count, uint64_t milsec_timeout)
{
  for (; count != 0; count--)
    {
      __gen_proc_line (fd_out);
      usleep (milsec_timeout);
    }
}
