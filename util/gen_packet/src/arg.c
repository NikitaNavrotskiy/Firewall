#include "arg.h"
#include "generator.h"

int
gen_opt_get (int argc, char **argv, gen_opt_t *options)
{
  int status_code = 0;
  int c = 0;
  char *arg_t = NULL;
  char *arg_c = NULL;

  while (c != -1)
    {
      int opt_index = 0;
      static struct option long_options[]
          = { { "timeout", required_argument, NULL, 't' },
              { "count", required_argument, NULL, 'c' },
              { "output", required_argument, NULL, 'o' } };

      c = getopt_long (argc, argv, "t:c:o:", long_options, &opt_index);

      switch (c)
        {
        case 'c':
          arg_c = optarg;
          break;
        case 't':
          arg_t = optarg;
          break;
        case 'o':
          options->arg_o = optarg;
          break;
        case -1:
          break;
        default:
          status_code = 1;
        }
    }

  if (arg_t)
    {
      options->timeout = (uint64_t)strtoul (arg_t, NULL, 10) * 1000;
    }

  if (arg_c && strlen (arg_c) > 0 && arg_c[0] != '-')
    {
      options->count = (uint64_t)strtoul (arg_c, NULL, 10);
    }

  if (options->count == 0)
    options->count = GEN_COUNT_DEFAULT;

  return status_code;
}
