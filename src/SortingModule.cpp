#include "SortingModule.h"

#include <chrono>
#include <cstddef>
#include <vector>

namespace {

// This keeps the ranking rule in one place for merge sort
bool comesBefore(const Task& left, const Task& right) {
    if (left.deadline != right.deadline) {
        return left.deadline < right.deadline;
    }
    if (left.importance != right.importance) {
        return left.importance > right.importance;
    }
    if (left.studyTime != right.studyTime) {
        return left.studyTime < right.studyTime;
    }
    return left.id < right.id;
}

// This merges two sorted halves back into one ordered range
void merge(
    std::vector<Task>& tasks,
    std::vector<Task>& buffer,
    std::size_t left,
    std::size_t middle,
    std::size_t right
) {
    std::size_t first = left;
    std::size_t second = middle;
    std::size_t target = left;

    while (first < middle && second < right) {
        if (comesBefore(tasks[first], tasks[second])) {
            buffer[target++] = tasks[first++];
        } else {
            buffer[target++] = tasks[second++];
        }
    }

    while (first < middle) {
        buffer[target++] = tasks[first++];
    }

    while (second < right) {
        buffer[target++] = tasks[second++];
    }

    for (std::size_t index = left; index < right; ++index) {
        tasks[index] = buffer[index];
    }
}

// This is the recursive split-and-merge part of merge sort
void mergeSort(
    std::vector<Task>& tasks,
    std::vector<Task>& buffer,
    std::size_t left,
    std::size_t right
) {
    if (right - left <= 1) {
        return;
    }

    std::size_t middle = left + (right - left) / 2;
    mergeSort(tasks, buffer, left, middle);
    mergeSort(tasks, buffer, middle, right);
    merge(tasks, buffer, left, middle, right);
}

// This walks the ranked list and stops when time runs out
std::vector<Task> chooseTasksWithinTimeLimit(const std::vector<Task>& rankedTasks, int availableTime) {
    std::vector<Task> selectedTasks;
    int usedTime = 0;

    for (const Task& task : rankedTasks) {
        if (usedTime + task.studyTime <= availableTime) {
            selectedTasks.push_back(task);
            usedTime += task.studyTime;
        }
    }

    return selectedTasks;
}

// This totals the selected hours for the result summary
int totalStudyTime(const std::vector<Task>& tasks) {
    int total = 0;
    for (const Task& task : tasks) {
        total += task.studyTime;
    }
    return total;
}

// This totals the selected importance for the result summary
int totalImportance(const std::vector<Task>& tasks) {
    int total = 0;
    for (const Task& task : tasks) {
        total += task.importance;
    }
    return total;
}

}  // namespace

StrategyResult runSortingStrategy(const Scenario& scenario) {
    const auto start = std::chrono::high_resolution_clock::now();

    StrategyResult result;
    result.strategyName = "Sorting-based ranking";
    result.rankedTasks = scenario.tasks;

    std::vector<Task> buffer(result.rankedTasks.size());
    mergeSort(result.rankedTasks, buffer, 0, result.rankedTasks.size());

    result.selectedTasks = chooseTasksWithinTimeLimit(result.rankedTasks, scenario.availableTime);
    result.totalStudyTime = totalStudyTime(result.selectedTasks);
    result.totalImportance = totalImportance(result.selectedTasks);

    const auto end = std::chrono::high_resolution_clock::now();
    result.executionTimeMs = std::chrono::duration<double, std::milli>(end - start).count();
    // Keep the final note aligned with the actual ranking rule used above
    result.comment =
        "Merge Sort ranks tasks by earliest deadline first, then higher importance, "
        "shorter study time, and task ID. Tasks are selected in that order while "
        "staying within the available study time.";

    return result;
}
