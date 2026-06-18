#pragma once

#include <vector>

#include "Exercise.h"
#include "WorkoutPlan.h"

class WorkoutPlanner {
public:
    static WorkoutPlan generateOptimalPlan(
        const std::vector<Exercise>& exercises,
        int maxDurationMinutes
    );
};