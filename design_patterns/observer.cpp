#include<iostream>
#include<vector>
#include<algorithm>

class Observer{
private:
	std::string nm;
public:
	Observer(std::string name): nm(name){}
	void update(){
		std::cout << "Updating " << nm << std::endl;		
	}
	bool operator ==(const Observer &o){
		return nm == o.nm;
	}
	const std::string get_name(){
		return nm;
	}
};
class Observable{
private:
	std::vector<Observer> o_v;
public:
	void Add(Observer o){
		std::cout << "Adding " << o.get_name() << std::endl;		
		o_v.push_back(o);  
	}
	void Delete(Observer &o){
		std::cout << "Deleting " << o.get_name() << std::endl;		
		o_v.erase(std::find(o_v.begin(), o_v.end(), o));
	};
	void Notify(){
		std::cout << "Notifying All" <<  std::endl;		
		for(auto i: o_v){
			i.update();
		}
	};
};


int main(){
  Observable ob;
  Observer x{"x"}, y{"y"}, z{"z"};
  ob.Add(x);
  ob.Add(y);
  ob.Add(z);
  std::cout << "===============" << std::endl;
  ob.Notify();
  std::cout << "===============" << std::endl;
  ob.Delete(x);
  std::cout << "===============" << std::endl;
  ob.Notify();
}
