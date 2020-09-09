// Copyright 2020 Daniel Parker
// Distributed under the Boost license, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// See https://github.com/danielaparker/jsoncons for latest version

#ifndef JSONCONS_YAML_YAML_OPTIONS_HPP
#define JSONCONS_YAML_YAML_OPTIONS_HPP

#include <string>
#include <limits> // std::numeric_limits
#include <cwchar>
#include <jsoncons/json_exception.hpp>
#include <jsoncons/detail/more_type_traits.hpp>

namespace jsoncons {
namespace yaml {

    enum class float_chars_format : uint8_t {general,fixed,scientific,hex};

    enum class indenting : uint8_t {no_indent = 0, indent = 1};

    enum class line_split_kind  : uint8_t {same_line,new_line,multi_line};

    enum class bigint_chars_format : uint8_t {number, base10, base64, base64url};

    enum class byte_string_chars_format : uint8_t {none=0,base16,base64,base64url};

    enum class spaces_option : uint8_t {no_spaces=0,space_after,space_before,space_before_and_after};

    template <class CharT>
    class basic_yaml_options;

    template <class CharT>
    class basic_yaml_options_common
    {
        friend class basic_yaml_options<CharT>;
    public:
        using char_type = CharT;
        using string_type = std::basic_string<CharT>;
    private:
        bool enable_nan_to_num_:1;
        bool enable_inf_to_num_:1;
        bool enable_neginf_to_num_:1;
        bool enable_nan_to_str_:1;
        bool enable_inf_to_str_:1;
        bool enable_neginf_to_str_:1;
        bool enable_str_to_nan_:1;
        bool enable_str_to_inf_:1;
        bool enable_str_to_neginf_:1;

        string_type nan_to_num_;
        string_type inf_to_num_;
        string_type neginf_to_num_;
        string_type nan_to_str_;
        string_type inf_to_str_;
        string_type neginf_to_str_;
        int max_nesting_depth_;

    protected:
        basic_yaml_options_common()
           :
            enable_nan_to_num_(false),
            enable_inf_to_num_(false),
            enable_neginf_to_num_(false),
            enable_nan_to_str_(false),
            enable_inf_to_str_(false),
            enable_neginf_to_str_(false),
            enable_str_to_nan_(false),
            enable_str_to_inf_(false),
            enable_str_to_neginf_(false),
            max_nesting_depth_(1024)
        {}

        virtual ~basic_yaml_options_common() noexcept = default;

        basic_yaml_options_common(const basic_yaml_options_common&) = default;
        basic_yaml_options_common& operator=(const basic_yaml_options_common&) = default;
        basic_yaml_options_common(basic_yaml_options_common&&) = default;
        basic_yaml_options_common& operator=(basic_yaml_options_common&&) = default;

    public:

        bool enable_nan_to_num() const
        {
            return enable_nan_to_num_;
        }

        bool enable_inf_to_num() const
        {
            return enable_inf_to_num_;
        }

        bool enable_neginf_to_num() const
        {
            return enable_neginf_to_num_ || enable_inf_to_num_;
        }

        bool enable_nan_to_str() const
        {
            return enable_nan_to_str_;
        }

        bool enable_str_to_nan() const
        {
            return enable_str_to_nan_;
        }

        bool enable_inf_to_str() const
        {
            return enable_inf_to_str_;
        }

        bool enable_str_to_inf() const
        {
            return enable_str_to_inf_;
        }

        bool enable_neginf_to_str() const
        {
            return enable_neginf_to_str_ || enable_inf_to_str_;
        }

        bool enable_str_to_neginf() const
        {
            return enable_str_to_neginf_ || enable_str_to_inf_;
        }

        string_type nan_to_num() const
        {
            if (enable_nan_to_num_)
            {
                return nan_to_num_;
            }
            else
            {
                return nan_to_num_; // empty string
            }
        }

        string_type inf_to_num() const
        {
            if (enable_inf_to_num_)
            {
                return inf_to_num_;
            }
            else
            {
                return inf_to_num_; // empty string
            }
        }

        string_type neginf_to_num() const
        {
            if (enable_neginf_to_num_)
            {
                return neginf_to_num_;
            }
            else if (enable_inf_to_num_)
            {
                string_type s;
                s.push_back('-');
                s.append(inf_to_num_);
                return s;
            }
            else
            {
                return neginf_to_num_; // empty string
            }
        }

        string_type nan_to_str() const
        {
            if (enable_nan_to_str_)
            {
                return nan_to_str_;
            }
            else
            {
                return nan_to_str_; // empty string
            }
        }

