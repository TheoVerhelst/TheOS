#include <io/in.hpp>
#include <io/out.hpp>
#include <kernel/ps2/Ps2Driver.hpp>

namespace ps2
{

bool Ps2Driver::read(uint8_t& byte)
{
	byte = inb(_dataPort);
	return byte != 0 and byte != 0xFF;
}

bool Ps2Driver::write(uint8_t byte)
{
	unsigned int triesNumber{0};
	bool ready{false};
	while(triesNumber < _triesMaxNumber and not ready)
		ready = not testStatus(Status::InBufferFull);
	if(ready)
		outb(_dataPort, byte);
	return ready;
}

bool Ps2Driver::testStatus(uint8_t statusToTest)
{
	return inb(_commandPort) & statusToTest;
}

}// namespace ps2
