#ifndef AI_MODULE_H
#define AI_MODULE_H

#include "Scenario.h"
#include "StrategyResult.h"

struct ScenarioFeatures {
    int numberOfTasks = 0;
    int totalRequiredTime = 0;
    int availableTime = 0;
    double timePressureRatio = 0.0;
    double averageImportance = 0.0;
    double deadlineTightness = 0.0;
    double importanceVariation = 0.0;
};

ScenarioFeatures extractFeatures(const Scenario& scenario);
StrategyResult runAIModule(const Scenario& scenario);

#endif

