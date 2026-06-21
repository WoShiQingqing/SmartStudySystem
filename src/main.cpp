#include <iostream>
#include <limits>
#include <vector>

#include "AIModule.h"
#include "DPModule.h"
#include "GreedyModule.h"
#include "ScenarioFactory.h"
#include "SortingModule.h"
#include "Utils.h"

namespace {

int readInt(const char* prompt) {
    int value = 0;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            return value;
        }

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a number.\n";
    }
}

const Scenario& chooseScenario(const std::vector<Scenario>& scenarios) {
    printScenarioMenu(scenarios);
    int choice = readInt("Choose a scenario number: ");

    while (choice < 1 || choice > static_cast<int>(scenarios.size())) {
        choice = readInt("Out of range. Choose a valid scenario number: ");
    }

    return scenarios[static_cast<std::size_t>(choice - 1)];
}

void inspectScenario(const Scenario& scenario) {
    printScenarioSummary(scenario);
    printTaskTable(scenario.tasks);
}

void runScenario(const Scenario& scenario) {
    printScenarioSummary(scenario);

    StrategyResult sortingResult = runSortingStrategy(scenario);
    StrategyResult greedyResult = runGreedyStrategy(scenario);
    StrategyResult dpResult = runDPStrategy(scenario);
    StrategyResult aiResult = runAIModule(scenario);

    std::vector<StrategyResult> results = {
        sortingResult,
        greedyResult,
        dpResult,
        aiResult
    };

    for (const StrategyResult& result : results) {
        printStrategyResult(result);
    }

    printComparisonTable(results);
}

}  // namespace

int main() {
    std::vector<Scenario> scenarios = createScenarios();

    while (true) {
        std::cout << "\nStudySmart AI\n";
        std::cout << "1. List scenarios\n";
        std::cout << "2. Inspect scenario dataset\n";
        std::cout << "3. Run integration demo for one scenario\n";
        std::cout << "4. Show collaboration rules\n";
        std::cout << "0. Exit\n";

        int choice = readInt("Enter your choice: ");

        if (choice == 0) {
            std::cout << "Exiting StudySmart AI.\n";
            break;
        }

        if (choice == 1) {
            printScenarioMenu(scenarios);
        } else if (choice == 2) {
            const Scenario& scenario = chooseScenario(scenarios);
            inspectScenario(scenario);
        } else if (choice == 3) {
            const Scenario& scenario = chooseScenario(scenarios);
            runScenario(scenario);
        } else if (choice == 4) {
            printIntegrationRules();
        } else {
            std::cout << "Unsupported option. Please choose 0 to 4.\n";
        }
    }

    return 0;
}

