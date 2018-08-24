
Allocating common symbols
Common symbol       size              file

g_fat16_fat_status  0x10              main.o
timerTicks          0x10              timer.o
prompt              0x100             main.o
EDITBOX_LARGURA     0x10              main.o
partition           0x10              main.o
system_info         0x10              main.o
g_initialized       0x10              main.o
bliTesting          0x10              main.o
EDITBOX_BG_COLOR    0x10              main.o
shell_status        0x10              shell.o
STATUS_X            0x10              main.o
prompt_pos          0x10              main.o
g_fat16_root_status
                    0x10              main.o
STATUS_Y            0x10              main.o
shell_string_buffer
                    0x400             shell.o
deslocamento        0x10              shell.o
buffer_dir_entry    0x200             main.o
BootLoaderCR3       0x10              main.o
next_address        0x10              main.o
shift_status        0x10              keyboard.o
alt_status          0x10              keyboard.o
EDITBOX_ALTURA      0x10              main.o
g_lbf_va            0x10              main.o
LegacyCR3           0x10              main.o
g_proc_status       0x10              main.o
gdefTesting         0x10              main.o
proximo             0x10              main.o
procedure_info      0x10              main.o
EDITBOX_TEXT_COLOR  0x10              main.o
CURSOR_Y            0x10              main.o
EDITBOX_Y           0x10              main.o
current_task        0x10              main.o
g_system_color      0x10              main.o
CURSOR_X            0x10              main.o
useGUI              0x10              main.o
ret_string          0x10              shell.o
file_cluster_list   0x800             main.o
vesa_mode           0x10              main.o
escape_status       0x10              keyboard.o
g_next_app          0x10              main.o
tab_status          0x10              keyboard.o
VideoBlock          0x20              main.o
g_cursor_y          0x10              main.o
g_cmd_status        0x10              main.o
ShellInitialized    0x10              shell.o
key_status          0x10              keyboard.o
g_file_system_type  0x10              main.o
g_char_attrib       0x10              main.o
ctrl_status         0x10              keyboard.o
g_next_proc         0x10              main.o
g_lbf_pa            0x10              main.o
winkey_status       0x10              keyboard.o
g_nova_mensagem     0x10              main.o
EDITBOX_X           0x10              main.o
g_cursor_x          0x10              main.o

Memory Configuration

Name             Origin             Length             Attributes
*default*        0x00000000         0xffffffff

Linker script and memory map

                0x00400000                __image_base__ = 0x400000
                0x00000000                __dll__ = 0x0
                0x00400000                ___ImageBase = 0x400000
                0x00001000                __section_alignment__ = 0x1000
                0x00000200                __file_alignment__ = 0x200
                0x00000004                __major_os_version__ = 0x4
                0x00000000                __minor_os_version__ = 0x0
                0x00000001                __major_image_version__ = 0x1
                0x00000000                __minor_image_version__ = 0x0
                0x00000004                __major_subsystem_version__ = 0x4
                0x00000000                __minor_subsystem_version__ = 0x0
                0x00000003                __subsystem__ = 0x3
                0x00200000                __size_of_stack_reserve__ = 0x200000
                0x00001000                __size_of_stack_commit__ = 0x1000
                0x00100000                __size_of_heap_reserve__ = 0x100000
                0x00001000                __size_of_heap_commit__ = 0x1000
                0x00000000                __loader_flags__ = 0x0

