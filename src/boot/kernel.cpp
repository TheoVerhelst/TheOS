#if defined (__linux__) || !defined (__i386__)
 #error "Must be cross-compiled i686-elf to work properly!"
#endif

#include <io/Printer.hpp>
#include <boot/MultibootInfo.hpp>

Printer out;

extern "C" void kernel_main(const MultibootInfo& info)
{
	uint32_t memSize = reinterpret_cast<uint32_t>(info.mem_upper) - reinterpret_cast<uint32_t>(info.mem_lower);
	out << "Available memory = " << memSize/1024 << " Mb\n";
	if(info.flags & InfoAvailable::boot_device)
	{
		switch(info.boot_device.drive)
		{
			case 0x00:
				out << "Loaded from 1st floppy disk";
				break;
			case 0x01:
				out << "Loaded from 2nd floppy disk";
				break;
			case 0x80:
				out << "Loaded from 1st hard disk";
				break;
			case 0x81:
				out << "Loaded from 2nd hard disk";
				break;
			default:
				out << "Unrecognized drive number";
		}
		out << " on partition " << info.boot_device.part1;
		out << "." << info.boot_device.part2;
		out << "." << info.boot_device.part3 << "\n";
	}
	if(info.flags & InfoAvailable::cmdline)
		out << "Command line: \"" << info.cmdline << "\"\n";
	if(info.flags & InfoAvailable::mods)
		out << info.mods_count << "modules loaded\n";
	if(info.flags & InfoAvailable::mmap)
		out << "Memory map buffer size = " << info.mmap_length << "\n";
	if(info.flags & InfoAvailable::drives)
		out << "Size of the drives structure: " << info.drives_length << "\n";
	if(info.flags & InfoAvailable::boot_loader_name)
		out << "Adress of the config table: " << info.config_table << "\n";
	if(info.flags & InfoAvailable::boot_loader_name)
		out << "This kernel has been loaded by " << info.boot_loader_name << "\n";
	if(info.flags & InfoAvailable::apm_table)
		out << "APM table adress: " << info.apm_table << "\n";
	if(info.flags & InfoAvailable::vbe)
		out << "Video mode is enabled\n";
}
