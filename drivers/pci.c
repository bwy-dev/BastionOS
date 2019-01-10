#import "../kernel/ports.h"


unsigned short pci_read_config(unsigned char bus, unsigned char device,
										 unsigned char function,unsigned char offset)
{
	unsigned long address;
	unsigned long lbus = (unsigned long)bus;
	unsigned long ldevice = (unsigned long)device;
	unsigned long lfunction = (unsigned long)function;
	unsigned short temp = 0;

	address = (unsigned long)((lbus <<16) | (ldevice <<11) | 
					(lfunction <<8)|(offset&0xfc)| ((unsigned long)0x80000000));

	port_outl(0xcf8, address);

	temp = (unsigned short)((port_inl(0xcfc)>>((offset&2)*8)) & 0xffff);
	return (temp);
}

unsigned short pci_check_vendor(unsigned char bus, unsigned char device, unsigned char function)
{
	vendor = pci_read_config(bus,device,function,0);
	return vendor;
}

unsigned short pci_check_function(unsigned char bus, unsigned char device,unsigned char function)
{
	function = pci_read_config(bus,device,function,8);
	return function;
}

unsigned short pci_check_header(unsigned char bus, unsigned char device,unsigned char function)
{
	header = pci_read_config(bus,device,function,0x0c);
	return header;
}

void pci_check_device(unsigned char bus, unsigned char device)
{
	unsigned short function = 0;

	vendor = pci_check_vendor(bus,device);
	if(vendor == 0xffff) {return;}
	header = pci_check_header(bus,device,function);
	if((header & 0x80) != 0)
	{
		for (function = 1;function<8;function ++)
		{
			if(pci_check_vendor(bus,device,function) != 0xffff)
			{
				pci_check_function(bus,device,function);
			}
		}
	}
}

void pci_check_all(void)
{
	unsigned short bus;
	unsigned char device;

	for(bus=0;bus<256;bus++)
	{
		for(device=0;device<32;device++)
		{
			pci_check_device(bus,device);
		}
	}
}