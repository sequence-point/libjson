#include <libjson/parser.hxx>
#include <libjson/read.hxx>

#include <libunittest/unittest.hxx>

DEFINE_TEST("boolean: parse false")
{
  std::string const text{ "false" };

  json::diagnostics diag;
  auto var = json::read(diag, text);

  TEST_EQUAL(diag.errors().size(), 0);
  TEST_EQUAL(diag.warnings().size(), 0);

  TEST_TRUE(var.is_boolean());
  TEST_EQUAL(var.get< bool >(), false);
  TEST_EQUAL(var.location().line, 1);
  TEST_EQUAL(var.location().column, 1);
}

DEFINE_TEST("boolean: parse false, with whitespace")
{
  std::string const text{ " false " };

  json::diagnostics diag;
  auto var = json::read(diag, text);

  TEST_EQUAL(diag.errors().size(), 0);
  TEST_EQUAL(diag.warnings().size(), 0);

  TEST_TRUE(var.is_boolean());
  TEST_EQUAL(var.get< bool >(), false);
  TEST_EQUAL(var.location().line, 1);
  TEST_EQUAL(var.location().column, 2);
}

DEFINE_TEST("boolean: parse true")
{
  std::string const text{ "true" };

  json::diagnostics diag;
  auto var = json::read(diag, text);

  TEST_EQUAL(diag.errors().size(), 0);
  TEST_EQUAL(diag.warnings().size(), 0);

  TEST_TRUE(var.is_boolean());
  TEST_EQUAL(var.get< bool >(), true);
}

DEFINE_TEST("boolean: parse true, with whitespace")
{
  std::string const text{ " true " };

  json::diagnostics diag;
  auto var = json::read(diag, text);

  TEST_EQUAL(diag.errors().size(), 0);
  TEST_EQUAL(diag.warnings().size(), 0);

  TEST_TRUE(var.is_boolean());
  TEST_EQUAL(var.get< bool >(), true);
  TEST_EQUAL(var.location().line, 1);
  TEST_EQUAL(var.location().column, 2);
}

DEFINE_TEST("null: parse null")
{
  std::string const text{ "null" };

  json::diagnostics diag;
  auto var = json::read(diag, text);

  TEST_EQUAL(diag.errors().size(), 0);
  TEST_EQUAL(diag.warnings().size(), 0);

  TEST_TRUE(var.is_undefined());
  TEST_EQUAL(var.location().line, 1);
  TEST_EQUAL(var.location().column, 1);
}

DEFINE_TEST("null: parse null, with whitespace")
{
  std::string const text{ "  null  " };

  json::diagnostics diag;
  auto var = json::read(diag, text);

  TEST_EQUAL(diag.errors().size(), 0);
  TEST_EQUAL(diag.warnings().size(), 0);

  TEST_TRUE(var.is_undefined());
  TEST_EQUAL(var.location().line, 1);
  TEST_EQUAL(var.location().column, 3);
}

DEFINE_TEST("array: parse empty")
{
  std::string const text{ "[]" };

  json::diagnostics diag;
  auto var = json::read(diag, text);

  TEST_EQUAL(diag.errors().size(), 0);
  TEST_EQUAL(diag.warnings().size(), 0);

  TEST_TRUE(var.is_array());
  TEST_TRUE(var.get< json::array >().empty());
  TEST_EQUAL(var.location().line, 1);
  TEST_EQUAL(var.location().column, 1);
}

DEFINE_TEST("array: parse empty, with whitespace")
{
  std::string const text{ " [ ] " };

  json::diagnostics diag;
  auto var = json::read(diag, text);

  TEST_EQUAL(diag.errors().size(), 0);
  TEST_EQUAL(diag.warnings().size(), 0);

  TEST_TRUE(var.is_array());
  TEST_TRUE(var.get< json::array >().empty());
  TEST_EQUAL(var.location().line, 1);
  TEST_EQUAL(var.location().column, 2);
}

