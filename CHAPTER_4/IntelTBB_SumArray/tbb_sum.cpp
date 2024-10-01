#include <tbb/tbb.h>
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

    // Tính tổng sử dụng TBB
    sum = tbb::parallel_reduce(
        tbb::blocked_range<std::vector<int>::iterator>(data.begin(), data.end()),
        0LL, // Giá trị khởi tạo
        [](const tbb::blocked_range<std::vector<int>::iterator>& r, long long init) {
            for (auto it = r.begin(); it != r.end(); ++it) {
                init += *it; // Tính tổng
            }
            return init;
        },
        std::plus<long long>() // Gộp kết quả
    );

    // Đo thời gian kết thúc
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_time = end_time - start_time;

    std::cout << "TBB Total sum = " << sum << std::endl;
    std::cout << "TBB Elapsed time: " << elapsed_time.count() << " seconds" << std::endl;

    return 0;
}
