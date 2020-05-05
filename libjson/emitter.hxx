#ifndef libjson__emitter_hxx_
#define libjson__emitter_hxx_

#include <libjson/variant.hxx>

#include <ostream>
#include <stack>

namespace json {

class emitter {
public:
  explicit emitter(std::ostream& output);

  std::ostream&
  output();

  void
  operator()(variant::undefined const& value);

  void
  operator()(bool const& value);

  void
  operator()(long long int const& value);

  void
  operator()(unsigned long long int const& value);

  void
  operator()(long double const& value);

  void
  operator()(std::string const& value);

  void
  operator()(std::vector< variant > const& value);

  void
  operator()(std::map< std::string, variant > const& value);

private:
  void
  do_indent();

  std::ostream& output_;
  std::size_t indent_{ 0 };
};

} // namespace json

#include <libjson/emitter.ixx>

#endif
