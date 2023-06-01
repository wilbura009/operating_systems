---
name: address_calculator
description: A CLI program that calculates paging infomation.
---

## Usage

```
USAGE: ./address-calculator <virtual_address_space_SZ> [-unit] <physical_memory_SZ> [-unit] <page_frame_SZ> [-unit]
  EXAMPLE: 
    ./address-calculator 16 -mb 128 -kb 2 -kb
```

## Test

```
./address-calculator 16 -mb 128 -kb 2 -kb
bits_for_v_addr:  24
bits_for_p_addr:  17
bits_for_offset:  11
bits_for_page_num: 13
bits_for_frame_num: 6
```

