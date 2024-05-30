#include "arg.h"

int
fw_opt_get (int argc, char **argv, fw_opt_t *options)
{
  int status_code = 0;
  int c = 0;

  while (c != -1)
    {
      int opt_index = 0;
      static struct option long_options[]
          = { { "file-db", required_argument, NULL, 'f' },
              { "input", required_argument, NULL, 'i' },
              { "output", required_argument, NULL, 'o' } };

      c = getopt_long (argc, argv, "f:i:o:", long_options, &opt_index);

      switch (c)
        {
        case 'f':
          options->arg_f = optarg;
          break;
        case 'i':
          options->arg_i = optarg;
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

  if (options->arg_f == NULL)
    status_code = -1;

  return status_code;
}
