;
; File: lib16\s2detect.inc
;
; Descrição:
;     Rotinas que usam os recursos do BIOS para detectar hardware presente.
; 
; Version: 1.0, 2015 - Created.
;

;------------------------------------------------------------------
; SATA Controller Modes: IDE, AHCI, or RAID. Enabling RAID mode 
;                        also enables the AHCI features.
;
; IDE mode is the simplest mode. In IDE mode, 
; the hard drive is set to run as an IDE or Parallel ATA (PATA) hard drive.
;
; AHCI:
; =====
; Advanced Host Controller Interface.
; AHCI is a newer way to interface with the SATA controller. This allows you 
; to take advantage of SATA features such as Native Command Queuing. 
; AHCI mode becomes really relevant with SSD for queuing and processing 
; commands and for some other features.
;

;--------------------------------------------------------------------
; DetectionMain:
; Rotinas que usam os recursos do BIOS para detectar hadware presente.
;
DetectionMain:
    nop    ; Ainda não implementada. 
    ret
	
;
; End.
;

