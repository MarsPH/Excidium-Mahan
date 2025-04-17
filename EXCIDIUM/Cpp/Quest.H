#ifndef QUEST_H
#define QUEST_H

#include <string>
#include <vector>
#include <algorithm>

class Quest {
private:
    std::vector<std::string> exercises;
    std::string statType;
    bool completed;
    float successChance;
    int rewardAmount;

public:
    Quest();
    Quest(std::vector<std::string> exercises, std::string statType, float chance, int reward);

    static Quest generateRandom(); // The magic maker

    void display(int index = -1) const;
    void markCompleted();
    bool isCompleted() const;

    std::string getStatType() const;
    int getRewardAmount() const;
    float getSuccessChance() const;

    std::string serialize() const;
    static Quest deserialize(const std::string& data);
};

#endif
