#import "../kernel/ports.h"
#import "../drivers/screen.h"
#import "../drivers/serial.h"

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
	unsigned short vendor = pci_read_config(bus,device,function,0);
	return vendor;
}

unsigned short pci_check_device_id(unsigned char bus, unsigned char device, unsigned char function)
{
	unsigned short device_id = pci_read_config(bus,device,function,2);
	return device_id;
}

unsigned short pci_check_function(unsigned char bus, unsigned char device,unsigned char function)
{
	unsigned short device_function = pci_read_config(bus,device,function,11);
	return device_function;
}

unsigned short pci_check_subfunction(unsigned char bus, unsigned char device, unsigned char function)
{
	unsigned short device_subfunction = pci_read_config(bus,device,function,10);
	return device_subfunction;
}

unsigned short pci_check_header(unsigned char bus, unsigned char device,unsigned char function)
{
	unsigned short header = pci_read_config(bus,device,function,14);
	return header;
}

unsigned short* pci_check_device(unsigned char bus, unsigned char device)
{
	unsigned short* pci_info[4];
	unsigned short function = 0;
	
	unsigned short vendor = pci_check_vendor(bus,device,function);
	pci_info[0] = vendor;

	if(vendor == 0xffff) {return pci_info;}
	unsigned short header = pci_check_header(bus,device,function);
	pci_info[1] = header;
	if((header & 0x80) != 0)
	{
		for (function = 1;function<8;function ++)
		{
			if(pci_check_vendor(bus,device,function) != 0xffff)
			{
				unsigned short device_function = pci_check_function(bus,device,function);
				pci_info[2] = device_function;
				return pci_info;
			}
		}
	}
}

void pci_check_for_ahci(void)
{
	unsigned short bus;
	unsigned char device;
	unsigned char function;

	for(bus=0;bus<256;bus++)
	{
		for(device=0;device<32;device++)
		{
			char* buffer1[3];
			char* buffer2[3];
			char* buffer3[7];
			char* buffer4[7];
			char* buffer5[7];
			char* busstr = itoa(bus,buffer1,10);
			char* devicestr= itoa(device,buffer2,10);
			char* vendorstr= itoa(pci_check_vendor(bus,device,0),buffer3,6);
			char* deviceidstr= itoa(pci_check_device_id(bus,device,0),buffer5,6);
			char* classcodestr= itoa(pci_check_function(bus,device,0),buffer4,6);

			s_print(SINFO, "Checking for PCI port on bus: ",9,busstr," device: ",devicestr, " vendor: 0x",vendorstr,
					  "Device ID: 0x",deviceidstr," Class Code: 0x", classcodestr);

			if(pci_check_vendor(bus,device,0)==0xffff)
			{
				s_print(SINFO,"PCI port vendor 0xFFFF, no device found.",0);
			}
			else
			{
				for(function=0;function<8;function++)
				{
					if(pci_check_subfunction(bus,device,function)==0x06 && 
						pci_check_function(bus,device,function) ==0x01)
					{
						print("\nfound AHCI port at PCI bus %d , device %d, function %d",WHITE_ON_BLACK,3,
								bus,device,function);
						s_print(SINFO,"found AHCI port at PCI bus %d , device %d, function %d",3,
								bus,device,function);
					}
				}
			}
			
		}
	}
}