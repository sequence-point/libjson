#ifndef libjson__pointer_hxx_
#define libjson__pointer_hxx_

#include <libjson/exception.hxx>
#include <libjson/read.hxx>
#include <libjson/variant.hxx>

#include <queue>

namespace json {

variant
resolve(variant const& var, std::string const& pointer)
{
  std::queue< std::string > refs;

  for (auto it = std::begin(pointer); it != std::end(pointer);) {
    if ('/' != *it)
      throw invalid_syntax{};

    ++it;

    std::string cref;

    while (it != std::end(pointer) && '/' != *it) {
      switch (*it) {
        case '~':
          ++it; // skip tilde
          if (it == std::end(pointer))
            throw invalid_syntax{};
          else if ('0' == *it)
            cref += '~';
          else if ('1' == *it)
            cref += '/';
          else
            throw invalid_syntax{};
          ++it;
          break;
        default:
          cref += *it;
          ++it;
          break;
      }
    }

    if (!cref.empty())
      refs.push(std::move(cref));
  }

  variant current = var;

  while (!refs.empty()) {
    auto cref = refs.front();
    refs.pop();

    // Check what current is.
    if (current.is_object()) {
      auto o = get< object >(current);
      auto el = o.find(cref);

      if (el == std::end(o))
        throw invalid_object_key{ cref };

      current = el->second;
    }
    else if (current.is_array()) {
      if (cref.size() == 1 && '~' == cref[0])
        throw invalid_array_index{ cref };

      auto i = std::stoul(cref);
      auto a = get< array >(current);

      if (a.size() <= i)
        throw invalid_array_index{ cref };

      current = a[i];
    }
    else {
      throw unexpected_type{};
    }
  }

  return current;
}

inline variant
resolve(std::string const& json, std::string const& pointer)
{
  auto decoded = read(json);
  return resolve(decoded, pointer);
}

} // namespace json

#endif
