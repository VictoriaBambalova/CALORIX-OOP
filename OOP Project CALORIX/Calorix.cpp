#include "Calorix.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>

Calorix::Calorix()
    : loggedUser(nullptr),
    nextUserId(1),
    nextFoodId(1),
    nextExerciseId(1),
    nextFoodEntryId(1),
    nextExerciseEntryId(1) {
}

Calorix& Calorix::getInstance() {
    static Calorix instance;
    return instance;
}

User* Calorix::findUserByUsername(const std::string& username) {
    for (const auto& user : users) {
        if (user->getUsername() == username) {
            return user.get();
        }
    }

    return nullptr;
}

Food* Calorix::findFoodByName(const std::string& name) {
    for (Food& food : foods) {
        if (food.getName() == name) {
            return &food;
        }
    }

    return nullptr;
}

Food* Calorix::findFoodById(int foodId) {
    for (Food& food : foods) {
        if (food.getFoodId() == foodId) {
            return &food;
        }
    }

    return nullptr;
}

Exercise* Calorix::findExerciseByName(const std::string& name) {
    for (Exercise& exercise : exercises) {
        if (exercise.getName() == name) {
            return &exercise;
        }
    }

    return nullptr;
}

Exercise* Calorix::findExerciseById(int exerciseId) {
    for (Exercise& exercise : exercises) {
        if (exercise.getExerciseId() == exerciseId) {
            return &exercise;
        }
    }

    return nullptr;
}

Trainee* Calorix::getLoggedTrainee() {
    return dynamic_cast<Trainee*>(loggedUser);
}

Admin* Calorix::getLoggedAdmin() {
    return dynamic_cast<Admin*>(loggedUser);
}

bool Calorix::usernameExists(const std::string& username) const {
    for (const auto& user : users) {
        if (user->getUsername() == username) {
            return true;
        }
    }

    return false;
}

void Calorix::createDefaultAdminIfNeeded() {
    if (!users.empty()) {
        return;
    }

    UserProfile adminProfile(
        30,
        80,
        180,
        Gender::MALE,
        ActivityLevel::MODERATE
    );

    users.push_back(std::make_unique<Admin>(
        nextUserId++,
        "admin",
        "admin123",
        adminProfile
    ));

    std::cout << "Default admin created.\n";
    std::cout << "Username: admin\n";
    std::cout << "Password: admin123\n";
}

void Calorix::handleRegister(std::istringstream& input) {
    std::string username;
    std::string password;
    int age;
    double weight;
    double height;
    std::string genderStr;
    std::string activityLevelStr;

    input >> username >> password >> age >> weight >> height >> genderStr;

    if (!input) {
        std::cout << "Usage: register <username> <password> <age> <weight> <height> <gender> [activity-level]\n";
        return;
    }

    if (!(input >> activityLevelStr)) {
        activityLevelStr = "SEDENTARY";
    }

    if (usernameExists(username)) {
        std::cout << "Username already exists.\n";
        return;
    }

    UserProfile profile(
        age,
        weight,
        height,
        stringToGender(genderStr),
        stringToActivityLevel(activityLevelStr)
    );

    users.push_back(std::make_unique<Trainee>(
        nextUserId++,
        username,
        password,
        profile
    ));

    std::cout << "User registered successfully.\n";
}

void Calorix::handleLogin(std::istringstream& input) {
    std::string username;
    std::string password;

    input >> username >> password;

    if (!input) {
        std::cout << "Usage: login <username> <password>\n";
        return;
    }

    User* user = findUserByUsername(username);

    if (user == nullptr || !user->checkPassword(password)) {
        std::cout << "Invalid username or password.\n";
        return;
    }

    loggedUser = user;

    std::cout << "Logged in successfully as " << loggedUser->getUsername() << ".\n";
}

void Calorix::handleLogout() {
    if (loggedUser == nullptr) {
        std::cout << "No user is currently logged in.\n";
        return;
    }

    std::cout << "User " << loggedUser->getUsername() << " logged out.\n";
    loggedUser = nullptr;
}

