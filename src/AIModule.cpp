#include "AIModule.h"
#include "SortingModule.h"  // For Student 2's Merge Sort Module
#include "GreedyModule.h"   // For Student 3's Greedy Ratio Module
#include "DPModule.h"       // For Student 4's 0/1 Knapsack DP Module
#include <cmath>
#include <numeric>
#include <chrono>

// Module 5: Extract mathematical scenario features from input
ScenarioFeatures extractFeatures(const Scenario& scenario) {
    ScenarioFeatures features;
    features.numberOfTasks = static_cast<int>(scenario.tasks.size());
    features.availableTime = scenario.availableTime;

    // Handle edge case where task list is empty
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

    // First pass: Calculate sums for required time, importance, and deadlines
    for (const auto& task : scenario.tasks) {
        totalRequiredTime += task.studyTime;
        sumImportance += task.importance;
        sumDeadline += task.deadline;
    }

    features.totalRequiredTime = totalRequiredTime;
    
    // Calculate Time Pressure Ratio (TPR)
    if (features.availableTime > 0) {
        features.timePressureRatio = static_cast<double>(totalRequiredTime) / features.availableTime;
    } else {
        features.timePressureRatio = 99.0; // High value representing extreme time shortage
    }

    // Calculate mean statistics
    features.averageImportance = sumImportance / features.numberOfTasks;
    features.deadlineTightness = sumDeadline / features.numberOfTasks;

    // Second pass: Calculate Importance Variation (Statistical Variance)
    double varianceSum = 0.0;
    for (const auto& task : scenario.tasks) {
        varianceSum += std::pow(task.importance - features.averageImportance, 2);
    }
    features.importanceVariation = varianceSum / features.numberOfTasks;

    return features;
}

// Module 5 & 6: Intelligent strategy prediction and execution tracking
StrategyResult runAIModule(const Scenario& scenario) {
    // 1. Extract context features from the current scenario
    ScenarioFeatures features = extractFeatures(scenario);

    // 2. Map features to the best algorithmic strategy via Rule-based Decision Tree
    std::string predictedStrategy;

    if (features.timePressureRatio <= 0.8) {
        // Condition A: Time is highly abundant framework (TPR <= 0.8)
        // Recommend Student 2's Divide-and-Conquer Sorting (Merge Sort)
        predictedStrategy = "Sorting-based ranking";
    } 
    else if (features.timePressureRatio > 1.5 && features.deadlineTightness <= 3.0) {
        // Condition B: Extreme time shortage and urgent deadlines close by
        // Recommend Student 3's cost-benefit ratio scheduler (Greedy Strategy)
        predictedStrategy = "Greedy strategy";
    } 
    else {
        // Condition C: Standard constrained resource allocation situations
        // Treat as 0/1 Knapsack, recommend Student 4's Dynamic Programming Module
        predictedStrategy = "Dynamic Programming";
    }

    // 3. Execute the predicted strategy and measure runtime performance precision (Module 6)
    StrategyResult result;
    
    auto start = std::chrono::high_resolution_clock::now();

    if (predictedStrategy == "Sorting-based ranking") {
        result = runSortingStrategy(scenario); // Triggers Student 2's system
    } 
    else if (predictedStrategy == "Greedy strategy") {
        result = runGreedyStrategy(scenario);   // Triggers Student 3's system
    } 
    else {
        result = runDPStrategy(scenario);       // Triggers Student 4's system
    }

    auto end = std::chrono::high_resolution_clock::now();
    double elapsedMs = std::chrono::duration<double, std::milli>(end - start).count();

    // 4. Wrap metadata and performance logs into the final result object
    result.strategyName = "AI Recommendation (" + predictedStrategy + ")";
    result.executionTimeMs = elapsedMs;
    result.comment = "AI Decision Tree selected '" + predictedStrategy + "' based on TPR=" + 
                     std::to_string(features.timePressureRatio).substr(0,4) + 
                     " and DeadlineTightness=" + std::to_string(features.deadlineTightness).substr(0,4) + " days.";

    return result;
}
