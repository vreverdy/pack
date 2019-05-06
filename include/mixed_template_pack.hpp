// ========================== MIXED TEMPLATE PACK =========================== //
// Project:         Pack
// Name:            mixed_template_pack.hpp
// Description:     A pack of templates of a type and non-types
// Creator:         Vincent Reverdy
// Contributor(s):  Vincent Reverdy [2019]
// License:         BSD 3-Clause License
// ========================================================================== //
#ifndef _MIXED_TEMPLATE_PACK_HPP_INCLUDED
#define _MIXED_TEMPLATE_PACK_HPP_INCLUDED
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



/* ********************** MIXED TEMPLATE PACK TEMPLATE ********************** */
// Mixed template pack template structure declaration
template <class>
struct mixed_template_pack_template;

// Mixed template pack template structure specialization
template <
    template <class, auto...> class Template,
    class Type,
    auto... Nontypes
>
struct mixed_template_pack_template<Template<Type, Nontypes...>>
{
    template <class T, auto... V>
    using type = Template<T, V...>;
};
/* ************************************************************************** */



/* *********************** MIXED TEMPLATE PACK ELEMENT ********************** */
// Mixed template pack element definition
template <
    template <class, auto...> class Template,
    class Index,
    template <class, auto...> class Key = Template
>
class mixed_template_pack_element
{
    // Types and constants
    public:
    using element_type = mixed_template_pack_element;
    template <class Type, auto... Nontypes>
    using type = Template<Type, Nontypes...>;
    using index_type = Index;
    template <class Type, auto... Nontypes>
    using key_type = Key<Type, Nontypes...>;
    static constexpr auto index = index_type::value;

    // Lifecycle
    public:
    constexpr mixed_template_pack_element() noexcept = default;
    template <class Arg, auto... Args>
    explicit constexpr mixed_template_pack_element(
        const Template<Arg, Args...>&
    ) noexcept;
    template <class Arg, auto... Args>
    constexpr mixed_template_pack_element(
        const Template<Arg, Args...>&,
        index_type
    ) noexcept;
    template <class Arg, auto... Args, class T, auto... K>
    constexpr mixed_template_pack_element(
        const Template<Arg, Args...>&,
        index_type,
        const Key<T, K...>&
    );

    // Access
    public:
    constexpr element_type operator[](index_type) const noexcept;
    template <class Arg, auto... Args>
    constexpr element_type operator[](const Key<Arg, Args...>&) const noexcept;
};
/* ************************************************************************** */



/* ************************ MIXED TEMPLATE PACK BASE ************************ */
// Mixed template pack base class declaration
template <class, template <class, auto...> class...>
class mixed_template_pack_base;

// Mixed template pack base class specialization
template <std::size_t... Indices, template <class, auto...> class... Templates>
class mixed_template_pack_base<
    pack_index_sequence<Indices...>,
    Templates...
>
: mixed_template_pack_element<Templates, pack_index<Indices>>...
{
    // Inheritance
    public:
    using mixed_template_pack_element<
        Templates,
        pack_index<Indices>
    >::operator[]...;

    // Implementation details: types and constants
    private:
    using element_type = void;
    using type = void;
    using index_type = void;
    using key_type = void;
    static constexpr std::size_t index = -1;
};
/* ************************************************************************** */



/* *************************** MIXED TEMPLATE PACK ************************** */
// Mixed template pack class definition
template <template <class, auto...> class... Templates>
class mixed_template_pack
: mixed_template_pack_base<
    make_pack_index_sequence<sizeof...(Templates)>,
    Templates...
