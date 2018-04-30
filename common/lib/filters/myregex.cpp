#include "myregex.h"

std::pair<std::list<std::string>, std::list<std::string> >  myregex::search_pattern(std::list<std::string> input_strings, std::string PATTERN_STRING){
  std::list<std::string>output_match;
  std::list<std::string>output_no_match;
  std::regex PATTERN(PATTERN_STRING);
  std::list<std::string>::iterator filter_strings  = std::remove_if(input_strings.begin(), input_strings.end(), \
                                     [PATTERN](const std::string SUBJECT) -> bool{ \
                                      return std::regex_match(SUBJECT, PATTERN);});
  for (auto iter = input_strings.begin(); iter != filter_strings; iter++){
    output_no_match.push_back(*iter); 
  }
  for (auto iter = input_strings.begin(); iter != input_strings.end(); iter++){
    if(iter == filter_strings){
      output_match.push_back(*iter); 
      filter_strings++;
    }
  }
  return std::make_pair(output_no_match, output_match);
}
