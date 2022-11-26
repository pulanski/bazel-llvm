
#include "mandelbrot/src/source_buffer/source_buffer.h"

#include <gtest/gtest.h>

#include <fstream>

#include "absl/status/statusor.h"

namespace Mandelbrot {

fs::path createTestFile(string_view source_text) {
    fs::path test_file_path =
        fs::temp_directory_path() / "kaleidoscope_source_buffer_test_file.txt";
    ofstream test_file_stream(test_file_path);
    test_file_stream << source_text;
    test_file_stream.close();

    return test_file_path;
}

TEST(SourceBufferTest, CreateFromFile) {
    fs::path test_file_path = createTestFile("Hello World");
    StatusOr<unique_ptr<SourceBuffer>> expected_buffer =
        SourceBufferFactory::createFromFile(test_file_path.string());

    ASSERT_TRUE(expected_buffer.ok());
    ASSERT_EQ(expected_buffer->get()->filePath(), test_file_path);
    ASSERT_EQ(expected_buffer->get()->contents(), "Hello World");
}

TEST(SourceBufferTest, CreateFromSourceText) {
    StatusOr<unique_ptr<SourceBuffer>> expected_buffer =
        SourceBufferFactory::createFromSourceText("Hello World");

    ASSERT_TRUE(expected_buffer.ok());
    ASSERT_EQ(expected_buffer->get()->filePath(), nullopt);
    ASSERT_EQ(expected_buffer->get()->contents(), "Hello World");
}

}  // namespace Mandelbrot
