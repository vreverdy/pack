// =============================== PACK INDEX =============================== //
// Project:         Pack
// Name:            pack_index.hpp
// Description:     Utilities for pack indexing
// Creator:         Vincent Reverdy
// Contributor(s):  Vincent Reverdy [2019]
// License:         BSD 3-Clause License
// ========================================================================== //
#ifndef _PACK_INDEX_INCLUDED
#define _PACK_INDEX_INCLUDED
// ========================================================================== //



// ================================ PREAMBLE ================================ //
// C++ standard library
// Project sources
#include "pack_details.hpp"
// Third-party libraries
// Miscellaneous
namespace pck {
// ========================================================================== //



/* ******************************* PACK INDEX ******************************* */
// Pack index class definition
template <std::size_t Value>
class pack_index
{
    // Types and constants
    public:
    using type = pack_index;
    using value_type = std::size_t;
    using integral_constant = std::integral_constant<std::size_t, Value>;
    static constexpr value_type value = Value;

    // Lifecycle
    public:
    constexpr pack_index() noexcept = default;
    constexpr pack_index(integral_constant) noexcept;

    // Conversion
    public:
    constexpr operator value_type() const noexcept;
    constexpr operator integral_constant() const noexcept;
};

// Variable template helper
template <std::size_t Value>
inline constexpr auto pack_index_v = pack_index<Value>{};
/* ************************************************************************** */



/* ************************** PACK INDEX SEQUENCE *************************** */
// Pack index sequence class definition
template <std::size_t... Values>
class pack_index_sequence
{
    // Types
    public:
    using type = pack_index_sequence;
    using value_type = std::size_t;
    using size_type = std::size_t;
    using integer_sequence = std::integer_sequence<std::size_t, Values...>;

    // Lifecycle
    public:
    constexpr pack_index_sequence() noexcept = default;
    constexpr pack_index_sequence(integer_sequence) noexcept;

    // Conversion
    public:
    constexpr operator integer_sequence() const noexcept;

    // Size
    public:
    static constexpr size_type size() noexcept;
};

// Variable template helper
template <std::size_t... Values>
inline constexpr auto pack_index_sequence_v = pack_index_sequence<Values...>{};
/* ************************************************************************** */



/* ************************ MAKE PACK INDEX SEQUENCE ************************ */
// Pack index sequence maker structure declaration
template <class>
struct pack_index_sequence_maker;

// Pack index sequence maker structure specialization
template <std::size_t... Values>
struct pack_index_sequence_maker<std::integer_sequence<std::size_t, Values...>>
{
    using type = pack_index_sequence<Values...>;
};

// Alias template maker
template <std::size_t Size>
using make_pack_index_sequence = typename pack_index_sequence_maker<
    std::make_index_sequence<Size>
>::type;

// Variable template maker
template <std::size_t Size>
inline constexpr auto make_pack_index_sequence_v = make_pack_index_sequence<
    Size
>{};
/* ************************************************************************** */



// -------------------------- PACK INDEX: LIFECYCLE ------------------------- //
// Implicitly constructs a pack index from an integral constant
template <std::size_t Value>
constexpr pack_index<Value>::pack_index(
    integral_constant
) noexcept
{
}
// -------------------------------------------------------------------------- //



// ------------------------- PACK INDEX: CONVERSION ------------------------- //
// Implicitly converts a pack index to its value
template <std::size_t Value>
constexpr pack_index<Value>::operator
typename pack_index<Value>::value_type(
) const noexcept
{
    return value;
}

// Implicitly converts a pack index to an integral constant
template <std::size_t Value>
constexpr pack_index<Value>::operator integral_constant(
) const noexcept
{
    return integral_constant{};
}
// -------------------------------------------------------------------------- //



// --------------------- PACK INDEX SEQUENCE: LIFECYCLE --------------------- //
// Implicitly constructs a pack index sequence from an integer sequence
template <std::size_t... Values>
constexpr pack_index_sequence<Values...>::pack_index_sequence(
    integer_sequence
) noexcept
{
}
// -------------------------------------------------------------------------- //



// -------------------- PACK INDEX SEQUENCE: CONVERSION --------------------- //
// Implicitly converts a pack index sequence to an integer sequence
template <std::size_t... Values>
constexpr pack_index_sequence<Values...>::operator integer_sequence(
) const noexcept
{
    return integer_sequence{};
}
// -------------------------------------------------------------------------- //



// ----------------------- PACK INDEX SEQUENCE: SIZE ------------------------ //
// Returns the size of the pack index sequence
template <std::size_t... Values>
constexpr typename pack_index_sequence<Values...>::size_type
pack_index_sequence<Values...>::size(
) noexcept
{
    return sizeof...(Values);
}
// -------------------------------------------------------------------------- //



// ========================================================================== //
} // namespace pck
#endif // _PACK_INDEX_HPP_INCLUDED
// ========================================================================== //
