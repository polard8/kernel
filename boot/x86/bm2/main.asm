;
; bm/main.asm 
;    Main file of Boot manager.
; Video modes:
; ============
; VirtualBox:
; ===============
; Oracle VirtualBox: 0x0112   640x480x24bpp
; Oracle VirtualBox: 0x0115   800x600x24BPP
; Oracle VirtualBox: 0x0118  1024x768x24BPP
; Nvidia GeForce:  
; =================
; GeForce_8400_GS equ 0x06E4  
; GeForce 8400 GS: 0x0115   800x600x32BPP
; The main resolution is 800x600x24.
; The only way to change the resolution for now is 
; changing a global variable in this document.
; History:
; 2005 - Created by Fred Nora. 
; Credits: MikeOS (License: BSD).
;---------------------------------------------------
; #importante
; This image was loaded in 0H:8000H.
; It's easier to handle the gdt stuff 
; when the org is in 8000H and the segment is 0H.
; 32768 - 65535 (hex: 8000h - FFFFh)

; #bugbug
; 32KB is the limit for this program?
; We are almost there.



;       +----------+
;       |          | 
;       |----------| 
;       | BL.BIN   | 
;       |          | 
;       |----------| 0x2000:0x0000
;       |          | 
;       |----------| 
;       |          | 
;       |BM.BIN    | 
;       |          | The entry point.
;  >>>  |----------| 0x0000:0x8000 :)
;       |          |
;       |----------| 0x0000:0x6000
;       |INITIAL   | Initial stack address.
;       |STACK     | It goes down.
;       |----------| 
;       |          |
;       |----------| 
;       | FAT/ROOT |
;       |----------| 0x0000:0x1000
;       |          |
;       +----------+

	%DEFINE GBM_VER '1.1'	; version number

[ORG 0x8000]

;;=====================================
;;    Entry point do Boot Manager    ;;
;;=====================================
;; The gramado mode
;; it will select the video mode.
;; The video mode depends on the gramado mode.
;; See: rmStartGUI on pm.inc
;; This is the default mode.
;; But actually the mode is selected by the user
;; in the command shell.
;; It's like a 'gamemode'.

;;GRAMADO_DEFAULT_MODE EQU 0x00  ; jail        320x200
;;GRAMADO_DEFAULT_MODE EQU 0x01  ; p1          640x480
GRAMADO_DEFAULT_MODE EQU 0x02  ; home        800x600
;;GRAMADO_DEFAULT_MODE EQU 0x03  ; p2          1024x768
;;GRAMADO_DEFAULT_MODE EQU 0x04  ; castle      ??
;;GRAMADO_DEFAULT_MODE EQU 0x05  ; california  ??
;; ...

;; == Selecting the mode =======================
;; This is the default video mode.
;; we will use this if the 'gramado mode' fail.
;; the video mode depends on the 'gramado mode'
;; Global variables to set the video mode 
;; Well tested modes.
;; ok on qemu.
;; It works on nvidia geforce too, but with 32bpp.

;; 24bpp on qemu
;; G_VIDEO_MODE EQU 0x010F    ;320x200
G_VIDEO_MODE EQU 0x0112    ;640x480
;; G_VIDEO_MODE EQU 0x0115    ;800x600
;; G_VIDEO_MODE EQU 0x0118    ;1024x768
;; ...
;; ======================================

;; 16 bit:
;; Estamos no primeiro setor do BM.BIN, ele começa em 16 bit.
[bits 16]

; Entry point.
; This is the entry point for the BM.BIN.
; Jump after the data area.
os_call_vectors:
    jmp bm_main
    ;jmp bm_vector1
    ;jmp bm_vector2
    ;jmp bm_vector3
    ;jmp bm_vector4
    ; ...

; Data
; see: features/disk.inc
ROOTDIRSTART EQU  (bootmanagerOEM_ID)
ROOTDIRSIZE  EQU  (bootmanagerOEM_ID+4)

