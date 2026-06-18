#include "UserProfile.h"

UserProfile::UserProfile()
    : age(0),
    weight(0),
    height(0),
    gender(Gender::UNKNOWN),
    activityLevel(ActivityLevel::SEDENTARY) {
}

UserProfile::UserProfile(
    int age,
    double weight,
    double height,
    Gender gender,
    ActivityLevel activityLevel
)
    : age(age),
    weight(weight),
    height(height),
    gender(gender),
    activityLevel(activityLevel) {
}

int UserProfile::getAge() const {
    return age;
}

double UserProfile::getWeight() const {
    return weight;
}

double UserProfile::getHeight() const {
    return height;
}

Gender UserProfile::getGender() const {
    return gender;
}

ActivityLevel UserProfile::getActivityLevel() const {
    return activityLevel;
}

void UserProfile::setAge(int age) {
    this->age = age;
}

void UserProfile::setWeight(double weight) {
    this->weight = weight;
}

void UserProfile::setHeight(double height) {
    this->height = height;
}

void UserProfile::setGender(Gender gender) {
    this->gender = gender;
}

void UserProfile::setActivityLevel(ActivityLevel activityLevel) {
    this->activityLevel = activityLevel;
}

double UserProfile::calculateBMI() const {
    double heightInMeters = height / 100.0;

    if (heightInMeters <= 0) {
        return 0;
    }

    return weight / (heightInMeters * heightInMeters);
}

double UserProfile::calculateBMR() const {
    if (gender == Gender::MALE) {
        return 10 * weight + 6.25 * height - 5 * age + 5;
    }

    if (gender == Gender::FEMALE) {
        return 10 * weight + 6.25 * height - 5 * age - 161;
    }

    return 0;
}

double UserProfile::calculateDailyCalories() const {
    double bmr = calculateBMR();

    switch (activityLevel) {
    case ActivityLevel::SEDENTARY:
        return bmr * 1.2;
    case ActivityLevel::LIGHT:
        return bmr * 1.375;
    case ActivityLevel::MODERATE:
        return bmr * 1.55;
    case ActivityLevel::ACTIVE:
        return bmr * 1.725;
    case ActivityLevel::VERY_ACTIVE:
        return bmr * 1.9;
    default:
        return bmr;
    }
}