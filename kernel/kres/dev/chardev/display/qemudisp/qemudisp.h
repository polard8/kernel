// qemudisp.h
// Display controller support.

#ifndef __QEMUDISP_H
#define __QEMUDISP_H    1

extern struct pci_device_d *PCIDeviceQemuDisplay;

//
// ======================================================
//


int qemu_display_initialize(void);

#endif  

