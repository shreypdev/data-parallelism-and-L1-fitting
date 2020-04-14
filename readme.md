## Table of contents
* [Author Info](#author-info)
* [Problem Statement](#problem-statement)
* [Technique To Solve Promblem](#technique-to-solve-promblem)
* [Single Thread VS. Multi-Thread](#single-thread-vs.-multi-thread)
* [Setup](#setup)
* [Known Bugs](#known-bugs)
* [References](#references)
* [Worked With](#worked-with)

## Author Info
Name: Shrey Patel

## Problem Statement
This project solves "The best fit line problem", in this problem we were given with multiple data points and we have to find the best fit line for that graph.
The problem with this is that is we have lot of points say 5000 then it could take significantly long time as it will take all two possible points and check 
for if that line is the best fit line or not.
	
## Technique To Solve Promblem
This problem can be solved using "Parallel Programming". By using "openMP".

```c
#pragma omp parallel
{
   SAR = findSAR();
}
```

## Single Thread VS. Multi-Thread
This is a complicated question you're asking. Without knowing more about the nature of your threads it's difficult to say. Some things to consider when diagnosing system performance:

Is the process/thread

CPU bound (needs lots of CPU resources)
Memory bound (needs lots of RAM resources)
I/O bound (Network and/or hard drive resources)
All of these three resources are finite and any one can limit the performance of a system. You need to look at which (might be 2 or 3 together) your particular situation is consuming.

You can use ntop and iostat, and vmstat to diagnose what's going on.

## Setup
To run this project, follow below given steps:

```shell
$ cd ../Project_Directory
$ make
$ make run
$ make clean
$ clear
```

## Known Bugs
N/A

## References
N/A

## Worked With
* Amee Gorana
