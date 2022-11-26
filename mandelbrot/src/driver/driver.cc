#include "driver.h"

#include "absl/strings/str_cat.h"
#include "fmt/color.h"
#include "third_party/linenoise/linenoise.h"

using namespace absl;
using namespace fmt;
using namespace linenoise;
using namespace std;

Status replMainLoop() {
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

    return OkStatus();
}

Status compileFiles(vector<string> files) {
    for (auto& file : files) {
        cout << "Compiling file: " << file << endl;
    }
    return OkStatus();
}
