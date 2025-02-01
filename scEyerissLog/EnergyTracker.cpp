#include "EnergyTracker.h"

void EnergyTracker::count_GLB_accesses() { GLB_access++; }
void EnergyTracker::count_DRAM_accesses() { DRAM_access++; }
void EnergyTracker::count_mac_op() { mac_operations++; }

void EnergyTracker::report() {
    cout << "Global Buffer Accesses: " << GLB_access << endl;
    cout << "DRAM Accesses: " << DRAM_access << endl;
    cout << "MAC Operations: " << mac_operations << endl;
}