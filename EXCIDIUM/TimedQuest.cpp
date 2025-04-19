#include "TimedQuest.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <thread>
#include <map>


namespace {
    const std::vector<std::string> statTypes = { "strength", "endurance", "stamina" };

    const std::map<std::string, std::vector<std::string>> exercisePools = {
        {"strength", {"Push-up pyramid", "Weighted dips", "One-arm push-up", "Clap push-ups"}},
        {"endurance", {"Wall sit 3 min", "Slow lunges 40 reps", "Squat hold 3 min", "5-minute plank"}},
        {"stamina", {"Sprint 400m x5", "Plank 4 min", "Jump squats 50", "Mountain climbers x100"}}
    };

    const int minTimeLimit{ 60 };
    const int maxTimeLimit{ 180 };

    int getRandomInt(int min, int max)
    {
        return min + rand() % ((max - min) + 1);
    }

    float getRandomFloat(float min, float max)
    {
        return min + static_cast<float>(rand()) / RAND_MAX * (max - min);
    }
}

TimedQuest::TimedQuest(std::vector<std::string> ex, std::string stat, float chance, 
    int reward, int timeLimit) : Quest(ex, stat, chance, reward), timeLimitSeconds(timeLimit){}

void TimedQuest::start() {
    startTime = std::chrono::steady_clock::now();
}

void TimedQuest::tick() {
    // No need to do anything. We calculate remaining time dynamically.
}


int TimedQuest::getTimeRemaining() const {
    using namespace std::chrono;
    auto now = steady_clock::now();
    auto elapsed = duration_cast<seconds>(now - startTime).count();
    int remaining = timeLimitSeconds - static_cast<int>(elapsed);
    return remaining > 0 ? remaining : 0;
}

bool TimedQuest::isExpired() const {
    return getTimeRemaining() <= 0;
}

void TimedQuest::display(int index) const {
    if (index >= 0)
        std::cout << "[" << index << "] ";
    std::cout << (completed ? "[COMPLETED] " : "[ ] ");
    std::cout << "Stat: " << statType << " | Reward: +" << rewardAmount
        << " | Success Chance: " << int(successChance * 100) << "%\n";
    for (const std::string& ex : exercises) {
        std::cout << "  - " << ex << "\n";
    }
    std::cout << "Time Remaining: " << getTimeRemaining() << " seconds\n";
}

TimedQuest TimedQuest::generateRandom() {
    srand(static_cast<unsigned>(time(0)));

    std::string selectedStat = statTypes[rand() % statTypes.size()];
    const auto& pool = exercisePools.at(selectedStat);

    std::vector<std::string> picked;
    while (picked.size() < 3) {
        std::string ex = pool[rand() % pool.size()];
        if (std::find(picked.begin(), picked.end(), ex) == picked.end()) {
            picked.push_back(ex);
        }
    }

    float chance = getRandomFloat(Quest::minChance, Quest::maxChance);
    int reward = getRandomInt(Quest::minReward, Quest::maxReward);
    int timeLimit = getRandomInt(minTimeLimit, maxTimeLimit);

    TimedQuest q(picked, selectedStat, chance, reward, timeLimit);
    q.start();
    return q;
}





