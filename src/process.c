#include "process.h"

static void
__fw_process_log_packet (FILE *fd_out, fw_packet_t *packet,
                         enum fw_action action)
{
  char *action_str = "ACCEPT";
  char *proto = "tcp";
  char src_ip[16] = { 0 };
  char dst_ip[16] = { 0 };

  if (action == DROP)
    action_str = "DROP";

  if (packet->proto == UDP)
    proto = "udp";

  fw_convert_ip_int_to_str (packet->saddr, src_ip);
  fw_convert_ip_int_to_str (packet->daddr, dst_ip);

  fprintf (fd_out, FW_PROCESS_LOG_FORMAT, src_ip, packet->sport, dst_ip,
           packet->dport, proto, action_str);
}

static inline enum fw_action
__fw_process_action_for_packet (fw_rule_t *rules, fw_packet_t *packet)
{
  return fw_rule_process_packet (rules, packet);
}

static bool
__fw_process_regex_ip (regex_t *regexp, const char *ip)
{
  bool ret = false;

  int res = regexec (regexp, ip, 0, NULL, 0);

  switch (res)
    {
    case 0:
      ret = true;
      break;
    case REG_NOMATCH:
      res = false;
      break;
    default:
      ret = false;
      regerror (res, regexp, NULL, 0);
      break;
    }

  return ret;
}

static inline bool
__fw_process_valid_proto (int proto)
{
  return (proto == UDP || proto == TCP);
}

static inline bool
__fw_process_valid_port (int port)
{
  return port < 65536 && port > 0;
}

static int
__fw_process_line_to_packet (const char *line, fw_packet_t *packet)
{
  char src_ip[16] = { 0 };
  char dst_ip[16] = { 0 };
  int sport = 0;
  int dport = 0;
  int proto = 0;
  int status = 0;
  int err = 0;
  regex_t regex_ip = { 0 };

  err = regcomp (&regex_ip, FW_REGEX_IP, REG_EXTENDED | REG_NEWLINE);

  if (err)
    return -2;

  status = sscanf (line, FW_PROCESS_FORMAT, src_ip, dst_ip, &sport, &dport,
                   &proto);

  if (status != 5)
    err = 1;
  else
    {
      if (!__fw_process_regex_ip (&regex_ip, src_ip)
          || !__fw_process_regex_ip (&regex_ip, dst_ip)
          || !__fw_process_valid_port (sport)
          || !__fw_process_valid_port (dport)
          || !__fw_process_valid_proto (proto))
        err = 1;
      else
        {
          fw_packet_fill (packet, src_ip, dst_ip, sport, dport, proto);
        }
    }

  regfree (&regex_ip);

  return err;
}

int
fw_process_input (fw_opt_t *options, fw_rule_t *rules)
{
  FILE *fd_in = stdin;
  FILE *fd_out = stdout;
  fw_packet_t cur_packet = { 0 };
  char *line = NULL;
  size_t len = 0;
  int err = 0;

  if (options->arg_i)
    {
      fd_in = fopen (options->arg_i, "r");

      if (fd_in == NULL)
        return 1;
    }

  if (options->arg_o)
    {
      fd_out = fopen (options->arg_o, "w");

      if (fd_out == NULL)
        {
          if (fd_in != NULL && fd_in != stdin)
            fclose (fd_in);
          return 1;
        }
    }

  while (getline (&line, &len, fd_in) != -1)
    {
      err = __fw_process_line_to_packet (line, &cur_packet);

      if (!err)
        {
          enum fw_action action
              = __fw_process_action_for_packet (rules, &cur_packet);
          __fw_process_log_packet (fd_out, &cur_packet, action);
        }
    }

  if (line)
    free (line);

  if (fd_in && fd_in != stdin)
    fclose (fd_in);

  if (fd_out && fd_out != stdout)
    fclose (fd_out);

  return 0;
}
