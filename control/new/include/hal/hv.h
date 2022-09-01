

// hv.h
// Hypervisor stuff.

#ifndef __HV_H
#define __HV_H    1

// #remember: Little endian?


// ----------------------------
// "ACRNACRNACRN"
// A Big Little Hypervisor for IoT Development.
// 0x4E524341, 0x4E524341, 0x4E524341
#define HV_STRING_ACRN_PART1  0x4E524341
#define HV_STRING_ACRN_PART2  0x4E524341
#define HV_STRING_ACRN_PART3  0x4E524341

// -------------------
// apple
// "GenuineIntel" – Apple Rosetta 2[8]
// "VirtualApple" – Newer versions of Apple Rosetta 2


// ----------------------------
// "bhyve bhyve "
// THE BSD HYPERVISOR.
// 0x76796862, 0x68622065, 0x20657679
#define HV_STRING_BHYVE_PART1  0x76796862
#define HV_STRING_BHYVE_PART2  0x68622065
#define HV_STRING_BHYVE_PART3  0x20657679

// ----------------------------
// "Microsoft Hv" – Microsoft Hyper-V or Windows Virtual PC

// ----------------------------
// " KVMKVMKVM "  – KVM ??

// ----------------------------
// QEMU hypervisor
// "TCGTCGTCGTCG" – QEMU
#define HV_STRING_QEMU_PART1  0x54474354
#define HV_STRING_QEMU_PART2  0x43544743
#define HV_STRING_QEMU_PART3  0x47435447

// ----------------------------
// " QNXQVMBSQG "
// QNX Hypervisor
// 0x51584E51, 0x53424D56, 0x00004751
#define HV_STRING_QNX_PART1  0x51584E51
#define HV_STRING_QNX_PART2  0x53424D56
#define HV_STRING_QNX_PART3  0x00004751

// ----------------------------
// "VMwareVMware" – VMware

// ----------------------------
// "XenVMMXenVMM" – Xen HVM

// =============================================


#define HV_TYPE_UNDEFINED  0
#define HV_TYPE_QEMU       1000
#define HV_TYPE_KVM        1001
#define HV_TYPE_BHYVE      1002
#define HV_TYPE_QNX        1003
#define HV_TYPE_ACRN       1004
// ...

struct hv_d
{
// The structure is fully initializzed.
    int initialized;
    int type;
};

// see: detect.c
extern struct hv_d  HVInfo;


#endif    



