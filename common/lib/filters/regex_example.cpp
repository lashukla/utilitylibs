#include<iostream>
#include "myregex.h"

int main(){
  std::list<std::string>input_strings{"This is India", "That is Delhi", "Mathematics", "This is World", "London"};
  std::string PATTERN("Thi.*");
  std::pair<std::list<std::string>, std::list<std::string> > output;
  output = myregex::search_pattern(input_strings, PATTERN);
  std::cout << "============NO MATCH===============" << std::endl;
  for(auto &iter : output.first){
    std::cout << iter << std::endl;
  }
  std::cout << "==============MATCH================" << std::endl;
  for(auto &iter : output.second){
    std::cout << iter << std::endl;
  }
  return 0;
}

