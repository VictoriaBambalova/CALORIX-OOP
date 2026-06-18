#pragma once

#include <vector>
#include <iostream>

#include "Exercise.h"

class WorkoutPlan {
private:
    std::vector<Exercise> selectedExercises;
    int totalDurationMinutes;
    double totalBurnedCalories;

public:
    WorkoutPlan()
        : selectedExercises(),
        totalDurationMinutes(0),
        totalBurnedCalories(0) {
    }

    WorkoutPlan(
        const std::vector<Exercise>& selectedExercises,
        int totalDurationMinutes,
        double totalBurnedCalories
    )
        : selectedExercises(selectedExercises),
        totalDurationMinutes(totalDurationMinutes),
        totalBurnedCalories(totalBurnedCalories) {
    }

    const std::vector<Exercise>& getSelectedExercises() const {
        return selectedExercises;
    }

    int getTotalDurationMinutes() const {
        return totalDurationMinutes;
    }

    double getTotalBurnedCalories() const {
        return totalBurnedCalories;
    }

    void print() const {
        if (selectedExercises.empty()) {
            std::cout << "No workout plan could be generated.\n";
            return;
        }

        std::cout << "Generated workout plan:\n";

        for (const Exercise& exercise : selectedExercises) {
            std::cout << "- " << exercise.getName()
                << " | Duration: " << exercise.getDefaultDurationMinutes()
                << " min | Expected calories: "
                << exercise.calculateBurnedCalories(exercise.getDefaultDurationMinutes())
                << "\n";
        }

        std::cout << "Total duration: " << totalDurationMinutes << " minutes\n";
        std::cout << "Total expected burned calories: " << totalBurnedCalories << "\n";
    }
};