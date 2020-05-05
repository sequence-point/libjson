#ifndef libjson__variant_hxx_
#define libjson__variant_hxx_

#include <libjson/diagnostics.hxx>
#include <libjson/exception.hxx>

#include <map>
#include <string>
#include <variant>
#include <vector>

namespace json {

class variant;

//! Alias for a JSON array.
using array = std::vector< variant >;

//! Alias for a JSON object.
using object = std::map< std::string, variant >;

//! Variant holding any valid JSON value.
class variant {
public:
  //! Type used to denote an undefined variant.
  struct undefined {
  };

  //! Construct an undefined variant.
  variant() = default;

  //! Construct an undefined variant.
  variant(undefined) : value_{ undefined{} }
  {}

  //! Construct a variant holding a boolean value.
  variant(bool value);

  //! Construct a variant holding a signed number.
  variant(short int value);

  //! Construct a variant holding a signed number.
  variant(int value);

  //! Construct a variant holding a signed number.
  variant(long int value);

  //! Construct a variant holding a signed number.
  variant(long long int value);

  //! Construct a variant holding an unsigned number.
  variant(unsigned short int value);

  //! Construct a variant holding an unsigned number.
  variant(unsigned int value);

  //! Construct a variant holding an unsigned number.
  variant(unsigned long int value);

  //! Construct a variant holding an unsigned number.
  variant(unsigned long long int value);

  //! Construct a variant holding a real number.
  variant(float value);

  //! Construct a variant holding a real number.
  variant(double value);

  //! Construct a variant holding a real number.
  variant(long double value);

  //! Construct a variant holding a string.
  variant(std::string value);

  //! Construct a variant holding a string.
  variant(char const* value);

  //! Construct a variant holding an array.
  variant(array value);

  //! Construct a variant holding an object.
  variant(object value);

  variant(diagnostics::location location, undefined);

  variant(diagnostics::location location, bool value);

  variant(diagnostics::location location, short int value);

  variant(diagnostics::location location, int value);

  variant(diagnostics::location location, long int value);

  variant(diagnostics::location location, long long int value);

  variant(diagnostics::location location, unsigned short int value);

  variant(diagnostics::location location, unsigned int value);

  variant(diagnostics::location location, unsigned long int value);

  variant(diagnostics::location location, unsigned long long int value);

  variant(diagnostics::location location, float value);

  variant(diagnostics::location location, double value);

  variant(diagnostics::location location, long double value);

  variant(diagnostics::location location, std::string value);

  variant(diagnostics::location location, char const* value);

  variant(diagnostics::location location, array value);

  variant(diagnostics::location location, object value);

  //! Check if this variant is undefined.
  bool
  is_undefined() const;

  //! Check if this variant holds a boolean.
  bool
  is_boolean() const;

  //! Check if this variant holds a number.
  bool
  is_number() const;

  //! Check if this variant holds a signed value.
  bool
  is_signed() const;

  //! Check if this variant holds an unsigned value.
  bool
  is_unsigned() const;

  //! Check if this variant holds a real value.
  bool
  is_real() const;

  //! Check if this variant holds a string.
  bool
  is_string() const;

  //! Check if this variant holds an array.
  bool
  is_array() const;

  //! Check if this variant holds an object.
  bool
  is_object() const;

  //! Access the inner value.
  template< typename T >
  T
  get() const;

  //! Get the location of this value.
  diagnostics::location const&
  location() const;

  template< typename Visitor >
  friend void
  visit(Visitor&&, variant const& value);

private:
  using variant_type = std::variant< undefined,
                                     bool,
                                     long long int,
                                     unsigned long long int,
                                     long double,
                                     std::string,
                                     std::vector< variant >,
                                     std::map< std::string, variant > >;

  diagnostics::location location_;
  variant_type value_;
};

} // namespace json

#include <libjson/variant.ixx>
#include <libjson/variant.txx>

#endif
