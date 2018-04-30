#ifndef __MYREGEX_H__
#define __MYREGEX_H__
#include<regex>
#include<algorithm>
#include<list>


namespace myregex{
std::pair<std::list<std::string>, std::list<std::string> > search_pattern(std::list<std::string> input_strings, std::string PATTERN_STRING);
};

#endif
