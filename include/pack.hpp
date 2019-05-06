// ================================== PACK ================================== //
// Project:         Pack
// Name:            pack.hpp
// Description:     Include the entire pack library
// Creator:         Vincent Reverdy
// Contributor(s):  Vincent Reverdy [2019]
// License:         BSD 3-Clause License
// ========================================================================== //
#ifndef _PACK_HPP_INCLUDED
#define _PACK_HPP_INCLUDED
// ========================================================================== //



// ================================ PREAMBLE ================================ //
// C++ standard library
// Project sources
#include "pack_details.hpp"
#include "pack_index.hpp"
#include "empty_pack.hpp"
#include "type_pack.hpp"
#include "nontype_pack.hpp"
#include "type_template_pack.hpp"
#include "nontype_template_pack.hpp"
#include "mixed_template_pack.hpp"
#include "object_pack.hpp"
#include "reference_pack.hpp"
// Third-party libraries
// Miscellaneous
namespace pck {
// ========================================================================== //



/* ********************************** PACK ********************************** */
// Pack overload set declaration
constexpr empty_pack pack() noexcept;
template <class... Types>
constexpr type_pack<Types...> pack() noexcept;
template <auto... Nontypes>
constexpr nontype_pack<Nontypes...> pack() noexcept;
template <template <class...> class... Templates>
constexpr type_template_pack<Templates...> pack() noexcept;
template <template <auto...> class... Templates>
constexpr nontype_template_pack<Templates...> pack() noexcept;
template <template <class, auto...> class... Templates>
constexpr mixed_template_pack<Templates...> pack() noexcept;
template <class... References>
constexpr reference_pack<References&&...> pack(References&&...);
/* ************************************************************************** */



// ---------------------------------- PACK ---------------------------------- //
// Creates an empty pack
constexpr empty_pack pack(
) noexcept
{
    return {};
}

// Creates a pack of types
template <class... Types>
constexpr type_pack<Types...> pack(
) noexcept
{
    return {};
}

// Creates a pack of non-types
template <auto... Nontypes>
constexpr nontype_pack<Nontypes...> pack(
) noexcept
{
    return {};
}

// Creates a pack of type templates
template <template <class...> class... Templates>
constexpr type_template_pack<Templates...> pack(
) noexcept
{
    return {};
}

// Creates a pack of non-type templates
template <template <auto...> class... Templates>
constexpr nontype_template_pack<Templates...> pack(
) noexcept
{
    return {};
}

// Creates a pack of mixed templates
template <template <class, auto...> class... Templates>
constexpr mixed_template_pack<Templates...> pack(
) noexcept
{
    return {};
}

// Creates a pack of references
template <class... References>
constexpr reference_pack<References&&...> pack(
    References&&... references
)
{
    return {std::forward<References>(references)...};
}
// -------------------------------------------------------------------------- //



// ========================================================================== //
} // namespace pck
#endif // _PACK_HPP_INCLUDED
// ========================================================================== //
