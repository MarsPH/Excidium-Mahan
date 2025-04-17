#include "Player.h"
#include "RankingSystem.h"
#include <iostream>

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
  std::cout << "Total stats: " << totalStats;
    rank = tree.evaluate(totalStats);
    std::cout << "\n>> Rank Evaluation Complete! You are ranked: " << rank << "\n";
}

