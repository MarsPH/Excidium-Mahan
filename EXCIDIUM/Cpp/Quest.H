#ifndef QUEST_H
#define QUEST_H

#include <string>
#include <vector>
#include <algorithm>

//Base Quest for quests that we have
class Quest {
protected:// Changed to protected as they are needed in children
    std::vector<std::string> exercises;
    std::string statType;
    bool completed;
    float successChance;
    int rewardAmount;

    static constexpr float minChance = 0.3f;
    static constexpr float maxChance = 0.6f;
    static constexpr int minReward = 2;
    static constexpr int maxReward = 4;

public:
    Quest();
    Quest(std::vector<std::string> exercises, std::string statType, float chance, int reward);
    virtual ~Quest() = default;

    static Quest generateRandom(); // The magic maker

    virtual void display(int index = -1) const; //Made it virtual to override it in children
    void markCompleted();
    bool isCompleted() const;

    std::string getStatType() const;
    int getRewardAmount() const;
    float getSuccessChance() const;

    std::string serialize() const;
    static Quest deserialize(const std::string& data);

    virtual float getMinChance() const { return minChance; }
    virtual float getMaxChance() const { return maxChance; }
    virtual int getMinReward() const { return minReward; }
    virtual int getMaxReward() const { return maxReward; }

};

#endif
