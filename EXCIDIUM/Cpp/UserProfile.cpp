#include <string>
#include <vector>
class UserProfile {
    private:
        std::string name;
        int age;
        double weight, height;
        std::string gender;
        std::string rank; // E to Monarch
        std::vector<std::string> workoutHistory;
        int assessmentScore;
    
    public:
        void performAssessment();
        void updateRank();
        void logWorkout(std::string workout);
        void displayStats();
    };
    