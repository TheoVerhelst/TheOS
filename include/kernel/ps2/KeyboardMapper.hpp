#ifndef KeyboardMapper_HPP
#define KeyboardMapper_HPP

#include <cstddef>
#include <cstdint>
#include <type_traits>
#include <kernel/ps2/Key.hpp>
#include <kernel/ps2/ScancodeSequence.hpp>

namespace ps2
{

class KeyboardMapper
{
	public:
		enum class Mapping : size_t
		{
			ScancodeSet1 = 0,
			ScancodeSet2,
			ScancodeSet3,
			MappingNumber
		};

		KeyboardMapper(Mapping mapping);
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

#endif// KeyboardMapper_HPP
