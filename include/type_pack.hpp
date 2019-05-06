// ================================ TYPE PACK =============================== //
// Project:         Pack
// Name:            type_pack.hpp
// Description:     A pack of types
// Creator:         Vincent Reverdy
// Contributor(s):  Vincent Reverdy [2019]
// License:         BSD 3-Clause License
// ========================================================================== //
#ifndef _TYPE_PACK_HPP_INCLUDED
#define _TYPE_PACK_HPP_INCLUDED
// ========================================================================== //



// ================================ PREAMBLE ================================ //
// C++ standard library
// Project sources
#include "pack_details.hpp"
#include "pack_index.hpp"
// Third-party libraries
// Miscellaneous
namespace pck {
// ========================================================================== //



/* *************************** TYPE PACK ELEMENT **************************** */
// Type pack element definition
template <class Type, class Index, class Key = Type>
class type_pack_element
{
    // Types and constants
    public:
    using element_type = type_pack_element;
    using type = Type;
    using index_type = Index;
    using key_type = Key;
    static constexpr auto index = index_type::value;

    // Lifecycle
    public:
    constexpr type_pack_element() noexcept = default;
    explicit constexpr type_pack_element(const type&) noexcept;
    constexpr type_pack_element(const type&, index_type) noexcept;
    constexpr type_pack_element(const type&, index_type, const key_type&);

    // Access
    public:
    constexpr element_type operator[](index_type) const noexcept;
    constexpr element_type operator[](const key_type&) const noexcept;
};
/* ************************************************************************** */



/* ***************************** TYPE PACK BASE ***************************** */
// Type pack base class declaration
template <class, class...>
class type_pack_base;

// Type pack base class specialization
template <std::size_t... Indices, class... Types>
class type_pack_base<pack_index_sequence<Indices...>, Types...>
: type_pack_element<Types, pack_index<Indices>>...
{
    // Inheritance
    public:
    using type_pack_element<Types, pack_index<Indices>>::operator[]...;

    // Implementation details: types and constants
    private:
    using element_type = void;
    using type = void;
    using index_type = void;
    using key_type = void;
    static constexpr std::size_t index = -1;
};
/* ************************************************************************** */



/* ******************************* TYPE PACK ******************************** */
// Type pack class definition
template <class... Types>
class type_pack
: type_pack_base<make_pack_index_sequence<sizeof...(Types)>, Types...>
{
    // Types and inheritance
    public:
    using size_type = std::size_t;
    using index_sequence = make_pack_index_sequence<sizeof...(Types)>;
    using base = type_pack_base<index_sequence, Types...>;
    using base::operator[];

    // Lifecycle
    public:
    constexpr type_pack() noexcept = default;
    explicit constexpr type_pack(const Types&...) noexcept;

    // Size
    public:
    static constexpr size_type size() noexcept;
};
/* ************************************************************************** */



// ---------------------- TYPE PACK ELEMENT: LIFECYCLE ---------------------- //
// Explicitly constructs a type pack element from a type
template <class Type, class Index, class Key>
constexpr type_pack_element<Type, Index, Key>::type_pack_element(
    const type&
) noexcept
{
}

// Explicitly constructs a type pack element from a type and an index
template <class Type, class Index, class Key>
constexpr type_pack_element<Type, Index, Key>::type_pack_element(
    const type&,
    index_type
) noexcept
{
}

// Explicitly constructs a type pack element from a type, index, and key
template <class Type, class Index, class Key>
constexpr type_pack_element<Type, Index, Key>::type_pack_element(
    const type&,
    index_type,
    const key_type&
)
{
}
// -------------------------------------------------------------------------- //



// ------------------------ TYPE PACK ELEMENT: ACCESS ----------------------- //
// Returns the type pack element corresponding to the index
template <class Type, class Index, class Key>
constexpr typename type_pack_element<Type, Index, Key>::element_type
type_pack_element<Type, Index, Key>::operator[](
    index_type
) const noexcept
{
    return {};
}

// Returns the type pack element corresponding to the key
template <class Type, class Index, class Key>
constexpr typename type_pack_element<Type, Index, Key>::element_type
type_pack_element<Type, Index, Key>::operator[](
    const key_type&
) const noexcept
{
    return {};
}
// -------------------------------------------------------------------------- //



// -------------------------- TYPE PACK: LIFECYCLE -------------------------- //
// Explicitly constructs a type pack from objects of these types
template <class... Types>
constexpr type_pack<Types...>::type_pack(
    const Types&...
) noexcept
{
}
// -------------------------------------------------------------------------- //



// ---------------------------- TYPE PACK: SIZE ----------------------------- //
// Returns the number of elements in the pack
template <class... Types>
constexpr typename type_pack<Types...>::size_type
type_pack<Types...>::size(
) noexcept
{
    return sizeof...(Types);
}
// -------------------------------------------------------------------------- //



// ========================================================================== //
} // namespace pck
#endif // _TYPE_PACK_HPP_INCLUDED
// ========================================================================== //
