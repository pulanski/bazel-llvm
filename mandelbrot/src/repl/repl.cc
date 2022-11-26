#include "repl.h"

#include <iostream>

#include "fmt/color.h"
#include "third_party/linenoise/linenoise.h"

using namespace absl;
using namespace fmt;
using namespace linenoise;
using namespace std;

void mainDisplay() {
    cout << format(fg(fmt::color::white) | fmt::emphasis::bold,
                   "\n\n                                 :::::                 "
                   "    ")
         << endl;
    cout << format(
                fg(fmt::color::white) | fmt::emphasis::bold,
                "                            :::::::#+:::::                 ")
         << endl;
    cout << format(
                fg(fmt::color::white) | fmt::emphasis::bold,
                "                         :::::::::++#++:::::               ")
         << endl;
    cout << format(
                fg(fmt::color::white) | fmt::emphasis::bold,
                "                       :::::::::++@@@@@+::::::             ")
         << endl;
    cout << format(
                fg(fmt::color::white) | fmt::emphasis::bold,
                "                     :::::::+%++++#@@@x+++::%::            ")
         << endl;
    cout << format(
                fg(fmt::color::white) | fmt::emphasis::bold,
                "                  :::::::::+x@@@@@@@@@@@@@@@@+::           ")
         << endl;
    cout << format(
                fg(fmt::color::white) | fmt::emphasis::bold,
                "               ::::::::::+@@#@@@@@@@@@@@@@@@++:::          ")
         << endl;
    cout << format(
                fg(fmt::color::white) | fmt::emphasis::bold,
                "         :::::::+x++++++++@@@@@@@@@@@@@@@@@@@@+::          ")
         << endl;
    cout << format(
                fg(fmt::color::white) | fmt::emphasis::bold,
                "      :::::::::+++@@@@@@%x@@@@@@@@@@@@@@@@@@@%::::         ")
         << endl;
    cout << format(
                fg(fmt::color::white) | fmt::emphasis::bold,
                "     ::::::::++xx@@@@@@@@@@@@@@@@@@@@@@@@@@@@+::::         ")
         << endl;
    cout << format(
                fg(fmt::color::white) | fmt::emphasis::bold,
                "     @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@x+:::::         ")
         << endl;
    cout << format(
                fg(fmt::color::white) | fmt::emphasis::bold,
                "     ::::::::++xx@@@@@@@@@@@@@@@@@@@@@@@@@@@@+::::         ")
         << endl;
    cout << format(
                fg(fmt::color::white) | fmt::emphasis::bold,
                "      :::::::::+++@@@@@@%x@@@@@@@@@@@@@@@@@@@%::::         ")
         << endl;
    cout << format(
                fg(fmt::color::white) | fmt::emphasis::bold,
                "         :::::::+x++++++++@@@@@@@@@@@@@@@@@@@@+::          ")
         << endl;
    cout << format(
                fg(fmt::color::white) | fmt::emphasis::bold,
                "               ::::::::::+@@#@@@@@@@@@@@@@@@++:::          ")
         << endl;
    cout << format(
                fg(fmt::color::white) | fmt::emphasis::bold,
                "                  :::::::::+x@@@@@@@@@@@@@@@@+::           ")
         << endl;
    cout << format(
                fg(fmt::color::white) | fmt::emphasis::bold,
                "                     :::::::+%++++#@@@x+++::%::            ")
         << endl;
    cout << format(
                fg(fmt::color::white) | fmt::emphasis::bold,
                "                       :::::::::++@@@@@+::::::             ")
         << endl;
    cout << format(
                fg(fmt::color::white) | fmt::emphasis::bold,
                "                         :::::::::++#++:::::               ")
         << endl;
    cout << format(
                fg(fmt::color::white) | fmt::emphasis::bold,
                "                            :::::::#+:::::                 ")
         << endl;
    cout << format(
                fg(fmt::color::white) | fmt::emphasis::bold,
                "                                 :::::                     ")
         << endl;
    cout << format(fg(fmt::color::white) | fmt::emphasis::bold,
                   "\n                        _      _ _               _   ")
         << endl;
    cout << format(fg(fmt::color::white) | fmt::emphasis::bold,
                   "  /\\/\\   __ _ _ __   __| | ___| | |__  _ __ ___ | |_ ")
         << endl;
    cout << format(fg(fmt::color::white) | fmt::emphasis::bold,
                   " /    \\ / _` | '_ \\ / _` |/ _ \\ | '_ \\| '__/ _ \\| __|")
         << endl;
    cout << format(fg(fmt::color::white) | fmt::emphasis::bold,
                   "/ /\\/\\ \\ (_| | | | | (_| |  __/ | |_) | | | (_) | |_ ")
         << endl;
    cout << format(fg(fmt::color::white) | fmt::emphasis::bold,
                   "\\/    \\/\\__,_|_| |_|\\__,_|\\___|_|_.__/|_|  \\___/ "
                   "\\__|\n\n")
         << endl;
}

void initializeRepl() {
    // Setup completion words every time when a user types
    linenoise::SetCompletionCallback(
        [](const char* edit_buffer, std::vector<std::string>& completions) {
            if (edit_buffer[0] == 'f') {
                completions.push_back("fn");
                completions.push_back("fn main() {");
            }
        });

    // Enable the multi-line mode
    linenoise::SetMultiLine(true);

    // Set max length of the history
    linenoise::SetHistoryMaxLen(20);
}
