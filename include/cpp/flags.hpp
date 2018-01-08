#ifndef FLAGS_HPP
#define FLAGS_HPP

/// Namespace with functions related to bitfield and flags manipulation. It is
/// not suited to a class, since we sometimes need to have bitfields with unusual
/// length (such as for the page table entry flags). Then, here are free
/// template functions applicable on any bit field type.
namespace flags
{
	/// Checks whether flags are all set in a bitfield.
	/// \param bitField The bit field to check.
	/// \param flags The flags to look for.
	/// \tparam BitField An unsigned integer type.
	/// \tparam Flags A type convertible to BitField.
	/// \return true if the flags are set, false otherwhise.
	template <typename BitField, typename Flags>
	constexpr bool allSet(BitField bitField, Flags flags);

} // namespace flags

namespace flags
{
	template <typename BitField, typename Flags>
	constexpr bool allSet(BitField bitField, Flags flags)
	{
		return (bitField & static_cast<BitField>(flags)) == static_cast<BitField>(flags);
	}

} // namespace flags

#endif // FLAGS_HPP
