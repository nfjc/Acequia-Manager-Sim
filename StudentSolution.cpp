#include "acequia_manager.h"
#include <iostream>

/*Instructions for this problem:

    The intent of this project is to simulate water management conservation principles in the context of New Mexico

    In this simulation, there exists several Regions (North, South, etc.). Each region class includes both:
    - a given water level
    - a given water need
    - an indicator boolean for if the region is flooded
    - an indicator boolean for if the region is in drought

    With each region, there are given waterSources provided (perhaps a .dat file lists each waterSource to a region) 
    and certain waterSources have canals connected to them to deliver water across regions.

    Given the current state of the region, students will be asked to utilize the canals that connect regions to
    develop the logic and algorithm for finding a solution. The simulation has a fixed time.

    The student solution will be evaluated on the criteria that each region meets the following:
    - a given region is NOT flooded
    - a given region is NOT in drought
    - the region waterNeed does not exceed the region waterLevel 
*/

void solveProblems(AcequiaManager& manager)
{
    auto canals = manager.getCanals();
    auto regions = manager.getRegions();

    Region* north = nullptr;
    Region* south = nullptr;
    Region* east = nullptr;

    for (auto region : regions) {
        if (region->name == "North") north = region;
        else if (region->name == "South") south = region;
        else if (region->name == "East") east = region;
    }

    while (!manager.isSolved && manager.hour != manager.SimulationMax)
    {
        for (auto canal : canals)
        {
            Region* to = canal->destinationRegion;
            Region* from = canal->sourceRegion;

            // Canal A: North → South
            if (canal->name == "Canal A") {
                if (north->waterLevel >= 0.85 * north->waterNeed && south->waterLevel < south->waterNeed) {
                    canal->toggleOpen(true);
                    canal->setFlowRate(south->isInDrought ? 1.0 : 0.6);
                } else {
                    canal->toggleOpen(false);
                    canal->setFlowRate(0.0);
                }
                continue;
            }

            // Canal B: South → East
            if (canal->name == "Canal B") {
                if (south->waterLevel >= 0.85 * south->waterNeed && east->waterLevel < east->waterNeed) {
                    canal->toggleOpen(true);
                    canal->setFlowRate(east->isInDrought ? 1.0 : 0.6);
                } else {
                    canal->toggleOpen(false);
                    canal->setFlowRate(0.0);
                }
                continue;
            }

            // Canal C: North → East
            if (canal->name == "Canal C") {
                if (north->waterLevel >= 0.85 * north->waterNeed && east->waterLevel < east->waterNeed) {
                    canal->toggleOpen(true);
                    canal->setFlowRate(east->isInDrought ? 1.0 : 0.7);
                } else {
                    canal->toggleOpen(false);
                    canal->setFlowRate(0.0);
                }
                continue;
            }

            // Canal D: East → North (ALWAYS feed North early)
            if (canal->name == "Canal D") {
                if (north->waterLevel < north->waterNeed) {
                    canal->toggleOpen(true);
                    canal->setFlowRate(north->isInDrought ? 1.0 : 0.6);
                } else {
                    canal->toggleOpen(false);
                    canal->setFlowRate(0.0);
                }
                continue;
            }
        }

        manager.nexthour();
    }
}

