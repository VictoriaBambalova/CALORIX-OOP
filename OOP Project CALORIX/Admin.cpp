#include "Admin.h"

#include <iostream>

Admin::Admin()
    : User() {
}

Admin::Admin(
    int userId,
    const std::string& username,
    const std::string& password,
    const UserProfile& profile
)
    : User(userId, username, password, profile) {
}

UserRole Admin::getRole() const {
    return UserRole::ADMIN;
}

void Admin::printHelp() const {
    std::cout << "Available admin commands:\n";
    std::cout << "logout\n";
    std::cout << "help\n";
    std::cout << "list-foods\n";
    std::cout << "list-exercises\n";
    std::cout << "block-user <username>\n";
    std::cout << "add-food <name> <calories_per_100g> <protein_per_100g> <carbs_per_100g> <fat_per_100g>\n";
    std::cout << "add-exercise <name> <calories_burned_per_hour> <muscle-group> <default_duration_minutes>\n";
    std::cout << "update-food <food-name> <new-calories>\n";
    std::cout << "end\n";
}