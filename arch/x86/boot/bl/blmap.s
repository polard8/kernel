
Allocating common symbols
Common symbol       size              file

g_fat16_fat_status  0x4               main.o
timerTicks          0x4               timer.o
prompt              0xfa              main.o
EDITBOX_LARGURA     0x4               main.o
partition           0x10              main.o
system_info         0x8               main.o
g_initialized       0x4               main.o
bliTesting          0x4               main.o
EDITBOX_BG_COLOR    0x4               main.o
shell_status        0x4               shell.o
STATUS_X            0x4               main.o
prompt_pos          0x4               main.o
g_fat16_root_status
                    0x4               main.o
STATUS_Y            0x4               main.o
shell_string_buffer
                    0x400             shell.o
deslocamento        0x4               shell.o
buffer_dir_entry    0x200             main.o
BootLoaderCR3       0x4               main.o
next_address        0x4               main.o
shift_status        0x4               keyboard.o
alt_status          0x4               keyboard.o
EDITBOX_ALTURA      0x4               main.o
g_lbf_va            0x4               main.o
LegacyCR3           0x4               main.o
g_proc_status       0x4               main.o
gdefTesting         0x4               main.o
proximo             0x4               main.o
procedure_info      0x10              main.o
EDITBOX_TEXT_COLOR  0x4               main.o
CURSOR_Y            0x4               main.o
EDITBOX_Y           0x4               main.o
current_task        0x4               main.o
g_system_color      0x4               main.o
CURSOR_X            0x4               main.o
useGUI              0x4               main.o
ret_string          0x4               shell.o
file_cluster_list   0x800             main.o
vesa_mode           0x10              main.o
escape_status       0x4               keyboard.o
g_next_app          0x4               main.o
tab_status          0x4               keyboard.o
VideoBlock          0x1c              main.o
g_cursor_y          0x4               main.o
g_cmd_status        0x4               main.o
ShellInitialized    0x4               shell.o
key_status          0x4               keyboard.o
g_file_system_type  0x4               main.o
g_char_attrib       0x4               main.o
ctrl_status         0x4               keyboard.o
g_next_proc         0x4               main.o
g_lbf_pa            0x4               main.o
winkey_status       0x4               keyboard.o
g_nova_mensagem     0x4               main.o
EDITBOX_X           0x4               main.o
g_cursor_x          0x4               main.o

Memory Configuration

Name             Origin             Length             Attributes
*default*        0x0000000000000000 0xffffffffffffffff

Linker script and memory map

                0x0000000000400000                __image_base__ = 0x400000
                0x0000000000000000                __dll__ = 0x0
                0x0000000000400000                ___ImageBase = 0x400000
                0x0000000000001000                __section_alignment__ = 0x1000
                0x0000000000000200                __file_alignment__ = 0x200
                0x0000000000000004                __major_os_version__ = 0x4
                0x0000000000000000                __minor_os_version__ = 0x0
                0x0000000000000001                __major_image_version__ = 0x1
                0x0000000000000000                __minor_image_version__ = 0x0
                0x0000000000000004                __major_subsystem_version__ = 0x4
                0x0000000000000000                __minor_subsystem_version__ = 0x0
                0x0000000000000003                __subsystem__ = 0x3
                0x0000000000200000                __size_of_stack_reserve__ = 0x200000
                0x0000000000001000                __size_of_stack_commit__ = 0x1000
                0x0000000000100000                __size_of_heap_reserve__ = 0x100000
                0x0000000000001000                __size_of_heap_commit__ = 0x1000
                0x0000000000000000                __loader_flags__ = 0x0
                0x0000000000000000                __dll_characteristics__ = 0x0

