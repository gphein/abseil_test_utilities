cc_library(
  visibility = ["//visibility:public"],
  name = 'absl_utilities',
  hdrs = ['absl_utilities.h'],
  testonly = True,
  deps = [
    '@google_absl//absl/status:statusor',
    '@gtest//:gtest', 
    '@gtest//:gtest_main', 
  ]
)

cc_test(
  name = 'absl_utilities_test',
  srcs = ['absl_utilities_test.cpp'],
  deps = [
    ':absl_utilities',
  ]
)
