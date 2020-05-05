#ifndef libjson__exception_hxx_
#define libjson__exception_hxx_

#include <libjson/diagnostics.hxx>

#include <sstream>
#include <stdexcept>
#include <string>

namespace json {

/// Exception-class used to indicated invalid JSON.
class invalid_json : public std::runtime_error {
public:
  invalid_json(diagnostics::location const& loc, std::string const& what)
    : location_{ loc }, std::runtime_error{ make_error_string(loc, what) }
  {}

  diagnostics::location const&
  location() const
  {
    return location_;
  }

  static std::string
  make_error_string(diagnostics::location const& loc, std::string const& what)
  {
    std::ostringstream str;
    str << loc.column << " " << loc.line << ": " << what;
    return str.str();
  }

private:
  diagnostics::location location_;
};

/// Exception-class used to indicate an invalid type.
class invalid_type : public std::runtime_error {
public:
  invalid_type() : std::runtime_error{ "invalid type" }
  {}
};

/// Exception class used to indicate invalid JSON pointer syntax.
class invalid_syntax : public std::runtime_error {
public:
  invalid_syntax() : std::runtime_error{ "invalid syntax" }
  {}
};

/// Exception class used to indicate an unexpected JSON type.
class unexpected_type : public std::runtime_error {
public:
  unexpected_type() : std::runtime_error{ "unexpected JSON type" }
  {}
};

/// Exception-class used to indicate an object key.
class invalid_object_key : public std::runtime_error {
public:
  explicit invalid_object_key(std::string const& key)
    : std::runtime_error{ "invalid key '" + key + "'" }
  {}
};

/// Exception-class used to indicate an invalid array index.
class invalid_array_index : public std::runtime_error {
public:
  explicit invalid_array_index(std::string const& index)
    : std::runtime_error{ "invalid key '" + index + "'" }
  {}
};

} // namespace json

#endif
