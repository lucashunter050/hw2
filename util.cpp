#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/

// note: figure out how to differentiate ISBN hyphens from punctuation hyphens
std::set<std::string> parseStringToWords(string rawWords)
{
    std::set<std::string> searchWords;
    std::string currWord;
    rawWords = trim(rawWords);

    for (unsigned long i = 0; i < rawWords.size(); i++) {
        // checks if the current character is a punctuation mark by ASCII value
        if ((static_cast<int>(rawWords[i]) > 32 && static_cast<int>(rawWords[i]) < 43) ||
            static_cast<int>(rawWords[i]) > 43 && static_cast<int>(rawWords[i]) < 48) {
                // sees if this word needs to be added to keywords
                // otherwise, resets the current word being analyzed
                if (currWord.size() > 1) {
                    searchWords.insert(convToLower(currWord));
                } else {
                    currWord = "";
                }
            } 
        else if (rawWords[i] == ' ') {
            if (currWord.size() > 1) {
                searchWords.insert(convToLower(currWord));
            } else {
                currWord = "";
            }
        } 
        // otherwise keeps adding characters to the active comparison
        else {
            currWord += rawWords[i];
        }
    }

    // returns the set of all keywords in the rawWords string
    return searchWords;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