; ========
; bm_main:
; The real entry point.
; #importante: 
; O unico argumento passado pelo MBR foi o numero do disco.
; IN: dl = Disk number.
; /dev/sda - 0x80
; /dev/sdb - 0x81
; /dev/sdc - 0x82
; /dev/sdd - 0x83

bm_main:
; Entry point. (16bits)

; Set up registers.
; Adjust segment registers and stack.
; Code located at 0000:0x8000. 
; Stack located at 0000:0x6000.

    cli
    mov ax, 0x0000
    mov ss, ax
    mov sp, 0x6000 
    sti

; The default direction for string operations
; will be 'up' - incrementing address in RAM
    cld

    mov ax, 0x0000
    mov ds, ax
    mov es, ax

; Save disk number.

    mov byte [bootmanagerDriveNumber], dl
    mov byte [META$FILE.DISK_NUMBER], dl
    mov byte [DISKINFO16_disk_number], dl

; =====================
; Reset keyboard controller.
; see:
; http://www.ctyme.com/intr/int-16.htm

; Int 16/AX=0601h - AAKEYS - EMPTY KEY-EVENT BUFFER
    ;xor ax, ax
    ;mov ax,  0601h
    ;int 0x16

; Int 16/AH=04h - Tandy 2000 - KEYBOARD - FLUSH KEYBOARD BUFFER
    ;xor ax, ax
    ;mov ah,  04h
    ;int 0x16

; Int 16/AH=25h - HUNTER 16 - RESET KEYBOARD
    ;xor ax, ax
    ;mov ah,  25h
    ;int 0x16

; Int 16/AX=6F09h - HP Vectra EX-BIOS - F16_KBD_RESET - RESET KEYBOARD TO DEFAULTS
    ;xor ax, ax
    ;mov ax,  6F09h
    ;int 0x16

; Int 16/AH=FFh - KEYBOARD - KBUF extensions - ADD KEY TO TAIL OF KEYBOARD BUFFER
    ;xor ax, ax
    ;mov ah,  0xFF
    ;int 0x16


; #test
; Set the keyboard repeat rate to the max
    ;; mov ax, 0x0305
    ;; xor bx,bx 
    ;; int 0x16

; get keystroke
; Int 16/AH=00h - KEYBOARD - GET KEYSTROKE
; On extended keyboards, this function discards any extended keystrokes, 
; returning only when a non-extended keystroke is available. 
    ;xor ax, ax
    ;int 0x16

; Get disk info.
; Get drive parameters: 
; =====================
; Return: CF set on error.
; AH = status (07h).
; CF clear if successful.
; AH = 00h.
; AL = 00h on at least some BIOSes.
; BL = drive type (AT/PS2 floppies only). 
; CH = low eight bits of maximum cylinder number.
; CL = maximum sector number (bits 5-0).
;      high two bits of maximum cylinder number (bits 7-6).
; DH = maximum head number.
; DL = number of drives.

    xor ax, ax
    mov ah, byte 08h
    int 0x13 

; Heads.
; Numero de heads.
; Logical last index of heads = (number_of - 1). 
; (Because index starts with 0).
; Obs: 
; O valor de Heads foi gravado no BPB mas precisar� ser passado a diante
; para uso posterior.

    xor ax, ax
    mov al, dh
    inc ax    ;From 0-based to count.
    ;Number of heads.
    mov word [bootmanagerNumHeads], ax
    mov word [META$FILE.HEADS], ax
    mov word [DISKINFO16_heads], ax

; Sectors Per Track e Cylinders.
; Essas informações apresentam meio truncadas
; O valor do número de cilindros é aprentado
; de forma parcial, uma parte em cada registrador.
; spt:
; bits [5:0] logical last index of sectors per track = number_of 
; (because index starts with 1).
; cyl:
; bits [7:6] [15:8] logical last index of cylinders = number_of - 1 
; (because index starts with 0).
; Sectors Per Track - (SPT).
; "Esconde 2 bits que pertencem a quantidade de setores".
; Obs: 
; O valor de SPT foi gravado no BPB mas precisar 
; ser passado a diante para uso posterior.

    xor eax, eax 
    mov al, cl
    and al, byte 00111111b            ;03Fh
    mov byte [SectorsPerTrack], al    ;BPB (word).
    ;Sectors per track.
    mov ah, 0                                  ; enviamos apenas 'al' 
    mov word [bootmanagerSectorsPerTrack], ax  ; enviamos apenas 'al'
    mov word [META$FILE.SPT], ax
    mov word [DISKINFO16_spt], ax   

