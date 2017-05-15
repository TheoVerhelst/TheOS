#ifndef SCANCODEMAPPER_HPP
#define SCANCODEMAPPER_HPP

#include <std/cstddef>
#include <std/cstdint>
#include <std/type_traits>
#include <kernel/ps2/Key.hpp>
#include <kernel/ps2/Scancode.hpp>

namespace ps2
{

class ScancodeMapper
{
	public:
		enum class Mapping : size_t
		{
			ScancodeSet1 = 0,
			ScancodeSet2,
			ScancodeSet3,
			MappingNumber
		};

		ScancodeMapper(Mapping mapping);
		const KeyEvent& get(const Scancode& scancode);

	private:
		struct ScancodeMapping
		{
			Scancode _scancode;
			KeyEvent _keyEvent;
		};

		Mapping _currentMapping{Mapping::ScancodeSet1};
		static constexpr KeyEvent _unknowEvent{Key::Unknown, false};
		static constexpr uint8_t _firstEscapeByte{0xE0};
		static constexpr uint8_t _secondEscapeByte{0xE1};
		static constexpr size_t _scancodeMappingNumber{2 * static_cast<size_t>(Key::KeyNumber)};
		static constexpr size_t _mappingNumber{static_cast<size_t>(Mapping::MappingNumber)};
		static const ScancodeMapping _mappings[_mappingNumber][_scancodeMappingNumber];
};

} // namespace ps2



#endif // SCANCODEMAPPER_HPP