void Calorix::handleHelp() const {
    if (loggedUser == nullptr) {
        std::cout << "Available commands:\n";
        std::cout << "register <username> <password> <age> <weight> <height> <gender> [activity-level]\n";
        std::cout << "login <username> <password>\n";
        std::cout << "help\n";
        std::cout << "end\n";
        return;
    }

    loggedUser->printHelp();
}

void Calorix::handleSetGoals(std::istringstream& input) {
    Trainee* trainee = getLoggedTrainee();

    if (trainee == nullptr) {
        std::cout << "Only trainees can set goals.\n";
        return;
    }

    std::string goalTypeStr;
    double targetValue;
    std::string deadlineStr;

    input >> goalTypeStr >> targetValue >> deadlineStr;

    if (!input) {
        std::cout << "Usage: set-goals <goal-type> <target-value> <deadline YYYY-MM-DD>\n";
        return;
    }

    GoalType goalType = stringToGoalType(goalTypeStr);

    if (goalType == GoalType::NONE) {
        std::cout << "Invalid goal type. Use WEIGHT_LOSS, BULKING or MAINTENANCE.\n";
        return;
    }

    Date deadline = Date::fromString(deadlineStr);
    Date today = Date::today();

    if (deadline.getYear() < today.getYear() ||
        (deadline.getYear() == today.getYear() && deadline.getMonth() < today.getMonth()) ||
        (deadline.getYear() == today.getYear() && deadline.getMonth() == today.getMonth() && deadline.getDay() < today.getDay())) {
        std::cout << "Invalid deadline. Deadline cannot be in the past.\n";
        return;
    }

    FitnessGoal goal(
        goalType,
        targetValue,
        today,
        deadline,
        false
    );

    trainee->setGoal(goal);

    std::cout << "Goal set successfully.\n";
}

void Calorix::handleLogFood(std::istringstream& input) {
    Trainee* trainee = getLoggedTrainee();

    if (trainee == nullptr) {
        std::cout << "Only trainees can log food.\n";
        return;
    }

    std::string foodName;
    double quantityGrams;

    input >> foodName >> quantityGrams;

    if (!input) {
        std::cout << "Usage: log-food <food-name> <quantity_grams>\n";
        return;
    }

    Food* food = findFoodByName(foodName);

    if (food == nullptr) {
        std::cout << "Food not found.\n";
        return;
    }

    FoodEntry entry(
        nextFoodEntryId++,
        food->getFoodId(),
        quantityGrams,
        Date::today()
    );

    trainee->addFoodEntry(entry);

    std::cout << "Food logged successfully.\n";
}

void Calorix::handleLogExercise(std::istringstream& input) {
    Trainee* trainee = getLoggedTrainee();

    if (trainee == nullptr) {
        std::cout << "Only trainees can log exercises.\n";
        return;
    }

    std::string exerciseName;
    int durationMinutes;

    input >> exerciseName >> durationMinutes;

    if (!input) {
        std::cout << "Usage: log-exercise <exercise-name> <duration_minutes>\n";
        return;
    }

    Exercise* exercise = findExerciseByName(exerciseName);

    if (exercise == nullptr) {
        std::cout << "Exercise not found.\n";
        return;
    }

    ExerciseEntry entry(
        nextExerciseEntryId++,
        exercise->getExerciseId(),
        durationMinutes,
        Date::today()
    );

    trainee->addExerciseEntry(entry);

    std::cout << "Exercise logged successfully.\n";
}

