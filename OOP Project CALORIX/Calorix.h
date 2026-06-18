#pragma once

#include <vector>
#include <memory>
#include <string>

#include "User.h"
#include "Trainee.h"
#include "Admin.h"
#include "Food.h"
#include "Exercise.h"
#include "WorkoutPlanner.h"

class Calorix {
private:
    std::vector<std::unique_ptr<User>> users;
    std::vector<Food> foods;
    std::vector<Exercise> exercises;

    User* loggedUser;

    int nextUserId;
    int nextFoodId;
    int nextExerciseId;
    int nextFoodEntryId;
    int nextExerciseEntryId;

    Calorix();

    User* findUserByUsername(const std::string& username);
    Food* findFoodByName(const std::string& name);
    Food* findFoodById(int foodId);
    Exercise* findExerciseByName(const std::string& name);
    Exercise* findExerciseById(int exerciseId);

    Trainee* getLoggedTrainee();
    Admin* getLoggedAdmin();

    bool usernameExists(const std::string& username) const;

    void createDefaultAdminIfNeeded();

    void handleRegister(std::istringstream& input);
    void handleLogin(std::istringstream& input);
    void handleLogout();
    void handleHelp() const;
    void handleListFoods() const;
    void handleListExercises() const;

    void handleSetGoals(std::istringstream& input);
    void handleLogFood(std::istringstream& input);
    void handleLogExercise(std::istringstream& input);
    void handleViewDailySummary();
    void handleViewProgress();
    void handleCalculateBMI();
    void handleCalculateBMR();
    void handleGenerateWorkoutPlan(std::istringstream& input);
    void handleAddToFavorites(std::istringstream& input);
    void handleViewFavorites();

    void handleBlockUser(std::istringstream& input);
    void handleAddFood(std::istringstream& input);
    void handleAddExercise(std::istringstream& input);
    void handleUpdateFood(std::istringstream& input);
    void handleUpdateWeight(std::istringstream& input);

    void loadUsers();
    void saveUsers() const;

    void loadFoods();
    void saveFoods() const;

    void loadExercises();
    void saveExercises() const;

    void loadFoodDiary();
    void saveFoodDiary() const;

    void loadExerciseDiary();
    void saveExerciseDiary() const;

    void loadGoals();
    void saveGoals() const;

    void loadFavorites();
    void saveFavorites() const;

    void loadAll();
    void saveAll() const;

public:
    Calorix(const Calorix&) = delete;
    Calorix& operator=(const Calorix&) = delete;

    static Calorix& getInstance();

    void run();
};