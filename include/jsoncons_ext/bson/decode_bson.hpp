// Copyright 2013 Daniel Parker
// Distributed under the Boost license, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// See https://github.com/danielaparker/jsoncons for latest version

#ifndef JSONCONS_BSON_DECODE_BSON_HPP
#define JSONCONS_BSON_DECODE_BSON_HPP

#include <string>
#include <vector>
#include <memory>
#include <type_traits> // std::enable_if
#include <istream> // std::basic_istream
#include <jsoncons/json.hpp>
#include <jsoncons/config/jsoncons_config.hpp>
#include <jsoncons_ext/bson/bson_reader.hpp>
#include <jsoncons_ext/bson/bson_cursor.hpp>

namespace jsoncons { 
namespace bson {

    template<class T>
    typename std::enable_if<is_basic_json_class<T>::value,T>::type 
    decode_bson(const std::vector<uint8_t>& v)
    {
        jsoncons::json_decoder<T> decoder;
        auto adaptor = make_json_visitor_adaptor<json_visitor>(decoder);
        basic_bson_reader<jsoncons::bytes_source> reader(v, adaptor);
        reader.read();
        return decoder.get_result();
    }

    template<class T>
    typename std::enable_if<!is_basic_json_class<T>::value,T>::type 
    decode_bson(const std::vector<uint8_t>& v)
    {
        basic_bson_cursor<bytes_source> cursor(v);
        json_decoder<basic_json<char,sorted_policy>> decoder{};

        std::error_code ec;
        T val = deser_traits<T,char>::deserialize(cursor, decoder, ec);
        if (ec)
        {
            JSONCONS_THROW(ser_error(ec, cursor.context().line(), cursor.context().column()));
        }
        return val;
    }

    template<class T>
    typename std::enable_if<is_basic_json_class<T>::value,T>::type 
    decode_bson(std::istream& is)
    {
        jsoncons::json_decoder<T> decoder;
        auto adaptor = make_json_visitor_adaptor<json_visitor>(decoder);
        bson_stream_reader reader(is, adaptor);
        reader.read();
        return decoder.get_result();
    }

    template<class T>
    typename std::enable_if<!is_basic_json_class<T>::value,T>::type 
    decode_bson(std::istream& is)
    {
        basic_bson_cursor<binary_stream_source> cursor(is);
        json_decoder<basic_json<char,sorted_policy>> decoder{};

        std::error_code ec;
        T val = deser_traits<T,char>::deserialize(cursor, decoder, ec);
        if (ec)
        {
            JSONCONS_THROW(ser_error(ec, cursor.context().line(), cursor.context().column()));
        }
        return val;
    }

    // With leading allocator parameter

    template<class T,class TempAllocator>
    typename std::enable_if<is_basic_json_class<T>::value,T>::type 
    decode_bson(temp_allocator_arg_t, const TempAllocator& temp_alloc,
                const std::vector<uint8_t>& v)
    {
        json_decoder<T,TempAllocator> decoder(temp_alloc);
        auto adaptor = make_json_visitor_adaptor<json_visitor>(decoder);
        basic_bson_reader<jsoncons::bytes_source,TempAllocator> reader(v, adaptor, temp_alloc);
        reader.read();
        return decoder.get_result();
    }

    template<class T,class TempAllocator>
    typename std::enable_if<!is_basic_json_class<T>::value,T>::type 
    decode_bson(temp_allocator_arg_t, const TempAllocator& temp_alloc,
                const std::vector<uint8_t>& v)
    {
        basic_bson_cursor<bytes_source,TempAllocator> cursor(v, temp_alloc);
        json_decoder<basic_json<char,sorted_policy,TempAllocator>,TempAllocator> decoder(temp_alloc, temp_alloc);

        std::error_code ec;
        T val = deser_traits<T,char>::deserialize(cursor, decoder, ec);
        if (ec)
        {
            JSONCONS_THROW(ser_error(ec, cursor.context().line(), cursor.context().column()));
        }
        return val;
    }

    template<class T,class TempAllocator>
    typename std::enable_if<is_basic_json_class<T>::value,T>::type 
    decode_bson(temp_allocator_arg_t, const TempAllocator& temp_alloc,
                std::istream& is)
    {
        json_decoder<T,TempAllocator> decoder(temp_alloc);
        auto adaptor = make_json_visitor_adaptor<json_visitor>(decoder);
        basic_bson_reader<jsoncons::binary_stream_source,TempAllocator> reader(is, adaptor, temp_alloc);
        reader.read();
        return decoder.get_result();
    }

    template<class T,class TempAllocator>
    typename std::enable_if<!is_basic_json_class<T>::value,T>::type 
    decode_bson(temp_allocator_arg_t, const TempAllocator& temp_alloc,
                std::istream& is)
    {
        basic_bson_cursor<binary_stream_source,TempAllocator> cursor(is, temp_alloc);
        json_decoder<basic_json<char,sorted_policy,TempAllocator>,TempAllocator> decoder(temp_alloc, temp_alloc);

        std::error_code ec;
        T val = deser_traits<T,char>::deserialize(cursor, decoder, ec);
        if (ec)
        {
            JSONCONS_THROW(ser_error(ec, cursor.context().line(), cursor.context().column()));
        }
        return val;
    }
  
} // bson
} // jsoncons

#endif