        string_type inf_to_str() const
        {
            if (enable_inf_to_str_)
            {
                return inf_to_str_;
            }
            else
            {
                return inf_to_str_; // empty string
            }
        }

        string_type neginf_to_str() const
        {
            if (enable_neginf_to_str_)
            {
                return neginf_to_str_;
            }
            else if (enable_inf_to_str_)
            {
                string_type s;
                s.push_back('-');
                s.append(inf_to_str_);
                return s;
            }
            else
            {
                return neginf_to_str_; // empty string
            }
        }

        int max_nesting_depth() const 
        {
            return max_nesting_depth_;
        }

    };

    template <class CharT>
    class basic_yaml_decode_options : public virtual basic_yaml_options_common<CharT>
    {
        friend class basic_yaml_options<CharT>;
        using super_type = basic_yaml_options_common<CharT>;
    public:
        using typename super_type::char_type;
        using typename super_type::string_type;
    private:
        bool lossless_number_:1;
    public:
        basic_yaml_decode_options()
            : lossless_number_(false)
        {
        }

        basic_yaml_decode_options(const basic_yaml_decode_options&) = default;

        basic_yaml_decode_options(basic_yaml_decode_options&& other)
            : super_type(std::forward<basic_yaml_decode_options>(other)),
                         lossless_number_(other.lossless_number_)
        {
        }

        basic_yaml_decode_options& operator=(const basic_yaml_decode_options&) = default;

        bool lossless_number() const 
        {
            return lossless_number_;
        }

    };

    template <class CharT>
    class basic_yaml_encode_options : public virtual basic_yaml_options_common<CharT>
    {
        friend class basic_yaml_options<CharT>;
        using super_type = basic_yaml_options_common<CharT>;
    public:
        using typename super_type::char_type;
        using typename super_type::string_type;

        static constexpr uint8_t indent_size_default = 4;
        static constexpr size_t line_length_limit_default = 120;
    private:
        bool escape_all_non_ascii_:1;
        bool escape_solidus_:1;
        bool pad_inside_object_braces_:1;
        bool pad_inside_array_brackets_:1;
        float_chars_format float_format_;
        byte_string_chars_format byte_string_format_;
        bigint_chars_format bigint_format_;
        line_split_kind object_object_line_splits_;
        line_split_kind object_array_line_splits_;
        line_split_kind array_array_line_splits_;
        line_split_kind array_object_line_splits_;
        spaces_option spaces_around_colon_;
        spaces_option spaces_around_comma_;
        int8_t precision_;
        uint8_t indent_size_;
        std::size_t line_length_limit_;
        string_type new_line_chars_;
    public:
        basic_yaml_encode_options()
            : escape_all_non_ascii_(false),
              escape_solidus_(false),
              pad_inside_object_braces_(false),
              pad_inside_array_brackets_(false),
              float_format_(float_chars_format::general),
              byte_string_format_(byte_string_chars_format::none),
              bigint_format_(bigint_chars_format::base10),
              object_object_line_splits_(line_split_kind::multi_line),
              object_array_line_splits_(line_split_kind::same_line),
              array_array_line_splits_(line_split_kind::new_line),
              array_object_line_splits_(line_split_kind::multi_line),
              spaces_around_colon_(spaces_option::space_after),
              spaces_around_comma_(spaces_option::space_after),
              precision_(0),
              indent_size_(indent_size_default),
              line_length_limit_(line_length_limit_default)
        {
            new_line_chars_.push_back('\n');
        }

        basic_yaml_encode_options(const basic_yaml_encode_options&) = default;

        basic_yaml_encode_options(basic_yaml_encode_options&& other)
            : super_type(std::forward<basic_yaml_encode_options>(other)),
              escape_all_non_ascii_(other.escape_all_non_ascii_),
              escape_solidus_(other.escape_solidus_),
              pad_inside_object_braces_(other.pad_inside_object_braces_),
              pad_inside_array_brackets_(other.pad_inside_array_brackets_),
              float_format_(other.float_format_),
              byte_string_format_(other.byte_string_format_),
              bigint_format_(other.bigint_format_),
              object_object_line_splits_(other.object_object_line_splits_),
              object_array_line_splits_(other.object_array_line_splits_),
              array_array_line_splits_(other.array_array_line_splits_),
              array_object_line_splits_(other.array_object_line_splits_),
              spaces_around_colon_(other.spaces_around_colon_),
              spaces_around_comma_(other.spaces_around_comma_),
              precision_(other.precision_),
              indent_size_(other.indent_size_),
              line_length_limit_(other.line_length_limit_),
              new_line_chars_(std::move(other.new_line_chars_))
        {
        }

