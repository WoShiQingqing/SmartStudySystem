#include "SortingModule.h"

StrategyResult runSortingStrategy(const Scenario& scenario) {
    StrategyResult result;
    result.strategyName = "Sorting-based ranking";
    // Hand back the raw tasks for now so Student 2 has a clear drop-in starting point.
    result.rankedTasks = scenario.tasks;
    result.comment =
        "Integration stub only. Student 2 should replace this with Merge Sort or Quick Sort "
        "based on the chosen ranking criterion.";
    return result;
}