.text           0x0000000000021000     0x5000
                0x0000000000021000                code = .
                0x0000000000021000                _code = .
                0x0000000000021000                __code = .
 *(.head_x86)
 .head_x86      0x0000000000021000     0x137a head.o
                0x0000000000021000                bootloader_entry_point
                0x0000000000021181                SavedBootBlock
                0x0000000000021185                SavedLFB
                0x0000000000021189                SavedX
                0x000000000002118d                SavedY
                0x0000000000021191                SavedBPP
                0x0000000000021195                SavedBootMode
                0x0000000000021b1d                task0_stack
                0x0000000000021b21                task1_stack
                0x0000000000021b25                task2_stack
                0x0000000000021b5d                setup_idt_vector
                0x0000000000021df5                irq0
                0x0000000000021dfb                timer_test
                0x0000000000021e03                irq1
                0x0000000000021e1f                fault_N0
                0x0000000000021e29                fault_N1
                0x0000000000021e33                fault_N2
                0x0000000000021e3d                fault_N3
                0x0000000000021e47                fault_N4
                0x0000000000021e51                fault_N5
                0x0000000000021e5b                fault_INTRUCAO_INVALIDA
                0x0000000000021e65                fault_N7
                0x0000000000021e6f                fault_DOUBLE
                0x0000000000021e79                fault_N9
                0x0000000000021e83                fault_N10
                0x0000000000021e8d                fault_N11
                0x0000000000021e97                fault_STACK
                0x0000000000021ea1                fault_GP
                0x0000000000021eab                fault_N14
                0x0000000000021eb5                fault_N15
                0x0000000000021ebf                fault_N16
                0x0000000000021ec9                fault_N17
                0x0000000000021ed3                fault_N18
                0x0000000000021edd                fault_N19
                0x0000000000021ee7                fault_N20
                0x0000000000021ef1                fault_N21
                0x0000000000021efb                fault_N22
                0x0000000000021f05                fault_N23
                0x0000000000021f0f                fault_N24
                0x0000000000021f19                fault_N25
                0x0000000000021f23                fault_N26
                0x0000000000021f2d                fault_N27
                0x0000000000021f37                fault_N28
                0x0000000000021f41                fault_N29
                0x0000000000021f4b                fault_N30
                0x0000000000021f55                fault_N31
                0x0000000000021f5f                hd_buffer
                0x0000000000021f63                hd_lba
                0x0000000000021f67                test_write
                0x0000000000021f77                os_read_sector
                0x0000000000021f90                os_write_sector
                0x000000000002209f                reset_ide0
                0x0000000000022136                int48
                0x000000000002213b                int49
                0x0000000000022140                int50
                0x0000000000022145                int51
                0x000000000002214a                int52
                0x000000000002214f                int53
                0x0000000000022154                int54
                0x0000000000022159                int55
                0x000000000002215e                int56
                0x0000000000022163                int57
                0x0000000000022168                int58
                0x000000000002216d                int59
                0x0000000000022172                int100
                0x0000000000022177                int200
                0x0000000000022196                int201
                0x000000000002219b                int213
                0x00000000000221a2                my_buffer_load_bitmap_16x16
                0x0000000000022234                background
                0x0000000000022289                gui_buffer_putpixel
                0x0000000000022317                refresh_screen
                0x0000000000022368                softwarelibReboot
                0x0000000000022376                asm_shut_down
 *(.text)
 .text          0x000000000002237a      0x10b main.o
                0x000000000002237a                BlMain
                0x00000000000223d4                BlLoadKernel
                0x0000000000022400                BlLoadFiles
                0x000000000002242c                BlSetupPaging
                0x000000000002243a                BlAbort
                0x0000000000022448                BlKernelModuleMain
                0x0000000000022466                die
 .text          0x0000000000022485      0x239 loader.o
                0x0000000000022485                load_kernel
                0x000000000002254a                load_files
 .text          0x00000000000226be      0x112 init.o
                0x00000000000226be                set_up_color
                0x00000000000226cc                set_up_text_color
                0x00000000000226f8                init_globals
                0x000000000002273a                init
 .text          0x00000000000227d0       0xd5 ports.o
                0x00000000000227d0                bloutportb
                0x00000000000227dd                outb
                0x00000000000227ea                inportb
                0x00000000000227ff                outportb
                0x000000000002280c                inport8
                0x000000000002281b                outport8
                0x0000000000022828                inport16
                0x0000000000022838                outport16
                0x0000000000022846                inport32
                0x0000000000022855                outport32
                0x0000000000022862                inb
                0x0000000000022884                inportl
                0x0000000000022898                outportl
 .text          0x00000000000228a5       0xd6 x86.o
                0x00000000000228a5                enable
                0x00000000000228ac                disable
                0x00000000000228b3                stopCpu
                0x00000000000228bb                intReturn
                0x00000000000228c2                farReturn
                0x00000000000228c9                getFlags
                0x00000000000228d4                setFlags
                0x00000000000228df                BlProcessorInPort8
                0x00000000000228ee                BlProcessorOutPort8
                0x00000000000228fb                BlProcessorInPort16
                0x000000000002290b                BlProcessorOutPort16
                0x0000000000022919                BlProcessorInPort32
                0x0000000000022928                BlProcessorOutPort32
                0x0000000000022935                Push
                0x000000000002293f                Pop
                0x0000000000022949                pushRegs
                0x0000000000022950                popRegs
                0x0000000000022957                pushFlags
                0x000000000002295e                popFlags
                0x0000000000022965                getStackPointer
                0x0000000000022970                setStackPointer
 .text          0x000000000002297b      0xacc stdio.o
                0x000000000002297b                panic
                0x000000000002299c                scroll
                0x0000000000022a27                bl_clear
                0x0000000000022a81                kprintf
                0x0000000000022ed5                printf
                0x0000000000022ef2                sprintf
                0x0000000000022f47                putchar
                0x0000000000022f60                outbyte
                0x00000000000230c7                _outbyte
                0x000000000002319d                printf_main
                0x00000000000231a7                input
                0x00000000000232d6                my_buffer_horizontal_line
                0x0000000000023300                my_buffer_put_pixel
                0x000000000002331f                my_buffer_char_blt
                0x000000000002339c                vsync
                0x00000000000233d9                gui_inb
                0x00000000000233fe                get_cursor_x
                0x0000000000023413                get_cursor_y
                0x0000000000023428                carrega_bitmap_16x16
 .text          0x0000000000023447      0x25b string.o
                0x0000000000023447                strcmp
                0x00000000000234ac                strncmp
                0x0000000000023510                str_cmp
                0x000000000002358e                memcpy
                0x00000000000235cc                strlen
                0x00000000000235f3                strcpy
                0x0000000000023627                strcat
                0x0000000000023656                bcopy
                0x0000000000023682                bzero
 .text          0x00000000000236a2      0x1d6 keyboard.o
                0x00000000000236a2                keyboardHandler
 .text          0x0000000000023878      0x253 pci.o
                0x0000000000023878                pciConfigReadWord
                0x000000000002391f                pciCheckDevice
                0x0000000000023979                pciCheckVendor
                0x00000000000239b9                pciGetClassCode
                0x00000000000239ea                pciInfo
                0x0000000000023ac1                pciInit
 .text          0x0000000000023acb       0x48 hdd.o
                0x0000000000023acb                my_read_hd_sector
                0x0000000000023ae9                my_write_hd_sector
                0x0000000000023b07                limpa_root
                0x0000000000023b0d                limpa_fat
 .text          0x0000000000023b13       0x48 timer.o
                0x0000000000023b13                timer
                0x0000000000023b3f                BltimerInit
 .text          0x0000000000023b5b      0x588 pages.o
                0x0000000000023b5b                SetUpPaging
 .text          0x00000000000240e3       0x92 procedure.o
                0x00000000000240e3                bl_procedure
 .text          0x0000000000024175      0x7cf fs.o
                0x0000000000024175                fatClustToSect
                0x000000000002419c                fatLoadCluster
                0x00000000000241d8                fs_format
                0x00000000000241f1                fs_search_empty_entry
                0x00000000000241fb                fs_find_not_empty_entry
                0x0000000000024205                fs_test_fat_vector
                0x000000000002420b                fs_get_fat_entry
                0x0000000000024215                fs_create_entry
                0x000000000002421b                fsCreateFileName
                0x0000000000024221                fsSaveFileName
                0x0000000000024227                fs_save_entry_on_disc
                0x000000000002422d                fs_set_structures
                0x0000000000024233                fs_set_entry
                0x0000000000024239                fs_get_entry
                0x000000000002423f                fs_show_dir_entry
                0x0000000000024245                fs_show_dir
                0x000000000002424b                fs_check_cluster
                0x0000000000024255                fsSaveRootDir
                0x000000000002425b                fs_load_dir
                0x0000000000024261                fs_save_dir
                0x0000000000024267                fs_save_structure
                0x000000000002426d                fs_save_entry_on_root
                0x0000000000024273                fs_show_entry
                0x0000000000024279                fs_delete_entry
                0x000000000002427f                fs_init_bootfile_struct
                0x0000000000024285                fs_get_entry_status
                0x000000000002428f                fs_set_entry_status
                0x0000000000024295                fs_makeboot
                0x000000000002429f                fs_set_fat_entry
                0x00000000000242a5                fs_find_empty_entry
                0x00000000000242af                fs_install
                0x00000000000242b5                fs_relood_dir
                0x00000000000242bb                fsLoadFile
                0x0000000000024477                fsSearchFile
                0x0000000000024549                fsSearchFileName
                0x000000000002455f                fs_load_rootdirEx
                0x00000000000245b0                fs_load_fatEx
                0x00000000000245fe                fs_put_list_on_fat
                0x00000000000246c1                fs_find_n_empty_entries
                0x0000000000024742                fs_load_rootdir
                0x0000000000024750                read_lba
                0x000000000002476b                write_lba
                0x0000000000024786                fsSaveFile
                0x0000000000024790                fsCreateDir
                0x00000000000247a9                fsCreateFile
                0x00000000000248a4                fsClearFat
                0x00000000000248b2                fsCheckFat
                0x0000000000024924                fsInitFat
                0x000000000002492a                fsInitStructures
                0x0000000000024930                fsInit
 .text          0x0000000000024944      0x60b shell.o
                0x0000000000024944                shellMain
                0x00000000000249af                shellProcedure
                0x0000000000024a24                shellInitializePrompt
                0x0000000000024ab3                shellWaitCmd
                0x0000000000024acd                shellCompare
                0x0000000000024e81                shellHelp
                0x0000000000024e9a                boot
                0x0000000000024ea0                debug
                0x0000000000024ebb                testa_mbr
                0x0000000000024eec                testa_root
                0x0000000000024f20                reboot
                0x0000000000024f2e                shellInit
 .text          0x0000000000024f4f       0x14 services.o
                0x0000000000024f4f                blServices
                0x0000000000024f5d                system_services
 .text          0x0000000000024f63       0x1f abort.o
                0x0000000000024f63                abort
 .text          0x0000000000024f82      0x12b faults.o
                0x0000000000024f82                cpu_falts
                0x00000000000250a7                mostra_reg
                0x0000000000026000                . = ALIGN (0x1000)
 *fill*         0x00000000000250ad      0xf53 

