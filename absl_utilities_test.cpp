#include "absl_utilities.h"

namespace project_namespace {
namespace {

using ::testing::Eq;
using ::testing::Property;
using ::testing::StrEq;

class MoveOnly {
 public:
  explicit MoveOnly(std::string message) : message_(message) {}
  MoveOnly(const MoveOnly& other) = delete;
  MoveOnly operator=(const MoveOnly) = delete;

  MoveOnly(MoveOnly&& other) = default;
  MoveOnly& operator=(MoveOnly&& other) = default;

  std::string message() const { return this->message_; }

 private:
  std::string message_;
};

class TestFunctionsContainer : public ::testing::Test {
 public:
  absl::Status ReturnOkStatus() {
    return absl::OkStatus();
  }

  absl::Status ReturnNonOkStatus() {
    return absl::InvalidArgumentError("This is not an Ok Status.");
  }

  absl::StatusOr<int> ReturnOkStatusOrWithInt() {
    return 100;
  }

  absl::StatusOr<int> ReturnNonOkStatusOr() {
    return absl::InvalidArgumentError("This is not an Ok StatusOr.");
  }

  absl::StatusOr<MoveOnly> ReturnOkStatusOrWithMoveOnly() {
    return MoveOnly("MoveOnly class");
  }

};

TEST_F(TestFunctionsContainer, IsOkWorksOkAndNonOkStatus) {
  EXPECT_TRUE(IsOk(this->ReturnOkStatus()));
  EXPECT_FALSE(IsOk(this->ReturnNonOkStatus()));
}

TEST_F(TestFunctionsContainer, IsOkWorksForOkAndNonOkStatusOr) {
  EXPECT_TRUE(IsOk(this->ReturnOkStatusOrWithInt()));
  EXPECT_TRUE(IsOk(this->ReturnOkStatusOrWithMoveOnly()));
  EXPECT_FALSE(IsOk(this->ReturnNonOkStatusOr()));
}

// Test macro wrappers of the functions above.
TEST_F(TestFunctionsContainer, ExpectOkMacroWorksForOkAndNonOkStatus) {
  EXPECT_OK(this->ReturnOkStatus());
  EXPECT_NOT_OK(this->ReturnNonOkStatus());
}

TEST_F(TestFunctionsContainer, AssertOkWorksForOkAndNonOkStatus) {
  ASSERT_OK(this->ReturnOkStatus());
  ASSERT_NOT_OK(this->ReturnNonOkStatus());
}

// Test the StatusOr overload.
TEST_F(TestFunctionsContainer, ExpectOkMacroWorksForOkAndNonOkStatusOr) {
  EXPECT_OK(this->ReturnOkStatusOrWithInt());
  EXPECT_OK(this->ReturnOkStatusOrWithMoveOnly());
  EXPECT_NOT_OK(this->ReturnNonOkStatusOr());
}

TEST_F(TestFunctionsContainer, AssertOkWorksForOkAndNonOkStatusOr) {
  ASSERT_OK(this->ReturnOkStatusOrWithInt());
  ASSERT_OK(this->ReturnOkStatusOrWithMoveOnly());
  ASSERT_NOT_OK(this->ReturnNonOkStatusOr());
}

TEST_F(TestFunctionsContainer, AssertOkAndAssignWorks) {
  ASSERT_OK_AND_ASSIGN(number, this->ReturnOkStatusOrWithInt());
  EXPECT_EQ(number, 100);

  ASSERT_OK_AND_ASSIGN(move_only, this->ReturnOkStatusOrWithMoveOnly());
  EXPECT_THAT(move_only.message(), StrEq("MoveOnly class"));
}

TEST_F(TestFunctionsContainer, AssertOkAndValidatesPayload) {
  ASSERT_OK_AND(this->ReturnOkStatusOrWithInt(), Eq(100));
  ASSERT_OK_AND(this->ReturnOkStatusOrWithMoveOnly(),
                Property(&MoveOnly::message, StrEq("MoveOnly class")));
}

}  // namespace
}  // namespace project_namespace 
