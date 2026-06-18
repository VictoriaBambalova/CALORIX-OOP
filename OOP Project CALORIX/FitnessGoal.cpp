#include "FitnessGoal.h"

#include <iostream>
#include <sstream>

FitnessGoal::FitnessGoal()
    : goalType(GoalType::NONE),
    targetValue(0),
    startDate(Date::today()),
    deadline(Date::today()),
    achieved(false) {
}

FitnessGoal::FitnessGoal(
    GoalType goalType,
    double targetValue,
    const Date& startDate,
    const Date& deadline,
    bool achieved
)
    : goalType(goalType),
    targetValue(targetValue),
    startDate(startDate),
    deadline(deadline),
    achieved(achieved) {
}

GoalType FitnessGoal::getGoalType() const {
    return goalType;
}

double FitnessGoal::getTargetValue() const {
    return targetValue;
}

Date FitnessGoal::getStartDate() const {
    return startDate;
}

Date FitnessGoal::getDeadline() const {
    return deadline;
}

bool FitnessGoal::isAchieved() const {
    return achieved;
}

void FitnessGoal::setGoalType(GoalType goalType) {
    this->goalType = goalType;
}

void FitnessGoal::setTargetValue(double targetValue) {
    this->targetValue = targetValue;
}

void FitnessGoal::setStartDate(const Date& startDate) {
    this->startDate = startDate;
}

void FitnessGoal::setDeadline(const Date& deadline) {
    this->deadline = deadline;
}

void FitnessGoal::setAchieved(bool achieved) {
    this->achieved = achieved;
}

bool FitnessGoal::hasGoal() const {
    return goalType != GoalType::NONE;
}

std::string FitnessGoal::toFileString() const {
    std::ostringstream out;

    out << goalTypeToString(goalType) << ";"
        << targetValue << ";"
        << startDate.toString() << ";"
        << deadline.toString() << ";"
        << achieved;

    return out.str();
}

FitnessGoal FitnessGoal::fromFileString(const std::string& line) {
    std::istringstream in(line);

    std::string goalTypeStr;
    std::string targetValueStr;
    std::string startDateStr;
    std::string deadlineStr;
    std::string achievedStr;

    std::getline(in, goalTypeStr, ';');
    std::getline(in, targetValueStr, ';');
    std::getline(in, startDateStr, ';');
    std::getline(in, deadlineStr, ';');
    std::getline(in, achievedStr, ';');

    bool achieved = achievedStr == "1";

    return FitnessGoal(
        stringToGoalType(goalTypeStr),
        std::stod(targetValueStr),
        Date::fromString(startDateStr),
        Date::fromString(deadlineStr),
        achieved
    );
}

void FitnessGoal::print() const {
    if (!hasGoal()) {
        std::cout << "No fitness goal set.\n";
        return;
    }

    std::cout << "Goal type: " << goalTypeToString(goalType) << "\n";
    std::cout << "Target value: " << targetValue << "\n";
    std::cout << "Start date: " << startDate.toString() << "\n";
    std::cout << "Deadline: " << deadline.toString() << "\n";
    std::cout << "Achieved: " << (achieved ? "Yes" : "No") << "\n";
}