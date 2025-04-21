#include "Quest.h"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>

// default constructor — safe fallback values
Quest::Quest() {
    completed = false;
    statType = "unknown";
    successChance = 0.5f;
    rewardAmount = 1;
}

// main constructor for creating a real quest
Quest::Quest(std::vector<std::string> exercises, std::string statType, float chance, int reward)
    : exercises(exercises), statType(statType), successChance(chance), rewardAmount(reward), completed(false) {}

// shows quest info to player — index just makes it look cleaner in menu
void Quest::display(int index) const {
    if (index >= 0)
        std::cout << "[" << index << "] ";

    std::cout << (completed ? "[COMPLETED] " : "[ ] ");
    std::cout << "Stat: " << statType << " | Reward: +" << rewardAmount << " | Success Chance: " << int(successChance * 100) << "%\n";

    for (const std::string& ex : exercises) {
        std::cout << "  - " << ex << "\n";
    }
}

// flips quest to "done" so they can't farm it
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

// randomly generate a new quest — this is where the juice is
Quest Quest::generateRandom() {
    srand(time(0)); // yea, it's not cryptographic, but it's fine for now

    // pick a stat this quest will target
    std::vector<std::string> statTypes = { "strength", "endurance", "stamina" };
    std::string selectedStat = statTypes[rand() % statTypes.size()];

    // pools of exercises — can expand later
    std::vector<std::string> strengthPool = {
        "Do 20 push-ups", "15 pull-ups", "20 tricep dips",
        "Shoulder press (15 reps)", "10 push-up holds", "Diamond 5 push-ups"
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

    // pick the pool based on stat
    std::vector<std::string>* source;
    if (selectedStat == "strength") source = &strengthPool;
    else if (selectedStat == "endurance") source = &endurancePool;
    else source = &staminaPool;

    // pick 5 unique exercises from the selected pool
    while (pickedExercises.size() < 5) {
        std::string candidate = (*source)[rand() % source->size()];
        if (std::find(pickedExercises.begin(), pickedExercises.end(), candidate) == pickedExercises.end()) {
            pickedExercises.push_back(candidate);
        }
    }

    // roll for quest chance and reward
    float chance = 0.4f + static_cast<float>(rand() % 41) / 100.0f; // between 0.4 and 0.8
    int reward = 1 + rand() % 2; // 1 or 2 points

    return Quest(pickedExercises, selectedStat, chance, reward);
}

// turns quest data into a string for saving
std::string Quest::serialize() const {
    std::ostringstream oss;
    oss << statType << "|" << successChance << "|" << rewardAmount << "|" << completed;
    for (const auto& ex : exercises) {
        oss << "|" << ex;
    }
    return oss.str();
}

// turns saved string back into a quest
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
