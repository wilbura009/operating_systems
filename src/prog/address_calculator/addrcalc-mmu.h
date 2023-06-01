#ifndef ADDRCALC_MMU_H
#define ADDRCALC_MMU_H

typedef struct MemoryManagementUnit MMU;

struct MemoryManagementUnit
{
  int v_mem_sz;
  int p_mem_sz;
  int page_sz;

  int bits_for_v_addr;
  int bits_for_p_addr;
  int bits_for_offset;
  int bits_for_page_num;
  int bits_for_frame_num;
};

MMU* mmu_create(int v_mem_sz, int p_mem_sz, int page_sz);
void mmu_destory(MMU* mmu); 

void mmu_set_bits_for_v_addr(MMU* mmu);
void mmu_set_bits_for_p_mem(MMU* mmu);
void mmu_set_bits_for_offset(MMU* mmu);
void mmu_set_bits_for_page_num(MMU* mmu);
void mmu_set_bits_for_frame_num(MMU* mmu);

int mmu_get_bits_for_v_addr(MMU* mmu);
int mmu_get_bits_for_p_mem(MMU* mmu);
int mmu_get_bits_for_offset(MMU* mmu);
int mmu_get_bits_for_page_num(MMU* mmu);
int mmu_get_bits_for_frame_num(MMU* mmu);

void mmu_print(MMU* mmu);

#endif // ADDRCALC_MMU_H
