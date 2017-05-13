#ifndef KEYEVENTMAPPER_HPP
#define KEYEVENTMAPPER_HPP

#include <std/limits>
#include <std/cstddef>
#include <cpp/List.hpp>
#include <kernel/ps2/Key.hpp>

/// \addtogroup Kernel
/// \{

namespace ps2
{

class KeyEventMapper
{
	public:
		typedef char Character;

		enum class Mapping
		{
			QwertyUk,
			QwertyUs,
			AzertyFr,
			AzertyBe,
			MappingNumber
		};
		
		KeyEventMapper(Mapping mapping);
		void registerEvent(const KeyEvent& event);
		bool pendingCharacter() const;
		Character getCharacter();

	private:
		struct KeyEventMapping
		{
			Key _key;
			Character _character;
			bool _shiftNeeded;
			bool _altNeeded;
		};

		bool isEventSatisfied(const KeyEventMapping& event) const;

		List<Character> _characterQueue;
		bool _lShiftPressed{false};
		bool _rShiftPressed{false};
		bool _capsLocked{false};
		bool _lControlPressed{false};
		bool _rControlPressed{false};
		bool _lAltPressed{false};
		bool _rAltPressed{false};
		Mapping _currentMapping;
		static constexpr size_t _mappingNumber{static_cast<size_t>(Mapping::MappingNumber)};
		static constexpr size_t _keyEventMappingNumber{std::numeric_limits<Character>::max()};
		static const KeyEventMapping _mappings[_mappingNumber][_keyEventMappingNumber];
};

}// namespace ps2

/// \}

#endif// KEYEVENTMAPPER_HPP
