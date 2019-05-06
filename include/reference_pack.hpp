// ============================== REFERENCE PACK =<=========================== //
// Project:         Pack
// Name:            reference_pack.hpp
// Description:     A pack of references
// Creator:         Vincent Reverdy
// Contributor(s):  Vincent Reverdy [2019]
// License:         BSD 3-Clause License
// ========================================================================== //
#ifndef _REFERENCE_PACK_HPP_INCLUDED
#define _REFERENCE_PACK_HPP_INCLUDED
// ========================================================================== //



// ================================ PREAMBLE ================================ //
// C++ standard library
// Project sources
#include "pack_details.hpp"
#include "pack_index.hpp"
// Third-party libraries
// Miscellaneous
namespace pck {
template <class Type, class Index, class Key = std::decay_t<Type>>
class reference_pack_element;
template <class, class...>
class reference_pack_base;
template <class... Types>
class reference_pack;
// ========================================================================== //



/* ********************* IS REFERENCE PACK CONSTRUCTIBLE ******************** */
// Is reference pack constructible declaration
template <class, class...>
struct is_reference_pack_constructible
: std::false_type
{
};

// Is reference pack constructible specialization: reference pack element
template <class Type, class Index, class Key, class Arg>
struct is_reference_pack_constructible<
    reference_pack_element<Type, Index, Key>,
    Arg
>
: std::bool_constant<
    std::is_same_v<
        std::remove_cv_t<std::remove_reference_t<Arg>>,
        std::remove_cv_t<std::remove_reference_t<Type>>
    > &&
    !std::is_same_v<
        std::remove_cv_t<std::remove_reference_t<Arg>>,
        reference_pack_element<Type, Index, Key>
    >
>
{
};

// Is reference pack constructible specialization: reference pack base
template <class Index, class Type, class... Types, class Arg, class... Args>
struct is_reference_pack_constructible<
    reference_pack_base<Index, Type, Types...>,
    Arg,
    Args...
>
: std::bool_constant<
    std::is_same_v<
        std::tuple<Arg, std::remove_cv_t<std::remove_reference_t<Args>>...>,
        std::tuple<Type, std::remove_cv_t<std::remove_reference_t<Types>>...>
    > &&
    !std::is_same_v<
        std::remove_cv_t<std::remove_reference_t<Arg>>,
        reference_pack_base<Index, Type, Types...>
    >
>
{
};

// Is reference pack constructible specialization: reference pack
template <class Type, class... Types, class Arg, class... Args>
struct is_reference_pack_constructible<
    reference_pack<Type, Types...>,
    Arg,
    Args...
>
: std::bool_constant<
    std::is_same_v<
        std::tuple<Arg, std::remove_cv_t<std::remove_reference_t<Args>>...>,
        std::tuple<Type, std::remove_cv_t<std::remove_reference_t<Types>>...>
    > &&
    !std::is_same_v<
        std::remove_cv_t<std::remove_reference_t<Arg>>,
        reference_pack<Type, Types...>
    >
>
{
};

// Variable template
template <class Pack, class... Args>
inline constexpr bool is_reference_pack_constructible_v
= is_reference_pack_constructible<Pack, Args...>::value;

// Alias template
template <class Pack, class... Args>
using if_reference_pack_constructible_t = std::enable_if<
    is_reference_pack_constructible_v<Pack, Args...>
>;
/* ************************************************************************** */



/* ************************* REFERENCE PACK ELEMENT ************************* */
// Reference pack element definition
template <class Type, class Index, class Key>
class reference_pack_element
{
    // Implementation details: type traits and types
    private:
    template <class Arg>
    using _if_constructible_from_t = if_reference_pack_constructible_t<
        reference_pack_element,
        Arg
    >;
    using _reference_type = std::conditional_t<
        std::is_rvalue_reference_v<Type>,
        std::remove_cv_t<std::remove_reference_t<Type>>,
        Type
    >;
    
    // Types and constants
    public:
    using element_type = reference_pack_element;
    using type = Type;
    using index_type = Index;
    using key_type = Key;
    static constexpr auto index = index_type::value;

    // Lifecycle
    public:
    template <class Arg, class = _if_constructible_from_t<Arg&&>>
    explicit constexpr reference_pack_element(Arg&&);
    template <class Arg, class = _if_constructible_from_t<Arg&&>>
    constexpr reference_pack_element(Arg&&, index_type);
    template <class Arg, class = _if_constructible_from_t<Arg&&>>
    constexpr reference_pack_element(Arg&&, index_type, const key_type&);

    // Access
    public:
    constexpr element_type& operator[](index_type) noexcept;
    constexpr const element_type& operator[](index_type) const noexcept;
    constexpr element_type& operator[](const key_type&) noexcept;
    constexpr const element_type& operator[](const key_type&) const noexcept;

