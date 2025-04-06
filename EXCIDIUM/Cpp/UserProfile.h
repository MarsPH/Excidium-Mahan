#ifndef USERPROFILE_H      // Include guard - prevents multiple inclusion
#define USERPROFILE_H      

#include <string>          // Needed for string variables
#include <vector>          // If we need to store multiple objects

class UserProfile {        // Class declaration
private:
    std::string name;      // Private member variables
    float weight;
    float height;
    std::string fitnessLevel;
    int xp;
    std::string rank;

public:
    // Constructor
    UserProfile(std::string name, float weight, float height, std::string fitnessLevel);

    // Member functions (only declared, not defined here)
    void updateRank();
    void displayProfile() const;
};

#endif  // Ends the include guard