.rodata         0x0000000000026000      0x610
 .rodata        0x0000000000026000       0x5f main.o
 *fill*         0x000000000002605f        0x1 
 .rodata        0x0000000000026060       0xed loader.o
 .rodata        0x000000000002614d       0x11 init.o
 *fill*         0x000000000002615e        0x2 
 .rodata        0x0000000000026160       0x38 stdio.o
 .rodata        0x0000000000026198       0x44 pci.o
 .rodata        0x00000000000261dc        0xc procedure.o
 .rodata        0x00000000000261e8      0x1c8 fs.o
 .rodata        0x00000000000263b0      0x1b2 shell.o
 .rodata        0x0000000000026562        0xd abort.o
 *fill*         0x000000000002656f        0x1 
 .rodata        0x0000000000026570       0xa0 faults.o

.eh_frame       0x0000000000027000     0x1620
 .eh_frame      0x0000000000027000       0xf4 main.o
 .eh_frame      0x00000000000270f4       0x58 loader.o
 .eh_frame      0x000000000002714c       0x98 init.o
 .eh_frame      0x00000000000271e4      0x1b8 ports.o
 .eh_frame      0x000000000002739c      0x2b8 x86.o
 .eh_frame      0x0000000000027654      0x330 stdio.o
 .eh_frame      0x0000000000027984      0x138 string.o
 .eh_frame      0x0000000000027abc       0x38 keyboard.o
 .eh_frame      0x0000000000027af4       0xe0 pci.o
 .eh_frame      0x0000000000027bd4       0x98 hdd.o
 .eh_frame      0x0000000000027c6c       0x58 timer.o
 .eh_frame      0x0000000000027cc4       0x38 pages.o
 .eh_frame      0x0000000000027cfc       0x38 procedure.o
 .eh_frame      0x0000000000027d34      0x658 fs.o
 .eh_frame      0x000000000002838c      0x198 shell.o
 .eh_frame      0x0000000000028524       0x58 services.o
 .eh_frame      0x000000000002857c       0x34 abort.o
 .eh_frame      0x00000000000285b0       0x58 faults.o

