#ifndef PARALLEL_H
#define PARALLEL_H

#include "result.h"

result *parallel_firewall(int log_threads, int numSources, long mean, short experimentNumber, int M, int H, int is_dropped, float plus, float minus, float rate);

#endif
