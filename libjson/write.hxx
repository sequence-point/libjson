#ifndef libjson__write_hxx_
#define libjson__write_hxx_

#include <libjson/emitter.hxx>

#include <ostream>
#include <sstream>
#include <string>

namespace json {

class variant;

inline void
write(std::ostream& os, variant const& json)
{
  visit(emitter{ os }, json);
  os << '\n';
}

inline std::string
write(variant const& json)
{
  std::stringstream str;
  write(str, json);
  return str.str();
}

} // namespace json

#endif
