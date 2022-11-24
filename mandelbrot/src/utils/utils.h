#pragma once

#include "absl/status/statusor.h"

using namespace std;
using namespace absl;

StatusOr<string> getMandelbrotVersion();
