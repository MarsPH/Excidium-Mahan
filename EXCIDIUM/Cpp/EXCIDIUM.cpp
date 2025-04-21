#include <iostream>             // basic input/output
#include <algorithm>           // for std::min and std::max
#include <chrono>              // for timing delays
#include <thread>              // for sleep/delay between lines
#include "Player.h"            // our custom Player class
#include "RankingSystem.h"
#include "Quest.h"
#include <cstdlib>
#include <fstream>
#include <queue>
#include <conio.h>
#include <memory>
#include "../ComboQuest.h"
#include "../TimedQuest.h"
extern Player player;
using namespace std::chrono_literals;
void typeEffect(const std::string& text, int delayMs = 50) {
	for (char c : text) {
		std::cout << c << std::flush;
		std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
	}
}
void glitchText(const std::string& text, int repeat = 3, int delay = 50) {
	std::string glitchChars = "#$%&@!*^~";
	for (int i = 0; i < repeat; ++i) {
		for (char c : text) {
			if (rand() % 4 == 0) {
				std::cout << glitchChars[rand() % glitchChars.size()];
			}
			else {
				std::cout << c;
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(delay));
		}
		std::cout << "\r"; // overwrite line
		std::this_thread::sleep_for(std::chrono::milliseconds(80));
	}
	std::cout << text << "\n"; // Final clean line
}

