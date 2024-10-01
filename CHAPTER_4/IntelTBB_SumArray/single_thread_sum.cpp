#include <iostream>
#include <vector>
#include <random>
#include <chrono>

int main() {
    const size_t SIZE = 100000000; // Kích thước mảng
    std::vector<int> data(SIZE);

    // Khởi tạo mảng ngẫu nhiên
    std::mt19937 rng(12345); // Bộ sinh số ngẫu nhiên
    std::uniform_int_distribution<int> dist(1, 100);
    for (size_t i = 0; i < SIZE; ++i) {
        data[i] = dist(rng);
    }

    long long sum = 0;

    // Đo thời gian bắt đầu
    auto start_time = std::chrono::high_resolution_clock::now();

    // Tính tổng trong vòng lặp đơn
    for (size_t i = 0; i < SIZE; ++i) {
        sum += data[i]; // Tính tổng
    }

    // Đo thời gian kết thúc
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_time = end_time - start_time;

    std::cout << "Single-thread Total sum = " << sum << std::endl;
    std::cout << "Single-thread Elapsed time: " << elapsed_time.count() << " seconds" << std::endl;

    return 0;
}
