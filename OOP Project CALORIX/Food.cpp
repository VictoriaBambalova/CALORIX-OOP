#include "Food.h"

#include <iostream>
#include <sstream>

Food::Food()
    : foodId(0),
    name(""),
    caloriesPer100g(0),
    proteinPer100g(0),
    carbsPer100g(0),
    fatPer100g(0) {
}

Food::Food(
    int foodId,
    const std::string& name,
    double caloriesPer100g,
    double proteinPer100g,
    double carbsPer100g,
    double fatPer100g
)
    : foodId(foodId),
    name(name),
    caloriesPer100g(caloriesPer100g),
    proteinPer100g(proteinPer100g),
    carbsPer100g(carbsPer100g),
    fatPer100g(fatPer100g) {
}

int Food::getFoodId() const {
    return foodId;
}

const std::string& Food::getName() const {
    return name;
}

double Food::getCaloriesPer100g() const {
    return caloriesPer100g;
}

double Food::getProteinPer100g() const {
    return proteinPer100g;
}

double Food::getCarbsPer100g() const {
    return carbsPer100g;
}

double Food::getFatPer100g() const {
    return fatPer100g;
}

void Food::setFoodId(int foodId) {
    this->foodId = foodId;
}

void Food::setName(const std::string& name) {
    this->name = name;
}

void Food::setCaloriesPer100g(double caloriesPer100g) {
    this->caloriesPer100g = caloriesPer100g;
}

void Food::setProteinPer100g(double proteinPer100g) {
    this->proteinPer100g = proteinPer100g;
}

void Food::setCarbsPer100g(double carbsPer100g) {
    this->carbsPer100g = carbsPer100g;
}

void Food::setFatPer100g(double fatPer100g) {
    this->fatPer100g = fatPer100g;
}

double Food::calculateCalories(double quantityGrams) const {
    return caloriesPer100g * quantityGrams / 100.0;
}

double Food::calculateProtein(double quantityGrams) const {
    return proteinPer100g * quantityGrams / 100.0;
}

double Food::calculateCarbs(double quantityGrams) const {
    return carbsPer100g * quantityGrams / 100.0;
}

double Food::calculateFat(double quantityGrams) const {
    return fatPer100g * quantityGrams / 100.0;
}

std::string Food::toFileString() const {
    std::ostringstream out;

    out << foodId << ";"
        << name << ";"
        << caloriesPer100g << ";"
        << proteinPer100g << ";"
        << carbsPer100g << ";"
        << fatPer100g;

    return out.str();
}

Food Food::fromFileString(const std::string& line) {
    std::istringstream in(line);

    std::string idStr;
    std::string name;
    std::string caloriesStr;
    std::string proteinStr;
    std::string carbsStr;
    std::string fatStr;

    std::getline(in, idStr, ';');
    std::getline(in, name, ';');
    std::getline(in, caloriesStr, ';');
    std::getline(in, proteinStr, ';');
    std::getline(in, carbsStr, ';');
    std::getline(in, fatStr, ';');

    return Food(
        std::stoi(idStr),
        name,
        std::stod(caloriesStr),
        std::stod(proteinStr),
        std::stod(carbsStr),
        std::stod(fatStr)
    );
}

void Food::print() const {
    std::cout << "Food ID: " << foodId << "\n";
    std::cout << "Name: " << name << "\n";
    std::cout << "Calories per 100g: " << caloriesPer100g << "\n";
    std::cout << "Protein per 100g: " << proteinPer100g << "\n";
    std::cout << "Carbs per 100g: " << carbsPer100g << "\n";
    std::cout << "Fat per 100g: " << fatPer100g << "\n";
}