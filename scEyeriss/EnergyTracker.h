#ifndef ENERGY_TRACKER_H
#define ENERGY_TRACKER_H

#include <systemc.h>

SC_MODULE(EnergyTracker) {
    int GLB_access;
    int DRAM_access;
    int mac_operations;

    void count_GLB_accesses() { GLB_access++; }
    void count_DRAM_accesses() { DRAM_access++; }
    void count_mac_op() { mac_operations++; }

    void report() {
        cout << "Global Buffer Accesses: " << GLB_access << endl;
        cout << "DRAM Accesses: " << DRAM_access << endl;
        cout << "MAC Operations: " << mac_operations << endl;
    }

    SC_CTOR(EnergyTracker) : GLB_access(0), DRAM_access(0), mac_operations(0) {}
};

#endif
