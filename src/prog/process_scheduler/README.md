---
name: process-scheduler
description: A CLI program that simulates process scheduling.
---

## Usage

```
USAGE:
 ./prog -alg [FIFO|SJF|PR|RR] [-quantum integer(ms)] -input [input_file_name.txt]
```

## Test

```
---------------------------------------------
./process-scheduler -alg FIFO -input input.txt
---------------------------------------------
Student Name: wb
Input File Name: input.txt
CPU Scheduling Alg: FIFO

Process 1 is completed at 5 ms
Process 2 is completed at 12 ms
Process 3 is completed at 18 ms
Process 4 is completed at 22 ms

Average Waiting time =  8.75 ms  (35/4)
Average Turnaround time =  14.25 ms  (57/4)
Throughput =  0.18 ms  (4/22)
---------------------------------------------
./process-scheduler -alg SJF -input input.txt
---------------------------------------------
Student Name: wb
Input File Name: input.txt
CPU Scheduling Alg: SJF

Process 4 is completed at 4 ms
Process 1 is completed at 9 ms
Process 3 is completed at 15 ms
Process 2 is completed at 22 ms

Average Waiting time =  7.00 ms  (28/4)
Average Turnaround time =  12.50 ms  (50/4)
Throughput =  0.18 ms  (4/22)
---------------------------------------------
./process-scheduler -alg PR -input input.txt
---------------------------------------------
Student Name: wb
Input File Name: input.txt
CPU Scheduling Alg: PR

Process 3 is completed at 6 ms
Process 1 is completed at 11 ms
Process 2 is completed at 18 ms
Process 4 is completed at 22 ms

Average Waiting time =  8.75 ms  (35/4)
Average Turnaround time =  14.25 ms  (57/4)
Throughput =  0.18 ms  (4/22)
---------------------------------------------
./process-scheduler -alg RR -input input.txt
---------------------------------------------
Student Name: wb
Input File Name: input.txt
CPU Scheduling Alg: RR

Process 1 is completed at 5 ms
Process 2 is completed at 12 ms
Process 3 is completed at 18 ms
Process 4 is completed at 22 ms

Average Waiting time =  8.75 ms  (35/4)
Average Turnaround time =  14.25 ms  (57/4)
Throughput =  0.18 ms  (4/22)
```

