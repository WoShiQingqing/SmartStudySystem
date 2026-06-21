#include "DPModule.h"

StrategyResult runDPStrategy(const Scenario& scenario) {
    StrategyResult result;
    result.strategyName = "Dynamic Programming";
    // Student 4 can replace this with knapsack logic without touching the shared interface.
    result.rankedTasks = scenario.tasks;
    result.comment =
        "Integration stub only. Student 4 should replace this with 0/1 Knapsack using "
        "available study time as capacity.";
    return result;
}
