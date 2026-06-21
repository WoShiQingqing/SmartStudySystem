# Integration Contract

This document is the implementation contract for all group members.

## Shared structures

### `Task`

```cpp
struct Task {
    std::string id;
    std::string name;
    int studyTime;
    int importance;
    int deadline;
    int difficulty;
    std::string type;
};
```

Units:

- `studyTime`: hours
- `importance`: 1 to 10
- `deadline`: days remaining
- `difficulty`: 1 to 5

### `Scenario`

```cpp
struct Scenario {
    std::string name;
    std::string description;
    int availableTime;
    std::vector<Task> tasks;
};
```

### `StrategyResult`

```cpp
struct StrategyResult {
    std::string strategyName;
    std::vector<Task> rankedTasks;
    std::vector<Task> selectedTasks;
    int totalStudyTime = 0;
    int totalImportance = 0;
    double executionTimeMs = 0.0;
    std::string comment;
};
```

## Required function signatures

```cpp
StrategyResult runSortingStrategy(const Scenario& scenario);
StrategyResult runGreedyStrategy(const Scenario& scenario);
StrategyResult runDPStrategy(const Scenario& scenario);
StrategyResult runAIModule(const Scenario& scenario);
```

## Ownership

- Student 1: `Task`, `Scenario`, `StrategyResult`, `ScenarioFactory`, `Utils`, `main.cpp`
- Student 2: `SortingModule.h/.cpp`
- Student 3: `GreedyModule.h/.cpp`
- Student 4: `DPModule.h/.cpp`
- Student 5: `AIModule.h/.cpp`, comparison analysis, final report integration


## Scenario list

The current project already includes four scenarios:

1. `Low Pressure`
2. `High Pressure`
3. `Deadline Focused`
4. `Importance Focused`

At least two of them must be used in the final report. Keeping four scenarios in code makes later testing easier.

