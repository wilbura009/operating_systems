#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "addrcalc-mmu.h"

MMU* mmu_create(int v_mem_sz, int p_mem_sz, int page_sz)
{
  MMU* mmu = malloc(sizeof(MMU));
  mmu->v_mem_sz = v_mem_sz;
  mmu->p_mem_sz = p_mem_sz;
  mmu->page_sz  = page_sz;

  mmu_set_bits_for_v_addr(mmu);
  mmu_set_bits_for_p_mem(mmu);
  mmu_set_bits_for_offset(mmu);
  mmu_set_bits_for_page_num(mmu);
  mmu_set_bits_for_frame_num(mmu);

  return mmu;
}

void mmu_destory(MMU* mmu) { free(mmu); }

void mmu_set_bits_for_v_addr(MMU* mmu) { mmu->bits_for_v_addr = log2(mmu->v_mem_sz); }
void mmu_set_bits_for_p_mem(MMU* mmu) { mmu->bits_for_p_addr = log2(mmu->p_mem_sz); }
void mmu_set_bits_for_offset(MMU* mmu) { mmu->bits_for_offset = log2(mmu->page_sz); }
void mmu_set_bits_for_page_num(MMU* mmu) { mmu->bits_for_page_num  = mmu->bits_for_v_addr - mmu->bits_for_offset; }
void mmu_set_bits_for_frame_num(MMU* mmu) { mmu->bits_for_frame_num = mmu->bits_for_p_addr - mmu->bits_for_offset; }

int mmu_get_bits_for_v_addr(MMU* mmu) { return mmu->bits_for_v_addr; }
int mmu_get_bits_for_p_mem(MMU* mmu) { return mmu->bits_for_p_addr; }
int mmu_get_bits_for_offset(MMU* mmu) { return mmu->bits_for_offset; }
int mmu_get_bits_for_page_num(MMU* mmu) { return mmu->bits_for_page_num; }
int mmu_get_bits_for_frame_num(MMU* mmu) { return mmu->bits_for_frame_num; }

void mmu_print(MMU* mmu)
{
  printf("bits_for_v_addr:  %d\n", mmu_get_bits_for_v_addr(mmu));
  printf("bits_for_p_addr:  %d\n", mmu_get_bits_for_p_mem(mmu));
  printf("bits_for_offset:  %d\n", mmu_get_bits_for_offset(mmu));
  printf("bits_for_page_num: %d\n", mmu_get_bits_for_page_num(mmu));
  printf("bits_for_frame_num: %d\n", mmu_get_bits_for_frame_num(mmu));
}
