#include "FoodEntry.h"

#include <sstream>

FoodEntry::FoodEntry()
    : entryId(0),
    foodId(0),
    quantityGrams(0),
    date(Date::today()) {
}

FoodEntry::FoodEntry(
    int entryId,
    int foodId,
    double quantityGrams,
    const Date& date
)
    : entryId(entryId),
    foodId(foodId),
    quantityGrams(quantityGrams),
    date(date) {
}

int FoodEntry::getEntryId() const {
    return entryId;
}

int FoodEntry::getFoodId() const {
    return foodId;
}

double FoodEntry::getQuantityGrams() const {
    return quantityGrams;
}

Date FoodEntry::getDate() const {
    return date;
}

void FoodEntry::setEntryId(int entryId) {
    this->entryId = entryId;
}

void FoodEntry::setFoodId(int foodId) {
    this->foodId = foodId;
}

void FoodEntry::setQuantityGrams(double quantityGrams) {
    this->quantityGrams = quantityGrams;
}

void FoodEntry::setDate(const Date& date) {
    this->date = date;
}

std::string FoodEntry::toFileString() const {
    std::ostringstream out;

    out << entryId << ";"
        << foodId << ";"
        << quantityGrams << ";"
        << date.toString();

    return out.str();
}

FoodEntry FoodEntry::fromFileString(const std::string& line) {
    std::istringstream in(line);

    std::string entryIdStr;
    std::string foodIdStr;
    std::string quantityStr;
    std::string dateStr;

    std::getline(in, entryIdStr, ';');
    std::getline(in, foodIdStr, ';');
    std::getline(in, quantityStr, ';');
    std::getline(in, dateStr, ';');

    return FoodEntry(
        std::stoi(entryIdStr),
        std::stoi(foodIdStr),
        std::stod(quantityStr),
        Date::fromString(dateStr)
    );
}