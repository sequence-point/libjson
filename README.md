This package contains libjson.

libjson is a JSON header-only library for any standards compliant C++17
compiler.

See the LICENSE file for the distribution conditions.

Questions, bugs, and any other feedback can be sent to
support@sequence-point.se.

## Getting Started

### Using any compiler

Copy the entire directory `./libjson` to a place which is in your
include path. Make sure to also copy `libunicode` too
(https://github.com/sequence-point/libunicode).

### Using `build2`

1. Add the repository to `repositories.manifest`:

	`:`  
	`role: prerequisite`  
	`location: https://github.com/sequence-point/libjson.git##HEAD`

2. Add the dependency to the `manifest`:

	`depends: libjson ^0.1.0-`

3. Update your `buildfile` to link with libjson:

	for a binless library:

	import int_libs += libjson%lib{json}`

	or, if building a library or executable program:

	import imp_libs += libjson%lib{json}`

## Usage

### Basic Example

```cpp
#include <libjson/read.hxx>

int main(int argc, char* argv[])
{
	// Parse JSON.
	auto var = json::read("{ \"name\": \"Jane, Doe\" }");

	// Get object and lookup key name.
	auto dict = var.get< json::object >();
}
```
