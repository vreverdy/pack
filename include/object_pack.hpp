// =============================== OBJECT PACK ============================== //
// Project:         Pack
// Name:            object_pack.hpp
// Description:     A pack of objects
// Creator:         Vincent Reverdy
// Contributor(s):  Vincent Reverdy [2019]
// License:         BSD 3-Clause License
// ========================================================================== //
#ifndef _OBJECT_PACK_HPP_INCLUDED
#define _OBJECT_PACK_HPP_INCLUDED
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



/* ************************** OBJECT PACK ELEMENT *************************** */
// Object pack element definition
template <class Type, class Index, class Key = Type>
class object_pack_element
{
    // Types and constants
    public:
    using element_type = object_pack_element;
    using type = Type;
    using index_type = Index;
    using key_type = Key;
    static constexpr auto index = index_type::value;

    // Lifecycle
    public:
    constexpr object_pack_element();
    explicit constexpr object_pack_element(const type&);
    constexpr object_pack_element(const type&, index_type);
    constexpr object_pack_element(const type&, index_type, const key_type&);

    // Access
    public:
    constexpr element_type& operator[](index_type) noexcept;
    constexpr const element_type& operator[](index_type) const noexcept;
    constexpr element_type& operator[](const key_type&) noexcept;
    constexpr const element_type& operator[](const key_type&) const noexcept;

    // Implementation details: data members
    private:
    type _object;
};
/* ************************************************************************** */



/* **************************** OBJECT PACK BASE **************************** */
// Object pack base class declaration
template <class, class...>
class object_pack_base;

// Object pack base class specialization
template <std::size_t... Indices, class... Types>
class object_pack_base<pack_index_sequence<Indices...>, Types...>
: object_pack_element<Types, pack_index<Indices>>...
{
    // Inheritance
    public:
    using object_pack_element<Types, pack_index<Indices>>::operator[]...;

    // Lifecycle
    public:
    constexpr object_pack_base() = default;
    explicit constexpr object_pack_base(const Types&...);

    // Implementation details: types and constants
    private:
    using element_type = void;
    using type = void;
    using index_type = void;
    using key_type = void;
    static constexpr std::size_t index = -1;
};
/* ************************************************************************** */



/* ****************************** OBJECT PACK ******************************* */
// Object pack class definition
template <class... Types>
class object_pack
: object_pack_base<make_pack_index_sequence<sizeof...(Types)>, Types...>
{
    // Types and inheritance
    public:
    using size_type = std::size_t;
    using index_sequence = make_pack_index_sequence<sizeof...(Types)>;
    using base = object_pack_base<index_sequence, Types...>;
    using base::operator[];

    // Lifecycle
    public:
    constexpr object_pack() = default;
    explicit constexpr object_pack(const Types&...);

    // Size
    public:
    static constexpr size_type size() noexcept;
};
/* ************************************************************************** */



// --------------------- OBJECT PACK ELEMENT: LIFECYCLE --------------------- //
// Constructs an empty object pack through value initialization
template <class Type, class Index, class Key>
constexpr object_pack_element<Type, Index, Key>::object_pack_element(
)
: _object()
{
}

// Explicitly constructs an object pack element from an object
template <class Type, class Index, class Key>
constexpr object_pack_element<Type, Index, Key>::object_pack_element(
    const type& object
)
: _object(object)
{
}

// Explicitly constructs an object pack element from an object and index
template <class Type, class Index, class Key>
constexpr object_pack_element<Type, Index, Key>::object_pack_element(
    const type& object,
    index_type
)
: _object(object)
{
}

// Explicitly constructs an object pack element from an object, index and key
template <class Type, class Index, class Key>
constexpr object_pack_element<Type, Index, Key>::object_pack_element(
    const type& object,
    index_type,
    const key_type&
)
: _object(object)
{
}
// -------------------------------------------------------------------------- //



// ----------------------- OBJECT PACK ELEMENT: ACCESS ---------------------- //
// Returns the object pack element corresponding to the index
template <class Type, class Index, class Key>
constexpr typename object_pack_element<Type, Index, Key>::element_type&
object_pack_element<Type, Index, Key>::operator[](
    index_type
) noexcept
{
    return *this;
}

// Immutably returns the object pack element corresponding to the index
template <class Type, class Index, class Key>
constexpr const typename object_pack_element<Type, Index, Key>::element_type&
object_pack_element<Type, Index, Key>::operator[](
    index_type
) const noexcept
{
    return *this;
}

// Returns the object pack element corresponding to the key
template <class Type, class Index, class Key>
constexpr typename object_pack_element<Type, Index, Key>::element_type&
object_pack_element<Type, Index, Key>::operator[](
    const key_type&
) noexcept
{
    return *this;
}

// Immutably returns the object pack element corresponding to the key
template <class Type, class Index, class Key>
constexpr const typename object_pack_element<Type, Index, Key>::element_type&
object_pack_element<Type, Index, Key>::operator[](
    const key_type&
) const noexcept
{
    return *this;
}
// -------------------------------------------------------------------------- //



// ----------------------- OBJECT PACK BASE: LIFECYCLE ---------------------- //
// Explicitly constructs an object pack base from objects
template <std::size_t... Indices, class... Types>
constexpr
object_pack_base<pack_index_sequence<Indices...>, Types...>::object_pack_base(
    const Types&... objects
)
: object_pack_element<Types, pack_index<Indices>>(objects)...
{
}
// -------------------------------------------------------------------------- //



// ------------------------- OBJECT PACK: LIFECYCLE ------------------------- //
// Explicitly constructs an object pack from objects
template <class... Types>
constexpr object_pack<Types...>::object_pack(
    const Types&... objects
)
: base(objects...)
{
}
// -------------------------------------------------------------------------- //



// --------------------------- OBJECT PACK: SIZE ---------------------------- //
// Returns the number of elements in the pack
template <class... Types>
constexpr typename object_pack<Types...>::size_type
object_pack<Types...>::size(
) noexcept
{
    return sizeof...(Types);
}
// -------------------------------------------------------------------------- //



// ========================================================================== //
} // namespace pck
#endif // _OBJECT_PACK_HPP_INCLUDED
// ========================================================================== //

