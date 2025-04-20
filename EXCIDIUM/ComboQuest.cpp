#include "ComboQuest.h"
// ComboQuest.cpp
#include "ComboQuest.h"

ComboQuest::ComboQuest(std::vector<std::string> exercises, std::string stat, float chance, int reward)
    : Quest(exercises, stat, chance, reward), next(nullptr) {
}

void ComboQuest::setNext(const std::shared_ptr<ComboQuest>& nextQuest) {
    next = nextQuest;
}

std::shared_ptr<ComboQuest> ComboQuest::getNext() const {
    return next;
}