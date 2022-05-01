#include "pciheader.h"
#include <stdio.h>  /* printf */
#include <stdlib.h> /* strtol */
#include <string.h> /* str funcs */
#include <stddef.h> /* offsetof macro */

int pci_convert_hexstring(char* hexstring)
{
	int number;
	if (strstr(hexstring, "0x") == NULL) {
		number = (int) strtol(hexstring, NULL, 16);
	}
	else {
		number = (int) strtol(hexstring, NULL, 0);
	}
	return number;
}

struct pci_dev* pci_search_device(struct pci_access* pacc, uint8_t bus, uint8_t device, uint8_t func)
{
	struct pci_dev* dev = NULL;
	for (dev = pacc->devices; dev != NULL; dev = dev->next) {
		if ((dev->bus == bus) && (dev->dev == device) && (dev->func == func)) {
			break;
		}
	}
	return dev;
}

void pci_print_header(struct pci_dev* dev)
{
	printf("Vendor ID: 0x%X\n", pci_read_word(dev, offsetof(struct pci_type_0_header, vendor_id)));
	printf("device ID: 0x%X\n", pci_read_word(dev, offsetof(struct pci_type_0_header, device_id)));
	printf("Command: 0x%X\n", pci_read_word(dev, offsetof(struct pci_type_0_header, command)));
	printf("Status: 0x%X\n", pci_read_word(dev, offsetof(struct pci_type_0_header, status)));
	printf("Revision ID: 0x%X\n", pci_read_byte(dev, offsetof(struct pci_type_0_header, revision_id)));
	printf("BAR0: 0x%X\n", pci_read_long(dev, offsetof(struct pci_type_0_header, bar0)));
	printf("BAR1: 0x%X\n", pci_read_long(dev, offsetof(struct pci_type_0_header, bar1)));
	printf("BAR2: 0x%X\n", pci_read_long(dev, offsetof(struct pci_type_0_header, bar2)));
	printf("BAR3: 0x%X\n", pci_read_long(dev, offsetof(struct pci_type_0_header, bar3)));
	printf("BAR4: 0x%X\n", pci_read_long(dev, offsetof(struct pci_type_0_header, bar4)));
	printf("BAR5: 0x%X\n", pci_read_long(dev, offsetof(struct pci_type_0_header, bar5)));
}
