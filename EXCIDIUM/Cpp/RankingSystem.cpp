#include "RankingSystem.h"

// clean-up time
RankTree::~RankTree() {
    destroy(root);
}

// fire it up, drop the ranks right away
RankTree::RankTree() {
    root = nullptr;
    buildDefaultRanks();
}

// setup default rank thresholds — tweak if we ever rebalance
void RankTree::buildDefaultRanks() {
    insert("E", 0);
    insert("D", 40);
    insert("C", 90);
    insert("B", 150);
    insert("A", 200);
    insert("S", 250);
    insert("Monarch", 300);
}

// public insert wrapper
void RankTree::insert(std::string rank, int threshold) {
    insert(root, rank, threshold);
}

void RankTree::insert(RankNode*& node, std::string rank, int threshold) {
    if (!node) {
        node = new RankNode(rank, threshold);
        return;
    }

    if (threshold < node->minThreshold) {
        insert(node->left, rank, threshold);
    } else {
        insert(node->right, rank, threshold);
    }
}

// stat check — get best possible rank
std::string RankTree::evaluate(int total) const {
    return evaluate(root, total);
}

// find the rank node that fits the stat value
std::string RankTree::evaluate(RankNode* node, int total) const {
    if (!node) return "Unranked";

    if (total < node->minThreshold) {
        return evaluate(node->left, total);
    } else {
        std::string rightRank = evaluate(node->right, total);
        return (rightRank != "Unranked") ? rightRank : node->rank;
    }
}

// recursive nuke — free the whole tree
void RankTree::destroy(RankNode* node) {
    if (!node) return;
    destroy(node->left);
    destroy(node->right);
    delete node;
}
// so this is the header file , completed