        basic_yaml_encode_options& operator=(const basic_yaml_encode_options&) = default;

        byte_string_chars_format byte_string_format() const  {return byte_string_format_;}

        bigint_chars_format bigint_format() const  {return bigint_format_;}

        line_split_kind object_object_line_splits() const  {return object_object_line_splits_;}

        line_split_kind array_object_line_splits() const  {return array_object_line_splits_;}

        line_split_kind object_array_line_splits() const  {return object_array_line_splits_;}

        line_split_kind array_array_line_splits() const  {return array_array_line_splits_;}

        uint8_t indent_size() const 
        {
            return indent_size_;
        }

        spaces_option spaces_around_colon() const 
        {
            return spaces_around_colon_;
        }

        spaces_option spaces_around_comma() const 
        {
            return spaces_around_comma_;
        }

        bool pad_inside_object_braces() const 
        {
            return pad_inside_object_braces_;
        }

        bool pad_inside_array_brackets() const 
        {
            return pad_inside_array_brackets_;
        }

        string_type new_line_chars() const 
        {
            return new_line_chars_;
        }

        std::size_t line_length_limit() const 
        {
            return line_length_limit_;
        }

        float_chars_format float_format() const 
        {
            return float_format_;
        }

        int8_t precision() const 
        {
            return precision_;
        }

        bool escape_all_non_ascii() const 
        {
            return escape_all_non_ascii_;
        }

        bool escape_solidus() const 
        {
            return escape_solidus_;
        }

    };

