#pragma once

#include <string>
#include <vector>

#include "absl/status/status.h"

using namespace absl;
using namespace std;

Status replMainLoop();

Status compileFiles(vector<string> files);
