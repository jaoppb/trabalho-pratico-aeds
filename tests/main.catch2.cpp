#include <catch2/catch_session.hpp>

#include "handlers.hpp"

int main() {
  int result = Catch::Session().run();

  return result;
}