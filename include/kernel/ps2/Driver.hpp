#ifndef DRIVER_HPP
#define DRIVER_HPP

namespace ps2
{

class Driver
{
	protected:
		bool read(uint8_t& byte);
		bool write(uint8_t byte);

	private:
		bool testStatus(uint8_t statusToTest);

		static constexpr uint16_t _dataPort{0x60};
		static constexpr uint16_t _commandPort{0x64};
		unsigned int _triesMaxNumber{1000};

		enum Status : uint8_t
		{
			OutBufferFull      = 1 << 0,
			InBufferFull       = 1 << 1,
			SystemFlag         = 1 << 2,
			DeviceOrController = 1 << 3,
			Unknow1            = 1 << 4,
			Unknow2            = 1 << 5,
			TimeOutError       = 1 << 6,
			ParityError        = 1 << 7
		};
};

} // namespace ps2



#endif // DRIVER_HPP
