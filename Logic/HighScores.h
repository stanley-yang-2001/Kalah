#ifndef HIGHSCORES
#define HIGHSCORES

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

class HighScoreManager {
public:
    // Constructor that takes the file name
    HighScoreManager(const std::string& fileName) : fileName_(fileName) {}

    // Function to write a high score to the CSV file
    void WriteHighScore(const std::string& name, int score) {
        // Read existing high scores
        std::vector<std::pair<std::string, int>> highScores = ReadHighScores();

        // Check if the name is already in the high scores
        auto nameCheck = std::find_if(highScores.begin(), highScores.end(),
                               [&name](const std::pair<std::string, int>& entry) {
                                   return entry.first == name;
                               });

        // name is not in the high scores, add it
        if (nameCheck == highScores.end()) {
            highScores.push_back(std::make_pair(name, score));
        }
        // name is in the high scores and the new score is higher, update it
        else if (score > nameCheck->second) {
            nameCheck->second = score;
        }

        // Write the updated high scores to the file
        WriteHighScores(highScores);
    }

    // Function to get all high scores from the CSV file
    std::vector<std::pair<std::string, int>> GetHighScores() {
        return ReadHighScores();
    }

private:
    // Private function to read high scores from the CSV file
    std::vector<std::pair<std::string, int>> ReadHighScores() const {
        std::vector<std::pair<std::string, int>> highScores;

        std::ifstream inputFile(fileName_);

        if (!inputFile.is_open()) {
            std::cerr << "Error opening the file!" << std::endl;
            return highScores;
        }
        std::cout<<"File Opened for Reading" << std::endl;

        std::string line;
        while (std::getline(inputFile, line)) {
            std::istringstream iss(line);
            std::string name;
            int score;

            if (std::getline(iss, name, ',') && iss >> score) {
                highScores.push_back(std::make_pair(name, score));
            }
        }

        inputFile.close();

        return highScores;
    }

    // Private function to write high scores to the CSV file
    void WriteHighScores(const std::vector<std::pair<std::string, int>>& highScores) const {
        std::ofstream outputFile(fileName_);

        if (!outputFile.is_open()) {
            std::cerr << "Error opening the file!" << std::endl;
            return;
        }

        std::cout<<"File Opened for writing" << std::endl;

        for (const auto& entry : highScores) {
            std::cout << entry.first << "," << entry.second << std::endl;
            outputFile << entry.first << "," << entry.second << std::endl;
        }

        outputFile.close();
    }

    // Private member variable to store the file name
    std::string fileName_;
};

#endif
