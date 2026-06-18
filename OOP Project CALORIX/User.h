#pragma once

#include <string>

#include "UserProfile.h"
#include "Enums.h"

class User {
protected:
    int userId;
    std::string username;
    std::string password;
    UserProfile profile;

public:
    User();
    User(
        int userId,
        const std::string& username,
        const std::string& password,
        const UserProfile& profile
    );

    virtual ~User() = default;

    int getUserId() const;
    const std::string& getUsername() const;
    const std::string& getPassword() const;
    const UserProfile& getProfile() const;
    UserProfile& getProfile();

    void setUserId(int userId);
    void setUsername(const std::string& username);
    void setPassword(const std::string& password);
    void setProfile(const UserProfile& profile);

    bool checkPassword(const std::string& password) const;

    virtual UserRole getRole() const = 0;
    virtual void printHelp() const = 0;

    virtual std::string toFileString() const;
};