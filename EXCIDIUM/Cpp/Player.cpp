#include "Player.h"
#include "RankingSystem.h"
#include <iostream>
#include <fstream> 
// i was bored and getting creative with comments
// this class is literally the player — all stats, info, and identity live here
Player::Player() {
    name = "Unknown"; // mysterious gym rat
    age = 0;
    weight = 0;
    rank = "Unranked"; // everyone's gotta start somewhere
}

// actual constructor with data injection
Player::Player(std::string name, int age, double weight) {
    this->name = name;
    this->age = age;
    this->weight = weight;
    rank = "Unranked"; // still humble beginnings
}

// gives your rank some sauce with a title
std::string getRankTitle(const std::string& rank) {
    if (rank == "E") return "Unawakened"; // probably can't do a push-up
    if (rank == "D") return "Street Fighter"; // scraps at the local park
    if (rank == "C") return "Contender"; // okay okay,
    if (rank == "B") return "Elite"; // you're lifting for real now
    if (rank == "A") return "Gravity Defier"; // getting insane
    if (rank == "S") return "Calisthenic Phantom"; // no one sees you — they just see the blur
    if (rank == "Monarch") return "Monarch of Calisthenics"; // final boss, maxed out
    return "Unranked"; // backup case
}

// getter gang — nothing fancy
std::string Player::getName() const { return name; }
int Player::getAge() const { return age; }
double Player::getWeight() const { return weight; }
std::string Player::getRank() const { return rank; }
Stats Player::getStats() const { return stats; }

// set stats manually (used after assessment)
void Player::setStats(int strength, int stamina, int endurance) {
    stats.strength = strength;
    stats.stamina = stamina;
    stats.endurance = endurance;
}

// rank override if needed
void Player::setRank(std::string newRank) {
    rank = newRank;
}

// this just prints everything — use when flexing to friends
void Player::showStats() const {
    std::cout << "\n===== PLAYER STATS =====\n";
    std::cout << "Name: " << name << "\n";
    std::cout << "Age: " << age << "\n";
    std::cout << "Weight: " << weight << " kg\n";
    std::cout << "Rank: " << rank << "\n";
    std::cout << "Title: " << title << "\n";
    std::cout << "==========================\n";
    std::cout << "Strength: " << stats.strength << "\n";
    std::cout << "Stamina: " << stats.stamina << "\n";
    std::cout << "Endurance: " << stats.endurance << "\n";
}

// use this after stat updates — rechecks the rank
void Player::evaluateRank(const RankTree& tree) {
    int totalStats = stats.strength + stats.stamina + stats.endurance;
    rank = tree.evaluate(totalStats); // figure out where we stand
    title = getRankTitle(rank);       // give us a cooler label
}

// stat upgrades — capped at 100 cause we ain't breaking physics (yet)
void Player::updateStats(std::string statType, int amount) {
    if (statType == "strength") {
        stats.strength = std::min(stats.strength + amount, 100);
    } else if (statType == "endurance") {
        stats.endurance = std::min(stats.endurance + amount, 100);
    } else if (statType == "stamina") {
        stats.stamina = std::min(stats.stamina + amount, 100);
    }
}

// saves your grind to disk — DO NOT LOSE THIS
void Player::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file) {
        std::cout << ">> Error: Couldn't open file for saving.\n";
        return;
    }

    file << name << "\n"
         << age << "\n"
         << weight << "\n"
         << stats.strength << "\n"
         << stats.stamina << "\n"
         << stats.endurance << "\n"
         << rank << "\n"; // yeah, we'll add title later if needed

    file.close();
    std::cout << ">> Progress saved to " << filename << "\n";
}

// load the grind back in
void Player::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << ">> Error: No Files Found\n";
        return;
    }

    std::getline(file, name);
    file >> age >> weight;
    file >> stats.strength >> stats.stamina >> stats.endurance;
    file.ignore(); // skip newline mess after last int
    std::getline(file, rank);

    file.close();
    std::cout << ">> Progress loaded from " << filename << "\n";
}
