---
author: wb
creator: update_rm.sh
date: 05312023 - 17:19:42
name: page_replacement
description: Calculates FIFO and LRU page replacement algorithms for a given page reference string.
---

# Page Replacement


## Problem:

Consider a demand paged virtual memory system with 3 frames allocated to a process that makes the following sequence of page references:

    1 2 3 4 2 5 2 3 2 1 2 5 2 1

Assume that initially no frames are allocated for any pages. For each of the following page replacement algorithms, indicate which pages are in memory after each reference and determine which references produce page faults. Circle or underscore the page faults and give the total number of page faults for each algorithm.

Note: When tracing the algorithms, it will be easier if you use the below tables as the data structures (e.g., FIFO queue for FIFO alg, and Stack for LRU alg) as we discussed in the lectures.


1. FIFO, Number of page faults: 10

| page reference | 1 | 2 | 3 | 4 | 2 | 5 | 2 | 3 | 2 | 1 | 2 | 5 | 2 | 1 |
|----------------|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| in memory      | 1 | 1 | 1 | 2 | 2 | 3 | 4 | 5 | 5 | 2 | 2 | 3 | 1 | 1 |
| in memory      |   | 2 | 2 | 3 | 3 | 4 | 5 | 2 | 2 | 3 | 3 | 1 | 5 | 5 |
| in memory      |   |   | 3 | 4 | 4 | 5 | 2 | 3 | 3 | 1 | 1 | 5 | 2 | 2 |
| page fault     | T | T | T | T |   | T | T | T |   | T |   | T | T |   |


2. LRU, Number of page faults: 8

| page reference | 1 | 2 | 3 | 4 | 2 | 5 | 2 | 3 | 2 | 1 | 2 | 5 | 2 | 1 |
|----------------|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| in memory      | 1 | 1 | 1 | 2 | 3 | 4 | 4 | 5 | 5 | 3 | 3 | 1 | 1 | 5 |
| in memory      |   | 2 | 2 | 3 | 4 | 2 | 5 | 2 | 3 | 2 | 1 | 2 | 5 | 2 |
| in memory      |   |   | 3 | 4 | 2 | 5 | 2 | 3 | 2 | 1 | 2 | 5 | 2 | 1 |
| page fault     | T | T | T | T |   | T |   | T |   | T |   | T |   |   |


3. Optimal, Number of page faults: 6

| page reference | 1 | 2 | 3 | 4 | 2 | 5 | 2 | 3 | 2 | 1 | 2 | 5 | 2 | 1 |
|----------------|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| in memory      | 1 | 1 | 1 | 4 | 4 | 5 | 5 | 5 | 5 | 5 | 5 | 5 | 5 | 5 |
| in memory      |   | 2 | 2 | 2 | 2 | 2 | 2 | 2 | 2 | 2 | 2 | 2 | 2 | 2 |
| in memory      |   |   | 3 | 3 | 3 | 3 | 3 | 3 | 3 | 1 | 1 | 1 | 1 | 1 |
| page fault     | T | T | T | T |   | T |   |   |   | T |   |   |   |   |

## Solutions

### FIFO

```
./main -fifo input.txt
==================== INPUT ===================

Number of page references: 14
Page references: 1 3 2 4 2 5 1 3 2 4 2 5 3 1 

==================== FIFO ====================

1 | 1      | T |
3 | 1 3    | T |
2 | 1 3 2    | T |
4 | 1 3 2 4  | T |
2 | 1 3 2 4  |   |
5 | 3 2 4 5  | T |
1 | 2 4 5 1  | T |
3 | 4 5 1 3  | T |
2 | 5 1 3 2  | T |
4 | 1 3 2 4  | T |
2 | 1 3 2 4  |   |
5 | 3 2 4 5  | T |
3 | 3 2 4 5  |   |
1 | 2 4 5 1  | T |

Number of page faults: 11
Number of page hits: 3
```



### LRU

```
./main -lru input.txt
==================== INPUT ===================

Number of page references: 14
Page references: 1 3 2 4 2 5 1 3 2 4 2 5 3 1 

==================== LRU =====================

1 | 1       | T |
3 | 1 3     | T |
2 | 1 3 2     | T |
4 | 1 3 2 4   | T |
2 | 1 3 4 2   |   |
5 | 3 4 2 5   | T |
1 | 4 2 5 1   | T |
3 | 2 5 1 3   | T |
2 | 5 1 3 2   |   |
4 | 1 3 2 4   | T |
2 | 1 3 4 2   |   |
5 | 3 4 2 5   | T |
3 | 4 2 5 3   |   |
1 | 2 5 3 1   | T |

Number of page faults: 10
Number of page hits: 4
```