DEFINE_TEST("array: parse null element")
{
  std::string const text{ "[null]" };

  json::diagnostics diag;
  auto var = json::read(diag, text);

  TEST_EQUAL(diag.errors().size(), 0);
  TEST_EQUAL(diag.warnings().size(), 0);

  TEST_TRUE(var.is_array());
  TEST_EQUAL(var.location().line, 1);
  TEST_EQUAL(var.location().column, 1);
  TEST_FALSE(var.get< json::array >().empty());
  TEST_EQUAL(var.get< json::array >().size(), 1);
  TEST_TRUE(var.get< json::array >()[0].is_undefined());
  TEST_EQUAL(var.get< json::array >()[0].location().line, 1);
  TEST_EQUAL(var.get< json::array >()[0].location().column, 2);
}

DEFINE_TEST("array: parse null element, with whitespace")
{
  std::string const text{ " [ null ] " };

  json::diagnostics diag;
  auto var = json::read(diag, text);

  TEST_EQUAL(diag.errors().size(), 0);
  TEST_EQUAL(diag.warnings().size(), 0);

  TEST_TRUE(var.is_array());
  TEST_FALSE(var.get< json::array >().empty());
  TEST_EQUAL(var.get< json::array >().size(), 1);

  TEST_TRUE(var.get< json::array >()[0].is_undefined());
  TEST_EQUAL(var.get< json::array >()[0].location().line, 1);
  TEST_EQUAL(var.get< json::array >()[0].location().column, 4);
}

DEFINE_TEST("array: parse double null elements")
{
  std::string const text{ "[null,null]" };

  json::diagnostics diag;
  auto var = json::read(diag, text);

  TEST_EQUAL(diag.errors().size(), 0);
  TEST_EQUAL(diag.warnings().size(), 0);

  TEST_TRUE(var.is_array());
  TEST_FALSE(var.get< json::array >().empty());
  TEST_EQUAL(var.get< json::array >().size(), 2);

  TEST_TRUE(var.get< json::array >()[0].is_undefined());
  TEST_EQUAL(var.get< json::array >()[0].location().line, 1);
  TEST_EQUAL(var.get< json::array >()[0].location().column, 2);

  TEST_TRUE(var.get< json::array >()[1].is_undefined());
  TEST_EQUAL(var.get< json::array >()[1].location().line, 1);
  TEST_EQUAL(var.get< json::array >()[1].location().column, 7);
}

DEFINE_TEST("array: parse double null elements, with whitespace")
{
  std::string const text{ " [ null , null ] " };

  json::diagnostics diag;
  auto var = json::read(diag, text);

  TEST_EQUAL(diag.errors().size(), 0);
  TEST_EQUAL(diag.warnings().size(), 0);

  TEST_TRUE(var.is_array());
  TEST_FALSE(var.get< json::array >().empty());
  TEST_EQUAL(var.get< json::array >().size(), 2);

  TEST_TRUE(var.get< json::array >()[0].is_undefined());
  TEST_EQUAL(var.get< json::array >()[0].location().line, 1);
  TEST_EQUAL(var.get< json::array >()[0].location().column, 4);

  TEST_TRUE(var.get< json::array >()[1].is_undefined());
  TEST_EQUAL(var.get< json::array >()[1].location().line, 1);
  TEST_EQUAL(var.get< json::array >()[1].location().column, 11);
}

DEFINE_TEST("array: parse nested")
{
  std::string const text{ " [ [ null , null ] , [ null ] ]" };

  json::diagnostics diag;
  auto var = json::read(diag, text);

  TEST_EQUAL(diag.errors().size(), 0);
  TEST_EQUAL(diag.warnings().size(), 0);

  TEST_TRUE(var.is_array());
  TEST_FALSE(var.get< json::array >().empty());
  TEST_EQUAL(var.get< json::array >().size(), 2);

  TEST_TRUE(var.get< json::array >()[0].is_array());
  TEST_FALSE(var.get< json::array >()[0].get< json::array >().empty());
  TEST_EQUAL(var.get< json::array >()[0].get< json::array >().size(), 2);
  TEST_TRUE(var.get< json::array >()[0].get< json::array >()[0].is_undefined());
  TEST_TRUE(var.get< json::array >()[0].get< json::array >()[1].is_undefined());

  TEST_TRUE(var.get< json::array >()[1].is_array());
  TEST_FALSE(var.get< json::array >()[1].get< json::array >().empty());
  TEST_EQUAL(var.get< json::array >()[1].get< json::array >().size(), 1);
  TEST_TRUE(var.get< json::array >()[1].get< json::array >()[0].is_undefined());
}

