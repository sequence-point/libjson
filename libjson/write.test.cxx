#include <libjson/variant.hxx>
#include <libjson/write.hxx>

#include <libunittest/unittest.hxx>

#include <sstream>

DEFINE_TEST("write")
{
  auto document = json::object{ { { "title", "Coca-Cola Regular 1.5L" },
                                  { "gtin13", "5449000139306" } } };

  std::stringstream output;
  json::write(output, document);

  TEST_EQUAL(output.str(), R"({
  "gtin13": "5449000139306",
  "title": "Coca-Cola Regular 1.5L"
})");
}
