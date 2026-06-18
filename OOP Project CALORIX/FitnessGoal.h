#pragma once

#include <string>

#include "Date.h"
#include "Enums.h"

class FitnessGoal {
private:
    GoalType goalType;
    double targetValue;
    Date startDate;
    Date deadline;
    bool achieved;

public:
    FitnessGoal();
    FitnessGoal(
        GoalType goalType,
        double targetValue,
        const Date& startDate,
        const Date& deadline,
        bool achieved = false
    );

    GoalType getGoalType() const;
    double getTargetValue() const;
    Date getStartDate() const;
    Date getDeadline() const;
    bool isAchieved() const;

    void setGoalType(GoalType goalType);
    void setTargetValue(double targetValue);
    void setStartDate(const Date& startDate);
    void setDeadline(const Date& deadline);
    void setAchieved(bool achieved);

    bool hasGoal() const;

    std::string toFileString() const;
    static FitnessGoal fromFileString(const std::string& line);

    void print() const;
};