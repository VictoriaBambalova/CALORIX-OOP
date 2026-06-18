#pragma once

#include <string>

#include "Date.h"

class FoodEntry {
private:
    int entryId;
    int foodId;
    double quantityGrams;
    Date date;

public:
    FoodEntry();
    FoodEntry(
        int entryId,
        int foodId,
        double quantityGrams,
        const Date& date
    );

    int getEntryId() const;
    int getFoodId() const;
    double getQuantityGrams() const;
    Date getDate() const;

    void setEntryId(int entryId);
    void setFoodId(int foodId);
    void setQuantityGrams(double quantityGrams);
    void setDate(const Date& date);

    std::string toFileString() const;
    static FoodEntry fromFileString(const std::string& line);
};