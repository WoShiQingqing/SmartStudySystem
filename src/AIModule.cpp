#include "AIModule.h"
#include "SortingModule.h"  // For Student 2's Merge Sort Module
#include "GreedyModule.h"   // For Student 3's Greedy Ratio Module
#include "DPModule.h"       // For Student 4's 0/1 Knapsack DP Module
#include <cmath>
#include <numeric>
#include <chrono>

// This turns raw task data into a smaller feature summary
ScenarioFeatures extractFeatures(const Scenario& scenario) {
    ScenarioFeatures features;
    features.numberOfTasks = static_cast<int>(scenario.tasks.size());
    features.availableTime = scenario.availableTime;

    // Bail out early if the scenario has no tasks
    if (features.numberOfTasks == 0) {
        features.totalRequiredTime = 0;
        features.timePressureRatio = 0.0;
        features.averageImportance = 0.0;
        features.deadlineTightness = 0.0;
        features.importanceVariation = 0.0;
        return features;
    }

    int totalRequiredTime = 0;
    double sumImportance = 0.0;
    double sumDeadline = 0.0;

    // First pass collects the totals needed for the feature formulas
    for (const auto& task : scenario.tasks) {
        totalRequiredTime += task.studyTime;
        sumImportance += task.importance;
        sumDeadline += task.deadline;
    }

    features.totalRequiredTime = totalRequiredTime;
    
    // Time pressure compares required hours against available hours
    if (features.availableTime > 0) {
        features.timePressureRatio = static_cast<double>(totalRequiredTime) / features.availableTime;
    } else {
        // Use a large fallback value when there is no available time at all
        features.timePressureRatio = 99.0;
    }

    // These averages give the AI rule a quick picture of the task set
    features.averageImportance = sumImportance / features.numberOfTasks;
    features.deadlineTightness = sumDeadline / features.numberOfTasks;

    // Second pass measures how spread out the importance scores are
    double varianceSum = 0.0;
    for (const auto& task : scenario.tasks) {
        varianceSum += std::pow(task.importance - features.averageImportance, 2);
    }
    features.importanceVariation = varianceSum / features.numberOfTasks;

    return features;
}

// This predicts a strategy and then runs the matching module
StrategyResult runAIModule(const Scenario& scenario) {
    // Start by extracting the feature snapshot for this scenario
    ScenarioFeatures features = extractFeatures(scenario);

    // Use the rule set below to choose which module should handle the case
    std::string predictedStrategy;

    if (features.timePressureRatio <= 0.8) {
        // Plenty of time means ranking first is usually enough
        predictedStrategy = "Sorting-based ranking";
    } 
    else if (features.timePressureRatio > 1.5 && features.deadlineTightness <= 3.0) {
        // Tight time and close deadlines push the greedy choice
        predictedStrategy = "Greedy strategy";
    } 
    else {
        // Everything else falls back to the knapsack-style planner
        predictedStrategy = "Dynamic Programming";
    }

    // Run the chosen module and time the call for the final report
    StrategyResult result;
    
    auto start = std::chrono::high_resolution_clock::now();

    if (predictedStrategy == "Sorting-based ranking") {
        result = runSortingStrategy(scenario);
    } 
    else if (predictedStrategy == "Greedy strategy") {
        result = runGreedyStrategy(scenario);
    } 
    else {
        result = runDPStrategy(scenario);
    }

    auto end = std::chrono::high_resolution_clock::now();
    double elapsedMs = std::chrono::duration<double, std::milli>(end - start).count();

    // Re-label the result so the output shows both the AI pick and runtime
    result.strategyName = "AI Recommendation (" + predictedStrategy + ")";
    result.executionTimeMs = elapsedMs;
    result.comment = "AI Decision Tree selected '" + predictedStrategy + "' based on TPR=" + 
                     std::to_string(features.timePressureRatio).substr(0,4) + 
                     " and DeadlineTightness=" + std::to_string(features.deadlineTightness).substr(0,4) + " days.";

    return result;
}
