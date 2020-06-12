#ifndef libjson__read_hxx_
#define libjson__read_hxx_

#include <libjson/optional.hxx>
#include <libjson/parser.hxx>
#include <libjson/variant.hxx>

#include <istream>
#include <iterator>

namespace json {

inline variant
read(std::string const& input)
{
  diagnostics d;

  auto first = input.begin();
  return parser{}.parse(d, first, input.end());
}

inline variant
read(diagnostics& d, std::string const& input)
{
  auto first = input.begin();
  return parser{}.parse(d, first, input.end());
}

inline optional< variant >
try_read(diagnostics& d, std::string const& input)
{
  auto first = input.begin();
  return parser{}.try_parse(d, first, input.end());
}

inline optional< variant >
try_read(std::string const& input)
{
  diagnostics d;

  auto first = input.begin();
  return parser{}.try_parse(d, first, input.end());
}

inline variant
read(diagnostics& d, std::istream& input)
{
  input.unsetf(std::istream::skipws);

  std::istreambuf_iterator< char > first{ input };
  return parser{}.parse(d, first, std::istreambuf_iterator< char >{});
}

inline variant
read(std::istream& input)
{
  diagnostics d;
  return read(d, input);
}

inline optional< variant >
try_read(std::istream& input)
{
  input.unsetf(std::istream::skipws);

  diagnostics d;

  std::istreambuf_iterator< char > first{ input };
  return parser{}.try_parse(d, first, std::istreambuf_iterator< char >{});
}

} // namespace json

#endif
