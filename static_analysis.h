#ifndef _STATIC_ANALYSIS_H
#define _STATIC_ANALYSIS_H

typedef struct {
    int instruction_count;
    int data_proc_count;
    int memory_count;
    int branch_taken;
    int branch_not_taken;
    int cache_hit;
    int cache_miss;
} static_analysis;

#endif
