#include<iostream>
#include<thread>
#include<mutex>

class Singleton{
private:
	static Singleton *instance;
	int count;
	static std::mutex singleton_mutex;
	Singleton() : count(0){} 

public:
	static Singleton *get_instance(){
		std::lock_guard<std::mutex> guard(singleton_mutex);		
		if(instance ==  nullptr){
			instance = new Singleton();
		}
		return instance;
	}
	void increment(){ count++;}
	int get_count(){ return count;}
};

Singleton* Singleton::instance = nullptr;
std::mutex Singleton::singleton_mutex;

void worker(){
  Singleton *s1 = Singleton::get_instance();
  s1->increment();
  s1->increment();
  Singleton *s2 = Singleton::get_instance();
  std::cout << s1->get_count() << " " << s1 << std::endl;
  std::cout << s2->get_count() << " " << s2 << std::endl;
}

int main(){
  Singleton *s1 = Singleton::get_instance();
  s1->increment();
  s1->increment();
  Singleton *s2 = Singleton::get_instance();
  std::cout << s1->get_count() << " " << s1 << std::endl;
  std::cout << s2->get_count() << " " << s2 << std::endl;
  std::thread t1 = std::thread(&worker);
  std::thread t2 = std::thread(&worker);
  t1.join();
  t2.join();
  return 0;
}
