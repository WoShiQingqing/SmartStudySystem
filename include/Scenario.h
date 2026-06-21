#ifndef SCENARIO_H
#define SCENARIO_H

#include <string>
#include <vector>

#include "Task.h"

struct Scenario {
    std::string name;
    std::string description;
    int availableTime;
    std::vector<Task> tasks;
};

#endif