.text           0x00021000     0x5000
                0x00021000                code = .
                0x00021000                _code = .
                0x00021000                __code = .
 *(.head_x86)
 .head_x86      0x00021000     0x1482 head.o
                0x00021e5b                fault_N1
                0x00021ecb                fault_DOUBLE
                0x00021b3b                task1_stack
                0x0002204b                hd_buffer
                0x000211ab                SavedBPP
                0x00022478                asm_shut_down
                0x000211af                SavedBootMode
                0x0002203b                fault_N31
                0x0002200b                fault_N28
                0x00022250                int56
                0x00021f9b                fault_N21
                0x00021f2b                fault_N14
                0x0002228b                int201
                0x00021efb                fault_N11
                0x00021e15                irq0
                0x00022246                int54
                0x00021e7b                fault_N3
                0x00022237                int51
                0x00022264                int100
                0x00021fcb                fault_N24
                0x00021feb                fault_N26
                0x00022053                test_write
                0x00021e4b                fault_N0
                0x00022063                os_read_sector
                0x00022464                softwarelibReboot
                0x0002202b                fault_N30
                0x00021b7d                setup_idt_vector
                0x00021f0b                fault_STACK
                0x00021b3f                task2_stack
                0x00021ffb                fault_N27
                0x0002222d                int49
                0x00021b37                task0_stack
                0x00022241                int53
                0x000211a3                SavedX
                0x00021f4b                fault_N16
                0x00021f1b                fault_GP
                0x00021e1b                timer_test
                0x00022228                int48
                0x00021f7b                fault_N19
                0x00021ebb                fault_N7
                0x00022232                int50
                0x0002225a                int58
                0x0002201b                fault_N29
                0x00022297                my_buffer_load_bitmap_16x16
                0x0002224b                int55
                0x00022290                int213
                0x00021fbb                fault_N23
                0x000211a7                SavedY
                0x00022269                int200
                0x00022413                refresh_screen
                0x00021eab                fault_INTRUCAO_INVALIDA
                0x0002119f                SavedLFB
                0x0002119b                SavedBootBlock
                0x0002232d                background
                0x00021e8b                fault_N4
                0x00021e6b                fault_N2
                0x0002207c                os_write_sector
                0x00021f8b                fault_N20
                0x0002223c                int52
                0x00022255                int57
                0x00021fab                fault_N22
                0x00021eeb                fault_N10
                0x00021e2f                irq1
                0x00021f3b                fault_N15
                0x00021f5b                fault_N17
                0x00021f6b                fault_N18
                0x0002204f                hd_lba
                0x00021fdb                fault_N25
                0x00022385                gui_buffer_putpixel
                0x0002218e                reset_ide0
                0x00021edb                fault_N9
                0x0002225f                int59
                0x00021000                bootloader_entry_point
                0x00021e9b                fault_N5
 *(.text)
 *fill*         0x00022482        0x2 00
 .text          0x00022484       0xf0 main.o
                0x0002253e                BlKernelModuleMain
                0x00022526                BlSetupPaging
                0x00022557                die
                0x00022484                BlMain
                0x000224d8                BlLoadKernel
                0x000224ff                BlLoadFiles
                0x00022533                BlAbort
 .text          0x00022574      0x220 loader.o
                0x00022574                load_kernel
                0x0002262e                load_files
 .text          0x00022794      0x110 init.o
                0x0002280d                init
                0x000227cc                init_globals
                0x00022794                set_up_color
                0x000227a1                set_up_text_color
 .text          0x000228a4       0xd0 ports.o
                0x000228db                inport8
                0x00022919                outport32
                0x000228a4                bloutportb
                0x00022925                inb
                0x00022959                outportl
                0x00022947                inportl
                0x000228cf                outportb
                0x000228e7                outport8
                0x00022900                outport16
                0x000228f3                inport16
                0x000228bc                inportb
                0x0002290d                inport32
                0x000228b0                outb
 .text          0x00022974       0xd0 x86.o
                0x00022a19                pushFlags
                0x00022a0d                pushRegs
                0x00022a04                Pop
                0x00022997                farReturn
                0x0002299d                getFlags
                0x00022a1f                popFlags
                0x0002298a                stopCpu
                0x000229b1                BlProcessorInPort8
                0x00022a2f                setStackPointer
                0x000229e3                BlProcessorInPort32
                0x000229bd                BlProcessorOutPort8
                0x00022a13                popRegs
                0x000229ef                BlProcessorOutPort32
                0x000229d6                BlProcessorOutPort16
                0x000229fb                Push
                0x000229c9                BlProcessorInPort16
                0x000229a7                setFlags
                0x00022a25                getStackPointer
                0x0002297f                disable
                0x00022991                intReturn
                0x00022974                enable
 .text          0x00022a44      0xb70 stdio.o
                0x000230f3                putchar
                0x0002353d                gui_inb
                0x000230af                sprintf
                0x00022a44                panic
                0x00023476                my_buffer_char_blt
                0x00023576                get_cursor_y
                0x0002358d                carrega_bitmap_16x16
                0x00023310                input
                0x00022a64                scroll
                0x00023306                printf_main
                0x00023458                my_buffer_put_pixel
                0x00023109                outbyte
                0x00023422                my_buffer_horizontal_line
                0x00022aeb                kclear
                0x00022b45                kprintf
                0x0002355f                get_cursor_x
                0x0002322e                _outbyte
                0x00023094                printf
                0x000234ff                vsync
 .text          0x000235b4      0x240 string.o
                0x00023779                strcat
                0x000235b4                strcmp
                0x000237d0                bzero
                0x000236e8                memcpy
                0x000237a9                bcopy
                0x00023749                strcpy
                0x0002366d                str_cmp
                0x0002360f                strncmp
                0x00023725                strlen
 .text          0x000237f4      0x1d0 keyboard.o
                0x000237f4                keyboardHandler
 .text          0x000239c4      0x290 pci.o
                0x00023ae8                pciCheckVendor
                0x000239c4                pciConfigReadWord
                0x00023b7d                pciInfo
                0x00023b3e                pciGetClassCode
                0x00023c3e                pciInit
                0x00023a6a                pciCheckDevice
 .text          0x00023c54      0x100 hdd.o
                0x00023c54                my_read_hd_sector
                0x00023cce                limpa_fat
                0x00023c71                my_write_hd_sector
                0x00023c8e                limpa_root
 .text          0x00023d54       0x30 timer.o
                0x00023d54                timer
                0x00023d5f                BltimerInit
 .text          0x00023d84      0x5a0 pages.o
                0x00023d84                SetUpPaging
 .text          0x00024324       0x80 procedure.o
                0x00024324                bl_procedure
 .text          0x000243a4      0x950 fs.o
                0x00024430                fs_get_fat_entry
                0x00024676                fsSearchFile
                0x00024cd5                fsInitFat
                0x000244b2                fs_set_fat_entry
                0x0002443a                fs_create_entry
                0x0002448a                fs_show_entry
                0x00024444                fsSaveFileName
                0x00024453                fs_set_entry
                0x00024768                fs_load_rootdirEx
                0x0002442b                fs_test_fat_vector
                0x00024b63                fsCreateFile
                0x00024cda                fsInitStructures
                0x00024cdf                fsInit
                0x000247b9                fs_load_fatEx
                0x00024403                fs_format
                0x000244cb                fsLoadFile
                0x00024755                fsSearchFileName
                0x000244a3                fs_set_entry_status
                0x00024c68                fsCheckFat
                0x00024471                fsSaveRootDir
                0x00024485                fs_save_entry_on_root
                0x000244c6                fs_relood_dir
                0x00024421                fs_find_not_empty_entry
                0x0002494e                read_lba
                0x00024449                fs_save_entry_on_disc
                0x00024480                fs_save_structure
                0x000244b7                fs_find_empty_entry
                0x000244a8                fs_makeboot
                0x00024417                fs_search_empty_entry
                0x0002448f                fs_delete_entry
                0x00024458                fs_get_entry
                0x00024462                fs_show_dir
                0x00024499                fs_get_entry_status
                0x000249a2                fsSaveFile
                0x00024467                fs_check_cluster
                0x00024476                fs_load_dir
                0x0002447b                fs_save_dir
                0x00024808                fs_put_list_on_fat
                0x00024c5b                fsClearFat
                0x00024494                fs_init_bootfile_struct
                0x000243c7                fatLoadCluster
                0x000248bb                fs_find_n_empty_entries
                0x0002445d                fs_show_dir_entry
                0x0002444e                fs_set_structures
                0x0002443f                fsCreateFileName
                0x00024941                fs_load_rootdir
                0x000244c1                fs_install
                0x00024b49                fsCreateDir
                0x00024978                write_lba
                0x000243a4                fatClustToSect
 .text          0x00024cf4      0x640 shell.o
                0x00024d5c                shellProcedure
                0x00024cf4                shellMain
                0x0002525a                boot
                0x00025305                shellInit
                0x00024e5e                shellWaitCmd
                0x0002525f                debug
                0x00024e76                shellCompare
                0x00025278                testa_mbr
                0x00024dde                shellInitializePrompt
                0x000252b8                testa_root
                0x000252f8                reboot
                0x00025246                shellHelp
 .text          0x00025334       0x10 services.o
                0x0002533e                system_services
                0x00025334                blServices
 .text          0x00025344       0x20 abort.o
                0x00025344                abort
 .text          0x00025364      0x100 faults.o
                0x00025453                mostra_reg
                0x00025364                cpu_falts
                0x00026000                . = ALIGN (0x1000)
 *fill*         0x00025464      0xb9c 00

