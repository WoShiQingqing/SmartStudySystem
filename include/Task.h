#ifndef TASK_H
#define TASK_H

#include <string>

// This keeps the shared fields every module reads from
struct Task {
    std::string id;
    std::string name;
    int studyTime;
    int importance;
    int deadline;
    int difficulty;
    std::string type;

    // This gives greedy-style rules a quick score to compare
    double importanceTimeRatio() const {
        return studyTime == 0 ? 0.0 : static_cast<double>(importance) / studyTime;
    }
};

#endif
