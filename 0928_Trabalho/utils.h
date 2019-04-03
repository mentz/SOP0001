#ifndef UTILS_H
#define UTILS_H

#include <unistd.h>
#include <math.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SLEEP_MAIN 12
#define SLEEP_THREAD 10

unsigned long get_time_msec(void);
unsigned long exp_msleep(int t);
void rand_sleep(int t);

#endif