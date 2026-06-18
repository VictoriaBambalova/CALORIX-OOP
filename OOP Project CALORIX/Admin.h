#pragma once

#include "User.h"

class Admin : public User {
public:
    Admin();
    Admin(
        int userId,
        const std::string& username,
        const std::string& password,
        const UserProfile& profile
    );

    UserRole getRole() const override;
    void printHelp() const override;
};