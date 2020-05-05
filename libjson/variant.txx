namespace json {

template< typename T >
T
variant::get() const
{
  auto const& var = value_;

  if constexpr (std::is_same_v< bool, T >) {
    if (std::holds_alternative< bool >(var))
      return std::get< bool >(var);

    throw invalid_type{};
  }

  if constexpr (std::is_arithmetic_v< T >) {
    if (std::holds_alternative< long long int >(var))
      return static_cast< T >(std::get< long long int >(var));
    else if (std::holds_alternative< unsigned long long int >(var))
      return static_cast< T >(std::get< unsigned long long int >(var));
    else if (std::holds_alternative< long double >(var))
      return static_cast< T >(std::get< long double >(var));

    throw invalid_type{};
  }

  if constexpr (std::is_convertible_v< std::string, T >) {
    if (std::holds_alternative< std::string >(var))
      return std::get< std::string >(var);

    throw invalid_type{};
  }

  if constexpr (std::is_convertible_v< array, T >) {
    if (std::holds_alternative< array >(var))
      return std::get< array >(var);

    throw invalid_type{};
  }

  if constexpr (std::is_convertible_v< object, T >) {
    if (std::holds_alternative< object >(var))
      return std::get< object >(var);

    throw invalid_type{};
  }

  throw invalid_type{};
}

template< typename T >
T
get(variant const& value)
{
  return value.get< T >();
}

template< typename Visitor >
void
visit(Visitor&& visitor, variant const& value)
{
  std::visit(std::forward< Visitor >(visitor), value.value_);
}

} // namespace json
