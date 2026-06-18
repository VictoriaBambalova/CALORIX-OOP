#pragma once

#include <string>

class Food {
private:
    int foodId;
    std::string name;
    double caloriesPer100g;
    double proteinPer100g;
    double carbsPer100g;
    double fatPer100g;

public:
    Food();
    Food(
        int foodId,
        const std::string& name,
        double caloriesPer100g,
        double proteinPer100g,
        double carbsPer100g,
        double fatPer100g
    );

    int getFoodId() const;
    const std::string& getName() const;
    double getCaloriesPer100g() const;
    double getProteinPer100g() const;
    double getCarbsPer100g() const;
    double getFatPer100g() const;

    void setFoodId(int foodId);
    void setName(const std::string& name);
    void setCaloriesPer100g(double caloriesPer100g);
    void setProteinPer100g(double proteinPer100g);
    void setCarbsPer100g(double carbsPer100g);
    void setFatPer100g(double fatPer100g);

    double calculateCalories(double quantityGrams) const;
    double calculateProtein(double quantityGrams) const;
    double calculateCarbs(double quantityGrams) const;
    double calculateFat(double quantityGrams) const;

    std::string toFileString() const;
    static Food fromFileString(const std::string& line);

    void print() const;
};