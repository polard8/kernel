;
; main.asm
; Main file for creating a 32MB virtual disk using nasm.
; The goal is loading the boot manager, BM.BIN in 0:8000H
; and pass the control to the boot loader, also delivering
; some few arguments.
; Here you will also find the VBR of the first partition
; at the sector 63, in hex, two FATs, reserved sectors, root dir,
; data area and a VHD footer.
; The video mode is the text mode.
; 2017 - Created by Fred Nora.

; The standard MBR entry point is 0x7C00.
; The origin in 0x0000,
; but the segments in 0x07C0.

[ORG 0]

[bits 16]

MBR_main:

; ----------------------------------
; Stage 1. The MBR.
    %include "stage1.asm"
; Padding for setting up the VBR at the right place.
eof:                                                      ; 
    times (63*512) - (eof-MBR_main) db 'b' ;63 sec.

; ----------------------------------
; The VBR of the first partition.
; Sector 63.
; FAT16 for EFI support.
; Maybe it needs to be FAT32.
fs_fat16_vbr:
    %include "vbr1.asm"    

; ----------------------------------
; Three hidden sectors.
fs_hidden_sectors:
    times (512) db 'h'  ;64
    times (512) db 'h'  ;65
    times (512) db 'h'  ;66

; ----------------------------------
; First FAT.
; Sector 67.
; 246 sectors size.
fs_fat16_fat1: 
.firstSector:
    db 0xf8, 0xff, 0xff, 0xff
    times (512)-(4) db 0
.allTheRest:
    times (245*512) db 0 

; ----------------------------------
; Second FAT.
; Sector 313.
; 246 sectors size.
fs_fat16_fat2:
.firstSector:
    db 0xf8, 0xff, 0xff, 0xff
    times (512)-(4) db 0
.allTheRest:
    times (245*512) db 0 

; ----------------------------------
; Root dir.
; Sector 559.
; Size?
; The first two entries are labels.
fs_fat16_rootdir:
.firstEntry:   
; Label: (GRAMAD1)
    db 0x47, 0x52, 0x41, 0x4D, 0x41, 0x44, 0x31, 0x20
    db 0x20, 0x20, 0x20, 0x08, 0x00, 0x00, 0x00, 0x00 
    db 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xEE, 0x7B
    db 0x1B, 0x4B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
; Label: (GRAMAD2)
    db 0x47, 0x52, 0x41, 0x4D, 0x41, 0x44, 0x32, 0x20
    db 0x20, 0x20, 0x20, 0x08, 0x00, 0x00, 0x00, 0x00 
    db 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xEE, 0x7B
    db 0x1B, 0x4B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
; Padding to fill the whole directory.
; Each entry has 32 bytes and the directory has 512 entries.
    times (32*512) - (32*2) db  0

; ----------------------------------
; Data area
; Sector 591
; Size?
; 32MB of data area.
fs_fat16_data_area:                                                   
    times  (32*1024*1024) - ( fs_fat16_data_area - MBR_main ) -(4) db 0  
end_of_disk:
    db '$FN$'
; ========
; ## END OF DISK ##


; ----------------------------------
; VHD footer.
; M$
; This is the last component,
; maybe it helps on Windows machines.
vhdfooter_start:
    %include "footer1.asm"

;
; End
;



