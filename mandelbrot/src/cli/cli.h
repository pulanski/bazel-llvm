#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "absl/strings/str_join.h"

using namespace std;
using namespace absl;

struct CLIOptions {
    bool debug_mode;
    bool verbose_output;
    string eval_expr;
    bool emit_tokens;
    bool emit_ast;
    bool emit_ir;
};

struct CLIPositionals {
    vector<string> files;
};

class MandelbrotCLI {
   public:
    CLIOptions cliOptions{};
    CLIPositionals cliPositionals{{}};
    string mandelbrotVersion;

    MandelbrotCLI(bool debug_mode = false, bool verbose_output = false,
                  string eval_expr = "", bool emit_tokens = false,
                  bool emit_ast = false, bool emit_ir = false,
                  vector<string> files = {}, string mandelbrot_version = "")
        : cliOptions{debug_mode,  verbose_output, eval_expr,
                     emit_tokens, emit_ast,       emit_ir},
          cliPositionals{files},
          mandelbrotVersion{mandelbrot_version} {}

    string toString() {
        string files = cliPositionals.files.empty()
                           ? "N/A"
                           : StrJoin(cliPositionals.files, ", ");
        return StrJoin(
            vector<string>{
                "MandelbrotCLI {", "  cliOptions {",
                "    debug_mode: " + to_string(cliOptions.debug_mode) + ", ",
                "    verbose_output: " + to_string(cliOptions.verbose_output) +
                    ", ",
                "    eval_expr: " + cliOptions.eval_expr + ", ",
                "    emit_tokens: " + to_string(cliOptions.emit_tokens) + ", ",
                "    emit_ast: " + to_string(cliOptions.emit_ast) + ", ",
                "    emit_ir: " + to_string(cliOptions.emit_ir), "  }, ",
                "  cliPositionals {", "    files: " + files + ",", "  }, ",
                "  mandelbrotVersion: " + mandelbrotVersion, "  },", "}"},
            "\n");
    }
};

extern shared_ptr<MandelbrotCLI> mandelbrotCLI;

int parseCommandLineArgs(int argc, char* argv[],
                         shared_ptr<MandelbrotCLI> mandelbrot_cli);