DEFINE_TEST("object: parse empty")
{
  std::string const text{ "{}" };

  json::diagnostics diag;
  auto var = json::read(diag, text);

  TEST_EQUAL(diag.errors().size(), 0);
  TEST_EQUAL(diag.warnings().size(), 0);

  TEST_TRUE(var.is_object());
  TEST_TRUE(var.get< json::object >().empty());
}

DEFINE_TEST("object: parse empty, with whitespace")
{
  std::string const text{ " { } " };

  json::diagnostics diag;
  auto var = json::read(diag, text);

  TEST_EQUAL(diag.errors().size(), 0);
  TEST_EQUAL(diag.warnings().size(), 0);

  TEST_TRUE(var.is_object());
  TEST_TRUE(var.get< json::object >().empty());
}

DEFINE_TEST("object: parse 1-element object")
{
  std::string const text{ "{\"key\":null}" };

  json::diagnostics diag;
  auto var = json::read(diag, text);

  TEST_EQUAL(diag.errors().size(), 0);
  TEST_EQUAL(diag.warnings().size(), 0);

  TEST_TRUE(var.is_object());
  TEST_FALSE(var.get< json::object >().empty());
  TEST_EQUAL(var.get< json::object >().size(), 1UL);

  TEST_TRUE(var.get< json::object >().at("key").is_undefined());
}

DEFINE_TEST("object: parse 1-element object (with whitespace)")
{
  std::string const text{ " { \"key\" : null } " };

  json::diagnostics diag;
  auto var = json::read(diag, text);

  TEST_EQUAL(diag.errors().size(), 0);
  TEST_EQUAL(diag.warnings().size(), 0);

  TEST_TRUE(var.is_object());
  TEST_FALSE(var.get< json::object >().empty());
  TEST_EQUAL(var.get< json::object >().size(), 1UL);

  TEST_TRUE(var.get< json::object >().at("key").is_undefined());
}

DEFINE_TEST("object: parse 2-element object")
{
  std::string const text{ "{\"key1\":null,\"key2\":null}" };

  json::diagnostics diag;
  auto var = json::read(diag, text);

  TEST_EQUAL(diag.errors().size(), 0);
  TEST_EQUAL(diag.warnings().size(), 0);

  TEST_TRUE(var.is_object());
  TEST_FALSE(var.get< json::object >().empty());
  TEST_EQUAL(var.get< json::object >().size(), 2UL);

  TEST_TRUE(var.get< json::object >().at("key1").is_undefined());
  TEST_TRUE(var.get< json::object >().at("key2").is_undefined());
}

DEFINE_TEST("object: parse 2-element object (with whitespace)")
{
  std::string const text{ " { \"key1\" : null, \"key2\" : null } " };

  json::diagnostics diag;
  auto var = json::read(diag, text);

  TEST_EQUAL(diag.errors().size(), 0);
  TEST_EQUAL(diag.warnings().size(), 0);

  TEST_TRUE(var.is_object());
  TEST_FALSE(var.get< json::object >().empty());
  TEST_EQUAL(var.get< json::object >().size(), 2UL);

  TEST_TRUE(var.get< json::object >().at("key1").is_undefined());
  TEST_TRUE(var.get< json::object >().at("key2").is_undefined());
}