void systemBootSequence() {

	system("CLS"); // Clear console at start

	typeEffect("Establishing Neural Link...\n", 40);
	std::this_thread::sleep_for(1s);

	typeEffect("Synchronizing Body Metrics...\n", 40);
	std::this_thread::sleep_for(2s);

	typeEffect("Calibrating Muscle Fibers...\n", 40);
	std::this_thread::sleep_for(1s);

	typeEffect("\n>> SYSTEM CORE BOOTING\n\n", 30);
	std::this_thread::sleep_for(2s);

	for (int i = 3; i > 0; --i) {
		std::cout << "Initializing in: " << i << "...\n";
		std::this_thread::sleep_for(700ms);
	}

	std::cout << "Reinitializing";
	for (int i = 0; i < 3; ++i) {
		std::cout << ".";
		std::this_thread::sleep_for(400ms);
	}

	std::cout << "\n\n";
	typeEffect(">> PLAYER PRESENCE DETECTED...\n", 40);
	std::this_thread::sleep_for(600ms);
	typeEffect(">> Connecting Neural Pathways...\n", 40);
	std::this_thread::sleep_for(600ms);
	typeEffect(">> SYSTEM READY.\n\n", 40);
	std::this_thread::sleep_for(700ms);
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

//needed for the timing of the quests.
std::queue<std::shared_ptr<TimedQuest>> timedQuestQueue;
bool timedQuestsGenerated = false;

void monitorTimedQuests() {
	std::cout << "\n=== ACTIVE TIMED QUESTS ===\n";

	while (!timedQuestQueue.empty()) {
		auto& currentQuest = timedQuestQueue.front();

		while (!currentQuest->isExpired()) {
			system("CLS");
			currentQuest->display(1);

			std::cout << "(Press Q to quit monitoring, A to accept quest)\n";

			std::this_thread::sleep_for(std::chrono::seconds(1));
			currentQuest->tick();

			if (_kbhit()) {
				char c = _getch();
				if (c == 'q' || c == 'Q') {
					std::cout << "\n>> Exiting monitor mode.\n";
					return;
				}
				else if (c == 'a' || c == 'A') {
					std::cout << "\n>> Quest Accepted!\n";
					currentQuest->markCompleted();
					float roll = static_cast<float>(rand()) / RAND_MAX;
					if (roll < currentQuest->getSuccessChance()) {
						std::cout << "\n>> Success! " << currentQuest->getStatType()
							<< " increased by +" << currentQuest->getRewardAmount() << "!\n";
						player.updateStats(currentQuest->getStatType(), currentQuest->getRewardAmount());
					}
					else {
						std::cout << "\n>> You tried. No reward this time.\n";
					}
					timedQuestQueue.pop();
					auto newQuest = std::make_shared<TimedQuest>(TimedQuest::generateRandom());
					timedQuestQueue.push(newQuest);
					std::this_thread::sleep_for(std::chrono::seconds(2));
					break;
				}
			}
		}

		if (currentQuest->isExpired()) {
			std::cout << "\n>> This quest has expired and will be removed.\n";
			timedQuestQueue.pop();
			std::this_thread::sleep_for(std::chrono::seconds(2));
		}
	}

	std::cout << "\nAll timed quests completed or expired.\n";
}

void showTimedQuestMenu() {
	int choice;
	while (true) {
		std::cout << "\n===== TIMED QUEST MENU =====\n";
		std::cout << "1. Generate Timed Quests\n";
		std::cout << "2. Monitor Timed Quests (press Q to stop, A to accept)\n";
		std::cout << "0. Back to Main Menu\n";
		std::cout << "Enter your choice: ";
		std::cin >> choice;

		switch (choice) {
		case 1:
			if (!timedQuestsGenerated) {
				for (int i = 0; i < 3; ++i) {
					auto quest = std::make_shared<TimedQuest>(TimedQuest::generateRandom());
					timedQuestQueue.push(quest);
				}
				std::cout << "\n>> Timed Quests Generated.\n";
				timedQuestsGenerated = true;
			}
			else {
				std::cout << "\n>> Timed quests already generated.\n";
			}
			break;
		case 2:
			if (timedQuestQueue.empty()) {
				std::cout << "\n>> No timed quests available.\n";
			}
			else {
				monitorTimedQuests();
				timedQuestsGenerated = false;
			}
			break;
		case 0:
			return;
		default:
			std::cout << "Invalid choice.\n";
		}
	}
}


Player player("", 0, 0);
int main() {
	std::string name = "";
	int age = 0;
	double weight = 0;
	RankTree rankTree;
	std::vector<Quest> dailyQuests; // Broo, this will hold today's system quests
	bool questsGenerated = false;
	std::ifstream saveCheck("save.txt");

	if (saveCheck.is_open()) {

		player.loadFromFile("save.txt");

		// cinematic welcome
		typeEffect(">> Save File Detected.\n", 40);
		typeEffect(">> Restoring Player State...\n", 40);
		std::this_thread::sleep_for(std::chrono::seconds(1));

		// You may want to re-evaluate rank just in case
		player.evaluateRank(rankTree);
	}
	else {
		std::cout << "No Past memories Found \n establishing new connection";
		std::this_thread::sleep_for(1s);
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

		std::cout << "Welcome, " << name << "!\n" << "Physical Aptitude will begin Shortly";
		std::this_thread::sleep_for(2s);
		system("CLS");
		std::this_thread::sleep_for(500ms);

		typeEffect(">>> SYSTEM DIAGNOSTIC ENGAGED <<<\n\n", 40);
		std::this_thread::sleep_for(600ms);

		typeEffect("To evolve, your limits must first be exposed.\n", 50);
		std::this_thread::sleep_for(1000ms);

		typeEffect("Physical aptitude will now be assessed.\n", 40);
		std::this_thread::sleep_for(1000ms);

		typeEffect("\n>> Begin Assessment Protocol.\n", 35);
		std::this_thread::sleep_for(1000ms);

		system("CLS"); // Clean start for the questions

		// ====== ASSESSMENT TEST SECTION ======
		// Mahan this is where the user shows their grind IRL
		int pushups, seconds;
		float minutes;

		int strength, stamina, endurance;

		std::cout << "\nAssessment Test Initiated...\n";

		std::cout << "Enter your push-up count: ";
		std::cout << "Average person can do 20 pushups \n ";
		std::cin >> pushups;

		std::cout << "Enter your 5km run time in minutes : ";
		std::cout << "Average person can run 5km in 33 minutes \n ";
		std::cin >> minutes;

		std::cout << "How long can you Plank (in seconds)?: ";
		std::cout << "Average person can plank for 90 seconds \n ";
		std::cin >> seconds;
		std::cout << "Can you Use Telekenisis \n";
		std::string temp;
		std::cin >> temp;



		// Convert raw inputs to game stats
		strength = convertPushupsToStrength(pushups);
		stamina = convertRunToStamina(minutes);
		endurance = convertPlankToEndurance(seconds);

		// apply those stats to our player
		player.setStats(strength, stamina, endurance);
		player.evaluateRank(rankTree);
		player.saveToFile("save.txt");
		system("CLS");
		std::this_thread::sleep_for(600ms);

		typeEffect(">>> SYSTEM INTERFACE UNLOCKED <<<\n\n", 40);
		std::this_thread::sleep_for(700ms);

		typeEffect("Welcome to the System, Hunter.\n", 40);
		std::this_thread::sleep_for(800ms);

		typeEffect("Your strength, stamina, and endurance have been logged.\n", 40);
		std::this_thread::sleep_for(800ms);

		typeEffect("You have been assigned a Rank.\n", 40);
		std::this_thread::sleep_for(600ms);

		typeEffect("From this point forward, your path will be forged through Quests.\n", 40);
		std::this_thread::sleep_for(900ms);

		typeEffect("Each Quest challenges your limits.\n", 40);
		std::this_thread::sleep_for(600ms);

		typeEffect("Complete them... and the System *may* reward you.\n", 50);
		std::this_thread::sleep_for(900ms);

		typeEffect("\nTrack your stats. Push your limits. Evolve.\n", 50);
		std::this_thread::sleep_for(1000ms);

		typeEffect("\n>> Main Interface Activating...\n", 35);
		std::this_thread::sleep_for(1000ms);
	}
	system("CLS");
	// MAIN MENU LOOP (after assessment is done)
	// Mahan this is the actual System UI the player interacts with

	int choice;
	while (true) {
		if (player.getStats().strength == 100 &&
		player.getStats().stamina == 100 &&
		player.getStats().endurance == 100) {
	
		system("CLS");
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		
		typeEffect(">>> SYSTEM ALERT <<<\n", 60);
		std::this_thread::sleep_for(std::chrono::milliseconds(600));
		typeEffect(">> ALL PARAMETERS MAXED\n", 50);
		std::this_thread::sleep_for(std::chrono::milliseconds(800));
		
		typeEffect(">> NEURAL INTEGRITY: UNSTABLE\n", 40);
		std::this_thread::sleep_for(std::chrono::milliseconds(700));
		typeEffect(">> CORE LIMIT EXCEEDED...\n", 40);
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		
		typeEffect("\n>> PHYSICAL FORM RESTRUCTURING INITIATED\n", 60);
		std::this_thread::sleep_for(std::chrono::milliseconds(1200));
		
		typeEffect(">> SYSTEM CAN NO LONGER CONTAIN THE USER...\n", 60);
		std::this_thread::sleep_for(std::chrono::milliseconds(800));
		glitchText(">>> R̴E̸W̶R̵I̴T̷I̴N̵G̵ ̴S̴Y̷S̷T̵E̴M̷ ̷P̴R̵O̷T̴O̷C̸O̶L̴S̴...\n", 1, 10);
		
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		typeEffect("\n>>> EVOLUTION: FINAL STAGE REACHED <<<\n", 70);
		std::this_thread::sleep_for(std::chrono::milliseconds(800));
	
		typeEffect(">> TITLE GRANTED: \"Monarch of Calisthenics\"\n", 60);
		std::this_thread::sleep_for(std::chrono::milliseconds(600));
		
		typeEffect(">> STATUS: UNCHAINED FROM SYSTEM LIMITS\n", 60);
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		
		typeEffect("\n...The System once judged you.\n", 70);
		std::this_thread::sleep_for(std::chrono::milliseconds(700));
		typeEffect("...Now it worships you.\n", 70);
		std::this_thread::sleep_for(std::chrono::milliseconds(900));
		
		glitchText(">>> RANK OVERRIDE: MONARCH\n", 1, 30);
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		
		typeEffect("\n>> You have become what others train lifetimes to touch.\n", 60);
		typeEffect(">> You no longer chase progress — you **are** progress.\n", 70);
		std::this_thread::sleep_for(std::chrono::milliseconds(1200));
		typeEffect(">> You have reached the end...\n", 80);
std::this_thread::sleep_for(std::chrono::milliseconds(1200));

typeEffect(">> ...and then stepped past it.\n", 90);
std::this_thread::sleep_for(std::chrono::milliseconds(1300));

typeEffect("\n\n");
typeEffect("“You didn’t beat the system — you became the reason it exists.”\n", 120);
std::this_thread::sleep_for(std::chrono::milliseconds(1300));
		typeEffect("\n>> SYSTEM: SHUTTING DOWN\n", 80);
		std::this_thread::sleep_for(std::chrono::milliseconds(1500));
		
		typeEffect("\n>>> GOODBYE, MONARCH. >>> R̴E̸W̶R̵I̴T̷I̴N̵G̵ ̴S̴Y̷S̷T̵E̴M̷ ̷P̴R̵O̷T̴O̷C̸O̶L̴S̴...\n\n", 100);
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	
		exit(0); // 👑 Exit like a Monarch
	}
else{	
	
		std::cout << "\n===== SYSTEM MENU =====\n";
		std::cout << "1. Show Stats\n";
		std::cout << "2. Generate Quests\n";
		std::cout << "3. Complete Quest\n";
		std::cout << "4. Evaluate Rank\n";
		std::cout << "5. Save Progress\n";
		std::cout << "6. Load Progress\n";
		std::cout << "7. New Begininng\n";
		std::cout << "8. Timed Quest System\n"; //queue
		std::cout << "9. Try Combo Quest\n";// circular linked list
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
			}
			else {
				std::cout << "\n>> You already have today's quests, soldier.\n";
			}


			break;
		case 3: {
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
				player.updateStats(q.getStatType(), q.getRewardAmount());

				std::this_thread::sleep_for(3s);
			}
			else {
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
		case 7: {
			std::cout << "\n>> This will delete all saved progress.\n";
			std::cout << "Are you sure? (Y/N): ";
			char confirm;
			std::cin >> confirm;

			if (confirm == 'Y' || confirm == 'y') {
				if (remove("save.txt") == 0) {
					std::cout << ">> Save file deleted successfully.\n";
					std::cout << ">> Rebooting System...\n";
					std::this_thread::sleep_for(std::chrono::seconds(2));
					system("CLS");

					// 🔄 Restart program cleanly
					main();  // 💀 Yes, we are calling main() again.
					return 0; // to avoid weird fallthrough
				}
				else {
					std::cout << ">> Error: Could not delete save file.\n";
				}
			}
			else {
				std::cout << ">> Abort. Save file is untouched.\n";
			}

			break;
		}
		case 8:
			showTimedQuestMenu();
			break;
		case 9: {
			// ComboQuest
			auto q1 = std::make_shared<ComboQuest>(
				std::vector<std::string>{"Burpees x20", "Plank 2min"}, "stamina", 0.7f, 5);
			auto q2 = std::make_shared<ComboQuest>(
				std::vector<std::string>{"Push-ups x30", "Dips x20"}, "strength", 0.6f, 8);
			auto q3 = std::make_shared<ComboQuest>(
				std::vector<std::string>{"Wall Sit 2min", "Slow Lunges x40"}, "endurance", 0.8f, 10);

			// Linking them into a circular list
			q1->setNext(q2);
			q2->setNext(q3);
			q3->setNext(q1);

			// Traverse and simulate
			auto current = q1;
			for (int i = 0; i < 6; ++i) {  // Loop twice through the circle
				current->display(i + 1);
				std::cout << "Accept this combo part? (Y/N): ";
				char input;
				std::cin >> input;
				if (input == 'Y' || input == 'y') {
					float roll = static_cast<float>(rand()) / RAND_MAX;
					if (roll < current->getSuccessChance()) {
						std::cout << ">> Success! " << current->getStatType()
							<< " + " << current->getRewardAmount() << "\n";
						player.updateStats(current->getStatType(), current->getRewardAmount());
					}
					else {
						std::cout << ">> Failed. No reward.\n";
					}
				}
				current = current->getNext();
			}
			break;
		}

		case 0:
			std::cout << "System Offline.\n";  // exit the program
			return 0;

		default:
			std::cout << "Invalid input,.\n";  // if user types wrong number
		}
	}}

}
