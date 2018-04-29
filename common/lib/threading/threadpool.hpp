#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__

#include<thread>
#include<mutex>
#include<condition_variable>
#include<array>
#include<list>
#include<functional>
#include<atomic>

namespace thread_pool{
template<unsigned ThreadCount = 10>
class ThreadPool{
private:
	std::array<std::thread, ThreadCount> th_arr;
	std::list<std::pair<std::function<void(int)>, int>> queue;	

	std::condition_variable wait_var;
	std::condition_variable job_available;
	std::mutex queue_mutex;
	std::mutex wait_mutex;
	std::atomic_bool bailout;
	std::atomic_bool finished;
	std::atomic_int job_left;

	void Task(){
	  std::pair<std::function<void(int)>, int> fun_with_arg;
	  while(!bailout){
	    fun_with_arg = next_job();
	    fun_with_arg.first(fun_with_arg.second);
	    job_left--;
	    wait_var.notify_one();
	  }
	}
	std::pair<std::function<void(int)>, int> next_job(){
	  std::pair<std::function<void(int)>, int> fun_with_arg;
	  std::unique_lock<std::mutex> job_lock(queue_mutex);
	  job_available.wait(job_lock, [this]()->bool{return queue.size() || bailout; });
	  if(!bailout){
	    fun_with_arg = queue.front();
	    queue.pop_front();
	  }else{
	    fun_with_arg = std::make_pair([](int x){}, 0);
	    job_left++;
	  }
	  return fun_with_arg;
	}
	
public:
	ThreadPool(): bailout(false), job_left(0), finished(false){
	  for(int i = 0; i < ThreadCount; i++){
	    th_arr[i] = std::thread([this](){ this->Task(); });
	  }
	}
	~ThreadPool(){
	  JoinAll();
	}
	void JoinAll(bool WaitForAll = true){
	  if(!finished){
	    if(WaitForAll){
	      WaitAll(); 
	    }
	    bailout = true;
	    job_available.notify_all();
	    for(auto &x: th_arr){
	      if(x.joinable()){
	        x.join();
	      }
	      finished = true;
	    }
	  }
	  
	}
	void WaitAll(){
	  if(job_left > 0){
	    std::unique_lock<std::mutex> lk( wait_mutex );
	    wait_var.wait( lk, [this]{ return this->job_left == 0; } );
	    lk.unlock(); 
	  }
	}

	void AddJob(std::function<void(int)> job, int x){
	  std::lock_guard<std::mutex> guard(queue_mutex);
	  queue.emplace_back(std::make_pair(job, x));
	  job_left++;
	  job_available.notify_one();
	}
	
};
};
#endif