DEFINE_TEST("object: parse nested object")
{
  std::string const text{ R"#({
    "k1": {
      "k1": null
    },
    "k2": {
      "k1": null,
      "k2": null
    }
  })#" };

  json::diagnostics diag;
  auto var = json::read(diag, text);

  TEST_EQUAL(diag.errors().size(), 0);
  TEST_EQUAL(diag.warnings().size(), 0);

  TEST_TRUE(var.is_object());
  TEST_FALSE(var.get< json::object >().empty());
  TEST_EQUAL(var.get< json::object >().size(), 2UL);

  // Nested object 1.
  auto object1 = var.get< json::object >().at("k1");
  TEST_TRUE(object1.is_object());
  TEST_EQUAL(object1.get< json::object >().size(), 1UL);
  TEST_TRUE(object1.get< json::object >().at("k1").is_undefined());

  // Nested object 2.
  auto object2 = var.get< json::object >().at("k2");
  TEST_TRUE(object2.is_object());
  TEST_EQUAL(object2.get< json::object >().size(), 2UL);
  TEST_TRUE(object2.get< json::object >().at("k1").is_undefined());
  TEST_TRUE(object2.get< json::object >().at("k2").is_undefined());
}

DEFINE_TEST("number: integer: 0")
{
  std::string const text{ "0" };

  json::diagnostics diag;
  auto var = json::read(diag, text);

  TEST_EQUAL(diag.errors().size(), 0);
  TEST_EQUAL(diag.warnings().size(), 0);

  TEST_FALSE(var.is_signed());
  TEST_TRUE(var.is_unsigned());
  TEST_EQUAL(var.get< unsigned long long >(), 0);
}

DEFINE_TEST("number: integer: 1")
{
  std::string const text{ "1" };

  json::diagnostics diag;
  auto var = json::read(diag, text);

  TEST_EQUAL(diag.errors().size(), 0);
  TEST_EQUAL(diag.warnings().size(), 0);

  TEST_FALSE(var.is_signed());
  TEST_TRUE(var.is_unsigned());
  TEST_EQUAL(var.get< unsigned long long >(), 1);
}

DEFINE_TEST("number: integer: -1")
{
  std::string const text{ "-1" };

  json::diagnostics diag;
  auto var = json::read(diag, text);

  TEST_EQUAL(diag.errors().size(), 0);
  TEST_EQUAL(diag.warnings().size(), 0);

  TEST_TRUE(var.is_signed());
  TEST_FALSE(var.is_unsigned());
  TEST_EQUAL(var.get< long long >(), -1);
}

DEFINE_TEST("number: integer: 18446744073709551615")
{
  std::string const text{ "18446744073709551615" };
  json::diagnostics diag;
  auto var = json::read(diag, text);

  TEST_EQUAL(diag.errors().size(), 0);
  TEST_EQUAL(diag.warnings().size(), 0);

  TEST_TRUE(var.is_unsigned());
  TEST_FALSE(var.is_signed());
  TEST_EQUAL(var.get< unsigned long long >(), 18446744073709551615ULL);
}

DEFINE_TEST("number: real: 0.0")
{
  std::string const text{ "0.0" };

  json::diagnostics diag;
  auto var = json::read(diag, text);

  TEST_EQUAL(diag.errors().size(), 0);
  TEST_EQUAL(diag.warnings().size(), 0);

  TEST_TRUE(var.is_real());
  TEST_EQUAL(var.get< double >(), 0.0);
}

DEFINE_TEST("number: real: 1.0")
{
  std::string const text{ "1.0" };

  json::diagnostics diag;
  auto var = json::read(diag, text);

  TEST_EQUAL(diag.errors().size(), 0);
  TEST_EQUAL(diag.warnings().size(), 0);

  TEST_TRUE(var.is_real());
  TEST_EQUAL(var.get< double >(), 1.0);
}

DEFINE_TEST("number: real: 1e3")
{
  std::string const text{ "1e3" };

  json::diagnostics diag;
  auto var = json::read(diag, text);

  TEST_EQUAL(diag.errors().size(), 0);
  TEST_EQUAL(diag.warnings().size(), 0);

  TEST_TRUE(var.is_real());
  TEST_EQUAL(var.get< double >(), 1000.0);
}

