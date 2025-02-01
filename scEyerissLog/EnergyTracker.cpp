#include "EnergyTracker.h"

void EnergyTracker::count_GLB_accesses() { GLB_access++; }
void EnergyTracker::count_DRAM_accesses() { DRAM_access++; }
void EnergyTracker::count_mac_op() { mac_operations++; }


double EnergyTracker::compute_energy() {
        const double mac_energy = 3.2;
        const double dram_energy = 100.0;
        const double glb_energy = 10.0;

        return (mac_operations * mac_energy) + (DRAM_access * dram_energy) + (GLB_access * glb_energy);
    }


void EnergyTracker::report() {
    cout << "Global Buffer Accesses: " << GLB_access << endl;
    cout << "DRAM Accesses: " << DRAM_access << endl;
    cout << "MAC Operations: " << mac_operations << endl;
    cout << "Total Energy Consumption: " << compute_energy() << " units" << endl;
}