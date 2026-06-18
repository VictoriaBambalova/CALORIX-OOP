#pragma once

#include <string>

#include "Enums.h"

class Exercise {
private:
    int exerciseId;
    std::string name;
    double caloriesBurnedPerHour;
    MuscleGroup muscleGroup;
    int defaultDurationMinutes;

public:
    Exercise();
    Exercise(
        int exerciseId,
        const std::string& name,
        double caloriesBurnedPerHour,
        MuscleGroup muscleGroup,
        int defaultDurationMinutes = 15
    );

    int getExerciseId() const;
    const std::string& getName() const;
    double getCaloriesBurnedPerHour() const;
    MuscleGroup getMuscleGroup() const;
    int getDefaultDurationMinutes() const;

    void setExerciseId(int exerciseId);
    void setName(const std::string& name);
    void setCaloriesBurnedPerHour(double caloriesBurnedPerHour);
    void setMuscleGroup(MuscleGroup muscleGroup);
    void setDefaultDurationMinutes(int defaultDurationMinutes);

    double calculateBurnedCalories(int durationMinutes) const;

    std::string toFileString() const;
    static Exercise fromFileString(const std::string& line);

    void print() const;
};