#ifndef RANKINGSYSTEM_H
#define RANKINGSYSTEM_H

#include <string>


// Yo broo, this is the node for each rank in the BST
// Each rank like "E", "B", "S", "Monarch" has a threshold
// If player's total stats >= threshold → they unlock that rank
// ===============================
struct RankNode {
    std::string rank;      // Name of the rank
    int minThreshold;      // Min stat total needed to reach this rank
    RankNode* left;        // BST left child
    RankNode* right;       // BST right child

    // Constructor for making a node
    RankNode(std::string r, int threshold)
        : rank(r), minThreshold(threshold), left(nullptr), right(nullptr) {}
};


// This tree holds all rank thresholds and helps evaluate player rank

class RankTree {
private:
    RankNode* root;  // Starting point of the BST

    // Bro these are private helpers for inserting, evaluating, and deleting nodes
    void insert(RankNode*& node, std::string rank, int threshold);
    std::string evaluate(RankNode* node, int total) const;
    void destroy(RankNode* node); // Cleanup memory when tree is deleted

public:
    // Constructor auto-builds default ranks
    RankTree();

    // Destructor clears all nodes from memory
    ~RankTree();

    // Add a new rank manually
    void insert(std::string rank, int threshold);

    // This one should be called in constructor to auto-load all default ranks
    void buildDefaultRanks();

    // This is the main function to call when we want to evaluate someone's rank
    std::string evaluate(int total) const;
};

#endif
