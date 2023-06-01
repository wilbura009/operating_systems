#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "addrcalc-mmu.h"

#define USAGE_MSG \
  "USAGE: ./address-calculator <virtual_address_space_SZ> [-unit] <physical_memory_SZ> [-unit] <page_frame_SZ> [-unit]\n" \
  "  EXAMPLE: \n" \
  "    ./address-calculator 16 -mb 128 -kb 2 -kb\n" \

#define MB_Y 20
#define KB_Y 10

void print_args(int argc, char *argv[])
{
  printf("argc = %d\n", argc);
  for (int i = 0; i < argc; i++)
  {
    printf("argv[%d] = %s\n", i, argv[i]);
  }
}

void msg_print_usage()
{
  printf("%s", USAGE_MSG);
}

int validate_arg_number(int argc, char *argv[])
{
  if (argc != 7)
  {
    printf("ERROR: Invalid number of arguments\n\n");
    msg_print_usage();
    return 1;
  }
  return 0;
}

int unit_is_mb(char *arg) { return strcmp(arg, "-mb") == 0; }
int unit_is_kb(char *arg) { return strcmp(arg, "-kb") == 0; }

int get_argn_y(char *arg)
{
  if (unit_is_mb(arg))
    return MB_Y;
  else if (unit_is_kb(arg))
    return KB_Y;
  else
    return -1;
}

int main(int argc, char *argv[])
{
  if (argc == 2 && strcmp(argv[1], "-h") == 0)
  {
    msg_print_usage();
    exit(0);
  }

  if (validate_arg_number(argc, argv))
    exit(1);
  
  int v_addr_y, p_mem_y, p_frame_y;
  v_addr_y  = p_mem_y = p_frame_y = -1;

  v_addr_y  = get_argn_y(argv[2]);
  p_mem_y   = get_argn_y(argv[4]);
  p_frame_y = get_argn_y(argv[6]);

  if (v_addr_y == -1 || p_mem_y == -1 || p_frame_y == -1)
  {
    printf("ERROR: Invalid unit\n\n");
    msg_print_usage();
    exit(1);
  }

  MMU* mmu = mmu_create(atoi(argv[1]) * pow(2, v_addr_y),
                        atoi(argv[3]) * pow(2, p_mem_y),
                        atoi(argv[5]) * pow(2, p_frame_y));

  mmu_print(mmu);
  mmu_destory(mmu);

  return 0;
}

