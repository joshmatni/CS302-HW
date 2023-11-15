#ifndef METRICS_H
#define METRICS_H

class Metrics
{
    public:
        uint64_t runTime, comparisons, swaps; // regular int caused negative 
        Metrics() : runTime(0), comparisons(0), swaps(0) {} // default constructor
};
#endif