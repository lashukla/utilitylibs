#include<iostream>
#include<chrono>

#include "threadpool.hpp"

int main(){
  thread_pool::ThreadPool<20> pool;
  int JOB_COUNT = 100;
  for( int i = 0; i < JOB_COUNT; ++i ){
    pool.AddJob( [](int x) { std::cout<< x << " "; std::this_thread::sleep_for( std::chrono::seconds( 1 ) ); }, i);
  }
  pool.JoinAll();
  std::cout << std::endl;
  std::cout << "Expected runtime: 5 seconds." << std::endl;
}

