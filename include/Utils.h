#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

#include "Scenario.h"
#include "StrategyResult.h"
#include "Task.h"

int sumStudyTime(const std::vector<Task>& tasks);
int sumImportance(const std::vector<Task>& tasks);
std::string formatTaskList(const std::vector<Task>& tasks);

void printScenarioMenu(const std::vector<Scenario>& scenarios);
void printScenarioSummary(const Scenario& scenario);
void printTaskTable(const std::vector<Task>& tasks);
void printStrategyResult(const StrategyResult& result);
void printComparisonTable(const std::vector<StrategyResult>& results);

#endif