.data           0x0000000000028620      0x9e0
                0x0000000000028620                data = .
                0x0000000000028620                _data = .
                0x0000000000028620                __data = .
 *(.data)
 .data          0x0000000000028620        0x2 head.o
                0x0000000000028620                data_start
 .data          0x0000000000028622        0x0 main.o
 .data          0x0000000000028622        0x0 loader.o
 .data          0x0000000000028622        0x0 init.o
 .data          0x0000000000028622        0x0 ports.o
 .data          0x0000000000028622        0x0 x86.o
 .data          0x0000000000028622        0x0 stdio.o
 .data          0x0000000000028622        0x0 string.o
 *fill*         0x0000000000028622       0x1e 
 .data          0x0000000000028640      0x1a0 keyboard.o
                0x0000000000028640                destroy_window
                0x0000000000028644                quit_message
 .data          0x00000000000287e0        0x0 pci.o
 .data          0x00000000000287e0        0x0 hdd.o
 .data          0x00000000000287e0        0x0 timer.o
 .data          0x00000000000287e0        0x0 pages.o
 .data          0x00000000000287e0        0x0 procedure.o
 .data          0x00000000000287e0        0x0 fs.o
 .data          0x00000000000287e0       0x2c shell.o
                0x00000000000287e0                help_string
 .data          0x000000000002880c        0x0 services.o
 .data          0x000000000002880c        0x0 abort.o
 .data          0x000000000002880c        0x0 faults.o
                0x0000000000029000                . = ALIGN (0x1000)
 *fill*         0x000000000002880c      0x7f4 