void Calorix::handleViewDailySummary() {
    Trainee* trainee = getLoggedTrainee();

    if (trainee == nullptr) {
        std::cout << "Only trainees can view daily summary.\n";
        return;
    }

    Date today = Date::today();

    double totalCalories = 0;
    double totalProtein = 0;
    double totalCarbs = 0;
    double totalFat = 0;
    double totalBurnedCalories = 0;

    for (const FoodEntry& entry : trainee->getFoodDiary()) {
        if (entry.getDate().toString() == today.toString()) {
            Food* food = findFoodById(entry.getFoodId());

            if (food != nullptr) {
                double quantity = entry.getQuantityGrams();

                totalCalories += food->calculateCalories(quantity);
                totalProtein += food->calculateProtein(quantity);
                totalCarbs += food->calculateCarbs(quantity);
                totalFat += food->calculateFat(quantity);
            }
        }
    }

    for (const ExerciseEntry& entry : trainee->getExerciseDiary()) {
        if (entry.getDate().toString() == today.toString()) {
            Exercise* exercise = findExerciseById(entry.getExerciseId());

            if (exercise != nullptr) {
                totalBurnedCalories += exercise->calculateBurnedCalories(
                    entry.getDurationMinutes()
                );
            }
        }
    }

    double netBalance = totalCalories - totalBurnedCalories;

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Daily summary for " << today.toString() << ":\n";
    std::cout << "Consumed calories: " << totalCalories << "\n";
    std::cout << "Protein: " << totalProtein << " g\n";
    std::cout << "Carbs: " << totalCarbs << " g\n";
    std::cout << "Fat: " << totalFat << " g\n";
    std::cout << "Burned calories: " << totalBurnedCalories << "\n";
    std::cout << "Net calorie balance: " << netBalance << "\n";
}

void Calorix::handleViewProgress() {
    Trainee* trainee = getLoggedTrainee();

    if (trainee == nullptr) {
        std::cout << "Only trainees can view progress.\n";
        return;
    }

    FitnessGoal& goal = trainee->getGoal();

    if (!goal.hasGoal()) {
        std::cout << "No goal has been set.\n";
        return;
    }

    double currentWeight = trainee->getProfile().getWeight();
    double difference = goal.getTargetValue() - currentWeight;
    const double tolerance = 0.1;

    if (goal.getGoalType() == GoalType::WEIGHT_LOSS ||
        goal.getGoalType() == GoalType::BULKING ||
        goal.getGoalType() == GoalType::MAINTENANCE) {
        if (difference >= -tolerance && difference <= tolerance) {
            goal.setAchieved(true);
        }
        else {
            goal.setAchieved(false);
        }
    }

    goal.print();

    if (goal.getGoalType() == GoalType::WEIGHT_LOSS ||
        goal.getGoalType() == GoalType::BULKING) {
        std::cout << "Current weight: " << currentWeight << " kg\n";

        if (difference > tolerance) {
            std::cout << "You need to gain " << difference << " kg to reach your target.\n";
        }
        else if (difference < -tolerance) {
            std::cout << "You need to lose " << -difference << " kg to reach your target.\n";
        }
        else {
            std::cout << "You have reached your target weight.\n";
        }
    }
    else if (goal.getGoalType() == GoalType::MAINTENANCE) {
        std::cout << "Current weight: " << currentWeight << " kg\n";

        if (difference > tolerance) {
            std::cout << "You are below your maintenance target by " << difference << " kg.\n";
        }
        else if (difference < -tolerance) {
            std::cout << "You are above your maintenance target by " << -difference << " kg.\n";
        }
        else {
            std::cout << "You are maintaining your target weight.\n";
        }
    }
}

void Calorix::handleCalculateBMI() {
    Trainee* trainee = getLoggedTrainee();

    if (trainee == nullptr) {
        std::cout << "Only trainees can calculate BMI.\n";
        return;
    }

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "BMI: " << trainee->getProfile().calculateBMI() << "\n";
}

void Calorix::handleCalculateBMR() {
    Trainee* trainee = getLoggedTrainee();

    if (trainee == nullptr) {
        std::cout << "Only trainees can calculate BMR.\n";
        return;
    }

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "BMR: " << trainee->getProfile().calculateBMR() << " kcal\n";
    std::cout << "Estimated daily calories: "
        << trainee->getProfile().calculateDailyCalories()
        << " kcal\n";
}

void Calorix::handleGenerateWorkoutPlan(std::istringstream& input) {
    Trainee* trainee = getLoggedTrainee();

    if (trainee == nullptr) {
        std::cout << "Only trainees can generate workout plans.\n";
        return;
    }

    int durationMinutes;

    input >> durationMinutes;

    if (!input) {
        std::cout << "Usage: generate-workout-plan <duration_minutes>\n";
        return;
    }

    WorkoutPlan plan = WorkoutPlanner::generateOptimalPlan(
        exercises,
        durationMinutes
    );

    plan.print();
}

