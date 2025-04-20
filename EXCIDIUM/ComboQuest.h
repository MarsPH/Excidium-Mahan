#pragma once
#include "Cpp/Quest.h"
#include <memory>

class ComboQuest :
    public Quest
{
private:
    std::shared_ptr<ComboQuest> next;
public:
	ComboQuest(std::vector<std::string> exercises, std::string stat, float chance, int reward);
    void setNext(const std::shared_ptr<ComboQuest>& nextQuest);
    std::shared_ptr<ComboQuest> getNext() const;
};

