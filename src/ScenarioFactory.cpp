#include "ScenarioFactory.h"

#include <vector>

namespace {

// This helper keeps the task list readable when we build scenarios below
Task makeTask(
    const char* id,
    const char* name,
    int studyTime,
    int importance,
    int deadline,
    int difficulty,
    const char* type
) {
    return Task{id, name, studyTime, importance, deadline, difficulty, type};
}

std::vector<Task> makeBaseTasks() {
    // All scenarios start from the same base dataset so later comparisons stay fair
    return {
        makeTask("T1", "Revise Dynamic Programming", 3, 8, 2, 4, "Revision"),
        makeTask("T2", "Complete Graph Tutorial", 2, 7, 3, 3, "Tutorial"),
        makeTask("T3", "Practise Greedy Problem Set", 2, 6, 5, 3, "Practice"),
        makeTask("T4", "Finish Algorithms Assignment Part A", 4, 9, 2, 5, "Assignment"),
        makeTask("T5", "Review Sorting Lecture Notes", 1, 5, 6, 2, "Lecture"),
        makeTask("T6", "Mock Quiz on Complexity Analysis", 2, 7, 4, 4, "Practice"),
        makeTask("T7", "Prepare Midterm Formula Sheet", 1, 8, 1, 2, "Revision"),
        makeTask("T8", "Revise Backtracking", 3, 6, 4, 4, "Revision"),
        makeTask("T9", "Complete Past-Year Question Set", 4, 9, 3, 5, "Practice"),
        makeTask("T10", "Watch MST Tutorial Video", 2, 4, 7, 2, "Tutorial"),
        makeTask("T11", "Rewrite Weak Tutorial Solutions", 3, 6, 5, 3, "Tutorial"),
        makeTask("T12", "Study NP-Completeness Overview", 2, 5, 6, 4, "Lecture")
    };
}

Scenario makeLowPressureScenario() {
    return Scenario{
        "Low Pressure",
        "Available time is enough for most tasks, so the student can focus on broad coverage.",
        26,
        makeBaseTasks()
    };
}

Scenario makeHighPressureScenario() {
    std::vector<Task> tasks = makeBaseTasks();
    // A few tasks get even more valuable here to make selection harder
    tasks[3].importance = 10;
    tasks[6].importance = 9;
    tasks[8].importance = 10;

    return Scenario{
        "High Pressure",
        "Available time is much lower than total required time, so task selection becomes critical.",
        10,
        tasks
    };
}

Scenario makeDeadlineFocusedScenario() {
    std::vector<Task> tasks = makeBaseTasks();
    // Tighten several deadlines so urgency matters more than usual
    tasks[0].deadline = 1;
    tasks[1].deadline = 1;
    tasks[3].deadline = 1;
    tasks[5].deadline = 2;
    tasks[8].deadline = 1;
    tasks[10].deadline = 2;

    return Scenario{
        "Deadline Focused",
        "Several tasks become urgent, so urgency should strongly affect prioritization.",
        14,
        tasks
    };
}

Scenario makeImportanceFocusedScenario() {
    std::vector<Task> tasks = makeBaseTasks();
    // Spread the importance scores more so top-value tasks stand out clearly
    tasks[3].importance = 10;
    tasks[6].importance = 10;
    tasks[8].importance = 10;
    tasks[4].importance = 3;
    tasks[9].importance = 2;
    tasks[11].importance = 3;

    return Scenario{
        "Importance Focused",
        "A few tasks carry exceptionally high academic value, so maximizing importance matters most.",
        14,
        tasks
    };
}

}  // namespace

std::vector<Scenario> createScenarios() {
    // Keep all scenario creation in one place so everyone tests the same inputs
    return {
        makeLowPressureScenario(),
        makeHighPressureScenario(),
        makeDeadlineFocusedScenario(),
        makeImportanceFocusedScenario()
    };
}