.bss            0x0000000000029000     0x2000
                0x0000000000029000                bss = .
                0x0000000000029000                _bss = .
                0x0000000000029000                __bss = .
 *(.bss)
 .bss           0x0000000000029000        0x0 head.o
                0x0000000000029000                bss_start
 .bss           0x0000000000029000        0x0 main.o
 .bss           0x0000000000029000        0x0 loader.o
 .bss           0x0000000000029000        0x0 init.o
 .bss           0x0000000000029000        0x0 ports.o
 .bss           0x0000000000029000        0x0 x86.o
 .bss           0x0000000000029000        0x1 stdio.o
 .bss           0x0000000000029001        0x0 string.o
 *fill*         0x0000000000029001        0x3 
 .bss           0x0000000000029004        0x4 keyboard.o
                0x0000000000029004                ambiente
 .bss           0x0000000000029008        0x0 pci.o
 .bss           0x0000000000029008        0x0 hdd.o
 .bss           0x0000000000029008        0x0 timer.o
 .bss           0x0000000000029008        0x0 pages.o
 .bss           0x0000000000029008        0x0 procedure.o
 .bss           0x0000000000029008        0x0 fs.o
 .bss           0x0000000000029008        0x0 shell.o
 .bss           0x0000000000029008        0x0 services.o
 .bss           0x0000000000029008        0x0 abort.o
 .bss           0x0000000000029008        0x0 faults.o
 *(COMMON)
 *fill*         0x0000000000029008       0x18 
 COMMON         0x0000000000029020      0xc14 main.o
                0x0000000000029020                g_fat16_fat_status
                0x0000000000029040                prompt
                0x000000000002913c                EDITBOX_LARGURA
                0x0000000000029140                partition
                0x0000000000029150                system_info
                0x0000000000029158                g_initialized
                0x000000000002915c                bliTesting
                0x0000000000029160                EDITBOX_BG_COLOR
                0x0000000000029164                STATUS_X
                0x0000000000029168                prompt_pos
                0x000000000002916c                g_fat16_root_status
                0x0000000000029170                STATUS_Y
                0x0000000000029180                buffer_dir_entry
                0x0000000000029380                BootLoaderCR3
                0x0000000000029384                next_address
                0x0000000000029388                EDITBOX_ALTURA
                0x000000000002938c                g_lbf_va
                0x0000000000029390                LegacyCR3
                0x0000000000029394                g_proc_status
                0x0000000000029398                gdefTesting
                0x000000000002939c                proximo
                0x00000000000293a0                procedure_info
                0x00000000000293b0                EDITBOX_TEXT_COLOR
                0x00000000000293b4                CURSOR_Y
                0x00000000000293b8                EDITBOX_Y
                0x00000000000293bc                current_task
                0x00000000000293c0                g_system_color
                0x00000000000293c4                CURSOR_X
                0x00000000000293c8                useGUI
                0x00000000000293e0                file_cluster_list
                0x0000000000029be0                vesa_mode
                0x0000000000029bf0                g_next_app
                0x0000000000029bf4                VideoBlock
                0x0000000000029c10                g_cursor_y
                0x0000000000029c14                g_cmd_status
                0x0000000000029c18                g_file_system_type
                0x0000000000029c1c                g_char_attrib
                0x0000000000029c20                g_next_proc
                0x0000000000029c24                g_lbf_pa
                0x0000000000029c28                g_nova_mensagem
                0x0000000000029c2c                EDITBOX_X
                0x0000000000029c30                g_cursor_x
 COMMON         0x0000000000029c34       0x1c keyboard.o
                0x0000000000029c34                shift_status
                0x0000000000029c38                alt_status
                0x0000000000029c3c                escape_status
                0x0000000000029c40                tab_status
                0x0000000000029c44                key_status
                0x0000000000029c48                ctrl_status
                0x0000000000029c4c                winkey_status
 COMMON         0x0000000000029c50        0x4 timer.o
                0x0000000000029c50                timerTicks
 *fill*         0x0000000000029c54        0xc 
 COMMON         0x0000000000029c60      0x42c shell.o
                0x0000000000029c60                shell_status
                0x0000000000029c80                shell_string_buffer
                0x000000000002a080                deslocamento
                0x000000000002a084                ret_string
                0x000000000002a088                ShellInitialized
 *(.bss_heap)
 .bss_heap      0x000000000002a08c      0x400 head.o
                0x000000000002a08c                bootloader_heap_start
                0x000000000002a48c                bootloader_heap_end
 *(.bss_stack)
 .bss_stack     0x000000000002a48c      0x400 head.o
                0x000000000002a48c                bootloader_stack_end
                0x000000000002a88c                bootloader_stack_start
                0x000000000002b000                . = ALIGN (0x1000)
 *fill*         0x000000000002a88c      0x774 
                0x000000000002b000                end = .
                0x000000000002b000                _end = .
                0x000000000002b000                __end = .
                0x000000000002b000                _bootloader_end = .
