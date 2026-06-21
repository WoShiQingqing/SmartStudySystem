#ifndef TASK_H
#define TASK_H

#include <string>

struct Task {
    std::string id;
    std::string name;
    int studyTime;
    int importance;
    int deadline;
    int difficulty;
    std::string type;

    double importanceTimeRatio() const {
        return studyTime == 0 ? 0.0 : static_cast<double>(importance) / studyTime;
    }
};

#endif

