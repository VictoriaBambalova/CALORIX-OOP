#include "Enums.h"

#include <algorithm>
#include <cctype>

//to upper
static std::string normalizeEnumString(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(),
        [](unsigned char ch) {
            return static_cast<char>(std::toupper(ch));
        });

    return str;
}

std::string genderToString(Gender gender) {
    switch (gender) {
    case Gender::MALE:
        return "MALE";
    case Gender::FEMALE:
        return "FEMALE";
    default:
        return "UNKNOWN";
    }
}

Gender stringToGender(const std::string& str) {
    std::string value = normalizeEnumString(str);

    if (value == "MALE") {
        return Gender::MALE;
    }
    if (value == "FEMALE") {
        return Gender::FEMALE;
    }

    return Gender::UNKNOWN;
}

std::string activityLevelToString(ActivityLevel level) {
    switch (level) {
    case ActivityLevel::SEDENTARY:
        return "SEDENTARY";
    case ActivityLevel::LIGHT:
        return "LIGHT";
    case ActivityLevel::MODERATE:
        return "MODERATE";
    case ActivityLevel::ACTIVE:
        return "ACTIVE";
    case ActivityLevel::VERY_ACTIVE:
        return "VERY_ACTIVE";
    default:
        return "SEDENTARY";
    }
}

ActivityLevel stringToActivityLevel(const std::string& str) {
    std::string value = normalizeEnumString(str);

    if (value == "SEDENTARY") {
        return ActivityLevel::SEDENTARY;
    }
    if (value == "LIGHT") {
        return ActivityLevel::LIGHT;
    }
    if (value == "MODERATE") {
        return ActivityLevel::MODERATE;
    }
    if (value == "ACTIVE") {
        return ActivityLevel::ACTIVE;
    }
    if (value == "VERY_ACTIVE") {
        return ActivityLevel::VERY_ACTIVE;
    }

    return ActivityLevel::SEDENTARY;
}

std::string goalTypeToString(GoalType type) {
    switch (type) {
    case GoalType::WEIGHT_LOSS:
        return "WEIGHT_LOSS";
    case GoalType::BULKING:
        return "BULKING";
    case GoalType::MAINTENANCE:
        return "MAINTENANCE";
    default:
        return "NONE";
    }
}

GoalType stringToGoalType(const std::string& str) {
    std::string value = normalizeEnumString(str);

    if (value == "WEIGHT_LOSS") {
        return GoalType::WEIGHT_LOSS;
    }
    if (value == "BULKING") {
        return GoalType::BULKING;
    }
    if (value == "MAINTENANCE") {
        return GoalType::MAINTENANCE;
    }

    return GoalType::NONE;
}

std::string muscleGroupToString(MuscleGroup group) {
    switch (group) {
    case MuscleGroup::CHEST:
        return "CHEST";
    case MuscleGroup::BACK:
        return "BACK";
    case MuscleGroup::LEGS:
        return "LEGS";
    case MuscleGroup::SHOULDERS:
        return "SHOULDERS";
    case MuscleGroup::ARMS:
        return "ARMS";
    case MuscleGroup::CORE:
        return "CORE";
    case MuscleGroup::CARDIO:
        return "CARDIO";
    default:
        return "UNKNOWN";
    }
}

MuscleGroup stringToMuscleGroup(const std::string& str) {
    std::string value = normalizeEnumString(str);

    if (value == "CHEST") {
        return MuscleGroup::CHEST;
    }
    if (value == "BACK") {
        return MuscleGroup::BACK;
    }
    if (value == "LEGS") {
        return MuscleGroup::LEGS;
    }
    if (value == "SHOULDERS") {
        return MuscleGroup::SHOULDERS;
    }
    if (value == "ARMS") {
        return MuscleGroup::ARMS;
    }
    if (value == "CORE") {
        return MuscleGroup::CORE;
    }
    if (value == "CARDIO") {
        return MuscleGroup::CARDIO;
    }

    return MuscleGroup::UNKNOWN;
}

std::string userRoleToString(UserRole role) {
    switch (role) {
    case UserRole::ADMIN:
        return "ADMIN";
    case UserRole::TRAINEE:
        return "TRAINEE";
    default:
        return "TRAINEE";
    }
}

UserRole stringToUserRole(const std::string& str) {
    std::string value = normalizeEnumString(str);

    if (value == "ADMIN") {
        return UserRole::ADMIN;
    }

    return UserRole::TRAINEE;
}