void Calorix::handleAddToFavorites(std::istringstream& input) {
    Trainee* trainee = getLoggedTrainee();

    if (trainee == nullptr) {
        std::cout << "Only trainees can add favorites.\n";
        return;
    }

    std::string exerciseName;

    input >> exerciseName;

    if (!input) {
        std::cout << "Usage: add-to-favorites <exercise-name>\n";
        return;
    }

    Exercise* exercise = findExerciseByName(exerciseName);

    if (exercise == nullptr) {
        std::cout << "Exercise not found.\n";
        return;
    }

    trainee->addFavoriteExercise(exercise->getExerciseId());

    std::cout << "Exercise added to favorites.\n";
}

void Calorix::handleViewFavorites() {
    Trainee* trainee = getLoggedTrainee();

    if (trainee == nullptr) {
        std::cout << "Only trainees can view favorites.\n";
        return;
    }

    const std::vector<int>& favoriteIds = trainee->getFavoriteExerciseIds();

    if (favoriteIds.empty()) {
        std::cout << "No favorite exercises.\n";
        return;
    }

    std::cout << "Favorite exercises:\n";

    for (int exerciseId : favoriteIds) {
        Exercise* exercise = findExerciseById(exerciseId);

        if (exercise != nullptr) {
            std::cout << "- " << exercise->getName()
                << " | Muscle group: "
                << muscleGroupToString(exercise->getMuscleGroup())
                << "\n";
        }
    }
}

void Calorix::handleBlockUser(std::istringstream& input) {
    Admin* admin = getLoggedAdmin();

    if (admin == nullptr) {
        std::cout << "Only admins can block users.\n";
        return;
    }

    std::string username;

    input >> username;

    if (!input) {
        std::cout << "Usage: block-user <username>\n";
        return;
    }

    if (username == admin->getUsername()) {
        std::cout << "Admin cannot block himself.\n";
        return;
    }

    auto oldSize = users.size();

    users.erase(
        std::remove_if(
            users.begin(),
            users.end(),
            [&username](const std::unique_ptr<User>& user) {
                return user->getUsername() == username;
            }
        ),
        users.end()
    );

    if (users.size() == oldSize) {
        std::cout << "User not found.\n";
    }
    else {
        std::cout << "User blocked and removed successfully.\n";
    }
}

void Calorix::handleAddFood(std::istringstream& input) {
    Admin* admin = getLoggedAdmin();

    if (admin == nullptr) {
        std::cout << "Only admins can add food.\n";
        return;
    }

    std::string name;
    double calories;
    double protein;
    double carbs;
    double fat;

    input >> name >> calories >> protein >> carbs >> fat;

    if (!input) {
        std::cout << "Usage: add-food <name> <calories_per_100g> <protein_per_100g> <carbs_per_100g> <fat_per_100g>\n";
        return;
    }

    if (findFoodByName(name) != nullptr) {
        std::cout << "Food already exists.\n";
        return;
    }

    foods.push_back(Food(
        nextFoodId++,
        name,
        calories,
        protein,
        carbs,
        fat
    ));

    std::cout << "Food added successfully.\n";
}

void Calorix::handleAddExercise(std::istringstream& input) {
    Admin* admin = getLoggedAdmin();

    if (admin == nullptr) {
        std::cout << "Only admins can add exercises.\n";
        return;
    }

    std::string name;
    double caloriesBurnedPerHour;
    std::string muscleGroupStr;
    int defaultDurationMinutes;

    input >> name >> caloriesBurnedPerHour >> muscleGroupStr >> defaultDurationMinutes;

    if (!input || defaultDurationMinutes <= 0) {
        std::cout << "Usage: add-exercise <name> <calories_burned_per_hour> <muscle-group> <default_duration_minutes>\n";
        return;
    }

    if (findExerciseByName(name) != nullptr) {
        std::cout << "Exercise already exists.\n";
        return;
    }

    exercises.push_back(Exercise(
        nextExerciseId++,
        name,
        caloriesBurnedPerHour,
        stringToMuscleGroup(muscleGroupStr),
        defaultDurationMinutes
    ));

    std::cout << "Exercise added successfully.\n";
}