.rdata          0x00026000      0x660
 .rdata         0x00026000       0xa0 faults.o
 .rdata         0x000260a0       0x20 abort.o
 .rdata         0x000260c0      0x1c0 shell.o
 .rdata         0x00026280      0x1d0 fs.o
 .rdata         0x00026450       0x10 procedure.o
 .rdata         0x00026460       0x50 pci.o
 .rdata         0x000264b0       0x40 stdio.o
 .rdata         0x000264f0       0x20 init.o
 .rdata         0x00026510       0xf0 loader.o
 .rdata         0x00026600       0x60 main.o

.data           0x00026660      0x9a0
                0x00026660                data = .
                0x00026660                _data = .
                0x00026660                __data = .
 *(.data)
 .data          0x00026660        0x2 head.o
                0x00026660                data_start
 *fill*         0x00026662        0x2 00
 .data          0x00026664        0x0 main.o
 .data          0x00026664        0x0 loader.o
 .data          0x00026664        0x0 init.o
 .data          0x00026664        0x0 ports.o
 .data          0x00026664        0x0 x86.o
 .data          0x00026664        0x0 stdio.o
 .data          0x00026664        0x0 string.o
 .data          0x00026664      0x1a0 keyboard.o
                0x00026664                destroy_window
                0x00026668                quit_message
 .data          0x00026804        0x0 pci.o
 .data          0x00026804        0x0 hdd.o
 .data          0x00026804        0x0 timer.o
 .data          0x00026804        0x0 pages.o
 .data          0x00026804        0x0 procedure.o
 .data          0x00026804        0x0 fs.o
 .data          0x00026804       0x40 shell.o
                0x00026804                help_string
 .data          0x00026844        0x0 services.o
 .data          0x00026844        0x0 abort.o
 .data          0x00026844        0x0 faults.o
                0x00027000                . = ALIGN (0x1000)
 *fill*         0x00026844      0x7bc 00

