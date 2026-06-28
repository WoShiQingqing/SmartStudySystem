#ifndef DP_MODULE_H
#define DP_MODULE_H

#include "Scenario.h"
#include "StrategyResult.h"

// This runs the DP planner on one scenario
StrategyResult runDPStrategy(const Scenario& scenario);

#endif
