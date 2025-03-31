#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits>   // Added for numeric_limits

// using namespace std;  // Not best practice – replaced with explicit using declarations below

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;
using std::getline;
using std::rand;
using std::srand;
using std::time;
using std::runtime_error;

// Structure to store user profile and workout stats
struct UserProfile {
    string name{};
    float weight{};          // in kg
    float height{};          // in meters
    string fitnessLevel{};   // Beginner, Intermediate, Advanced

    // Workout statistics
    int pushUps{};
    int pullUps{};
    int squats{};
    float runningDistance{}; // in kilometers

    // XP and leveling system
    int xp{};
    int level{};
    string rank{};
    int dailyStreak{};
};

// Function to update the rank based on the user's level
void updateRank(UserProfile& user) {
    if (user.level < 2)
        user.rank = "Weak Hunter";
    else if (user.level < 5)
        user.rank = "E-Rank";
    else if (user.level < 10)
        user.rank = "D-Rank";
    else if (user.level < 15)
        user.rank = "C-Rank";
    else if (user.level < 20)
        user.rank = "B-Rank";
    else if (user.level < 25)
        user.rank = "A-Rank";
    else
        user.rank = "S-Rank";
}

// Function to check if the user has enough XP to level up
void checkLevelUp(UserProfile& user) {
    // Level-up threshold: current level * 100 XP
    int requiredXp = user.level * 100;
    // Allow for multiple level-ups if enough XP is earned
    while (user.xp >= requiredXp) {
        user.xp -= requiredXp;
        user.level++;
        cout << "\nCongratulations! You've leveled up to level " << user.level << "!\n";
        updateRank(user);
        requiredXp = user.level * 100;
    }
}

// Function to display the current user profile and workout statistics
void displayProfile(const UserProfile& user) {
    cout << "\n----- User Profile -----" << endl;
    cout << "Name: " << user.name << endl;
    cout << "Weight: " << user.weight << " kg" << endl;
    cout << "Height: " << user.height << " m" << endl;
    cout << "Fitness Level: " << user.fitnessLevel << endl;
    cout << "Rank: " << user.rank << endl;
    cout << "Level: " << user.level << " (XP: " << user.xp << ")" << endl;
    cout << "Daily Streak: " << user.dailyStreak << endl;
    cout << "----- Workout Stats -----" << endl;
    cout << "Push-ups: " << user.pushUps << endl;
    cout << "Pull-ups: " << user.pullUps << endl;
    cout << "Squats: " << user.squats << endl;
    cout << "Running Distance: " << user.runningDistance << " km" << endl;
    cout << "-------------------------" << endl;
}

// Function to log a workout session
void logWorkout(UserProfile& user) {
    int choice;
    cout << "\nSelect workout type:" << endl;
    cout << "1. Push-ups" << endl;
    cout << "2. Pull-ups" << endl;
    cout << "3. Squats" << endl;
    cout << "4. Running" << endl;
    cout << "Enter choice: ";
    cin >> choice;
    // Validate workout choice
    while (cin.fail() || choice < 1 || choice > 4) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Invalid option. Please enter a number between 1 and 4: ";
        cin >> choice;
    }

    switch (choice) {
    case 1: {
        int count;
        cout << "How many push-ups did you do? ";
        cin >> count;
        // Validate push-up count (must be non-negative)
        while (cin.fail() || count < 0) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Invalid number. Please enter a non-negative number for push-ups: ";
            cin >> count;
        }
        user.pushUps += count;
        user.xp += count; // 1 XP per push-up
        cout << "Great job! You earned " << count << " XP." << endl;
        break;
    }
    case 2: {
        int count;
        cout << "How many pull-ups did you do? ";
        cin >> count;
        // Validate pull-up count (must be non-negative)
        while (cin.fail() || count < 0) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Invalid number. Please enter a non-negative number for pull-ups: ";
            cin >> count;
        }
        user.pullUps += count;
        user.xp += count * 2; // 2 XP per pull-up
        cout << "Awesome! You earned " << count * 2 << " XP." << endl;
        break;
    }
    case 3: {
        int count;
        cout << "How many squats did you do? ";
        cin >> count;
        // Validate squat count (must be non-negative)
        while (cin.fail() || count < 0) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Invalid number. Please enter a non-negative number for squats: ";
            cin >> count;
        }
        user.squats += count;
        user.xp += count; // 1 XP per squat
        cout << "Nice! You earned " << count << " XP." << endl;
        break;
    }
    case 4: {
        float distance;
        cout << "How many kilometers did you run? ";
        cin >> distance;
        // Validate running distance (must be non-negative)
        while (cin.fail() || distance < 0) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Invalid distance. Please enter a non-negative number for kilometers run: ";
            cin >> distance;
        }
        user.runningDistance += distance;
        int earnedXp = static_cast<int>(distance * 10); // 10 XP per km
        user.xp += earnedXp;
        cout << "Good run! You earned " << earnedXp << " XP." << endl;
        break;
    }
    default:
        cout << "Invalid option." << endl;
        return;
    }

    // Check for level-up after logging the workout
    checkLevelUp(user);
}

