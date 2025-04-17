#include "Quest.h"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>

Quest::Quest() {
    completed = false;
    statType = "unknown";
    successChance = 0.5f;
    rewardAmount = 1;
}

Quest::Quest(std::vector<std::string> exercises, std::string statType, float chance, int reward)
    : exercises(exercises), statType(statType), successChance(chance), rewardAmount(reward), completed(false) {}

void Quest::display(int index) const {
    if (index >= 0)
        std::cout << "[" << index << "] ";

    std::cout << (completed ? "[COMPLETED] " : "[ ] ");
    std::cout << "Stat: " << statType << " | Reward: +" << rewardAmount << " | Success Chance: " << int(successChance * 100) << "%\n";
    for (const std::string& ex : exercises) {
        std::cout << "  - " << ex << "\n";
    }
}

void Quest::markCompleted() {
    completed = true;
}

bool Quest::isCompleted() const {
    return completed;
}

std::string Quest::getStatType() const {
    return statType;
}

int Quest::getRewardAmount() const {
    return rewardAmount;
}

float Quest::getSuccessChance() const {
    return successChance;
}

// 🔥 THE QUEST GENERATOR 🔥
Quest Quest::generateRandom() {
    srand(time(0));

    std::vector<std::string> statTypes = { "strength", "endurance", "stamina" };
    std::string selectedStat = statTypes[rand() % statTypes.size()];

    std::vector<std::string> strengthPool = {
        "Do 20 push-ups", "15 pull-ups", "20 tricep dips",
        "Shoulder press (15 reps)", "10 push-up holds", "Diamond push-ups"
    };

    std::vector<std::string> endurancePool = {
        "Plank 2 minutes", "Wall sit 1 min", "Squat hold 90 seconds",
        "Plank + shoulder taps", "Step-ups 20 reps", "Slow air squats x30"
    };

    std::vector<std::string> staminaPool = {
        "Run 10 minutes", "Sprint 400m x3", "Jump rope 3 minutes",
        "Jog in place 5 mins", "Jumping jacks x50", "Mountain climbers x40"
    };

    std::vector<std::string> pickedExercises;

    std::vector<std::string>* source;
    if (selectedStat == "strength") source = &strengthPool;
    else if (selectedStat == "endurance") source = &endurancePool;
    else source = &staminaPool;

    while (pickedExercises.size() < 5) {
        std::string candidate = (*source)[rand() % source->size()];
        if (std::find(pickedExercises.begin(), pickedExercises.end(), candidate) == pickedExercises.end()) {
            pickedExercises.push_back(candidate);
        }
    }

    float chance = 0.4f + static_cast<float>(rand() % 41) / 100.0f; // 0.4 to 0.8
    int reward = 1 + rand() % 2; // 1 or 2

    return Quest(pickedExercises, selectedStat, chance, reward);
}

std::string Quest::serialize() const {
    std::ostringstream oss;
    oss << statType << "|" << successChance << "|" << rewardAmount << "|" << completed;
    for (const auto& ex : exercises) {
        oss << "|" << ex;
    }
    return oss.str();
}

Quest Quest::deserialize(const std::string& data) {
    std::istringstream iss(data);
    std::string token;
    std::getline(iss, token, '|');
    std::string stat = token;

    std::getline(iss, token, '|');
    float chance = std::stof(token);

    std::getline(iss, token, '|');
    int reward = std::stoi(token);

    std::getline(iss, token, '|');
    bool done = (token == "1");

    std::vector<std::string> exList;
    while (std::getline(iss, token, '|')) {
        exList.push_back(token);
    }

    Quest q(exList, stat, chance, reward);
    if (done) q.markCompleted();
    return q;
}
