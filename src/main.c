#include <stdio.h> /* printf */

#include "pciheader.h"

int main(int argc, char** argv)
{
	struct pci_access* pacc;
	struct pci_dev* dev;
	uint8_t bus, device, func; 

	if (argc != 4) {
		printf("Syntax Error. Exepect 3 arguments and it was given %d\n", argc-1);
		printf("Usage: %s <bus> <device> <function>\n", argv[0]);
		return -1;
	}
	
	pacc = pci_alloc(); 	/* get the pci_access struct */
	pci_init(pacc); 	/* init the pci lib */
	pci_scan_bus(pacc); 	/* get the list of devices */

	bus = pci_convert_hexstring(argv[1]);
	device = pci_convert_hexstring(argv[2]);
	func = pci_convert_hexstring(argv[3]);

	/* check if the input device exists */
	if ((dev = pci_search_device(pacc, bus, device, func)) == NULL) {
		printf("No device found with %x:%x:%x\n", bus, device, func);
		return -1;
	}

	pci_print_header(dev);

	return 0;
}

