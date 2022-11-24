#include "repl.h"

#include <iostream>

#include "absl/strings/str_cat.h"
#include "fmt/color.h"
#include "third_party/linenoise/linenoise.h"

using namespace std;
using namespace fmt;
using namespace absl;
using namespace linenoise;

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

void mainLoop() {
    int line_count = 0;
    while (true) {
        // Read line
        string line;

        string prompt = StrCat(format(fg(color::dark_gray), "["),
                               format(fg(color::cyan), to_string(line_count)),
                               format(fg(color::dark_gray), "] "),
                               format(fg(color::light_green), "mandelbrot"),
                               format(fg(color::dark_gray), "> "));

        auto quit = linenoise::Readline(prompt.c_str(), line);

        if (quit) {
            break;
        }

        cout << "echo: '" << line << "'" << endl;

        line_count++;

        // Add text to history
        linenoise::AddHistory(line.c_str());
    }
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
