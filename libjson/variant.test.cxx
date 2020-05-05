#include <libunittest/unittest.hxx>

#include <libjson/variant.hxx>

DEFINE_TEST("visit: undefined")
{
  TEST_NOT_IMPLEMENTED;
}

DEFINE_TEST("variant.get< undefined >()")
{
  TEST_THROWS(json::invalid_type, {
    json::variant var;
    var.get< json::variant::undefined >();
  });
}

DEFINE_TEST("variant.get< bool >()")
{
  TEST_DOES_NOT_THROW({
    json::variant var{ false };
    var.get< bool >();
  });
}

DEFINE_TEST("variant.get< string >()")
{
  TEST_DOES_NOT_THROW({
    json::variant var{ "Covfefe" };
    var.get< std::string >();
  });
}
