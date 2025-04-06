#include <string>

class Assessment {
    private:
        int pushups, pullups, squats, runTime;
    public:
        Assessment(int p, int pu, int s, int rt);
        int calculateScore();
        std::string determineRank();
    };
    