#include "Exercise.h"

#include <iostream>
#include <sstream>

Exercise::Exercise()
    : exerciseId(0),
    name(""),
    caloriesBurnedPerHour(0),
    muscleGroup(MuscleGroup::UNKNOWN),
    defaultDurationMinutes(15) {
}

Exercise::Exercise(
    int exerciseId,
    const std::string& name,
    double caloriesBurnedPerHour,
    MuscleGroup muscleGroup,
    int defaultDurationMinutes
)
    : exerciseId(exerciseId),
    name(name),
    caloriesBurnedPerHour(caloriesBurnedPerHour),
    muscleGroup(muscleGroup),
    defaultDurationMinutes(defaultDurationMinutes) {
}

int Exercise::getExerciseId() const {
    return exerciseId;
}

const std::string& Exercise::getName() const {
    return name;
}

double Exercise::getCaloriesBurnedPerHour() const {
    return caloriesBurnedPerHour;
}

MuscleGroup Exercise::getMuscleGroup() const {
    return muscleGroup;
}

int Exercise::getDefaultDurationMinutes() const {
    return defaultDurationMinutes;
}

void Exercise::setExerciseId(int exerciseId) {
    this->exerciseId = exerciseId;
}

void Exercise::setName(const std::string& name) {
    this->name = name;
}

void Exercise::setCaloriesBurnedPerHour(double caloriesBurnedPerHour) {
    this->caloriesBurnedPerHour = caloriesBurnedPerHour;
}

void Exercise::setMuscleGroup(MuscleGroup muscleGroup) {
    this->muscleGroup = muscleGroup;
}

void Exercise::setDefaultDurationMinutes(int defaultDurationMinutes) {
    this->defaultDurationMinutes = defaultDurationMinutes;
}

double Exercise::calculateBurnedCalories(int durationMinutes) const {
    return caloriesBurnedPerHour * durationMinutes / 60.0;
}

std::string Exercise::toFileString() const {
    std::ostringstream out;

    out << exerciseId << ";"
        << name << ";"
        << caloriesBurnedPerHour << ";"
        << muscleGroupToString(muscleGroup) << ";"
        << defaultDurationMinutes;

    return out.str();
}

Exercise Exercise::fromFileString(const std::string& line) {
    std::istringstream in(line);

    std::string idStr;
    std::string name;
    std::string caloriesStr;
    std::string muscleGroupStr;
    std::string durationStr;

    std::getline(in, idStr, ';');
    std::getline(in, name, ';');
    std::getline(in, caloriesStr, ';');
    std::getline(in, muscleGroupStr, ';');
    std::getline(in, durationStr, ';');

    int defaultDuration = 15;

    if (!durationStr.empty()) {
        defaultDuration = std::stoi(durationStr);
    }

    return Exercise(
        std::stoi(idStr),
        name,
        std::stod(caloriesStr),
        stringToMuscleGroup(muscleGroupStr),
        defaultDuration
    );
}

void Exercise::print() const {
    std::cout << "Exercise ID: " << exerciseId << "\n";
    std::cout << "Name: " << name << "\n";
    std::cout << "Calories burned per hour: " << caloriesBurnedPerHour << "\n";
    std::cout << "Muscle group: " << muscleGroupToString(muscleGroup) << "\n";
    std::cout << "Default duration: " << defaultDurationMinutes << " minutes\n";
}