#include "Player.h"
#include "RankingSystem.h"
#include <iostream>
#include <fstream> 

Player::Player() {
    name = "Unknown";
    age = 0;
    weight=0;
    rank = "Unranked";
}

Player::Player(std::string name,int age, double weight){
    this->name = name;
    rank = "Unranked";
    this ->age = age;
    this->weight = weight;
}

std::string Player::getName() const {
    return name;
}

int Player::getAge() const {
    return age;
    }
double Player::getWeight() const {
    return weight;
}

std::string Player::getRank() const {
    return rank;
}

Stats Player::getStats() const {
    return stats;
}

void Player::setStats(int strength, int stamina, int endurance) {
    stats.strength = strength;
    stats.stamina = stamina;
    stats.endurance = endurance;
}

void Player::setRank(std::string newRank) {
    rank = newRank;
}

void Player::showStats() const {
    std::cout << "\n===== PLAYER STATS =====\n";
    std::cout << "Name: " << name << "\n";
    std::cout << "Age: " << age << "\n";
    std::cout << "Weight: " << weight <<" kg"<< "\n";
    std::cout << "Rank: " << rank << "\n";
    std::cout << "Strength: " << stats.strength << "\n";
    std::cout << "Stamina: " << stats.stamina << "\n";
    std::cout << "Endurance: " << stats.endurance << "\n";
}

void Player::evaluateRank(const RankTree& tree) {
    int totalStats = stats.strength + stats.stamina + stats.endurance;
  //std::cout << "Total stats: " << totalStats;
    rank = tree.evaluate(totalStats);
   
}

void Player::updateStats(std::string statType, int amount) {
     if (statType == "strength") 
     {
        stats.strength = std::min(stats.strength + amount, 100);
     }
else if (statType == "endurance") {stats.endurance = std::min(stats.endurance + amount, 100);}

else if (statType == "stamina") {stats.stamina = std::min(stats.stamina + amount, 100);}}
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
         << rank << "\n";

    file.close();
    std::cout << ">> Progress saved to " << filename << "\n";
}

void Player::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << ">> Error: Couldn't open file for loading.\n";
        return;
    }

    std::getline(file, name);
    file >> age >> weight;
    file >> stats.strength >> stats.stamina >> stats.endurance;
    file.ignore(); // skip newline after last int
    std::getline(file, rank);

    file.close();
    std::cout << ">> Progress loaded from " << filename << "\n";
}



