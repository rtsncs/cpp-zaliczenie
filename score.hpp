#pragma once
#include <string>
#include <vector>

struct Score {
    int score;
    int day;
    int month;
    int year;
    Score(int score);
    void save();
    static std::vector<Score> load();
    friend std::ostream &operator<<(std::ostream &out, const Score &score);

  private:
    Score();
};