; Cylinders
; Obs: 
; O valor de CylinderNumbers foi gravado em variável 
; mas precisar ser passado a diante para uso posterior.

    xor eax, eax
    mov al, cl           ; Two high bits of cylinder number in bits 6&7.
    and al, 11000000b    ; Mask it.
    shl ax, 2            ; Move them to bits 8&9.
    mov al, ch           ; Rest of the cylinder bits.(low 8 bits)
    inc eax              ; Number is 0-based.
    ; Numero de cilindros do disco.
    mov word [save_cylinder_numbers], ax
    mov word [META$FILE.CYLINDERS], ax
    mov word [DISKINFO16_cylinders], ax

; ++
; ---------------------------------
restart_loop:

; Draw the background.
    mov ax, os_init_msg       ; Set up the welcome screen
    mov bx, os_version_msg
    mov cx, 10011111b         ; Colour: white text on light blue
    call os_draw_background

; Draw the dialog box.
; See: dialog.inc
    mov ax, dialog_string_1  ; Ask if user wants app selector or command-line
    mov bx, dialog_string_2
    mov cx, dialog_string_3
    mov dx, 1                ; We want a two-option dialog box (OK or Cancel)
    call os_dialog_box

; Select boot option.
; 1 = Starts system GUI.
; 0 = Starts the Boot Manager CLI.
    mov byte [finish_saved_boot_option], 1  ; default option.

; If OK (option 0) chosen, start app selector
; O right foi selecionado?
; Se não foi o right então carregue a imagem.
; usaremos a opçao de boot default.
; Load the BL.BIN image.
    cmp ax, 1 
    jne near load_stuff  ;app_selector

; Caso contrario usaremos a opção CLI.
; 1 = Starts system GUI.
; 0 = Starts the Boot Manager CLI.
    mov byte [finish_saved_boot_option], 0
    jmp load_stuff

    jmp restart_loop
    jmp $
; ---------------------------------
; --

;
; Load stuff --------------------------
;
load_stuff:
; Load the BL.BIN image.

    call Window.ClearScreen
    
; IN:
; ax = pointer to the image name.

    ;mov ax, word bootmanager_ImageName1
    ;call test_load_bl_image

    mov ax, word bootmanager_ImageName2
    call test_load_bl_image

; Trampoline.
; see: finish.inc
    push WORD 0
    push WORD AFTER_DATA 
    retf

;---------------------------------------------------------
; Data for the above code...

    os_init_msg     db 'Gramado Boot Manager', 0
    ;os_version_msg  db 'Version ', GBM_VER, 0
    os_version_msg  db ':) ', 0

    dialog_string_1  db 'Please select an option:', 0
    dialog_string_2  db '+ [OK] to initialize the system       ', 0
    dialog_string_3  db '+ [Cancel] for command line           ', 0

bootmanager_ImageName1:
    db "BL      BIN", 0x0D, 0x0A, 0x00
bootmanager_ImageName2:
    db "BL      BIN", 0x0D, 0x0A, 0x00

;
; == Includes ========
;

; 16bit includes.
    %include "features/s2metafile.inc"
    %include "features/s2header.inc"
    %include "features/s2bpb.inc"
    %include "features/s2gdt.inc"
    %include "features/s2vesa.inc" 
    %include "features/s2config16.inc" 
    %include "features/s2a20.inc"
    %include "features/s2lib.inc"
    %include "features/s2fat12.inc"
    %include "features/s2fat16.inc"
    %include "features/s2menu16.inc"
    %include "features/s2modes.inc"
    %include "features/s2detect.inc"
    %include "features/lib16.inc"
    %include "features/disk.inc"
    %include "features/screen.inc"
    %include "features/dialog.inc"
    %include "features/finish.inc"
    %include "features/pm.inc"

