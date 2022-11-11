#include "greeting.h"

#include "gtest/gtest.h"

namespace greeting {

TEST(GreetingTest, GetGreet) {
    EXPECT_EQ(get_greeting("Bazel"),
              "Looking up whether 'Bazel' is a valid word");
}

}  // namespace greeting