    // Implementation details: data members
    private:
    _reference_type _reference;
};

// Class template argument deduction guides
template <
    class Type,
    class Index,
    class = if_reference_pack_constructible_t<
        reference_pack_element<Type&&, Index>,
        Type&&
    >
>
reference_pack_element(Type&&, Index)
-> reference_pack_element<Type, Index>;
template <
    class Type,
    class Index,
    class Key,
    class = if_reference_pack_constructible_t<
        reference_pack_element<Type&&, Index, Key>,
        Type&&
    >
>
reference_pack_element(Type&&, Index, const Key&)
-> reference_pack_element<Type, Index, Key>;
/* ************************************************************************** */



/* *************************** REFERENCE PACK BASE ************************** */
// Reference pack base class specialization
template <std::size_t... Indices, class... Types>
class reference_pack_base<pack_index_sequence<Indices...>, Types...>
: reference_pack_element<Types, pack_index<Indices>>...
{
    // Implementation details: type traits
    private:
    template <class... Args>
    using _if_constructible_from_t = if_reference_pack_constructible_t<
        reference_pack_base,
        Args...
    >;
    
    // Inheritance
    public:
    using reference_pack_element<Types, pack_index<Indices>>::operator[]...;

    // Lifecycle
    public:
    template <class... Args, class = _if_constructible_from_t<Args&&...>>
    explicit constexpr reference_pack_base(Args&&...);

    // Implementation details: types and constants
    private:
    using element_type = void;
    using type = void;
    using index_type = void;
    using key_type = void;
    static constexpr std::size_t index = -1;
};

// Class template argument deduction guide
template <
    class... Types,
    class = if_reference_pack_constructible_t<
        reference_pack_base<Types&&...>,
        Types&&...
    >
>
reference_pack_base(Types&&...)
-> reference_pack_base<Types&&...>;
/* ************************************************************************** */



/* ***************************** REFERENCE PACK ***************************** */
// Object pack class definition
template <class... Types>
class reference_pack
: reference_pack_base<make_pack_index_sequence<sizeof...(Types)>, Types...>
{
    // Implementation details: type traits
    private:
    template <class... Args>
    using _if_constructible_from_t = if_reference_pack_constructible_t<
        reference_pack,
        Args...
    >;
    
    // Types and inheritance
    public:
    using size_type = std::size_t;
    using index_sequence = make_pack_index_sequence<sizeof...(Types)>;
    using base = reference_pack_base<index_sequence, Types...>;
    using base::operator[];

    // Lifecycle
    public:
    template <class... Args, class = _if_constructible_from_t<Args&&...>>
    explicit constexpr reference_pack(Args&&...);

    // Size
    public:
    static constexpr size_type size() noexcept;
};

// Class template argument deduction guides
template <
    class... Types,
    class = if_reference_pack_constructible_t<
        reference_pack<Types&&...>,
        Types&&...
    >
>
reference_pack(Types&&...)
-> reference_pack<Types&&...>;
/* ************************************************************************** */



// -------------------- REFERENCE PACK ELEMENT: LIFECYCLE ------------------- //
// Explicitly constructs a reference pack element from a reference
template <class Type, class Index, class Key>
template <class Arg, class>
constexpr reference_pack_element<Type, Index, Key>::reference_pack_element(
    Arg&& reference
)
: _reference(std::forward<Arg>(reference))
{
}

// Explicitly constructs a reference pack element from a reference and index
template <class Type, class Index, class Key>
template <class Arg, class>
constexpr reference_pack_element<Type, Index, Key>::reference_pack_element(
    Arg&& reference,
    index_type
)
: _reference(std::forward<Arg>(reference))
{
}

// Explicitly constructs a reference pack element from reference, index and key
template <class Type, class Index, class Key>
template <class Arg, class>
constexpr reference_pack_element<Type, Index, Key>::reference_pack_element(
    Arg&& reference,
    index_type,
    const key_type&
)
: _reference(std::forward<Arg>(reference))
{
}
// -------------------------------------------------------------------------- //



// ---------------------- REFERENCE PACK ELEMENT: ACCESS -------------------- //
// Returns the reference pack element corresponding to the index
template <class Type, class Index, class Key>
constexpr typename reference_pack_element<Type, Index, Key>::element_type&
reference_pack_element<Type, Index, Key>::operator[](
    index_type
) noexcept
{
    return *this;
}

// Immutably returns the reference pack element corresponding to the index
template <class Type, class Index, class Key>
constexpr const typename reference_pack_element<Type, Index, Key>::element_type&
reference_pack_element<Type, Index, Key>::operator[](
    index_type
) const noexcept
{
    return *this;
}

// Returns the reference pack element corresponding to the key
template <class Type, class Index, class Key>
constexpr typename reference_pack_element<Type, Index, Key>::element_type&
reference_pack_element<Type, Index, Key>::operator[](
    const key_type&
) noexcept
{
    return *this;
}

// Immutably returns the reference pack element corresponding to the key
template <class Type, class Index, class Key>
constexpr const typename reference_pack_element<Type, Index, Key>::element_type&
reference_pack_element<Type, Index, Key>::operator[](
    const key_type&
) const noexcept
{
    return *this;
}
// -------------------------------------------------------------------------- //



// ---------------------- REFERENCE PACK BASE: LIFECYCLE -------------------- //
// Explicitly constructs a reference pack base from references
template <std::size_t... Indices, class... Types>
template <class... Args, class>
constexpr reference_pack_base<pack_index_sequence<Indices...>, Types...>::
reference_pack_base(
    Args&&... args
)
: reference_pack_element<Types, pack_index<Indices>>(
    std::forward<Args>(args)
)...
{
}
// -------------------------------------------------------------------------- //



// ------------------------ REFERENCE PACK: LIFECYCLE ----------------------- //
// Explicitly constructs a reference pack from references
template <class... Types>
template <class... Args, class>
constexpr reference_pack<Types...>::reference_pack(
    Args&&... args
)
: base(std::forward<Args>(args)...)
{
}
// -------------------------------------------------------------------------- //



// -------------------------- REFERENCE PACK: SIZE -------------------------- //
// Returns the number of elements in the pack
template <class... Types>
constexpr typename reference_pack<Types...>::size_type
reference_pack<Types...>::size(
) noexcept
{
    return sizeof...(Types);
}
// -------------------------------------------------------------------------- //



// ========================================================================== //
} // namespace pck
#endif // _REFERENCE_PACK_HPP_INCLUDED
// ========================================================================== //


