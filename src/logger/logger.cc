#include "logger.h"

#include <cstdlib>
#include <iostream>

using namespace std;

void logError(const string& message) {
    cout << set_colors(VT_BLACK, VT_RED) << " ERROR " << default_attributes
         << " " << message << endl;
}

void logWarning(const string& message) {
    cout << set_colors(VT_BLACK, VT_YELLOW) << " WARNING " << default_attributes
         << " " << message << endl;
}

void logInfo(const string& message) {
    cout << set_colors(VT_BLACK, VT_YELLOW) << " INFO " << default_attributes
         << " " << message << endl;
}

unique_ptr<ExprAST> logSyntaxError(const string& message) {
    logError("Syntax Error: " + message);
    return nullptr;
}

unique_ptr<PrototypeAST> logSyntaxErrorP(const string& message) {
    logError("Syntax Error (Prototype): " + message);
    return nullptr;
}
