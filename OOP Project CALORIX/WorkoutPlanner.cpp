#include "WorkoutPlanner.h"

#include <algorithm>

WorkoutPlan WorkoutPlanner::generateOptimalPlan(
    const std::vector<Exercise>& exercises,
    int maxDurationMinutes
) {
    if (exercises.empty() || maxDurationMinutes <= 0) {
        return WorkoutPlan();
    }

    int n = static_cast<int>(exercises.size());

    std::vector<std::vector<double>> dp(
        n + 1,
        std::vector<double>(maxDurationMinutes + 1, 0)
    );

    for (int i = 1; i <= n; i++) {
        int duration = exercises[i - 1].getDefaultDurationMinutes();
        double calories = exercises[i - 1].calculateBurnedCalories(duration);

        for (int currentTime = 0; currentTime <= maxDurationMinutes; currentTime++) {
            dp[i][currentTime] = dp[i - 1][currentTime];

            if (duration <= currentTime) {
                double withCurrentExercise =
                    dp[i - 1][currentTime - duration] + calories;

                if (withCurrentExercise > dp[i][currentTime]) {
                    dp[i][currentTime] = withCurrentExercise;
                }
            }
        }
    }

    std::vector<Exercise> selectedExercises;
    int remainingTime = maxDurationMinutes;

    for (int i = n; i >= 1; i--) {
        if (dp[i][remainingTime] != dp[i - 1][remainingTime]) {
            const Exercise& selected = exercises[i - 1];
            selectedExercises.push_back(selected);
            remainingTime -= selected.getDefaultDurationMinutes();
        }
    }

    std::reverse(selectedExercises.begin(), selectedExercises.end());

    int totalDuration = 0;
    double totalCalories = 0;

    for (const Exercise& exercise : selectedExercises) {
        int duration = exercise.getDefaultDurationMinutes();
        totalDuration += duration;
        totalCalories += exercise.calculateBurnedCalories(duration);
    }

    return WorkoutPlan(selectedExercises, totalDuration, totalCalories);
}