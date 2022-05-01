#ifndef __PCIHEADER_H__
#define __PCIHEADER_H__

#include <stdint.h>
#include <pci/pci.h>

struct pci_type_0_header {
	uint16_t vendor_id;
	uint16_t device_id;
	uint16_t command;
	uint16_t status;
	uint8_t revision_id;
	uint8_t class_code[3];
	uint8_t cache_line_s;
	uint8_t lat_timer;
	uint8_t header_type;
	uint8_t bist;
	uint32_t bar0;
	uint32_t bar1;
	uint32_t bar2;
	uint32_t bar3;
	uint32_t bar4;
	uint32_t bar5;
	uint32_t carbus_cis_pointer;
	uint16_t subsystem_vendor_id;
	uint16_t subsystem_id;
	uint32_t expesion_rom_base_addr;
	uint8_t cap_pointer;
	uint8_t reserved[7];
	uint8_t interrupt_line;
	uint8_t interrupt_pin;
	uint8_t min_gnt;
	uint8_t max_lat;
} __attribute__((packed));

/* functions signature */
int 		pci_convert_hexstring (char*);
struct pci_dev* pci_search_device     (struct pci_access*, uint8_t, uint8_t, uint8_t);
void		pci_print_header      (struct pci_dev*);

#endif /* __PCIHEADER_H__ */