void Calorix::handleUpdateFood(std::istringstream& input) {
    Admin* admin = getLoggedAdmin();

    if (admin == nullptr) {
        std::cout << "Only admins can update food.\n";
        return;
    }

    std::string foodName;
    double newCalories;

    input >> foodName >> newCalories;

    if (!input) {
        std::cout << "Usage: update-food <food-name> <new-calories>\n";
        return;
    }

    Food* food = findFoodByName(foodName);

    if (food == nullptr) {
        std::cout << "Food not found.\n";
        return;
    }

    food->setCaloriesPer100g(newCalories);

    std::cout << "Food updated successfully.\n";
}

void Calorix::handleUpdateWeight(std::istringstream& input) {
    Trainee* trainee = getLoggedTrainee();

    if (trainee == nullptr) {
        std::cout << "Only trainees can update weight.\n";
        return;
    }

    double newWeight;
    input >> newWeight;

    if (!input || newWeight <= 0) {
        std::cout << "Usage: update-weight <new-weight>\n";
        return;
    }

    trainee->getProfile().setWeight(newWeight);

    std::cout << "Weight updated successfully.\n";
}

void Calorix::loadUsers() {
    std::ifstream file("users.txt");

    if (!file.is_open()) {
        return;
    }

    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        std::istringstream in(line);

        std::string idStr;
        std::string roleStr;
        std::string username;
        std::string password;
        std::string ageStr;
        std::string weightStr;
        std::string heightStr;
        std::string genderStr;
        std::string activityLevelStr;

        std::getline(in, idStr, ';');
        std::getline(in, roleStr, ';');
        std::getline(in, username, ';');
        std::getline(in, password, ';');
        std::getline(in, ageStr, ';');
        std::getline(in, weightStr, ';');
        std::getline(in, heightStr, ';');
        std::getline(in, genderStr, ';');
        std::getline(in, activityLevelStr, ';');

        int userId = std::stoi(idStr);

        UserProfile profile(
            std::stoi(ageStr),
            std::stod(weightStr),
            std::stod(heightStr),
            stringToGender(genderStr),
            stringToActivityLevel(activityLevelStr)
        );

        if (stringToUserRole(roleStr) == UserRole::ADMIN) {
            users.push_back(std::make_unique<Admin>(
                userId,
                username,
                password,
                profile
            ));
        }
        else {
            users.push_back(std::make_unique<Trainee>(
                userId,
                username,
                password,
                profile
            ));
        }

        if (userId >= nextUserId) {
            nextUserId = userId + 1;
        }
    }

    file.close();
}

void Calorix::saveUsers() const {
    std::ofstream file("users.txt");

    for (const auto& user : users) {
        file << user->toFileString() << "\n";
    }

    file.close();
}

void Calorix::loadFoods() {
    std::ifstream file("foods.txt");

    if (!file.is_open()) {
        return;
    }

    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        Food food = Food::fromFileString(line);
        foods.push_back(food);

        if (food.getFoodId() >= nextFoodId) {
            nextFoodId = food.getFoodId() + 1;
        }
    }

    file.close();
}

void Calorix::saveFoods() const {
    std::ofstream file("foods.txt");

    for (const Food& food : foods) {
        file << food.toFileString() << "\n";
    }

    file.close();
}

void Calorix::loadExercises() {
    std::ifstream file("exercises.txt");

    if (!file.is_open()) {
        return;
    }

    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        Exercise exercise = Exercise::fromFileString(line);
        exercises.push_back(exercise);

        if (exercise.getExerciseId() >= nextExerciseId) {
            nextExerciseId = exercise.getExerciseId() + 1;
        }
    }

    file.close();
}

void Calorix::saveExercises() const {
    std::ofstream file("exercises.txt");

    for (const Exercise& exercise : exercises) {
        file << exercise.toFileString() << "\n";
    }

    file.close();
}

