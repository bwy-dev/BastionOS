#ifndef PCI_H
#define PCI_H

unsigned short pci_read_config(unsigned char bus, unsigned char device,
										 unsigned char function,unsigned char offset);
unsigned short pci_check_vendor(unsigned char bus, unsigned char device, unsigned char function);
unsigned short pci_check_function(unsigned char bus, unsigned char device,unsigned char function);
unsigned short pci_check_subfunction(unsigned char bus, unsigned char device, unsigned char function);
unsigned short pci_check_header(unsigned char bus, unsigned char device,unsigned char function);
void pci_check_afor_ahci(void);
unsigned short* pci_check_device(unsigned char bus, unsigned char device);

#endif