.bss            0x00027000     0x2000
                0x00027000                bss = .
                0x00027000                _bss = .
                0x00027000                __bss = .
 *(.bss)
 .bss           0x00027000        0x0 head.o
                0x00027000                bss_start
 .bss           0x00027000        0x0 main.o
 .bss           0x00027000        0x0 loader.o
 .bss           0x00027000        0x0 init.o
 .bss           0x00027000        0x0 ports.o
 .bss           0x00027000        0x0 x86.o
 .bss           0x00027000       0x10 stdio.o
 .bss           0x00027010        0x0 string.o
 .bss           0x00027010       0x10 keyboard.o
                0x00027010                ambiente
 .bss           0x00027020        0x0 pci.o
 .bss           0x00027020        0x0 hdd.o
 .bss           0x00027020        0x0 timer.o
 .bss           0x00027020        0x0 pages.o
 .bss           0x00027020        0x0 procedure.o
 .bss           0x00027020        0x0 fs.o
 .bss           0x00027020        0x0 shell.o
 .bss           0x00027020        0x0 services.o
 .bss           0x00027020        0x0 abort.o
 .bss           0x00027020        0x0 faults.o
 *(COMMON)
 COMMON         0x00027020      0xd80 main.o
                0x00027020                g_fat16_fat_status
                0x00027030                prompt
                0x00027130                EDITBOX_LARGURA
                0x00027140                partition
                0x00027150                system_info
                0x00027160                g_initialized
                0x00027170                bliTesting
                0x00027180                EDITBOX_BG_COLOR
                0x00027190                STATUS_X
                0x000271a0                prompt_pos
                0x000271b0                g_fat16_root_status
                0x000271c0                STATUS_Y
                0x000271d0                buffer_dir_entry
                0x000273d0                BootLoaderCR3
                0x000273e0                next_address
                0x000273f0                EDITBOX_ALTURA
                0x00027400                g_lbf_va
                0x00027410                LegacyCR3
                0x00027420                g_proc_status
                0x00027430                gdefTesting
                0x00027440                proximo
                0x00027450                procedure_info
                0x00027460                EDITBOX_TEXT_COLOR
                0x00027470                CURSOR_Y
                0x00027480                EDITBOX_Y
                0x00027490                current_task
                0x000274a0                g_system_color
                0x000274b0                CURSOR_X
                0x000274c0                useGUI
                0x000274d0                file_cluster_list
                0x00027cd0                vesa_mode
                0x00027ce0                g_next_app
                0x00027cf0                VideoBlock
                0x00027d10                g_cursor_y
                0x00027d20                g_cmd_status
                0x00027d30                g_file_system_type
                0x00027d40                g_char_attrib
                0x00027d50                g_next_proc
                0x00027d60                g_lbf_pa
                0x00027d70                g_nova_mensagem
                0x00027d80                EDITBOX_X
                0x00027d90                g_cursor_x
 COMMON         0x00027da0       0x70 keyboard.o
                0x00027da0                shift_status
                0x00027db0                alt_status
                0x00027dc0                escape_status
                0x00027dd0                tab_status
                0x00027de0                key_status
                0x00027df0                ctrl_status
                0x00027e00                winkey_status
 COMMON         0x00027e10       0x10 timer.o
                0x00027e10                timerTicks
 COMMON         0x00027e20      0x440 shell.o
                0x00027e20                shell_status
                0x00027e30                shell_string_buffer
                0x00028230                deslocamento
                0x00028240                ret_string
                0x00028250                ShellInitialized
 *(.bss_heap)
 .bss_heap      0x00028260      0x400 head.o
                0x00028260                bootloader_heap_start
                0x00028660                bootloader_heap_end
 *(.bss_stack)
 .bss_stack     0x00028660      0x400 head.o
                0x00028a60                bootloader_stack_start
                0x00028660                bootloader_stack_end
                0x00029000                . = ALIGN (0x1000)
 *fill*         0x00028a60      0x5a0 00
                0x00029000                end = .
                0x00029000                _end = .
                0x00029000                __end = .
                0x00029000                _bootloader_end = .
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

.comment        0x00000000       0x20
 .comment       0x00000000       0x1f head.o
