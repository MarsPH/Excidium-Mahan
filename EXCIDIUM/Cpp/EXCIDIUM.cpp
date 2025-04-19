#include <iostream>             // basic input/output
#include <algorithm>           // for std::min and std::max
#include <chrono>              // for timing delays
#include <thread>              // for sleep/delay between lines
#include "Player.h"            // our custom Player class
#include "RankingSystem.h"
#include "Quest.h"


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
    std::vector<Quest> dailyQuests; // Broo, this will hold today's system quests
    bool questsGenerated = false;



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
    player.evaluateRank(rankTree);
    player.saveToFile("save.txt");

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
          
    if (!questsGenerated) {
        dailyQuests.clear(); // wipe any leftovers
        int numQuests = 3;
        for (int i = 0; i < numQuests; ++i) {
            Quest q = Quest::generateRandom();
            dailyQuests.push_back(q);
        }
        std::cout << "\n>> Daily Quests Generated:\n";
        for (int i = 0; i < dailyQuests.size(); ++i) {
            dailyQuests[i].display(i + 1);
        }
        questsGenerated = true;
    } else {
        std::cout << "\n>> You already have today's quests, soldier.\n";
    }
  

            break;
            case 3:{
            if (!questsGenerated || dailyQuests.empty()) {
                std::cout << "\n>> No quests to complete. Generate them first.\n";
                break;
            }
        
            std::cout << "\n>> Your Quests:\n";
            for (int i = 0; i < dailyQuests.size(); ++i) {
                dailyQuests[i].display(i + 1);
            }
        
            std::cout << "Choose a quest to complete (1-" << dailyQuests.size() << "): ";
            int qChoice;
            std::cin >> qChoice;
        
            if (qChoice < 1 || qChoice > dailyQuests.size()) {
                std::cout << ">> Invalid quest number.\n";
                break;
            }
        
            Quest& q = dailyQuests[qChoice - 1];
        
            if (q.isCompleted()) {
                std::cout << ">> You've already done this one, bro.\n";
                break;
            }
        
            q.markCompleted();
            float roll = static_cast<float>(rand()) / RAND_MAX;
        
            if (roll < q.getSuccessChance()) {
                std::cout << ">> Success! " << q.getStatType() << " increased by +" << q.getRewardAmount() << "!\n";
                 player.updateStats(q.getStatType(),q.getRewardAmount());
            } else {
                std::cout << ">> You tried. The System shows no mercy today.\n";
            }
        
            break;
        
        }
            case 4:
                player.evaluateRank(rankTree);
              //  std::cout <<"\n Stats : \n" << player.getStats() << "\n";
                std::cout << "\n>> Rank Evaluation Complete! You are ranked: " << player.getRank() << "\n";
                break;
            
            case 5:
         
            player.saveToFile("save.txt");
            break;
        

            case 6:
                player.loadFromFile("save.txt");
                break;

            case 0:
                std::cout << "System Offline.\n";  // exit the program
                return 0;

            default:
                std::cout << "Invalid input, Hunter.\n";  // if user types wrong number
        }
    }

    return 0;
}
