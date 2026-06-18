#pragma once

#include <vector>
#include <string>

#include "User.h"
#include "FoodEntry.h"
#include "ExerciseEntry.h"
#include "FitnessGoal.h"

class Trainee : public User {
private:
    std::vector<FoodEntry> foodDiary;
    std::vector<ExerciseEntry> exerciseDiary;
    FitnessGoal goal;
    std::vector<int> favoriteExerciseIds;

public:
    Trainee();
    Trainee(
        int userId,
        const std::string& username,
        const std::string& password,
        const UserProfile& profile
    );

    UserRole getRole() const override;
    void printHelp() const override;

    const std::vector<FoodEntry>& getFoodDiary() const;
    const std::vector<ExerciseEntry>& getExerciseDiary() const;
    const FitnessGoal& getGoal() const;
    FitnessGoal& getGoal();
    const std::vector<int>& getFavoriteExerciseIds() const;

    void setGoal(const FitnessGoal& goal);

    void addFoodEntry(const FoodEntry& entry);
    void addExerciseEntry(const ExerciseEntry& entry);

    void addFavoriteExercise(int exerciseId);
    bool hasFavoriteExercise(int exerciseId) const;

    void clearFoodDiary();
    void clearExerciseDiary();
    void clearFavorites();
};