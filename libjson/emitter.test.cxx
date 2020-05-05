#include <libjson/emitter.hxx>

#include <libunittest/unittest.hxx>

#include <sstream>

DEFINE_TEST("undefined")
{
  std::stringstream str;
  json::emitter emitter{ str };
  emitter(json::variant::undefined{});

  TEST_EQUAL(str.str(), "null");
}

DEFINE_TEST("boolean: true")
{
  std::stringstream str;
  json::emitter emitter{ str };
  emitter(true);

  TEST_EQUAL(str.str(), "true");
}

DEFINE_TEST("boolean: false")
{
  std::stringstream str;
  json::emitter emitter{ str };
  emitter(false);

  TEST_EQUAL(str.str(), "false");
}

DEFINE_TEST("signed number")
{
  std::stringstream str;
  json::emitter emitter{ str };
  emitter(-10LL);

  TEST_EQUAL(str.str(), "-10");
}

DEFINE_TEST("unsigned number")
{
  std::stringstream str;
  json::emitter emitter{ str };
  emitter(100LL);

  TEST_EQUAL(str.str(), "100");
}

DEFINE_TEST("real number")
{
  std::stringstream str;
  json::emitter emitter{ str };
  emitter(1.2L);

  TEST_EQUAL(str.str(), "1.200000");
}

DEFINE_TEST("string")
{
  std::stringstream str;
  json::emitter emitter{ str };
  emitter(std::string{ "hello" });

  TEST_EQUAL(str.str(), "\"hello\"");
}

DEFINE_TEST("array: []")
{
  std::stringstream str;
  json::emitter emitter{ str };
  emitter(std::vector< json::variant >{});

  TEST_EQUAL(str.str(), "[]");
}

DEFINE_TEST("array: [null]")
{
  std::stringstream str;
  json::emitter emitter{ str };

  emitter(std::vector< json::variant >{ json::variant{} });

  TEST_EQUAL(str.str(), "[\n  null\n]");
}

DEFINE_TEST("object: {}")
{
  std::stringstream str;
  json::emitter emitter{ str };

  emitter(std::map< std::string, json::variant >{});

  TEST_EQUAL(str.str(), "{}");
}

DEFINE_TEST("object: {...}")
{
  std::stringstream str;
  json::emitter emitter{ str };

  emitter(std::map< std::string, json::variant >{ { "", {} } });

  TEST_EQUAL(str.str(), "{\n  \"\": null\n}");
}
