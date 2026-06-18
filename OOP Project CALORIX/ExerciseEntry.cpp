#include "ExerciseEntry.h"

#include <sstream>

ExerciseEntry::ExerciseEntry()
    : entryId(0),
    exerciseId(0),
    durationMinutes(0),
    date(Date::today()) {
}

ExerciseEntry::ExerciseEntry(
    int entryId,
    int exerciseId,
    int durationMinutes,
    const Date& date
)
    : entryId(entryId),
    exerciseId(exerciseId),
    durationMinutes(durationMinutes),
    date(date) {
}

int ExerciseEntry::getEntryId() const {
    return entryId;
}

int ExerciseEntry::getExerciseId() const {
    return exerciseId;
}

int ExerciseEntry::getDurationMinutes() const {
    return durationMinutes;
}

Date ExerciseEntry::getDate() const {
    return date;
}

void ExerciseEntry::setEntryId(int entryId) {
    this->entryId = entryId;
}

void ExerciseEntry::setExerciseId(int exerciseId) {
    this->exerciseId = exerciseId;
}

void ExerciseEntry::setDurationMinutes(int durationMinutes) {
    this->durationMinutes = durationMinutes;
}

void ExerciseEntry::setDate(const Date& date) {
    this->date = date;
}

std::string ExerciseEntry::toFileString() const {
    std::ostringstream out;

    out << entryId << ";"
        << exerciseId << ";"
        << durationMinutes << ";"
        << date.toString();

    return out.str();
}

ExerciseEntry ExerciseEntry::fromFileString(const std::string& line) {
    std::istringstream in(line);

    std::string entryIdStr;
    std::string exerciseIdStr;
    std::string durationStr;
    std::string dateStr;

    std::getline(in, entryIdStr, ';');
    std::getline(in, exerciseIdStr, ';');
    std::getline(in, durationStr, ';');
    std::getline(in, dateStr, ';');

    return ExerciseEntry(
        std::stoi(entryIdStr),
        std::stoi(exerciseIdStr),
        std::stoi(durationStr),
        Date::fromString(dateStr)
    );
}