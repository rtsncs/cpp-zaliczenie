#include "score.hpp"
#include <algorithm>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>

Score::Score(int _score) : score{_score} {
    auto time = std::time(nullptr);
    std::tm *ltm = std::localtime(&time);
    day = ltm->tm_mday;
    month = ltm->tm_mon;
    year = 1900 + ltm->tm_year;
}

Score::Score() {}

std::ostream &operator<<(std::ostream &out, const Score &score) {
    out << score.score << "\t\t" << score.day << "/" << score.month << "/"
        << score.year;

    return out;
}

std::istream &operator>>(std::istream &in, Score &score) {
    in >> score.score >> score.day;
    in.ignore(1, '/');
    in >> score.month;
    in.ignore(1, '/');
    in >> score.year;

    return in;
}

void Score::save() {
    std::ofstream file;
    file.open("scores.txt", std::ios::app);
    file << *this << "\n";
    file.close();
}

bool compare(const Score &a, const Score &b) { return a.score > b.score; }
std::vector<Score> Score::load() {
    std::vector<Score> result;

    std::ifstream file;
    file.open("scores.txt", std::ios::in);
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        Score score;
        ss >> score;
        result.push_back(score);
    }

    file.close();

    std::sort(result.begin(), result.end(), compare);

    return result;
}
