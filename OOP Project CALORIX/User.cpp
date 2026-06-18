#include "User.h"

#include <sstream>

User::User()
    : userId(0),
    username(""),
    password(""),
    profile() {
}

User::User(
    int userId,
    const std::string& username,
    const std::string& password,
    const UserProfile& profile
)
    : userId(userId),
    username(username),
    password(password),
    profile(profile) {
}

int User::getUserId() const {
    return userId;
}

const std::string& User::getUsername() const {
    return username;
}

const std::string& User::getPassword() const {
    return password;
}

const UserProfile& User::getProfile() const {
    return profile;
}

UserProfile& User::getProfile() {
    return profile;
}

void User::setUserId(int userId) {
    this->userId = userId;
}

void User::setUsername(const std::string& username) {
    this->username = username;
}

void User::setPassword(const std::string& password) {
    this->password = password;
}

void User::setProfile(const UserProfile& profile) {
    this->profile = profile;
}

bool User::checkPassword(const std::string& password) const {
    return this->password == password;
}

std::string User::toFileString() const {
    std::ostringstream out;

    out << userId << ";"
        << userRoleToString(getRole()) << ";"
        << username << ";"
        << password << ";"
        << profile.getAge() << ";"
        << profile.getWeight() << ";"
        << profile.getHeight() << ";"
        << genderToString(profile.getGender()) << ";"
        << activityLevelToString(profile.getActivityLevel());

    return out.str();
}