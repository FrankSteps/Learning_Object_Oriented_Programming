/*
    std::range::sort(words);
*/

#include <iostream>
#include <vector>
#include <string>

int main(){
    std::vector<std::string> words;

    for(std::string s; std::cin >> s && s != "quit";){
        words.push_back(s);
    }

    for(std::string s : words){
        std::cout << s << std::endl;
    }
    return 0;
}