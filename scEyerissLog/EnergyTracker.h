#ifndef ENERGY_TRACKER_H
#define ENERGY_TRACKER_H

#include <systemc.h>

SC_MODULE(EnergyTracker) {
    int GLB_access;
    int DRAM_access;
    int mac_operations;

    void count_GLB_accesses();
    void count_DRAM_accesses();
    void count_mac_op();
    void report();
    double compute_energy();

    SC_CTOR(EnergyTracker) : GLB_access(0), DRAM_access(0), mac_operations(0) {}
};

#endif
