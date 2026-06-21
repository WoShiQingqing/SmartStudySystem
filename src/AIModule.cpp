#include "AIModule.h"

#include <cmath>

#include "Utils.h"

ScenarioFeatures extractFeatures(const Scenario& scenario) {
    ScenarioFeatures features;
    features.numberOfTasks = static_cast<int>(scenario.tasks.size());
    features.totalRequiredTime = sumStudyTime(scenario.tasks);
    features.availableTime = scenario.availableTime;
    features.timePressureRatio =
        scenario.availableTime == 0
            ? 0.0
            : static_cast<double>(features.totalRequiredTime) / scenario.availableTime;

    // Bail out early if someone feeds an empty scenario into the AI module.
    if (scenario.tasks.empty()) {
        return features;
    }

    double totalImportance = 0.0;
    double totalDeadlineInverse = 0.0;
    for (const Task& task : scenario.tasks) {
        totalImportance += task.importance;
        // Smaller deadlines should push the urgency feature upward.
        totalDeadlineInverse += 1.0 / task.deadline;
    }

    features.averageImportance = totalImportance / scenario.tasks.size();
    features.deadlineTightness = totalDeadlineInverse / scenario.tasks.size();

    double squaredDifference = 0.0;
    for (const Task& task : scenario.tasks) {
        double difference = task.importance - features.averageImportance;
        squaredDifference += difference * difference;
    }

    // Standard deviation is a simple way to show whether importance is tightly grouped or spread out.
    features.importanceVariation = std::sqrt(squaredDifference / scenario.tasks.size());
    return features;
}

StrategyResult runAIModule(const Scenario& scenario) {
    // This is only a starter heuristic so Student 5 can swap in a real model later.
    ScenarioFeatures features = extractFeatures(scenario);

    StrategyResult result;
    result.strategyName = "AI/ML recommendation";
    result.comment =
        "Starter rule only. Student 5 can replace this with rule-based AI, Decision Tree, or k-NN.";

    if (features.timePressureRatio >= 1.7) {
        result.comment += " Current placeholder prediction: Dynamic Programming.";
    } else if (features.deadlineTightness >= 0.45) {
        result.comment += " Current placeholder prediction: Sorting-based ranking.";
    } else {
        result.comment += " Current placeholder prediction: Greedy strategy.";
    }

    return result;
}