void Calorix::loadFoodDiary() {
    std::ifstream file("food_diary.txt");

    if (!file.is_open()) {
        return;
    }

    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        std::istringstream in(line);

        std::string userIdStr;
        std::string entryData;

        std::getline(in, userIdStr, ';');
        std::getline(in, entryData);

        int userId = std::stoi(userIdStr);

        for (const auto& user : users) {
            if (user->getUserId() == userId) {
                Trainee* trainee = dynamic_cast<Trainee*>(user.get());

                if (trainee != nullptr) {
                    FoodEntry entry = FoodEntry::fromFileString(entryData);
                    trainee->addFoodEntry(entry);

                    if (entry.getEntryId() >= nextFoodEntryId) {
                        nextFoodEntryId = entry.getEntryId() + 1;
                    }
                }
            }
        }
    }

    file.close();
}

void Calorix::saveFoodDiary() const {
    std::ofstream file("food_diary.txt");

    for (const auto& user : users) {
        const Trainee* trainee = dynamic_cast<const Trainee*>(user.get());

        if (trainee != nullptr) {
            for (const FoodEntry& entry : trainee->getFoodDiary()) {
                file << trainee->getUserId() << ";"
                    << entry.toFileString() << "\n";
            }
        }
    }

    file.close();
}

void Calorix::loadExerciseDiary() {
    std::ifstream file("exercise_diary.txt");

    if (!file.is_open()) {
        return;
    }

    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        std::istringstream in(line);

        std::string userIdStr;
        std::string entryData;

        std::getline(in, userIdStr, ';');
        std::getline(in, entryData);

        int userId = std::stoi(userIdStr);

        for (const auto& user : users) {
            if (user->getUserId() == userId) {
                Trainee* trainee = dynamic_cast<Trainee*>(user.get());

                if (trainee != nullptr) {
                    ExerciseEntry entry = ExerciseEntry::fromFileString(entryData);
                    trainee->addExerciseEntry(entry);

                    if (entry.getEntryId() >= nextExerciseEntryId) {
                        nextExerciseEntryId = entry.getEntryId() + 1;
                    }
                }
            }
        }
    }

    file.close();
}

void Calorix::saveExerciseDiary() const {
    std::ofstream file("exercise_diary.txt");

    for (const auto& user : users) {
        const Trainee* trainee = dynamic_cast<const Trainee*>(user.get());

        if (trainee != nullptr) {
            for (const ExerciseEntry& entry : trainee->getExerciseDiary()) {
                file << trainee->getUserId() << ";"
                    << entry.toFileString() << "\n";
            }
        }
    }

    file.close();
}

void Calorix::loadGoals() {
    std::ifstream file("goals.txt");

    if (!file.is_open()) {
        return;
    }

    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        std::istringstream in(line);

        std::string userIdStr;
        std::string goalData;

        std::getline(in, userIdStr, ';');
        std::getline(in, goalData);

        int userId = std::stoi(userIdStr);

        for (const auto& user : users) {
            if (user->getUserId() == userId) {
                Trainee* trainee = dynamic_cast<Trainee*>(user.get());

                if (trainee != nullptr) {
                    trainee->setGoal(FitnessGoal::fromFileString(goalData));
                }
            }
        }
    }

    file.close();
}

void Calorix::saveGoals() const {
    std::ofstream file("goals.txt");

    for (const auto& user : users) {
        const Trainee* trainee = dynamic_cast<const Trainee*>(user.get());

        if (trainee != nullptr && trainee->getGoal().hasGoal()) {
            file << trainee->getUserId() << ";"
                << trainee->getGoal().toFileString() << "\n";
        }
    }

    file.close();
}

void Calorix::loadFavorites() {
    std::ifstream file("favorites.txt");

    if (!file.is_open()) {
        return;
    }

    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        std::istringstream in(line);

        std::string userIdStr;
        std::string exerciseIdStr;

        std::getline(in, userIdStr, ';');
        std::getline(in, exerciseIdStr, ';');

        int userId = std::stoi(userIdStr);
        int exerciseId = std::stoi(exerciseIdStr);

        for (const auto& user : users) {
            if (user->getUserId() == userId) {
                Trainee* trainee = dynamic_cast<Trainee*>(user.get());

                if (trainee != nullptr) {
                    trainee->addFavoriteExercise(exerciseId);
                }
            }
        }
    }

    file.close();
}

