#include "acequia_manager.h"
#include <iostream>

/*Instructions for this problem:

	The intend of this project is to simulate water management conservation principles in the context of New Mexico

	In this simulation, there exists several Regions (North, South, etc.). Each region class includes both:
	- a given water level
	- a given water need
	- a indicator boolean for if the region is flooded
	- an indicator boolean for if the region is in drought

	With each region, there are given waterSources provided (perhaps a .dat file list each waterSource to  a region) 
	and certain waterSources have canals connected to them to deliver water across regions.

	Given the current state of the region, students wil be asked to utlize the canals that connect regions to
	develop the logic and algorithm for finding a solution. The simulation has a fixed time

	The student solution will be evaluated on the criteria that each region meets the following:
	- a given region is NOT flooded
	- a given region is NOT in drought
	- the region waterNeed does not exceed the region waterLevel 
*/

/*This will be how the solveProblems function is set up. The student may enter their on  */
void solveProblems(AcequiaManager& manager)
{
	//the student can call the members of the canals object such as name of canal. sourceRegion, and destinationRegion
	//This could be helpful in informing the students strategy to solve the problem
	auto canals = manager.getCanals();
	auto regions = manager.getRegions();

	while(!manager.isSolved && manager.hour!=manager.SimulationMax)
	{ 
		//enter student code here
		if(manager.hour == 0) {
			for (auto canal : canals) {
				canal->toggleOpen(true);
				canal->setFlowRate(0.5);
			}
		}

		// adjust based on region status
//Our code to solve!
		for (auto region : regions) {
			for (auto canal : canals) {
				if (canal->destinationRegion == region) {
					if (region->isInDrought) {
						canal->setFlowRate(1.0); // full blast if in drought
					} else if (region->isFlooded) {
						canal->setFlowRate(0.1); // slow drip if flooded
					}
				}
			}
		}

		manager.nexthour();
	}
}
