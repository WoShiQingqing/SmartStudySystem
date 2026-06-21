#include "Utils.h"

#include <iomanip>
#include <iostream>
#include <sstream>

int sumStudyTime(const std::vector<Task>& tasks) {
    int total = 0;
    for (const Task& task : tasks) {
        total += task.studyTime;
    }
    return total;
}

int sumImportance(const std::vector<Task>& tasks) {
    int total = 0;
    for (const Task& task : tasks) {
        total += task.importance;
    }
    return total;
}

std::string formatTaskList(const std::vector<Task>& tasks) {
    if (tasks.empty()) {
        return "-";
    }

    std::ostringstream stream;
    for (std::size_t index = 0; index < tasks.size(); ++index) {
        if (index > 0) {
            stream << ", ";
        }
        stream << tasks[index].id;
    }
    return stream.str();
}

void printScenarioMenu(const std::vector<Scenario>& scenarios) {
    std::cout << "\nAvailable scenarios\n";
    for (std::size_t index = 0; index < scenarios.size(); ++index) {
        std::cout << "  " << index + 1 << ". " << scenarios[index].name << '\n';
    }
}

void printScenarioSummary(const Scenario& scenario) {
    std::cout << "\nScenario: " << scenario.name << '\n';
    std::cout << "Description: " << scenario.description << '\n';
    std::cout << "Available study time: " << scenario.availableTime << " hours\n";
    std::cout << "Number of tasks: " << scenario.tasks.size() << '\n';
    std::cout << "Total required study time: " << sumStudyTime(scenario.tasks) << " hours\n";
}

void printTaskTable(const std::vector<Task>& tasks) {
    std::cout << '\n';
    std::cout << std::left
              << std::setw(5) << "ID"
              << std::setw(38) << "Task Name"
              << std::setw(8) << "Time"
              << std::setw(12) << "Importance"
              << std::setw(10) << "Deadline"
              << std::setw(11) << "Difficulty"
              << std::setw(12) << "Type"
              << std::setw(8) << "Ratio"
              << '\n';
    std::cout << std::string(104, '-') << '\n';

    for (const Task& task : tasks) {
        std::cout << std::left
                  << std::setw(5) << task.id
                  << std::setw(38) << task.name
                  << std::setw(8) << task.studyTime
                  << std::setw(12) << task.importance
                  << std::setw(10) << task.deadline
                  << std::setw(11) << task.difficulty
                  << std::setw(12) << task.type
                  << std::fixed << std::setprecision(2)
                  << std::setw(8) << task.importanceTimeRatio()
                  << '\n';
    }
}

void printStrategyResult(const StrategyResult& result) {
    std::cout << "\nStrategy: " << result.strategyName << '\n';
    std::cout << "Selected tasks: " << formatTaskList(result.selectedTasks) << '\n';
    std::cout << "Total study time: " << result.totalStudyTime << '\n';
    std::cout << "Total importance: " << result.totalImportance << '\n';
    std::cout << "Execution time (ms): " << std::fixed << std::setprecision(3)
              << result.executionTimeMs << '\n';
    std::cout << "Comment: " << result.comment << '\n';
}

void printComparisonTable(const std::vector<StrategyResult>& results) {
    std::cout << '\n';
    std::cout << std::left
              << std::setw(24) << "Strategy"
              << std::setw(22) << "Selected Tasks"
              << std::setw(18) << "Total Time"
              << std::setw(18) << "Total Importance"
              << std::setw(16) << "Exec Time (ms)"
              << "Comment\n";
    std::cout << std::string(118, '-') << '\n';

    for (const StrategyResult& result : results) {
        std::cout << std::left
                  << std::setw(24) << result.strategyName
                  << std::setw(22) << formatTaskList(result.selectedTasks)
                  << std::setw(18) << result.totalStudyTime
                  << std::setw(18) << result.totalImportance
                  << std::fixed << std::setprecision(3)
                  << std::setw(16) << result.executionTimeMs
                  << result.comment
                  << '\n';
    }
}

