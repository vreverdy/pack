// ============================== NONTYPE PACK ============================== //
// Project:         Pack
// Name:            nontype_pack.hpp
// Description:     A pack of non-types
// Creator:         Vincent Reverdy
// Contributor(s):  Vincent Reverdy [2019]
// License:         BSD 3-Clause License
// ========================================================================== //
#ifndef _NONTYPE_PACK_HPP_INCLUDED
#define _NONTYPE_PACK_HPP_INCLUDED
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



/* ************************** NONTYPE PACK ELEMENT ************************** */
// Non-type pack element definition
template <auto Nontype, class Index, auto Key = Nontype>
class nontype_pack_element
{
    // Implementation details: type traits
    private:
    template <class Arg, class K>
    using _if_constructible_from_t = std::enable_if_t<
        (Arg::value == Nontype) && (K::value == Key)
    >;
    
    // Types and constants
    public:
    using element_type = nontype_pack_element;
    using type = decltype(Nontype);
    using index_type = Index;
    using key_type = decltype(Key);
    static constexpr auto index = index_type::value;

    // Lifecycle
    public:
    constexpr nontype_pack_element() noexcept = default;
    template <class Arg, class = std::enable_if_t<Arg::value == Nontype>>
    explicit constexpr nontype_pack_element(const Arg&) noexcept;
    template <class Arg, class = std::enable_if_t<Arg::value == Nontype>>
    constexpr nontype_pack_element(const Arg&, index_type) noexcept;
    template <class Arg, class K, class = _if_constructible_from_t<Arg, K>>
    constexpr nontype_pack_element(const Arg&, index_type, const K&);

    // Access
    public:
    constexpr element_type operator[](index_type) const noexcept;
    template <class K, class = std::enable_if_t<K::value == Key>>
    constexpr element_type operator[](const K&) const noexcept;
};

// Class template argument deduction guides
template <
    class Arg,
    class Index,
    auto Nontype = Arg::value
>
nontype_pack_element(const Arg&, Index)
-> nontype_pack_element<Nontype, Index>;
template <
    class Arg,
    class Index,
    class K,
    auto Nontype = Arg::value,
    auto Key = K::value
>
nontype_pack_element(const Arg&, Index, const K&)
-> nontype_pack_element<Nontype, Index, Key>;
/* ************************************************************************** */



/* *************************** NONTYPE PACK BASE **************************** */
// Non-type pack base class declaration
template <class, auto...>
class nontype_pack_base;

// Non-type pack base class specialization
template <std::size_t... Indices, auto... Nontypes>
class nontype_pack_base<pack_index_sequence<Indices...>, Nontypes...>
: nontype_pack_element<Nontypes, pack_index<Indices>>...
{
    // Inheritance
    public:
    using nontype_pack_element<Nontypes, pack_index<Indices>>::operator[]...;

    // Implementation details: types and constants
    private:
    using element_type = void;
    using type = void;
    using index_type = void;
    using key_type = void;
    static constexpr std::size_t index = -1;
};
/* ************************************************************************** */



/* ****************************** NONTYPE PACK ****************************** */
// Non-type pack class definition
template <auto... Nontypes>
class nontype_pack
: nontype_pack_base<make_pack_index_sequence<sizeof...(Nontypes)>, Nontypes...>
{
    // Implementation details: type traits
    private:
    template <class Arg, auto Value>
    static constexpr bool _has_equal_value_v = Arg::value == Value;
    template <class... Args>
    using _if_constructible_from_t = std::enable_if_t<
        (_has_equal_value_v<Args, Nontypes> && ...)
    >;
    
    // Types and inheritance
    public:
    using size_type = std::size_t;
    using index_sequence = make_pack_index_sequence<sizeof...(Nontypes)>;
    using base = nontype_pack_base<index_sequence, Nontypes...>;
    using base::operator[];

    // Lifecycle
    public:
    constexpr nontype_pack() noexcept = default;
    template <class... Args, class = _if_constructible_from_t<Args...>>
    explicit constexpr nontype_pack(const Args&...) noexcept;

    // Size
    public:
    static constexpr size_type size() noexcept;
};

// Class template argument deduction guide
template <
    class... Args,
    class = std::void_t<decltype(Args::value)...>
>
nontype_pack(const Args&...)
-> nontype_pack<Args::value...>;
/* ************************************************************************** */



// -------------------- NONTYPE PACK ELEMENT: LIFECYCLE --------------------- //
// Explicitly constructs a nontype pack element from a constant value
template <auto Nontype, class Index, auto Key>
template <class Arg, class>
constexpr nontype_pack_element<Nontype, Index, Key>::nontype_pack_element(
    const Arg&
) noexcept
{
}

// Explicitly constructs a nontype pack element from constant value and index
template <auto Nontype, class Index, auto Key>
template <class Arg, class>
constexpr nontype_pack_element<Nontype, Index, Key>::nontype_pack_element(
    const Arg&,
    index_type
) noexcept
{
}

// Explicitly constructs a nontype pack element from constant value, index, key
template <auto Nontype, class Index, auto Key>
template <class Arg, class K, class>
constexpr nontype_pack_element<Nontype, Index, Key>::nontype_pack_element(
    const Arg&,
    index_type,
    const K&
)
{
}
// -------------------------------------------------------------------------- //



// ----------------------- NONTYPE PACK ELEMENT: ACCESS ---------------------- //
// Returns the non-type pack element corresponding to the index
template <auto Nontype, class Index, auto Key>
constexpr typename nontype_pack_element<Nontype, Index, Key>::element_type
nontype_pack_element<Nontype, Index, Key>::operator[](
    index_type
) const noexcept
{
    return {};
}

// Returns the non-type pack element corresponding to the key constant value
template <auto Nontype, class Index, auto Key>
template <class K, class>
constexpr typename nontype_pack_element<Nontype, Index, Key>::element_type
nontype_pack_element<Nontype, Index, Key>::operator[](
    const K&
) const noexcept
{
    return {};
}
// -------------------------------------------------------------------------- //



// ------------------------ NONTYPE PACK: LIFECYCLE ------------------------- //
// Explicitly constructs a non-type pack from constant values
template <auto... Nontypes>
template <class... Args, class>
constexpr nontype_pack<Nontypes...>::nontype_pack(
    const Args&...
) noexcept
{
}
// -------------------------------------------------------------------------- //



// --------------------------- NONTYPE PACK: SIZE --------------------------- //
// Returns the number of elements in the pack
template <auto... Nontypes>
constexpr typename nontype_pack<Nontypes...>::size_type
nontype_pack<Nontypes...>::size(
) noexcept
{
    return sizeof...(Nontypes);
}
// -------------------------------------------------------------------------- //



// ========================================================================== //
} // namespace pck
#endif // _NONTYPE_PACK_HPP_INCLUDED
// ========================================================================== //
