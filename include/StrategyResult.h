#ifndef STRATEGY_RESULT_H
#define STRATEGY_RESULT_H

#include <string>
#include <vector>

#include "Task.h"

// This is the common output shape every strategy returns
struct StrategyResult {
    std::string strategyName;
    std::vector<Task> rankedTasks;
    std::vector<Task> selectedTasks;
    int totalStudyTime = 0;
    int totalImportance = 0;
    double executionTimeMs = 0.0;
    std::string comment;
};

#endif
