#include "source_buffer.h"

#include <fstream>

namespace Mandelbrot {
SourceBuffer::SourceBuffer(string_view source)
    : path_(nullopt), buffer_contents_(source) {}

SourceBuffer::SourceBuffer(const fs::path& path, string_view source)
    : path_(path), buffer_contents_(source) {}

const optional<fs::path>& SourceBuffer::filePath() const { return path_; }

string_view SourceBuffer::contents() const { return buffer_contents_; }

StatusOr<unique_ptr<SourceBuffer>> SourceBufferFactory::createFromFile(
    string_view filename) {
    std::filesystem::path file_path(filename);
    if (!exists(file_path)) {
        return Status(StatusCode::kNotFound, "File not found");
    } else {
        ifstream file_stream(file_path);
        string file_contents((istreambuf_iterator<char>(file_stream)),
                             istreambuf_iterator<char>());

        return make_unique<SourceBuffer>(file_path, file_contents);
    }
}

StatusOr<unique_ptr<SourceBuffer>> SourceBufferFactory::createFromSourceText(
    string_view source) {
    return make_unique<SourceBuffer>(source);
}

}  // namespace Mandelbrot
