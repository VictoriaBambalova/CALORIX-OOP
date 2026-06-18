#include "Trainee.h"

#include <iostream>
#include <algorithm>

Trainee::Trainee()
    : User(), foodDiary(), exerciseDiary(), goal(), favoriteExerciseIds() {
}

Trainee::Trainee(
    int userId,
    const std::string& username,
    const std::string& password,
    const UserProfile& profile
)
    : User(userId, username, password, profile),
    foodDiary(),
    exerciseDiary(),
    goal(),
    favoriteExerciseIds() {
}

UserRole Trainee::getRole() const {
    return UserRole::TRAINEE;
}

void Trainee::printHelp() const {
    std::cout << "Available trainee commands:\n";
    std::cout << "logout\n";
    std::cout << "help\n";
    std::cout << "list-foods\n";
    std::cout << "list-exercises\n";
    std::cout << "set-goals <goal-type> <target-value> <deadline YYYY-MM-DD>\n";
    std::cout << "log-food <food-name> <quantity_grams>\n";
    std::cout << "log-exercise <exercise-name> <duration_minutes>\n";
    std::cout << "view-daily-summary\n";
    std::cout << "view-progress\n";
    std::cout << "calculate-bmi\n";
    std::cout << "calculate-bmr\n";
    std::cout << "generate-workout-plan <duration_minutes>\n";
    std::cout << "add-to-favorites <exercise-name>\n";
    std::cout << "view-favorites\n";
    std::cout << "update-weight <new-weight>\n";
    std::cout << "end\n";
}

const std::vector<FoodEntry>& Trainee::getFoodDiary() const {
    return foodDiary;
}

const std::vector<ExerciseEntry>& Trainee::getExerciseDiary() const {
    return exerciseDiary;
}

const FitnessGoal& Trainee::getGoal() const {
    return goal;
}

FitnessGoal& Trainee::getGoal() {
    return goal;
}

const std::vector<int>& Trainee::getFavoriteExerciseIds() const {
    return favoriteExerciseIds;
}

void Trainee::setGoal(const FitnessGoal& goal) {
    this->goal = goal;
}

void Trainee::addFoodEntry(const FoodEntry& entry) {
    foodDiary.push_back(entry);
}

void Trainee::addExerciseEntry(const ExerciseEntry& entry) {
    exerciseDiary.push_back(entry);
}

void Trainee::addFavoriteExercise(int exerciseId) {
    if (!hasFavoriteExercise(exerciseId)) {
        favoriteExerciseIds.push_back(exerciseId);
    }
}

bool Trainee::hasFavoriteExercise(int exerciseId) const {
    return std::find(
        favoriteExerciseIds.begin(),
        favoriteExerciseIds.end(),
        exerciseId
    ) != favoriteExerciseIds.end();
}

void Trainee::clearFoodDiary() {
    foodDiary.clear();
}

void Trainee::clearExerciseDiary() {
    exerciseDiary.clear();
}

void Trainee::clearFavorites() {
    favoriteExerciseIds.clear();
}