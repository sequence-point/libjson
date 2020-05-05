namespace json {

inline variant::variant(bool value) : value_{ value }
{}

inline variant::variant(short int value)
  : value_{ static_cast< long long int >(value) }
{}

inline variant::variant(int value)
  : value_{ static_cast< long long int >(value) }
{}

inline variant::variant(long int value)
  : value_{ static_cast< long long int >(value) }
{}

inline variant::variant(long long int value) : value_{ value }
{}

inline variant::variant(unsigned short int value)
  : value_{ static_cast< unsigned long long int >(value) }
{}

inline variant::variant(unsigned int value)
  : value_{ static_cast< unsigned long long int >(value) }
{}

inline variant::variant(unsigned long int value)
  : value_{ static_cast< unsigned long long int >(value) }
{}

inline variant::variant(unsigned long long int value) : value_{ value }
{}

inline variant::variant(float value)
  : value_{ static_cast< long double >(value) }
{}

inline variant::variant(double value)
  : value_{ static_cast< long double >(value) }
{}

inline variant::variant(long double value) : value_{ value }
{}

inline variant::variant(std::string value) : value_{ value }
{}

inline variant::variant(char const* value) : value_{ std::string{ value } }
{}

inline variant::variant(array value) : value_{ std::move(value) }
{}

inline variant::variant(object value) : value_{ std::move(value) }
{}

inline variant::variant(diagnostics::location location, undefined)
  : location_{ std::move(location) }, value_{ undefined{} }
{}

inline variant::variant(diagnostics::location location, bool value)
  : location_{ std::move(location) }, value_{ value }
{}

inline variant::variant(diagnostics::location location, short int value)
  : location_{ std::move(location) },
    value_{ static_cast< long long int >(value) }
{}

inline variant::variant(diagnostics::location location, int value)
  : location_{ std::move(location) },
    value_{ static_cast< long long int >(value) }
{}

inline variant::variant(diagnostics::location location, long int value)
  : location_{ std::move(location) },
    value_{ static_cast< long long int >(value) }
{}

inline variant::variant(diagnostics::location location, long long int value)
  : location_{ std::move(location) }, value_{ value }
{}

inline variant::variant(diagnostics::location location,
                        unsigned short int value)
  : location_{ std::move(location) },
    value_{ static_cast< unsigned long long int >(value) }
{}

inline variant::variant(diagnostics::location location, unsigned int value)
  : location_{ std::move(location) },
    value_{ static_cast< unsigned long long int >(value) }
{}

inline variant::variant(diagnostics::location location, unsigned long int value)
  : location_{ std::move(location) },
    value_{ static_cast< unsigned long long int >(value) }
{}

inline variant::variant(diagnostics::location location,
                        unsigned long long int value)
  : location_{ std::move(location) }, value_{ value }
{}

inline variant::variant(diagnostics::location location, float value)
  : location_{ std::move(location) },
    value_{ static_cast< long double >(value) }
{}

inline variant::variant(diagnostics::location location, double value)
  : location_{ std::move(location) },
    value_{ static_cast< long double >(value) }
{}

inline variant::variant(diagnostics::location location, long double value)
  : location_{ std::move(location) }, value_{ value }
{}

inline variant::variant(diagnostics::location location, std::string value)
  : location_{ std::move(location) }, value_{ std::move(value) }
{}

inline variant::variant(diagnostics::location location, char const* value)
  : location_{ std::move(location) }, value_{ std::string{ value } }
{}

inline variant::variant(diagnostics::location location, array value)
  : location_{ std::move(location) }, value_{ std::move(value) }
{}

inline variant::variant(diagnostics::location location, object value)
  : location_{ std::move(location) }, value_{ std::move(value) }
{}

inline bool
variant::is_undefined() const
{
  return std::holds_alternative< undefined >(value_);
}

inline bool
variant::is_boolean() const
{
  return std::holds_alternative< bool >(value_);
}

inline bool
variant::is_number() const
{
  return is_signed() || is_unsigned() || is_real();
}

inline bool
variant::is_signed() const
{
  return std::holds_alternative< long long int >(value_);
}

inline bool
variant::is_unsigned() const
{
  return std::holds_alternative< unsigned long long int >(value_);
}

inline bool
variant::is_real() const
{
  return std::holds_alternative< long double >(value_);
}

inline bool
variant::is_string() const
{
  return std::holds_alternative< std::string >(value_);
}

inline bool
variant::is_array() const
{
  return std::holds_alternative< std::vector< variant > >(value_);
}

inline bool
variant::is_object() const
{
  return std::holds_alternative< std::map< std::string, variant > >(value_);
}

inline diagnostics::location const&
variant::location() const
{
  return location_;
}

} // namespace json
