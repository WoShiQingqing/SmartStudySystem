#include "GreedyModule.h"
#include <algorithm>
#include <ctime>

// Compare two tasks by their ratio (importance / studyTime)
// Choose less studyTime task if ratios are equal.
static bool byRatio(const Task& a, const Task& b) {
    double ratioA = a.importanceTimeRatio();
    double ratioB = b.importanceTimeRatio();
    if (ratioA > ratioB) {
        return true;
    }
    return a.studyTime < b.studyTime;
}

// The core greedy strategy: Sort tasks by ratio, then select until avaliable time not enough
StrategyResult runGreedyStrategy(const Scenario& scenario) {
    StrategyResult result;
    result.strategyName = "Greedy strategy";
    result.totalStudyTime = 0;
    result.totalImportance = 0;

    clock_t start = clock();

    std::vector<Task> sorted = scenario.tasks;
    std::sort(sorted.begin(), sorted.end(), byRatio);

    result.rankedTasks = sorted;

    // Greedily select tasks and check if have enough avaliable time
    for (int i = 0; i < (int)sorted.size(); i++) {
        if (result.totalStudyTime + sorted[i].studyTime <= scenario.availableTime) {
            result.selectedTasks.push_back(sorted[i]);
            result.totalStudyTime += sorted[i].studyTime;
            result.totalImportance += sorted[i].importance;
        }
    }

    clock_t end = clock();
    result.executionTimeMs = (double)(end - start) / CLOCKS_PER_SEC * 1000.0;

    result.comment = "Greedy selection by importance/studyTime ratio";
    return result;
}
