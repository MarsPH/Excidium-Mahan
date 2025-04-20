#pragma once
#include "Cpp/Quest.h"
#include <chrono>

//Revision History      Mahan Poor Hamidian     Created Quest.h
// Timed quest will be available for a short period for the user to do.
class TimedQuest :
    public Quest
{
    int timeLimitSeconds{};
    std::chrono::steady_clock::time_point startTime;

public:
    TimedQuest(std::vector<std::string>, std::string stat, float chance, int reward, int timeLimit);
    void display(int index = -1) const override;
    int getTimeLimit() const;
    void tick(); // this will reduce time by 1 second

    static TimedQuest generateRandom();

    void start();
    int getTimeRemaining() const;
    bool isExpired() const;
};

