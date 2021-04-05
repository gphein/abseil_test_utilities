#include "absl/status/statusor.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

namespace project_namespace {

template <typename T>
::testing::AssertionResult IsOk(const absl::StatusOr<T>& status_or) {
  if (status_or.ok()) {
    return ::testing::AssertionSuccess();
  } else {
    return ::testing::AssertionFailure() << status_or.status();
  }
}

::testing::AssertionResult IsOk(const absl::Status& status) {
  if (status.ok()) {
    return ::testing::AssertionSuccess();
  } else {
    return ::testing::AssertionFailure() << status;
  }
}

template <typename T>
::testing::AssertionResult IsNotOk(const absl::StatusOr<T>& status_or) {
  if (status_or.ok()) {
    return ::testing::AssertionFailure() << "Expected Non-Ok status";
  } else {
    return ::testing::AssertionSuccess();
  }
}

#define EXPECT_OK(arg) EXPECT_TRUE(IsOk(arg))
#define EXPECT_NOT_OK(arg) EXPECT_FALSE(IsOk(arg))
#define ASSERT_OK(arg) ASSERT_TRUE(IsOk(arg))
#define ASSERT_NOT_OK(arg) ASSERT_FALSE(IsOk(arg))

// TODO: Convert to a template function that sets a failure.
#define ASSERT_OK_AND_ASSIGN(target, arg) \
    auto tmp ## target = std::move(arg); \
    ASSERT_OK(tmp ## target); \
    auto target = std::move(*(tmp ## target)); \

#define ASSERT_OK_AND(arg, ...) ASSERT_OK(arg); EXPECT_THAT(*arg, __VA_ARGS__);

}  // namespace project_namespace 
