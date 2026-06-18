#pragma once

#include <string>

enum class Gender {
    MALE,
    FEMALE,
    UNKNOWN
};

enum class ActivityLevel {
    SEDENTARY,
    LIGHT,
    MODERATE,
    ACTIVE,
    VERY_ACTIVE
};

enum class GoalType {
    WEIGHT_LOSS,
    BULKING,
    MAINTENANCE,
    NONE
};

enum class MuscleGroup {
    CHEST,
    BACK,
    LEGS,
    SHOULDERS,
    ARMS,
    CORE,
    CARDIO,
    UNKNOWN
};

enum class UserRole {
    ADMIN,
    TRAINEE
};

std::string genderToString(Gender gender);
Gender stringToGender(const std::string& str);

std::string activityLevelToString(ActivityLevel level);
ActivityLevel stringToActivityLevel(const std::string& str);

std::string goalTypeToString(GoalType type);
GoalType stringToGoalType(const std::string& str);

std::string muscleGroupToString(MuscleGroup group);
MuscleGroup stringToMuscleGroup(const std::string& str);

std::string userRoleToString(UserRole role);
UserRole stringToUserRole(const std::string& str);
