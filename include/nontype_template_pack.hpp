// ========================= NONTYPE TEMPLATE PACK ========================== //
// Project:         Pack
// Name:            nontype_template_pack.hpp
// Description:     A pack of templates of nontypes
// Creator:         Vincent Reverdy
// Contributor(s):  Vincent Reverdy [2019]
// License:         BSD 3-Clause License
// ========================================================================== //
#ifndef _NONTYPE_TEMPLATE_PACK_HPP_INCLUDED
#define _NONTYPE_TEMPLATE_PACK_HPP_INCLUDED
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



/* ********************* NONTYPE TEMPLATE PACK TEMPLATE ********************* */
// Non-type template pack template structure declaration
template <class>
struct nontype_template_pack_template;

// Non-type template pack template structure specialization
template <template <auto...> class Template, auto... Nontypes>
struct nontype_template_pack_template<Template<Nontypes...>>
{
    template <auto... V>
    using type = Template<V...>;
};
/* ************************************************************************** */



/* ********************** NONTYPE TEMPLATE PACK ELEMENT ********************* */
// Non-type template pack element definition
template <
    template <auto...> class Template,
    class Index,
    template <auto...> class Key = Template
>
class nontype_template_pack_element
{
    // Types and constants
    public:
    using element_type = nontype_template_pack_element;
    template <auto... Nontypes>
    using type = Template<Nontypes...>;
    using index_type = Index;
    template <auto... Nontypes>
    using key_type = Key<Nontypes...>;
    static constexpr auto index = index_type::value;

    // Lifecycle
    public:
    constexpr nontype_template_pack_element() noexcept = default;
    template <auto... Args>
    explicit constexpr nontype_template_pack_element(
        const Template<Args...>&
    ) noexcept;
    template <auto... Args>
    constexpr nontype_template_pack_element(
        const Template<Args...>&,
        index_type
    ) noexcept;
    template <auto... Args, auto... K>
    constexpr nontype_template_pack_element(
        const Template<Args...>&,
        index_type,
        const Key<K...>&
    );

    // Access
    public:
    constexpr element_type operator[](index_type) const noexcept;
    template <auto... Args>
    constexpr element_type operator[](const Key<Args...>&) const noexcept;
};
/* ************************************************************************** */



/* *********************** NONTYPE TEMPLATE PACK BASE *********************** */
// Non-type template pack base class declaration
template <class, template <auto...> class...>
class nontype_template_pack_base;

// Non-type template pack base class specialization
template <std::size_t... Indices, template <auto...> class... Templates>
class nontype_template_pack_base<
    pack_index_sequence<Indices...>,
    Templates...
>
: nontype_template_pack_element<Templates, pack_index<Indices>>...
{
    // Inheritance
    public:
    using nontype_template_pack_element<
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



/* ************************** NONTYPE TEMPLATE PACK ************************* */
// Non-type template pack class definition
template <template <auto...> class... Templates>
class nontype_template_pack
: nontype_template_pack_base<
    make_pack_index_sequence<sizeof...(Templates)>,
    Templates...
>
{
    // Implementation details: type traits
    template <class>
    struct _rebind;
    template <template <auto...> class T, auto... Nontypes>
    struct _rebind<T<Nontypes...>> {
        template <template <auto...> class U>
        using type = U<Nontypes...>;
    };
    template <class... Args>
    using _if_constructible_from_t = std::void_t<
        typename _rebind<Args>::template type<Templates>...
    >;
    
    // Types and inheritance
    public:
    using size_type = std::size_t;
    using index_sequence = make_pack_index_sequence<sizeof...(Templates)>;
    using base = nontype_template_pack_base<index_sequence, Templates...>;
    using base::operator[];

    // Lifecycle
    public:
    constexpr nontype_template_pack() noexcept = default;
    template <class... Args, class = _if_constructible_from_t<Args...>>
    explicit constexpr nontype_template_pack(const Args&...) noexcept;

    // Size
    public:
    static constexpr size_type size() noexcept;
};

// Class template argument deduction guide
template <class... Args>
nontype_template_pack(const Args&...)
-> nontype_template_pack<
    nontype_template_pack_template<Args>::template type...
>;
/* ************************************************************************** */



// ---------------- NONTYPE TEMPLATE PACK ELEMENT: LIFECYCLE ---------------- //
// Explicitly constructs a template pack element from a type
template <
    template <auto...> class Template,
    class Index,
    template <auto...> class Key
>
template <auto... Args>
constexpr nontype_template_pack_element<Template, Index, Key>::
nontype_template_pack_element(
    const Template<Args...>&
) noexcept
{
}

// Explicitly constructs a template pack element from a type and an index
template <
    template <auto...> class Template,
    class Index,
    template <auto...> class Key
>
template <auto... Args>
constexpr nontype_template_pack_element<Template, Index, Key>::
nontype_template_pack_element(
    const Template<Args...>&,
    index_type
) noexcept
{
}

// Explicitly constructs a template pack element from type, index, and key
template <
    template <auto...> class Template,
    class Index,
    template <auto...> class Key
>
template <auto... Args, auto... K>
constexpr nontype_template_pack_element<Template, Index, Key>::
nontype_template_pack_element(
    const Template<Args...>&,
    index_type,
    const Key<K...>&
)
{
}
// -------------------------------------------------------------------------- //



// ----------------- NONTYPE TEMPLATE PACK ELEMENT: ACCESS ------------------ //
// Returns the template pack element template corresponding to the index
template <
    template <auto...> class Template,
    class Index,
    template <auto...> class Key
>
constexpr
typename nontype_template_pack_element<Template, Index, Key>::element_type
nontype_template_pack_element<Template, Index, Key>::operator[](
    index_type
) const noexcept
{
    return {};
}

// Returns the template pack element corresponding to the key
template <
    template <auto...> class Template,
    class Index,
    template <auto...> class Key
>
template <auto... Args>
constexpr
typename nontype_template_pack_element<Template, Index, Key>::element_type
nontype_template_pack_element<Template, Index, Key>::operator[](
    const Key<Args...>&
) const noexcept
{
    return {};
}
// -------------------------------------------------------------------------- //



// -------------------- NONTYPE TEMPLATE PACK: LIFECYCLE -------------------- //
// Explicitly constructs a template pack from objects of these types
template <template <auto...> class... Templates>
template <class... Args, class>
constexpr nontype_template_pack<Templates...>::nontype_template_pack(
    const Args&...
) noexcept
{
}
// -------------------------------------------------------------------------- //



// ----------------------- NONTYPE TEMPLATE PACK: SIZE ---------------------- //
// Returns the number of elements in the pack
template <template <auto...> class... Templates>
constexpr typename nontype_template_pack<Templates...>::size_type
nontype_template_pack<Templates...>::size(
) noexcept
{
    return sizeof...(Templates);
}
// -------------------------------------------------------------------------- //



// ========================================================================== //
} // namespace pck
#endif // _NONTYPE_TEMPLATE_PACK_HPP_INCLUDED
// ========================================================================== //
