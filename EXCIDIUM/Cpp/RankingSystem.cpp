#include "RankingSystem.h"



RankTree::~RankTree() {
    destroy(root);
}
RankTree::RankTree() {
    root = nullptr;
    buildDefaultRanks(); // builds the rank tree automatically
}
void RankTree :: buildDefaultRanks() {
    insert("E", 0);
    insert("D", 40);
    insert("C", 90);
    insert("B", 150);
    insert("A", 200);
    insert("S", 250);
    insert("Monarch", 300);
}

// Add new rank into tree
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

// Find the highest possible rank for given total stats
std::string RankTree::evaluate(int total) const {
    return evaluate(root, total);
}

std::string RankTree::evaluate(RankNode* node, int total) const {
    if (!node) return "Unranked";

    if (total < node->minThreshold) {
        return evaluate(node->left, total);
    } else {
        // Might still be a better fit in the right subtree
        std::string rightRank = evaluate(node->right, total);
        return (rightRank != "Unranked") ? rightRank : node->rank;
    }
}


// Free memory
void RankTree::destroy(RankNode* node) {
    if (!node) return;
    destroy(node->left);
    destroy(node->right);
    delete node;
}
