#!/bin/bash

# Biên dịch chương trình TBB
g++ -std=c++11 tbb_sum.cpp -o tbb_sum -ltbb

# Biên dịch chương trình đơn luồng
g++ -std=c++11 single_thread_sum.cpp -o single_thread_sum

# Chạy cả hai chương trình
echo "Running TBB program..."
./tbb_sum

echo "Running single-thread program..."
./single_thread_sum
