#include <chrono>
#include <climits>
#include <iostream>
#include <vector>

#include <thread>
using namespace std;
// 距离太大，用归纳法证明
int calc(int rows, int cols, int row, int col)
{
    int sum = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            sum += std::abs(row - i) + std::abs(col - j);
        }
    }

    // sum += (0 + cols - 1) * cols / 2;
    // int last = sum;
    // for (int i = 1; i < rows; ++i) {
    //     last += cols;
    //     sum += last;
    // }

    return sum;
}

long long calcAll(int rows, int cols)
{
    long long sum = 0;
    int times = 0;
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            sum += 2 * calc(rows, cols, i, j);
            times++;
            if (times == rows * cols / 2) {
                if((rows * cols) % 2) {
                    sum += calc(rows, cols,i,j + 1);
                }
                return sum;
            }
        }
    }
    return sum;
}

int main()
{
    auto start = chrono::system_clock::now();
    cout << calc(256, 256, 0, 0) << "\n";
    cout << calc(256, 256, 128, 128) << "\n";
    cout << calc(256, 256, 255, 255) << "\n";
    // 732996567040

    // cout << calcAll(256, 256) / (256*256) << endl;
    auto end = chrono::system_clock::now();
    cout << (end - start).count() << endl;

    return 0;
}