#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "RankingSystem.h"  

struct Stats {
    int strength = 0;
    int stamina = 0;
    int endurance = 0;

    int total() const {
        return strength + stamina + endurance;
    }
};

class RankTree; 

class Player {
private:
    std::string name;
    std::string rank;
    Stats stats;
    int age;
    double weight;
    std::string title;

public:
    // Constructors
    Player();
    Player(std::string name,int age,double weight);

    // Getters
    std::string getName() const;
    int getAge() const;
    double getWeight() const;
    std::string getRank() const;
    Stats getStats() const;
    

    // Setters
    void setStats(int strength, int stamina, int endurance);
    void setRank(std::string newRank);

    // Display
    void showStats() const;
    void evaluateRank(const RankTree& tree);
    //update
    void updateStats(std::string statType , int amount);

    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);

  
};

#endif
