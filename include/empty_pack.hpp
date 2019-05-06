// =============================== EMPTY PACK =============================== //
// Project:         Pack
// Name:            empty_pack.hpp
// Description:     A pack of nothing
// Creator:         Vincent Reverdy
// Contributor(s):  Vincent Reverdy [2019]
// License:         BSD 3-Clause License
// ========================================================================== //
#ifndef _EMPTY_PACK_HPP_INCLUDED
#define _EMPTY_PACK_HPP_INCLUDED
// ========================================================================== //



// ================================ PREAMBLE ================================ //
// C++ standard library
// Project sources
#include "pack_details.hpp"
// Third-party libraries
// Miscellaneous
namespace pck {
// ========================================================================== //



/* ***************************** EMPTY PACK BASE **************************** */
// Empty pack base class definition
class empty_pack_base
{
    // Implementation details: types and constants
    private:
    using element_type = void;
    using type = void;
    using index_type = void;
    using key_type = void;
    static constexpr std::size_t index = -1;
};
/* ************************************************************************** */



/* ******************************* EMPTY PACK ******************************* */
// Empty pack class definition
class empty_pack
: empty_pack_base
{
    // Types and inheritance
    public:
    using size_type = std::size_t;
    using index_sequence = make_pack_index_sequence<0>;
    using base = empty_pack_base;

    // Lifecycle
    public:
    constexpr empty_pack() noexcept = default;

    // Size
    public:
    static constexpr size_type size() noexcept;
};
/* ************************************************************************** */



// ---------------------------- EMPTY PACK: SIZE ---------------------------- //
// Returns the number of elements in the pack, or in other words, zero
constexpr typename empty_pack::size_type empty_pack::size(
) noexcept
{
    return 0;
}
// -------------------------------------------------------------------------- //



// ========================================================================== //
} // namespace pck
#endif // _EMPTY_PACK_HPP_INCLUDED
// ========================================================================== //
