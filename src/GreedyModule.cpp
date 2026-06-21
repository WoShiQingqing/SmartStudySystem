#include "GreedyModule.h"

StrategyResult runGreedyStrategy(const Scenario& scenario) {
    StrategyResult result;
    result.strategyName = "Greedy strategy";
    result.rankedTasks = scenario.tasks;
    result.comment =
        "Integration stub only. Student 3 should replace this with the agreed greedy rule "
        "such as highest importance-to-time ratio.";
    return result;
}

