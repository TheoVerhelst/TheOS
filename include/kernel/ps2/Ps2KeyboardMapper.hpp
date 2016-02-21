#ifndef PS2KEYBOARDMAPPER_HPP
#define PS2KEYBOARDMAPPER_HPP

#include <cstddef>
#include <cstdint>
#include <type_traits>
#include <kernel/ps2/Key.hpp>

namespace ps2
{

class Ps2KeyboardMapper
{
	public:
		struct ScancodeSequence
		{
			static constexpr size_t _maxLength{6};
			size_t _length;
			uint8_t _scancodes[_maxLength];
			bool operator==(const ScancodeSequence& other) const;
		};

		enum class Mapping : size_t
		{
			ScancodeSet1 = 0,
			ScancodeSet2,
			ScancodeSet3,
			MappingNumber
		};

		Ps2KeyboardMapper(Mapping mapping);
		const KeyEvent& get(const ScancodeSequence& sequence);
		Mapping getCurrentMapping() const;
		void setCurrentMapping(Mapping newCurrentMapping);

	private:
		struct ScancodeMapping
		{
			ScancodeSequence _sequence;
			KeyEvent _keyEvent;
		};

		Mapping _currentMapping{Mapping::ScancodeSet1};
		static constexpr KeyEvent _unknowEvent{Key::Unknown, false};
		static constexpr size_t _scancodeMappingNumber{2 * static_cast<size_t>(Key::KeyNumber)};
		static constexpr size_t _mappingNumber{static_cast<size_t>(Mapping::MappingNumber)};
		static const ScancodeMapping _mappings[_mappingNumber][_scancodeMappingNumber];
};

}// namespace ps2

#endif// PS2KEYBOARDMAPPER_HPP
