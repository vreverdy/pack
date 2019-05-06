// =========================== TYPE TEMPLATE PACK =========================== //
// Project:         Pack
// Name:            type_template_pack.hpp
// Description:     A pack of templates of types
// Creator:         Vincent Reverdy
// Contributor(s):  Vincent Reverdy [2019]
// License:         BSD 3-Clause License
// ========================================================================== //
#ifndef _TYPE_TEMPLATE_PACK_HPP_INCLUDED
#define _TYPE_TEMPLATE_PACK_HPP_INCLUDED
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



/* ********************** TYPE TEMPLATE PACK TEMPLATE *********************** */
// Type template pack template structure declaration
template <class>
struct type_template_pack_template;

// Type template pack template structure specialization
template <template <class...> class Template, class... Types>
struct type_template_pack_template<Template<Types...>>
{
    template <class... T>
    using type = Template<T...>;
};
/* ************************************************************************** */



/* *********************** TYPE TEMPLATE PACK ELEMENT *********************** */
// Type template pack element definition
template <
    template <class...> class Template,
    class Index,
    template <class...> class Key = Template
>
class type_template_pack_element
{
    // Types and constants
    public:
    using element_type = type_template_pack_element;
    template <class... Types>
    using type = Template<Types...>;
    using index_type = Index;
    template <class... Types>
    using key_type = Key<Types...>;
    static constexpr auto index = index_type::value;

    // Lifecycle
    public:
    constexpr type_template_pack_element() noexcept = default;
    template <class... Args>
    explicit constexpr type_template_pack_element(
        const Template<Args...>&
    ) noexcept;
    template <class... Args>
    constexpr type_template_pack_element(
        const Template<Args...>&,
        index_type
    ) noexcept;
    template <class... Args, class... K>
    constexpr type_template_pack_element(
        const Template<Args...>&,
        index_type,
        const Key<K...>&
    );

    // Access
    public:
    constexpr element_type operator[](index_type) const noexcept;
    template <class... Args>
    constexpr element_type operator[](const Key<Args...>&) const noexcept;
};
/* ************************************************************************** */



/* ************************* TYPE TEMPLATE PACK BASE ************************ */
// Type template pack base class declaration
template <class, template <class...> class...>
class type_template_pack_base;

// Type template pack base class specialization
template <std::size_t... Indices, template <class...> class... Templates>
class type_template_pack_base<
    pack_index_sequence<Indices...>,
    Templates...
>
: type_template_pack_element<Templates, pack_index<Indices>>...
{
    // Inheritance
    public:
    using type_template_pack_element<
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



/* *************************** TYPE TEMPLATE PACK *************************** */
// Type template pack class definition
template <template <class...> class... Templates>
class type_template_pack
: type_template_pack_base<
    make_pack_index_sequence<sizeof...(Templates)>,
    Templates...
>
{
    // Implementation details: type traits
    template <class>
    struct _rebind;
    template <template <class...> class T, class... Types>
    struct _rebind<T<Types...>> {
        template <template <class...> class U>
        using type = U<Types...>;
    };
    template <class... Args>
    using _if_constructible_from_t = std::void_t<
        typename _rebind<Args>::template type<Templates>...
    >;
    
    // Types and inheritance
    public:
    using size_type = std::size_t;
    using index_sequence = make_pack_index_sequence<sizeof...(Templates)>;
    using base = type_template_pack_base<index_sequence, Templates...>;
    using base::operator[];

    // Lifecycle
    public:
    constexpr type_template_pack() noexcept = default;
    template <class... Args, class = _if_constructible_from_t<Args...>>
    explicit constexpr type_template_pack(const Args&...) noexcept;

    // Size
    public:
    static constexpr size_type size() noexcept;
};

// Class template argument deduction guide
template <class... Args>
type_template_pack(const Args&...)
-> type_template_pack<type_template_pack_template<Args>::template type...>;
/* ************************************************************************** */



// ------------------ TYPE TEMPLATE PACK ELEMENT: LIFECYCLE ----------------- //
// Explicitly constructs a template pack element from a type
template <
    template <class...> class Template,
    class Index,
    template <class...> class Key
>
template <class... Args>
constexpr type_template_pack_element<Template, Index, Key>::
type_template_pack_element(
    const Template<Args...>&
) noexcept
{
}

// Explicitly constructs a template pack element from a type and an index
template <
    template <class...> class Template,
    class Index,
    template <class...> class Key
>
template <class... Args>
constexpr type_template_pack_element<Template, Index, Key>::
type_template_pack_element(
    const Template<Args...>&,
    index_type
) noexcept
{
}

// Explicitly constructs a template pack element from type, index, and key
template <
    template <class...> class Template,
    class Index,
    template <class...> class Key
>
template <class... Args, class... K>
constexpr type_template_pack_element<Template, Index, Key>::
type_template_pack_element(
    const Template<Args...>&,
    index_type,
    const Key<K...>&
)
{
}
// -------------------------------------------------------------------------- //



// ------------------- TYPE TEMPLATE PACK ELEMENT: ACCESS ------------------- //
// Returns the template pack element template corresponding to the index
template <
    template <class...> class Template,
    class Index,
    template <class...> class Key
>
constexpr
typename type_template_pack_element<Template, Index, Key>::element_type
type_template_pack_element<Template, Index, Key>::operator[](
    index_type
) const noexcept
{
    return {};
}

// Returns the template pack element corresponding to the key
template <
    template <class...> class Template,
    class Index,
    template <class...> class Key
>
template <class... Args>
constexpr
typename type_template_pack_element<Template, Index, Key>::element_type
type_template_pack_element<Template, Index, Key>::operator[](
    const Key<Args...>&
) const noexcept
{
    return {};
}
// -------------------------------------------------------------------------- //



// ---------------------- TYPE TEMPLATE PACK: LIFECYCLE --------------------- //
// Explicitly constructs a template pack from objects of these types
template <template <class...> class... Templates>
template <class... Args, class>
constexpr type_template_pack<Templates...>::type_template_pack(
    const Args&...
) noexcept
{
}
// -------------------------------------------------------------------------- //



// ------------------------ TYPE TEMPLATE PACK: SIZE ------------------------ //
// Returns the number of elements in the pack
template <template <class...> class... Templates>
constexpr typename type_template_pack<Templates...>::size_type
type_template_pack<Templates...>::size(
) noexcept
{
    return sizeof...(Templates);
}
// -------------------------------------------------------------------------- //



// ========================================================================== //
} // namespace pck
#endif // _TYPE_TEMPLATE_PACK_HPP_INCLUDED
// ========================================================================== //
