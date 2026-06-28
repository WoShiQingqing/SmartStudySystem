#ifndef SCENARIO_H
#define SCENARIO_H

#include <string>
#include <vector>

#include "Task.h"

// This bundles one test case with its time limit and task list
struct Scenario {
    std::string name;
    std::string description;
    int availableTime;
    std::vector<Task> tasks;
};

#endif