    template <class CharT>
    class basic_yaml_options final: public basic_yaml_decode_options<CharT>, 
                                    public basic_yaml_encode_options<CharT>
    {
    public:
        using char_type = CharT;
        using string_type = std::basic_string<CharT>;

        using basic_yaml_options_common<CharT>::max_nesting_depth;

        using basic_yaml_decode_options<CharT>::enable_str_to_nan;
        using basic_yaml_decode_options<CharT>::enable_str_to_inf;
        using basic_yaml_decode_options<CharT>::enable_str_to_neginf;
        using basic_yaml_decode_options<CharT>::nan_to_str;
        using basic_yaml_decode_options<CharT>::inf_to_str;
        using basic_yaml_decode_options<CharT>::neginf_to_str;
        using basic_yaml_decode_options<CharT>::nan_to_num;
        using basic_yaml_decode_options<CharT>::inf_to_num;
        using basic_yaml_decode_options<CharT>::neginf_to_num;

        using basic_yaml_decode_options<CharT>::lossless_number;

        using basic_yaml_encode_options<CharT>::byte_string_format;
        using basic_yaml_encode_options<CharT>::bigint_format;
        using basic_yaml_encode_options<CharT>::object_object_line_splits;
        using basic_yaml_encode_options<CharT>::array_object_line_splits;
        using basic_yaml_encode_options<CharT>::object_array_line_splits;
        using basic_yaml_encode_options<CharT>::array_array_line_splits;
        using basic_yaml_encode_options<CharT>::indent_size;
        using basic_yaml_encode_options<CharT>::spaces_around_colon;
        using basic_yaml_encode_options<CharT>::spaces_around_comma;
        using basic_yaml_encode_options<CharT>::pad_inside_object_braces;
        using basic_yaml_encode_options<CharT>::pad_inside_array_brackets;
        using basic_yaml_encode_options<CharT>::new_line_chars;
        using basic_yaml_encode_options<CharT>::line_length_limit;
        using basic_yaml_encode_options<CharT>::float_format;
        using basic_yaml_encode_options<CharT>::precision;
        using basic_yaml_encode_options<CharT>::escape_all_non_ascii;
        using basic_yaml_encode_options<CharT>::escape_solidus;
    public:

    //  Constructors

        basic_yaml_options() = default;
        basic_yaml_options(const basic_yaml_options&) = default;
        basic_yaml_options(basic_yaml_options&&) = default;
        basic_yaml_options& operator=(const basic_yaml_options&) = default;
        basic_yaml_options& operator=(basic_yaml_options&&) = default;

        basic_yaml_options& nan_to_num(const string_type& value)
        {
            this->enable_nan_to_num_ = true;
            this->nan_to_str_.clear();
            this->nan_to_num_ = value;
            return *this;
        }

        basic_yaml_options& inf_to_num(const string_type& value)
        {
            this->enable_inf_to_num_ = true;
            this->inf_to_str_.clear();
            this->inf_to_num_ = value;
            return *this;
        }

        basic_yaml_options& neginf_to_num(const string_type& value)
        {
            this->enable_neginf_to_num_ = true;
            this->neginf_to_str_.clear();
            this->neginf_to_num_ = value;
            return *this;
        }

        basic_yaml_options& nan_to_str(const string_type& value, bool enable_inverse = true)
        {
            this->enable_nan_to_str_ = true;
            this->enable_str_to_nan_ = enable_inverse;
            this->nan_to_num_.clear();
            this->nan_to_str_ = value;
            return *this;
        }

        basic_yaml_options& inf_to_str(const string_type& value, bool enable_inverse = true)
        {
            this->enable_inf_to_str_ = true;
            this->enable_inf_to_str_ = enable_inverse;
            this->inf_to_num_.clear();
            this->inf_to_str_ = value;
            return *this;
        }

        basic_yaml_options& neginf_to_str(const string_type& value, bool enable_inverse = true)
        {
            this->enable_neginf_to_str_ = true;
            this->enable_neginf_to_str_ = enable_inverse;
            this->neginf_to_num_.clear();
            this->neginf_to_str_ = value;
            return *this;
        }

        basic_yaml_options&  byte_string_format(byte_string_chars_format value) {this->byte_string_format_ = value; return *this;}

        basic_yaml_options&  bigint_format(bigint_chars_format value) {this->bigint_format_ = value; return *this;}

        basic_yaml_options& object_object_line_splits(line_split_kind value) {this->object_object_line_splits_ = value; return *this;}

        basic_yaml_options& array_object_line_splits(line_split_kind value) {this->array_object_line_splits_ = value; return *this;}

        basic_yaml_options& object_array_line_splits(line_split_kind value) {this->object_array_line_splits_ = value; return *this;}

        basic_yaml_options& array_array_line_splits(line_split_kind value) {this->array_array_line_splits_ = value; return *this;}

        basic_yaml_options& indent_size(uint8_t value)
        {
            this->indent_size_ = value;
            return *this;
        }

        basic_yaml_options& spaces_around_colon(spaces_option value)
        {
            this->spaces_around_colon_ = value;
            return *this;
        }

        basic_yaml_options& spaces_around_comma(spaces_option value)
        {
            this->spaces_around_comma_ = value;
            return *this;
        }

        basic_yaml_options& pad_inside_object_braces(bool value)
        {
            this->pad_inside_object_braces_ = value;
            return *this;
        }

        basic_yaml_options& pad_inside_array_brackets(bool value)
        {
            this->pad_inside_array_brackets_ = value;
            return *this;
        }

        basic_yaml_options& new_line_chars(const string_type& value)
        {
            this->new_line_chars_ = value;
            return *this;
        }

        basic_yaml_options& lossless_number(bool value) 
        {
            this->lossless_number_ = value;
            return *this;
        }

        basic_yaml_options& line_length_limit(std::size_t value)
        {
            this->line_length_limit_ = value;
            return *this;
        }

        basic_yaml_options& float_format(float_chars_format value)
        {
            this->float_format_ = value;
            return *this;
        }

        basic_yaml_options& precision(int8_t value)
        {
            this->precision_ = value;
            return *this;
        }

        basic_yaml_options& escape_all_non_ascii(bool value)
        {
            this->escape_all_non_ascii_ = value;
            return *this;
        }

        basic_yaml_options& escape_solidus(bool value)
        {
            this->escape_solidus_ = value;
            return *this;
        }

        basic_yaml_options& max_nesting_depth(int value)
        {
            this->max_nesting_depth_ = value;
            return *this;
        }

    private:
        enum class input_state {initial,begin_quote,character,end_quote,escape,error};
        bool is_string(const string_type& s) const
        {
            input_state state = input_state::initial;
            for (char_type c : s)
            {
                switch (c)
                {
                case '\t': case ' ': case '\n': case'\r':
                    break;
                case '\\':
                    state = input_state::escape;
                    break;
                case '\"':
                    switch (state)
                    {
                    case input_state::initial:
                        state = input_state::begin_quote;
                        break;
                    case input_state::begin_quote:
                        state = input_state::end_quote;
                        break;
                    case input_state::character:
                        state = input_state::end_quote;
                        break;
                    case input_state::end_quote:
                        state = input_state::error;
                        break;
                    case input_state::escape:
                        state = input_state::character;
                        break;
                    default:
                        state = input_state::character;
                        break;
                    }
                    break;
                default:
                    break;
                }

            }
            return state == input_state::end_quote;
        }
    };

    using yaml_options = basic_yaml_options<char>;
    using wyaml_options = basic_yaml_options<wchar_t>;

} // namespace yaml
} // namespace jsoncons

#endif
