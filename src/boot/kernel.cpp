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
		out.setBase(16);
		out << "Loaded from " << (info.boot_device & 0x000000FF) << " on partition ";
		out << (info.boot_device & 0x0000FF00);
		out << "." << (info.boot_device & 0x00FF0000);
		out << "." << (info.boot_device  & 0xFF000000) << "\n";
		out.setBase(10);
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
