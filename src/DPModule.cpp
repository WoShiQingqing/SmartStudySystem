#include "DPModule.h"

#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

StrategyResult runDPStrategy(const Scenario& scenario) {
    auto start = chrono::high_resolution_clock::now();

    StrategyResult result;
    result.strategyName = "Dynamic Programming";

    const vector<Task>& tasks = scenario.tasks;
    int timeLimit = scenario.availableTime;
    int n = tasks.size();

    if (timeLimit <= 0 || n == 0) {
        auto end = chrono::high_resolution_clock::now();
        result.executionTimeMs = chrono::duration<double, milli>(end - start).count();
        result.comment = "No task is selected because the available study time is not enough.";
        return result;
    }

    // dp[i][w] means the best importance score using first i tasks within w hours
    vector<vector<int>> dp(n + 1, vector<int>(timeLimit + 1, 0));

    for (int i = 1; i <= n; i++) {
        int need = tasks[i - 1].studyTime;
        int value = tasks[i - 1].importance;

        for (int w = 0; w <= timeLimit; w++) {
            if (need <= w) {
                int notChoose = dp[i - 1][w];
                int choose = dp[i - 1][w - need] + value;
                dp[i][w] = max(notChoose, choose);
            }
            else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    int w = timeLimit;

    // backtrack to find which tasks are selected
    for (int i = n; i >= 1; i--) {
        if (dp[i][w] != dp[i - 1][w]) {
            result.selectedTasks.push_back(tasks[i - 1]);
            w -= tasks[i - 1].studyTime;
        }
    }

    reverse(result.selectedTasks.begin(), result.selectedTasks.end());

    result.totalStudyTime = 0;
    result.totalImportance = 0;

    for (const Task& task : result.selectedTasks) {
        result.totalStudyTime += task.studyTime;
        result.totalImportance += task.importance;
    }

    auto end = chrono::high_resolution_clock::now();
    result.executionTimeMs = chrono::duration<double, milli>(end - start).count();

    result.comment =
        "DP selects the task combination with the highest total importance under the available time limit.";

    return result;
}
