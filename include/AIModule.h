#ifndef AI_MODULE_H
#define AI_MODULE_H

#include "Scenario.h"
#include "StrategyResult.h"

// These are the summary signals the AI module looks at
struct ScenarioFeatures {
    int numberOfTasks = 0;
    int totalRequiredTime = 0;
    int availableTime = 0;
    double timePressureRatio = 0.0;
    double averageImportance = 0.0;
    double deadlineTightness = 0.0;
    double importanceVariation = 0.0;
};

// This turns a raw scenario into a smaller feature set
ScenarioFeatures extractFeatures(const Scenario& scenario);
// This picks a strategy from those features and runs it
StrategyResult runAIModule(const Scenario& scenario);

#endif
