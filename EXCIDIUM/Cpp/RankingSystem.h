#ifndef RANKINGSYSTEM_H
#define RANKINGSYSTEM_H
#include <string>

// Node for each rank in the BST
struct RankNode {
    std::string rank;
    int minThreshold;  // minimum total stat required
    RankNode* left;
    RankNode* right;

    RankNode(std::string r, int threshold)
        : rank(r), minThreshold(threshold), left(nullptr), right(nullptr) {}
};

// The Binary Search Tree that holds all ranks
class RankTree {
private:
    RankNode* root;

    void insert(RankNode*& node, std::string rank, int threshold);
    std::string evaluate(RankNode* node, int total) const;
    void destroy(RankNode* node); // for cleanup

public:
    RankTree();
    ~RankTree();

    void insert(std::string rank, int threshold);
    void buildDefaultRanks();
    std::string evaluate(int total) const;
};

#endif