// Function to simulate a daily challenge for bonus XP
void dailyChallenge(UserProfile& user) {
    // Seed the random number generator
    srand(static_cast<unsigned int>(time(0)));

    int challenge = rand() % 3;  // Generate a random challenge (0, 1, or 2)
    int bonusXp = 0;

    cout << "\n----- Daily Challenge -----" << endl;
    switch (challenge) {
    case 0:
        cout << "Challenge: Do 10 push-ups in one go." << endl;
        bonusXp = 10;
        break;
    case 1:
        cout << "Challenge: Do 5 pull-ups in one go." << endl;
        bonusXp = 10;
        break;
    case 2:
        cout << "Challenge: Run 1 kilometer." << endl;
        bonusXp = 10;
        break;
    }

    char completed;
    cout << "Did you complete the challenge? (y/n): ";
    cin >> completed;
    // Validate the character input (must be y/Y/n/N)
    while (cin.fail() || (completed != 'y' && completed != 'Y' && completed != 'n' && completed != 'N')) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Invalid input. Please enter 'y' for yes or 'n' for no: ";
        cin >> completed;
    }

    if (completed == 'y' || completed == 'Y') {
        cout << "Well done! You earned an extra " << bonusXp << " XP." << endl;
        user.xp += bonusXp;
        checkLevelUp(user);
    }
    else {
        cout << "Maybe next time!" << endl;
    }
    cout << "---------------------------" << endl;
}

// Function to save the current profile data to a file
void saveProfile(const UserProfile& user) {
    ofstream outFile("save.txt");
    if (outFile.is_open()) {
        outFile << user.name << endl;
        outFile << user.weight << endl;
        outFile << user.height << endl;
        outFile << user.fitnessLevel << endl;
        outFile << user.pushUps << endl;
        outFile << user.pullUps << endl;
        outFile << user.squats << endl;
        outFile << user.runningDistance << endl;
        outFile << user.xp << endl;
        outFile << user.level << endl;
        outFile << user.rank << endl;
        outFile << user.dailyStreak << endl;
        outFile.close();
        cout << "\nProfile saved successfully." << endl;
    }
    else {
        cout << "\nError saving profile." << endl;
    }
}

// Function to load the profile data from a file
void loadProfile(UserProfile& user) {
    ifstream inFile("save.txt");
    if (inFile.is_open()) {
        getline(inFile, user.name);
        inFile >> user.weight;
        inFile >> user.height;
        inFile.ignore(); // Ignore newline
        getline(inFile, user.fitnessLevel);
        inFile >> user.pushUps;
        inFile >> user.pullUps;
        inFile >> user.squats;
        inFile >> user.runningDistance;
        inFile >> user.xp;
        inFile >> user.level;
        inFile.ignore(); // Ignore newline
        getline(inFile, user.rank);
        inFile >> user.dailyStreak;
        inFile.close();
        cout << "\nProfile loaded successfully." << endl;
    }
    else {
        cout << "\nNo save file found." << endl;
    }
}

int main() {
    UserProfile user;

    // Initialize user profile with basic input
    cout << "Enter your name: ";
    getline(cin, user.name);
    // Validate name is not empty
    while (user.name.empty()) {
        cout << "Name cannot be empty. Please enter your name: ";
        getline(cin, user.name);
    }

    cout << "Enter your weight (in kg): ";
    cin >> user.weight;
    // Validate weight is a positive number
    while (cin.fail() || user.weight <= 0) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Invalid weight. Please enter a positive number: ";
        cin >> user.weight;
    }

    cout << "Enter your height (in meters): ";
    cin >> user.height;
    // Validate height is a positive number
    while (cin.fail() || user.height <= 0) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Invalid height. Please enter a positive number: ";
        cin >> user.height;
    }
    cin.ignore(); // Clear newline left in input buffer

    cout << "Enter your fitness level (Beginner/Intermediate/Advanced): ";
    getline(cin, user.fitnessLevel);
    // Validate fitness level input
    while (user.fitnessLevel != "Beginner" && user.fitnessLevel != "Intermediate" && user.fitnessLevel != "Advanced") {
        cout << "Invalid fitness level. Please enter (Beginner/Intermediate/Advanced): ";
        getline(cin, user.fitnessLevel);
    }

    // Initialize workout stats and XP system
    user.pushUps = 0;
    user.pullUps = 0;
    user.squats = 0;
    user.runningDistance = 0.0;
    user.xp = 0;
    user.level = 1;
    user.dailyStreak = 0;
    updateRank(user);

    // Main menu loop
    int option;
    option = 0; // Initialize option variable to avoid warnings
    do {
        cout << "\n===== Fitness Tracker Menu =====" << endl;
        cout << "1. Display Profile" << endl;
        cout << "2. Log Workout" << endl;
        cout << "3. Daily Challenge" << endl;
        cout << "4. Save Profile" << endl;
        cout << "5. Load Profile" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your option: ";
        cin >> option;
        // Validate menu option input
        while (cin.fail() || option < 1 || option > 6) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Invalid option. Please enter a number between 1 and 6: ";
            cin >> option;
        }
        cin.ignore(); // Clear newline

        switch (option) {
        case 1:
            displayProfile(user);
            break;
        case 2:
            logWorkout(user);
            break;
        case 3:
            dailyChallenge(user);
            break;
        case 4:
            saveProfile(user);
            break;
        case 5:
            loadProfile(user);
            break;
        case 6:
            cout << "\nExiting program. Stay fit!" << endl;
            break;
        default:
            cout << "\nInvalid option. Please choose again." << endl;
        }
    } while (option != 6);

    return 0;
}