LOAD head.o
LOAD main.o
LOAD loader.o
LOAD init.o
LOAD ports.o
LOAD x86.o
LOAD stdio.o
LOAD string.o
LOAD keyboard.o
LOAD pci.o
LOAD hdd.o
LOAD timer.o
LOAD pages.o
LOAD procedure.o
LOAD fs.o
LOAD shell.o
LOAD services.o
LOAD abort.o
LOAD faults.o
OUTPUT(BL.BIN pe-i386)

.comment        0x0000000000000000      0x1e8
 .comment       0x0000000000000000       0x1b main.o
 .comment       0x000000000000001b       0x1b loader.o
 .comment       0x0000000000000036       0x1b init.o
 .comment       0x0000000000000051       0x1b ports.o
 .comment       0x000000000000006c       0x1b x86.o
 .comment       0x0000000000000087       0x1b stdio.o
 .comment       0x00000000000000a2       0x1b string.o
 .comment       0x00000000000000bd       0x1b keyboard.o
 .comment       0x00000000000000d8       0x1b pci.o
 .comment       0x00000000000000f3       0x1b hdd.o
 .comment       0x000000000000010e       0x1b timer.o
 .comment       0x0000000000000129       0x1b pages.o
 .comment       0x0000000000000144       0x1b procedure.o
 .comment       0x000000000000015f       0x1b fs.o
 .comment       0x000000000000017a       0x1b shell.o
 .comment       0x0000000000000195       0x1b services.o
 .comment       0x00000000000001b0       0x1b abort.o
 .comment       0x00000000000001cb       0x1b faults.o

.note.GNU-stack
                0x0000000000000000        0x0
 .note.GNU-stack
                0x0000000000000000        0x0 main.o
 .note.GNU-stack
                0x0000000000000000        0x0 loader.o
 .note.GNU-stack
                0x0000000000000000        0x0 init.o
 .note.GNU-stack
                0x0000000000000000        0x0 ports.o
 .note.GNU-stack
                0x0000000000000000        0x0 x86.o
 .note.GNU-stack
                0x0000000000000000        0x0 stdio.o
 .note.GNU-stack
                0x0000000000000000        0x0 string.o
 .note.GNU-stack
                0x0000000000000000        0x0 keyboard.o
 .note.GNU-stack
                0x0000000000000000        0x0 pci.o
 .note.GNU-stack
                0x0000000000000000        0x0 hdd.o
 .note.GNU-stack
                0x0000000000000000        0x0 timer.o
 .note.GNU-stack
                0x0000000000000000        0x0 pages.o
 .note.GNU-stack
                0x0000000000000000        0x0 procedure.o
 .note.GNU-stack
                0x0000000000000000        0x0 fs.o
 .note.GNU-stack
                0x0000000000000000        0x0 shell.o
 .note.GNU-stack
                0x0000000000000000        0x0 services.o
 .note.GNU-stack
                0x0000000000000000        0x0 abort.o
 .note.GNU-stack
                0x0000000000000000        0x0 faults.o