void Calorix::saveFavorites() const {
    std::ofstream file("favorites.txt");

    for (const auto& user : users) {
        const Trainee* trainee = dynamic_cast<const Trainee*>(user.get());

        if (trainee != nullptr) {
            for (int exerciseId : trainee->getFavoriteExerciseIds()) {
                file << trainee->getUserId() << ";"
                    << exerciseId << "\n";
            }
        }
    }

    file.close();
}

void Calorix::loadAll() {
    loadUsers();
    createDefaultAdminIfNeeded();

    loadFoods();
    loadExercises();

    loadFoodDiary();
    loadExerciseDiary();
    loadGoals();
    loadFavorites();
}

void Calorix::saveAll() const {
    saveUsers();
    saveFoods();
    saveExercises();
    saveFoodDiary();
    saveExerciseDiary();
    saveGoals();
    saveFavorites();
}

void Calorix::handleListFoods() const {
    if (foods.empty()) {
        std::cout << "No foods available.\n";
        return;
    }

    std::cout << "Available foods:\n";

    for (const Food& food : foods) {
        std::cout << "- " << food.getName()
            << " | Calories per 100g: " << food.getCaloriesPer100g()
            << " | Protein: " << food.getProteinPer100g()
            << " g | Carbs: " << food.getCarbsPer100g()
            << " g | Fat: " << food.getFatPer100g()
            << " g\n";
    }
}

void Calorix::handleListExercises() const {
    if (exercises.empty()) {
        std::cout << "No exercises available.\n";
        return;
    }

    std::cout << "Available exercises:\n";

    for (const Exercise& exercise : exercises) {
        std::cout << "- " << exercise.getName()
            << " | Calories per hour: " << exercise.getCaloriesBurnedPerHour()
            << " | Muscle group: " << muscleGroupToString(exercise.getMuscleGroup())
            << " | Default duration: " << exercise.getDefaultDurationMinutes()
            << " min\n";
    }
}

void Calorix::run() {
    loadAll();

    std::cout << "Welcome to Calorix!\n";
    std::cout << "Type help to see available commands.\n";

    std::string line;

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, line);

        if (line.empty()) {
            continue;
        }

        std::istringstream input(line);

        std::string command;
        input >> command;

        if (command == "end") {
            saveAll();
            std::cout << "Data saved. Exiting Calorix.\n";
            break;
        }
        else if (command == "register") {
            handleRegister(input);
        }
        else if (command == "login") {
            handleLogin(input);
        }
        else if (command == "logout") {
            handleLogout();
        }
        else if (command == "help") {
            handleHelp();
        }
        else if (command == "list-foods") {
            handleListFoods();
        }
        else if (command == "list-exercises") {
            handleListExercises();
        }
        else if (command == "set-goals") {
            handleSetGoals(input);
        }
        else if (command == "log-food") {
            handleLogFood(input);
        }
        else if (command == "log-exercise") {
            handleLogExercise(input);
        }
        else if (command == "view-daily-summary") {
            handleViewDailySummary();
        }
        else if (command == "view-progress") {
            handleViewProgress();
        }
        else if (command == "calculate-bmi") {
            handleCalculateBMI();
        }
        else if (command == "calculate-bmr") {
            handleCalculateBMR();
        }
        else if (command == "generate-workout-plan") {
            handleGenerateWorkoutPlan(input);
        }
        else if (command == "add-to-favorites") {
            handleAddToFavorites(input);
        }
        else if (command == "view-favorites") {
            handleViewFavorites();
        }
        else if (command == "block-user") {
            handleBlockUser(input);
        }
        else if (command == "add-food") {
            handleAddFood(input);
        }
        else if (command == "add-exercise") {
            handleAddExercise(input);
        }
        else if (command == "update-food") {
            handleUpdateFood(input);
        }
        else if (command == "update-weight") {
            handleUpdateWeight(input);
        }
        else {
            std::cout << "Unknown command. Type help to see available commands.\n";
        }
    }
}