>
{
    // Implementation details: type traits
    template <class>
    struct _rebind;
    template <template <class, auto...> class T, class Type, auto... Nontypes>
    struct _rebind<T<Type, Nontypes...>> {
        template <template <class, auto...> class U>
        using type = U<Type, Nontypes...>;
    };
    template <class... Args>
    using _if_constructible_from_t = std::void_t<
        typename _rebind<Args>::template type<Templates>...
    >;
    
    // Types and inheritance
    public:
    using size_type = std::size_t;
    using index_sequence = make_pack_index_sequence<sizeof...(Templates)>;
    using base = mixed_template_pack_base<index_sequence, Templates...>;
    using base::operator[];

    // Lifecycle
    public:
    constexpr mixed_template_pack() noexcept = default;
    template <class... Args, class = _if_constructible_from_t<Args...>>
    explicit constexpr mixed_template_pack(const Args&...) noexcept;

    // Size
    public:
    static constexpr size_type size() noexcept;
};

// Class template argument deduction guide
template <class... Args>
mixed_template_pack(const Args&...)
-> mixed_template_pack<
    mixed_template_pack_template<Args>::template type...
>;
/* ************************************************************************** */



// ----------------- MIXED TEMPLATE PACK ELEMENT: LIFECYCLE ----------------- //
// Explicitly constructs a template pack element from a type
template <
    template <class, auto...> class Template,
    class Index,
    template <class, auto...> class Key
>
template <class Arg, auto... Args>
constexpr mixed_template_pack_element<Template, Index, Key>::
mixed_template_pack_element(
    const Template<Arg, Args...>&
) noexcept
{
}

// Explicitly constructs a template pack element from a type and an index
template <
    template <class, auto...> class Template,
    class Index,
    template <class, auto...> class Key
>
template <class Arg, auto... Args>
constexpr mixed_template_pack_element<Template, Index, Key>::
mixed_template_pack_element(
    const Template<Arg, Args...>&,
    index_type
) noexcept
{
}

// Explicitly constructs a template pack element from type, index, and key
template <
    template <class, auto...> class Template,
    class Index,
    template <class, auto...> class Key
>
template <class Arg, auto... Args, class T, auto... K>
constexpr mixed_template_pack_element<Template, Index, Key>::
mixed_template_pack_element(
    const Template<Arg, Args...>&,
    index_type,
    const Key<T, K...>&
)
{
}
// -------------------------------------------------------------------------- //



// ------------------ MIXED TEMPLATE PACK ELEMENT: ACCESS ------------------- //
// Returns the template pack element template corresponding to the index
template <
    template <class, auto...> class Template,
    class Index,
    template <class, auto...> class Key
>
constexpr
typename mixed_template_pack_element<Template, Index, Key>::element_type
mixed_template_pack_element<Template, Index, Key>::operator[](
    index_type
) const noexcept
{
    return {};
}

// Returns the template pack element corresponding to the key
template <
    template <class, auto...> class Template,
    class Index,
    template <class, auto...> class Key
>
template <class Arg, auto... Args>
constexpr
typename mixed_template_pack_element<Template, Index, Key>::element_type
mixed_template_pack_element<Template, Index, Key>::operator[](
    const Key<Arg, Args...>&
) const noexcept
{
    return {};
}
// -------------------------------------------------------------------------- //



// --------------------- MIXED TEMPLATE PACK: LIFECYCLE --------------------- //
// Explicitly constructs a template pack from objects of these types
template <template <class, auto...> class... Templates>
template <class... Args, class>
constexpr mixed_template_pack<Templates...>::mixed_template_pack(
    const Args&...
) noexcept
{
}
// -------------------------------------------------------------------------- //



// ------------------------ MIXED TEMPLATE PACK: SIZE ----------------------- //
// Returns the number of elements in the pack
template <template <class, auto...> class... Templates>
constexpr typename mixed_template_pack<Templates...>::size_type
mixed_template_pack<Templates...>::size(
) noexcept
{
    return sizeof...(Templates);
}
// -------------------------------------------------------------------------- //



// ========================================================================== //
} // namespace pck
#endif // _MIXED_TEMPLATE_PACK_HPP_INCLUDED
// ========================================================================== //
