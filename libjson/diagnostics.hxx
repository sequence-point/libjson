#ifndef libjson__diagnostics_hxx_
#define libjson__diagnostics_hxx_

#include <cstdint>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

namespace json {

class diagnostics {
public:
  struct location {
    std::uint32_t line;
    std::uint32_t column;
  };

  std::vector< std::pair< diagnostics::location, std::string > > const&
  warnings() const
  {
    return warnings_;
  }

  std::vector< std::pair< diagnostics::location, std::string > > const&
  errors() const
  {
    return errors_;
  }

  void
  warning(location loc, std::string description)
  {
    warnings_.emplace_back(std::make_pair(loc, description));
  }

  void
  error(location loc, std::string description)
  {
    errors_.emplace_back(std::make_pair(loc, description));
  }

private:
  std::vector< std::pair< location, std::string > > warnings_;
  std::vector< std::pair< location, std::string > > errors_;
};

inline std::ostream&
operator<<(std::ostream& o, diagnostics const& d)
{
  for (auto const& j : d.warnings()) {
    o << "warning: " << j.first.line << ':' << j.first.column << ": "
      << j.second << '\n';
  }

  for (auto const& j : d.errors()) {
    o << "error: " << j.first.line << ':' << j.first.column << ": "
      << j.second << '\n';
  }

  return o;
}

} // namespace json

#endif
