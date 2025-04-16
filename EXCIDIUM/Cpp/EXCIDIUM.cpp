#include <iostream>
#include "Player.h"
#include <algorithm>
#include <chrono>
#include <thread>



void systemBootSequence() {
    using namespace std::chrono_literals; // for 1s, 500ms etc.

    std::cout << "\nBooting the System...\n";
    std::this_thread::sleep_for(2s);
    std::cout << "\nSystem Initializing\n";
    for (int i = 3; i > 0; --i) {
        std::cout << i << "...\n";
        std::this_thread::sleep_for(700ms);
    }

    std::cout << "Reinitializing";
    for (int i = 0; i < 3; ++i) {
        std::cout << ".";
        std::this_thread::sleep_for(500ms);
    }
    
    std::cout << "\n\n";
    std::cout << "\nPlayer Detected...\n";
    std::this_thread::sleep_for(1s);
    std::cout << "Connecting to Player"<<"\n";
    std::this_thread::sleep_for(500ms);
}


int convertPushupsToStrength(int pushups) 
{
    int value = (pushups * 100) / 150;
    return std::min(value, 100);
}

int convertPlankToEndurance(int seconds) {
    int value = (seconds * 100) / 900;
    return std::min(value, 100);
}


int convertRunToStamina(float minutes) {
    int value = 100 - ((minutes - 12.0f) * 100 / 35.0f);    // 47min - 12min = 35min range
    return std::max(std::min(value, 100), 0);
}


int main() {
   
        systemBootSequence(); // <- dramatic entrance starts here
       
    std::string name;
    int age;
    double weight;
    std::cout << "Enter your name, Player: ";
    std::getline(std::cin, name);
    std::cout << "Enter Age: ";
    std::cin >> age;
    std::cout << "Enter Weight: ";
    std::cin >> weight;

    Player player(name,age,weight);

    // Simulate an assessment test for now
    int strength, stamina, endurance , pushups,seconds,minutes;
    std::cout << "\nAssessment Test Initiated...\n";
    std::cout << "Enter your push-up count (Strength): ";
    std::cin >> pushups;
    std::cout << "Enter your 5km run time in minutes (Stamina): ";
    std::cin >> minutes;
    std::cout << "How long can you Plank(in seconds)? (Endurance): ";
    std::cin >> seconds;
    strength = convertPushupsToStrength(pushups);
    stamina = convertRunToStamina(minutes);
    endurance = convertPlankToEndurance(seconds);
    
    player.setStats(strength,stamina,endurance);

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
            player.showStats();
            break;
        case 2:
            // player.generateQuests(...);
            break;
        case 3:
            // player.completeQuest(...);
            break;
        case 4:
            // player.evaluateRank(...);
            break;
        case 5:
            // player.saveToFile("data.txt");
            break;
        case 6:
            // player.loadFromFile("data.txt");
            break;
        case 0:
            std::cout << "System Offline.\n";
            return 0;
        default:
            std::cout << "Invalid input, Hunter.\n";
    }
}


    return 0;
}

