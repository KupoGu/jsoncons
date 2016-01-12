# jsoncons: a C++ library for json construction

jsoncons is a C++ library for the construction of [JavaScript Object Notation (JSON)](http://www.json.org). It supports parsing a JSON file or string into a tree structured `json` value, building a `json` value in C++ code, and serializing a `json` value to a file or string. It also provides an event-based API for reading and writing JSON documents that are too large to fit into available memory, somewhat analogously to SAX processing in the XML world. Consult the wiki for the latest [documentation and tutorials](https://github.com/danielaparker/jsoncons/wiki) and [roadmap](https://github.com/danielaparker/jsoncons/wiki/Roadmap). 

jsoncons uses some features that are new to C++ 11, particularly move semantics, however, it has been written to be compatible with VC++ 10 SP1 (note that SP1 is required for VC++ 10, it fixes compiler bugs with move semantics.) It has been tested with MS Visual C++ 10 SP1, Intel C++ Studio XE 2013, clang 3.3 and GCC 4.8. 

The [code repository](https://github.com/danielaparker/jsoncons) and [releases](https://github.com/danielaparker/jsoncons/releases) are on github. It is distributed under the [Boost Software License](http://www.boost.org/users/license.html)

The library has a number of features, which are listed below:

- Uses the standard C++ input/output streams library
- Implements parsing and serializing JSON text in UTF-8 for narrow character strings and streams
- Supports UTF16 (UTF32) encodings with size 2 (size 4) wide characters
- Correctly handles surrogate pairs in \uXXXX escape sequences
- Supports event based JSON parsing and serializing with user defined input and output handlers
- Accepts and ignores single line comments that start with //, and multi line comments that start with /* and end with */
- Supports optional escaping of the solidus (/) character
- Supports Nan, Inf and -Inf replacement
- Supports reading a sequence of JSON texts from a stream
- Supports optional escaping of non-ascii UTF-8 octets
- Allows extensions to the types accepted by the json class accessors and modifiers
- Supports storing "any" values in a json object or array, with specialized serialization
- Supports reading (writing) JSON values from (to) CSV files
- Passes all tests from [JSON_checker](http://www.json.org/JSON_checker/) except `fail1.json`, which is allowed in [RFC7159](http://www.ietf.org/rfc/rfc7159.txt)
- Handles JSON texts of arbitrarily large depth of nesting, a limit can be set if desired
- Supports [Stefan Goessner's JsonPath](http://goessner.net/articles/JsonPath/)

## What's new on master

New features

- Supports [Stefan Goessner's JsonPath](http://goessner.net/articles/JsonPath/). See example below and [documentation](https://github.com/danielaparker/jsoncons/wiki/json_query).
- json member function `find` added
- json member function `count` added
- json array range accessor `elements()` added, which supports range-based for loops over json arrays, and replaces `begin_elements` and `end_elements`
- json object range accessor `members()` added, which supports range-based for loops over json objects, and replaces `begin_members` and `end_members`

API Changes 
- The json internal representation of signed and unsigned integers has been changed from `long long` and `unsigned long long` to `int64_t` and `uint64_t`.
  This should not impact you unless you've implemented your own `json_input_handler` or `json_output_handler`, refer to the Changelog for more details.
- `output_format` drops support for `floatfield` property

Non-beaking API Changes
- `json::parse_string` has been renamed to `json::parse`, `parse_string` is deprecated but still works
- `json member function `is_empty` has been renamed to `empty`, `is_empty` is deprecated but still works. Rationale: consistency with C++ containers
- json member functions `begin_elements` and `end_elements` have been deprecated, instead use `elements().begin()` and `elements.end()`
- json member functions `begin_members` and `end_members` have been deprecated, instead use `members().begin()` and `members.end()`
- json member function `has_member` has been deprecated, instead use `count`. Rationale: consistency with C++ containers
- json member function `get` that takes one parameter, a `name`, and returns a json null if not found, has been deprecated, use instead the version of `get` that takes the default as a second parameter.

## Benchmarks

[json_benchmarks](https://github.com/danielaparker/json_benchmarks) provides some measurements about how `jsoncons` compares to other `json` libraries.

## Using the jsoncons library

The jsoncons library is header-only: it consists solely of header files containing templates and inline functions, and requires no separately-compiled library binaries when linking. It has no dependence on other libraries. The accompanying test suite uses boost, but not the library itself.

To install the jsoncons library, download the zip file, unpack the release, under `src` find the directory `jsoncons`, and copy it to your `include` directory. If you wish to use extensions, copy the `jsoncons_ext` directory as well. 

For a quick guide, see the article [jsoncons: a C++ library for json construction](http://danielaparker.github.io/jsoncons).

### Acknowledgements

Special thanks to our [contributors](https://github.com/danielaparker/jsoncons/blob/master/acknowledgements.txt)

