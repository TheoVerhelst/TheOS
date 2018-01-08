#include <kernel/io.hpp>
#include <kernel/ps2/Driver.hpp>

namespace ps2
{

bool Driver::read(uint8_t& byte)
{
	byte = inb(_dataPort);
	return byte != 0 and byte != 0xFF;
}

bool Driver::write(uint8_t byte)
{
	unsigned int triesNumber{0};
	bool ready{false};
	while(triesNumber < _triesMaxNumber and not ready)
		ready = not testStatus(Status::InBufferFull);
	if(ready)
		outb(_dataPort, byte);
	return ready;
}

bool Driver::testStatus(uint8_t statusToTest)
{
	return inb(_commandPort) & statusToTest;
}

} // namespace ps2