;--------------------------------------------------------
; 32 bits - (Boot Manager 32bit Asm.)
;--------------------------------------------------------

[bits 32]

bootmanager_main:

; Em ordem de prioridade na compilação.

; 14 - Header principal. 
; Definições globais usadas em 32bit.
; Header principal em 32 bits.
    %include "extras/header32.inc"
; 13 - Headers. 
    %include "extras/system.inc"       ; System configuration.
    %include "extras/init.inc"         ; Initialization configuration.
    %include "extras/sysvar32.inc"     ; Variáveis do sistema.
    %include "extras/x8632/gdt32.inc"  ; Gdt
    %include "extras/x8632/idt32.inc"  ; Idt
    %include "extras/x8632/ldt32.inc"  ; Ldt
    %include "extras/x8632/tss32.inc"  ; Tss
    %include "extras/stacks32.inc"     ; Stacks
    %include "extras/x8632/ints32.inc"    ; Handles para as interrupções.
    %include "extras/fs/fat16header.inc"  ; Headers para o sistema de arquivos fat16.
; 12 - Monitor.
    %include "extras/drivers/screen32.inc"  ; Rotinas de screen em 32 bits.
    %include "extras/drivers/input32.inc"   ; Rotinas de input 2m 32 bits.
    %include "extras/string32.inc"  ; Rotinas de strings em 32 bits.
    %include "extras/font32.inc"    ; Fonte.
; 11 - Hardware.
    %include "extras/x8632/cpuinfo.inc"  ; CPU
    %include "extras/hardware.inc"       ; Hardware
    ; ...
; 10 - Irqs.
    %include "extras/drivers/timer.inc"     ; Irq 0, Timer.
    %include "extras/drivers/keyboard.inc"  ; Irq 1, Keyboard.
    %include "extras/drivers/fdc32.inc"     ; Irq 6, Fdc. (@todo: Suspender o suporte.)
    %include "extras/drivers/clock.inc"     ; Irq 8, Clock.
    %include "extras/drivers/hdd32.inc"     ; Irq 14/15, Hdd.
    ; ...
; 9 - Tasks. (#no tasks)
; Rotinas de inicialização do sistema de tarefas.
    %include "extras/tasks32.inc"   
; 8 - lib32.
; Rotinas em 32 bits. 
; 7 - setup  
; Inicializa arquitetura.
    %include "extras/setup.inc"
; 6 - Disk.
    %include "extras/fs/fat12pm.inc"   ;FAT12 em 32 bits.
    %include "extras/fs/fat16lib.inc"  ;FAT16 (rotinas).
    %include "extras/fs/fat16.inc"     ;FAT16 (funçoes principais).
    %include "extras/fs/ramfs.inc"     ;RamDisk fs.
    %include "extras/fs/format.inc"    ;Formata.
    %include "extras/fs/fs32.inc"      ;fs, (gerencia os sistemas de arquivos).
; 5 - File.
    %include "extras/installer.inc"   ;Instala metafiles em LBAs específicas.
    %include "extras/fs/file.inc"     ;Operaçoes com aquivos.
    %include "extras/bootloader.inc"  ;Carrega o Boot Loader (BL.BIN).
; 4 - Debug.
; System debug.
    %include "extras/debug.inc"
; 3 - blconfig.
; Gerencia a inicialização.
    %include "extras/blconfig.inc"
; 2 - Boot Manager 32bit Mini-Shell.
; Prompt de comandos.
    %include "extras/shell32/shell.inc"
    %include "extras/shell32/shcalls.inc"  ;Chamadas dos comandos.
    %include "extras/shell32/shlib.inc"    ;Lib de funções do Shell.
    %include "extras/shell32/shmsg.inc"    ;Mensagens e variáveis do Shell.
; 1 - Start.
    %include "extras/start.inc"
; 0 - lib32.
;Rotinas em 32 bits.
    %include "extras/lib32.inc" 
; ========================================================

;
; Buffer
;

root_buffer:
fat_buffer:
    ; nop

;
; End
;

