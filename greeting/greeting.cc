#include "greeting.h"

#include <string>

namespace greeting {

std::string get_greeting(const std::string& word) {
    return "Looking up whether '" + word + "' is a valid word";
}

}  // namespace greeting
