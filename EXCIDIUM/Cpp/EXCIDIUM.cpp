#include <iostream>             // basic input/output
#include <algorithm>           // for std::min and std::max
#include <chrono>              // for timing delays
#include <thread>              // for sleep/delay between lines
#include "Player.h"            // our custom Player class
#include "RankingSystem.h"


// Mahan this just makes it look cool when the system starts
void systemBootSequence() {
    using namespace std::chrono_literals;

    std::cout << "\nBooting the System...\n";
    std::this_thread::sleep_for(2s);  // wait 2 seconds for drama

    std::cout << "\nSystem Initializing\n";
    for (int i = 3; i > 0; --i) {
        std::cout << i << "...\n";
        std::this_thread::sleep_for(700ms);  // countdown timer
    }

    std::cout << "Reinitializing";
    for (int i = 0; i < 3; ++i) {
        std::cout << ".";
        std::this_thread::sleep_for(500ms);  // dot loading effect
    }

    std::cout << "\n\n";
    std::cout << "\nPlayer Detected...\n";
    std::this_thread::sleep_for(1s);
    std::cout << "Connecting to Player\n";
    std::this_thread::sleep_for(500ms);
}


// bro these functions convert real-life numbers to in-game stats (0–100 scale)

// 150 push-ups = 100 strength
int convertPushupsToStrength(int pushups) {
    int value = (pushups * 100) / 150;
    return std::min(value, 100);  // just making sure it doesn’t go over 100
}

// 15 min plank = 100 endurance
int convertPlankToEndurance(int seconds) {
    int value = (seconds * 100) / 900;
    return std::min(value, 100);
}

// 12 min = 100 stamina, 47 min = 0 stamina (slower = worse)
int convertRunToStamina(float minutes) {
    int value = 100 - ((minutes - 12.0f) * 100 / 35.0f);
    return std::max(std::min(value, 100), 0);  // clamp between 0 and 100
}


int main() {
    // just a dramatic intro screen
    systemBootSequence();  

    // this part is where we take the player's basic info
    std::string name;
    int age;
    double weight;
    RankTree rankTree;


    std::cout << "Enter your name, Player: ";
    std::getline(std::cin, name);

    std::cout << "Enter Age: ";
    std::cin >> age;

    std::cout << "Enter Weight: ";
    std::cin >> weight;

    // we pass the name, age, and weight into our Player object
    Player player(name, age, weight);

    // ====== ASSESSMENT TEST SECTION ======
    // Mahan this is where the user shows their grind IRL
    int pushups, seconds;
    float minutes;

    int strength, stamina, endurance;

    std::cout << "\nAssessment Test Initiated...\n";

    std::cout << "Enter your push-up count (Strength): ";
    std::cin >> pushups;

    std::cout << "Enter your 5km run time in minutes (Stamina): ";
    std::cin >> minutes;

    std::cout << "How long can you Plank (in seconds)? (Endurance): ";
    std::cin >> seconds;

    // Convert raw inputs to game stats
    strength  = convertPushupsToStrength(pushups);
    stamina   = convertRunToStamina(minutes);
    endurance = convertPlankToEndurance(seconds);

    // apply those stats to our player
    player.setStats(strength, stamina, endurance);

    // MAIN MENU LOOP (after assessment is done)
    // Mahan this is the actual System UI the player interacts with
    int choice;
    while (true) {
        std::cout << "\n===== SYSTEM MENU =====\n";
        std::cout << "1. Show Stats\n";
        std::cout << "2. Generate Quests\n";
        std::cout << "3. Complete Quest\n";
        std::cout << "4. Evaluate Rank\n";
        std::cout << "5. Save Progress\n";
        std::cout << "6. Load Progress\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                player.showStats();  // show current stats to user
                break;

            case 2:
                // player.generateQuests();  // coming soon
                break;

            case 3:
                // player.completeQuest();   // WIP
                break;

            case 4:
                player.evaluateRank(rankTree);
                break;
            
            case 5:
                // player.saveToFile("data.txt"); // when save/load is added
                break;

            case 6:
                // player.loadFromFile("data.txt");
                break;

            case 0:
                std::cout << "System Offline.\n";  // exit the program
                return 0;

            default:
                std::cout << "Invalid input, Hunter.\n";  // if Mahan types wrong number
        }
    }

    return 0;
}
