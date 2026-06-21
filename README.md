# StudySmart AI

This workspace contains the Student 1 deliverables for the `CST207 StudySmart AI` project:

- shared data structures
- scenario dataset and scenario factory
- menu entry point
- common output helpers
- integration stubs for Students 2 to 5

## Local setup

The project uses a local virtual environment only for isolated helper work in this directory.

```bash
python3 -m venv .venv
source .venv/bin/activate
```

The C++ build itself uses the system compiler and does not install any packages.

## Build and run

```bash
make
./build/study_smart_ai
```

## File structure

```text
include/
  Task.h
  Scenario.h
  StrategyResult.h
  ScenarioFactory.h
  SortingModule.h
  GreedyModule.h
  DPModule.h
  AIModule.h
  Utils.h
src/
  main.cpp
  ScenarioFactory.cpp
  SortingModule.cpp
  GreedyModule.cpp
  DPModule.cpp
  AIModule.cpp
  Utils.cpp
docs/
  integration_contract.md
```

## Collaboration contract

Students 2 to 5 should follow these rules during integration:

1. Do not redefine `Task`, `Scenario`, or `StrategyResult`.
2. Keep module input as `const Scenario&`.
3. Keep module output as `StrategyResult`.
4. Change only your own module files.
5. Do not create another `main.cpp`.

## Current status

- Student 1 work is ready.
- Students 2 to 4 currently have compile-safe stubs only.
- Student 5 has a starter feature extractor and placeholder recommendation rule.

The stubs exist so the project can compile before the algorithm modules are fully implemented.
