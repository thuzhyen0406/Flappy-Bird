#ifndef score_h
#define score_h
#include <fstream>
int score = 0; // Điểm hiện tại
int highScore = 0; // Điểm cao nhất
const string score_fl = "highscore.txt";

void loadHighScore() {
    ifstream file(score_fl);
    if (file >> highScore) {
        file.close();
    } else {
        highScore = 0; // Nếu không có tệp, đặt mặc định là 0
    }
}


void updateScore(int const score, int &highScore) {
    // Cộng điểm khi vượt qua ống

    if (score > highScore) {
        highScore = score; // Cập nhật điểm cao nhất

        // Ghi file ngay khi có điểm cao mới
        ofstream file(score_fl);
        file << highScore;
        file.close();
    }
}
#endif // score_h
