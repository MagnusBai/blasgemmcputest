g++ test_simple_mm.cpp -lcblas -o test_simple_mm
g++ test_multi_mm.cpp -lcblas -o test_multi_mm
g++ -std=c++11 test_multi_mm_threads.cpp -lcblas -lpthread -o test_multi_mm_threads
