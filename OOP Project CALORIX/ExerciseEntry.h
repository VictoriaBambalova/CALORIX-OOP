#pragma once

#include <string>

#include "Date.h"

class ExerciseEntry {
private:
    int entryId;
    int exerciseId;
    int durationMinutes;
    Date date;

public:
    ExerciseEntry();
    ExerciseEntry(
        int entryId,
        int exerciseId,
        int durationMinutes,
        const Date& date
    );

    int getEntryId() const;
    int getExerciseId() const;
    int getDurationMinutes() const;
    Date getDate() const;

    void setEntryId(int entryId);
    void setExerciseId(int exerciseId);
    void setDurationMinutes(int durationMinutes);
    void setDate(const Date& date);

    std::string toFileString() const;
    static ExerciseEntry fromFileString(const std::string& line);
};