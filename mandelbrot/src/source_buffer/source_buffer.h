#pragma once

#include <filesystem>
#include <optional>
#include <string>

#include "absl/status/statusor.h"

using namespace absl;
using namespace std;
namespace fs = filesystem;
using namespace fs;

namespace Mandelbrot {

/// A `SourceBuffer` represents a buffer of source code that is being parsed.
/// It can be created from either a `file` or from a `string` of source code.
class SourceBuffer {
   private:
    optional<fs::path> path_;
    string buffer_contents_;

   public:
    friend class SourceBufferFactory;
    // TODO change to private constructor with factory
    SourceBuffer(string_view source);
    SourceBuffer(const fs::path& path, string_view source);

    // SourceBuffer() = delete;
    ~SourceBuffer() = default;

    /// Returns the path of the file that this `SourceBuffer` was created from.
    const optional<fs::path>& filePath() const;

    /// Returns the source code contents of the `SourceBuffer`.
    string_view contents() const;
};

/// Factory class for creating `SourceBuffers`.
/// Used to hide the implementation of the `SourceBuffer` class
/// and to provide a single point of entry for creating `SourceBuffers`
/// from different sources.
class SourceBufferFactory {
    friend class SourceBuffer;

   public:
    /// Creates a `SourceBuffer` from a file.
    static StatusOr<unique_ptr<SourceBuffer>> createFromFile(
        string_view filename);

    /// Creates a `SourceBuffer` from a string of source code.
    static StatusOr<unique_ptr<SourceBuffer>> createFromSourceText(
        string_view source);
};

}  // namespace Mandelbrot
