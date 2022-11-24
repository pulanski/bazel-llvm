#include "utils.h"

#include <filesystem>
#include <fstream>

#include "absl/strings/str_cat.h"
#include "fmt/core.h"
#include "glog/logging.h"

using namespace std;
namespace fs = filesystem;
using namespace fmt;

StatusOr<string> getMandelbrotVersion() {
    // check if $BUILD_WORKSPACE_DIRECTORY is set (running from bazel)
    fs::path version_file;
    if (string bazel_workspace = getenv("BUILD_WORKSPACE_DIRECTORY");
        !bazel_workspace.empty()) {
        version_file =
            StrCat(getenv("BUILD_WORKSPACE_DIRECTORY"), "/.mandelbrotversion");
    } else {
        version_file = ".mandelbrotversion";
    }

    if (!fs::exists(version_file)) {
        return Status(StatusCode::kNotFound,
                      "Mandelbrot version file not found");
    } else {
        ifstream version_stream(version_file);
        string version;
        getline(version_stream, version);
        LOG(INFO) << "Mandelbrot version: " << version;
        return version;
    }
}