DEFINE_TEST("number: real: 1E3")
{
  std::string const text{ "1E3" };

  json::diagnostics diag;
  auto var = json::read(diag, text);

  TEST_EQUAL(diag.errors().size(), 0);
  TEST_EQUAL(diag.warnings().size(), 0);

  TEST_TRUE(var.is_real());
  TEST_EQUAL(var.get< double >(), 1000.0);
}

DEFINE_TEST("number: real: 1e+3")
{
  std::string const text{ "1e+3" };

  json::diagnostics diag;
  auto var = json::read(diag, text);

  TEST_EQUAL(diag.errors().size(), 0);
  TEST_EQUAL(diag.warnings().size(), 0);

  TEST_TRUE(var.is_real());
  TEST_EQUAL(var.get< double >(), 1000.0);
}

DEFINE_TEST("number: real: 1E+3")
{
  std::string const text{ "1E+3" };

  json::diagnostics diag;
  auto var = json::read(diag, text);

  TEST_EQUAL(diag.errors().size(), 0);
  TEST_EQUAL(diag.warnings().size(), 0);

  TEST_TRUE(var.is_real());
  TEST_EQUAL(var.get< double >(), 1000.0);
}

DEFINE_TEST("number: real: 1e-3")
{
  std::string const text{ "1e-3" };

  json::diagnostics diag;
  auto var = json::read(diag, text);

  TEST_EQUAL(diag.errors().size(), 0);
  TEST_EQUAL(diag.warnings().size(), 0);

  TEST_TRUE(var.is_real());
  TEST_EQUAL(var.get< double >(), 0.001);
}

DEFINE_TEST("number: real: 1E-3")
{
  std::string const text{ "1E-3" };

  json::diagnostics diag;
  auto var = json::read(diag, text);

  TEST_EQUAL(diag.errors().size(), 0);
  TEST_EQUAL(diag.warnings().size(), 0);

  TEST_TRUE(var.is_real());
  TEST_EQUAL(var.get< double >(), 0.001);
}

DEFINE_TEST("string: empty string")
{
  json::diagnostics diag;
  auto var = json::read(R"("")");

  TEST_EQUAL(diag.errors().size(), 0);
  TEST_EQUAL(diag.warnings().size(), 0);

  TEST_TRUE(var.is_string());
  TEST_EQUAL(var.get< std::string >(), "");
}

DEFINE_TEST("string: escape sequences")
{
  std::pair< std::string, std::string > escapes[] = {
    { R"("\"")", "\x22" }, // " (quotation mark)
    { R"("\\")", "\x5C" }, // \ (reverse solidus)
    { R"("\/")", "\x2F" }, // / (solidus)
    { R"("\b")", "\x62" }, // b (backspace)
    { R"("\f")", "\x66" }, // f (form feed)
    { R"("\n")", "\x6E" }, // n (line feed)
    { R"("\r")", "\x72" }, // r (carriage return)
    { R"("\t")", "\x74" } // t (tab)
  };

  for (auto const& esc : escapes) {
    json::diagnostics diag;
    auto var = json::read(esc.first);

    TEST_EQUAL(diag.errors().size(), 0);
    TEST_EQUAL(diag.warnings().size(), 0);

    TEST_TRUE(var.is_string());
    TEST_EQUAL(var.get< std::string >(), esc.second);
  }
}

DEFINE_TEST("string: utf-16 escape sequences")
{
  std::pair< std::string, std::string > escapes[]{
    { R"("{\ud834\udd1e}")", "{\xf0\x9d\x84\x9e}" }, // MUSICAL SYMBOL G CLEF
  };

  for (auto const& escape : escapes) {
    std::string text = escape.first;

    json::diagnostics diag;
    auto var = json::read(diag, text);

    TEST_EQUAL(diag.errors().size(), 0);
    TEST_EQUAL(diag.warnings().size(), 0);

    TEST_TRUE(var.is_string());
    TEST_EQUAL(var.get< std::string >(), escape.second);
  }
}
