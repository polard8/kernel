
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
 .head_x86      0x00021000     0x14db head.o
                0x00021e6f                fault_N1
                0x00021edf                fault_DOUBLE
                0x00021b4f                task1_stack
                0x0002205f                hd_buffer
                0x000211bf                SavedBPP
                0x000224d1                asm_shut_down
                0x000211c3                SavedBootMode
                0x0002204f                fault_N31
                0x0002201f                fault_N28
                0x000222a9                int56
                0x00021faf                fault_N21
                0x00021f3f                fault_N14
                0x000222e4                int201
                0x00021f0f                fault_N11
                0x00021e29                irq0
                0x0002229f                int54
                0x00021e8f                fault_N3
                0x00022290                int51
                0x000222bd                int100
                0x00021fdf                fault_N24
                0x00021fff                fault_N26
                0x00022067                test_write
                0x00021e5f                fault_N0
                0x00022077                os_read_sector
                0x000224bd                softwarelibReboot
                0x0002203f                fault_N30
                0x00021b91                setup_idt_vector
                0x00021f1f                fault_STACK
                0x00021b53                task2_stack
                0x0002200f                fault_N27
                0x00022286                int49
                0x00021b4b                task0_stack
                0x0002229a                int53
                0x000211b7                SavedX
                0x00021f5f                fault_N16
                0x00021f2f                fault_GP
                0x00021e2f                timer_test
                0x00022281                int48
                0x00021f8f                fault_N19
                0x00021ecf                fault_N7
                0x0002228b                int50
                0x000222b3                int58
                0x0002202f                fault_N29
                0x000222f0                my_buffer_load_bitmap_16x16
                0x000222a4                int55
                0x000222e9                int213
                0x00021fcf                fault_N23
                0x000211bb                SavedY
                0x000222c2                int200
                0x0002246c                refresh_screen
                0x00021ebf                fault_INTRUCAO_INVALIDA
                0x000211b3                SavedLFB
                0x000211af                SavedBootBlock
                0x00022386                background
                0x00021e9f                fault_N4
                0x00021e7f                fault_N2
                0x00022091                os_write_sector
                0x00021f9f                fault_N20
                0x00022295                int52
                0x000222ae                int57
                0x00021fbf                fault_N22
                0x00021eff                fault_N10
                0x00021e43                irq1
                0x00021f4f                fault_N15
                0x00021f6f                fault_N17
                0x00021f7f                fault_N18
                0x00022063                hd_lba
                0x00021fef                fault_N25
                0x000223de                gui_buffer_putpixel
                0x000221e7                reset_ide0
                0x00021eef                fault_N9
                0x000222b8                int59
                0x00021000                bootloader_entry_point
                0x00021eaf                fault_N5
 *(.text)
 *fill*         0x000224db        0x1 00
 .text          0x000224dc       0xf0 main.o
                0x00022596                BlKernelModuleMain
                0x0002257e                BlSetupPaging
                0x000225af                die
                0x000224dc                BlMain
                0x00022530                BlLoadKernel
                0x00022557                BlLoadFiles
                0x0002258b                BlAbort
 .text          0x000225cc      0x200 loader.o
                0x000225cc                load_kernel
                0x0002265f                load_files
 .text          0x000227cc      0x110 init.o
                0x00022845                init
                0x00022804                init_globals
                0x000227cc                set_up_color
                0x000227d9                set_up_text_color
 .text          0x000228dc       0xd0 ports.o
                0x00022913                inport8
                0x00022951                outport32
                0x000228dc                bloutportb
                0x0002295d                inb
                0x00022991                outportl
                0x0002297f                inportl
                0x00022907                outportb
                0x0002291f                outport8
                0x00022938                outport16
                0x0002292b                inport16
                0x000228f4                inportb
                0x00022945                inport32
                0x000228e8                outb
 .text          0x000229ac       0xd0 x86.o
                0x00022a51                pushFlags
                0x00022a45                pushRegs
                0x00022a3c                Pop
                0x000229cf                farReturn
                0x000229d5                getFlags
                0x00022a57                popFlags
                0x000229c2                stopCpu
                0x000229e9                BlProcessorInPort8
                0x00022a67                setStackPointer
                0x00022a1b                BlProcessorInPort32
                0x000229f5                BlProcessorOutPort8
                0x00022a4b                popRegs
                0x00022a27                BlProcessorOutPort32
                0x00022a0e                BlProcessorOutPort16
                0x00022a33                Push
                0x00022a01                BlProcessorInPort16
                0x000229df                setFlags
                0x00022a5d                getStackPointer
                0x000229b7                disable
                0x000229c9                intReturn
                0x000229ac                enable
 .text          0x00022a7c      0xb70 stdio.o
                0x0002312b                putchar
                0x00023575                gui_inb
                0x000230e7                sprintf
                0x00022a7c                panic
                0x000234ae                my_buffer_char_blt
                0x000235ae                get_cursor_y
                0x000235c5                carrega_bitmap_16x16
                0x00023348                input
                0x00022a9c                scroll
                0x0002333e                printf_main
                0x00023490                my_buffer_put_pixel
                0x00023141                outbyte
                0x0002345a                my_buffer_horizontal_line
                0x00022b23                kclear
                0x00022b7d                kprintf
                0x00023597                get_cursor_x
                0x00023266                _outbyte
                0x000230cc                printf
                0x00023537                vsync
 .text          0x000235ec      0x240 string.o
                0x000237b1                strcat
                0x000235ec                strcmp
                0x00023808                bzero
                0x00023720                memcpy
                0x000237e1                bcopy
                0x00023781                strcpy
                0x000236a5                str_cmp
                0x00023647                strncmp
                0x0002375d                strlen
 .text          0x0002382c      0x1d0 keyboard.o
                0x0002382c                keyboardHandler
 .text          0x000239fc      0x290 pci.o
                0x00023b20                pciCheckVendor
                0x000239fc                pciConfigReadWord
                0x00023bb5                pciInfo
                0x00023b76                pciGetClassCode
                0x00023c76                pciInit
                0x00023aa2                pciCheckDevice
 .text          0x00023c8c      0x100 hdd.o
                0x00023c8c                my_read_hd_sector
                0x00023d06                limpa_fat
                0x00023ca9                my_write_hd_sector
                0x00023cc6                limpa_root
 .text          0x00023d8c       0x30 timer.o
                0x00023d8c                timer
                0x00023d97                BltimerInit
 .text          0x00023dbc      0x5a0 pages.o
                0x00023dbc                SetUpPaging
 .text          0x0002435c       0x80 procedure.o
                0x0002435c                bl_procedure
 .text          0x000243dc      0x990 fs.o
                0x00024468                fs_get_fat_entry
                0x000246e0                fsSearchFile
                0x00024d3f                fsInitFat
                0x000244ea                fs_set_fat_entry
                0x00024472                fs_create_entry
                0x000244c2                fs_show_entry
                0x0002447c                fsSaveFileName
                0x0002448b                fs_set_entry
                0x000247d2                fs_load_rootdirEx
                0x00024463                fs_test_fat_vector
                0x00024bcd                fsCreateFile
                0x00024d44                fsInitStructures
                0x00024d49                fsInit
                0x00024823                fs_load_fatEx
                0x0002443b                fs_format
                0x0002450d                fsLoadFile
                0x000247bf                fsSearchFileName
                0x000244db                fs_set_entry_status
                0x00024cd2                fsCheckFat
                0x000244a9                fsSaveRootDir
                0x000244bd                fs_save_entry_on_root
                0x000244fe                fs_relood_dir
                0x00024459                fs_find_not_empty_entry
                0x000249b8                read_lba
                0x00024481                fs_save_entry_on_disc
                0x000244b8                fs_save_structure
                0x000244ef                fs_find_empty_entry
                0x000244e0                fs_makeboot
                0x00024503                mostra
                0x0002444f                fs_search_empty_entry
                0x000244c7                fs_delete_entry
                0x00024490                fs_get_entry
                0x0002449a                fs_show_dir
                0x000244d1                fs_get_entry_status
                0x00024a0c                fsSaveFile
                0x0002449f                fs_check_cluster
                0x000244ae                fs_load_dir
                0x000244b3                fs_save_dir
                0x00024872                fs_put_list_on_fat
                0x00024cc5                fsClearFat
                0x000244cc                fs_init_bootfile_struct
                0x000243ff                fatLoadCluster
                0x00024925                fs_find_n_empty_entries
                0x00024495                fs_show_dir_entry
                0x00024486                fs_set_structures
                0x00024477                fsCreateFileName
                0x000249ab                fs_load_rootdir
                0x000244f9                fs_install
                0x00024bb3                fsCreateDir
                0x000249e2                write_lba
                0x000243dc                fatClustToSect
 .text          0x00024d6c      0x640 shell.o
                0x00024dd4                shellProcedure
                0x00024d6c                shellMain
                0x000252d2                boot
                0x0002537d                shellInit
                0x00024ed6                shellWaitCmd
                0x000252d7                debug
                0x00024eee                shellCompare
                0x000252f0                testa_mbr
                0x00024e56                shellInitializePrompt
                0x00025330                testa_root
                0x00025370                reboot
                0x000252be                shellHelp
 .text          0x000253ac       0x10 services.o
                0x000253b6                system_services
                0x000253ac                blServices
 .text          0x000253bc       0x20 abort.o
                0x000253bc                abort
 .text          0x000253dc      0x100 faults.o
                0x000254cb                mostra_reg
                0x000253dc                cpu_falts
                0x00026000                . = ALIGN (0x1000)
 *fill*         0x000254dc      0xb24 00

.rdata          0x00026000      0x690
 .rdata         0x00026000       0xa0 faults.o
 .rdata         0x000260a0       0x20 abort.o
 .rdata         0x000260c0      0x1c0 shell.o
 .rdata         0x00026280      0x1e0 fs.o
 .rdata         0x00026460       0x10 procedure.o
 .rdata         0x00026470       0x50 pci.o
 .rdata         0x000264c0       0x40 stdio.o
 .rdata         0x00026500       0x20 init.o
 .rdata         0x00026520      0x110 loader.o
 .rdata         0x00026630       0x60 main.o

.data           0x00026690      0x970
                0x00026690                data = .
                0x00026690                _data = .
                0x00026690                __data = .
 *(.data)
 .data          0x00026690        0x2 head.o
                0x00026690                data_start
 *fill*         0x00026692        0x2 00
 .data          0x00026694        0x0 main.o
 .data          0x00026694        0x0 loader.o
 .data          0x00026694        0x0 init.o
 .data          0x00026694        0x0 ports.o
 .data          0x00026694        0x0 x86.o
 .data          0x00026694        0x0 stdio.o
 .data          0x00026694        0x0 string.o
 .data          0x00026694      0x1a0 keyboard.o
                0x00026694                destroy_window
                0x00026698                quit_message
 .data          0x00026834        0x0 pci.o
 .data          0x00026834        0x0 hdd.o
 .data          0x00026834        0x0 timer.o
 .data          0x00026834        0x0 pages.o
 .data          0x00026834        0x0 procedure.o
 .data          0x00026834        0x0 fs.o
 .data          0x00026834       0x40 shell.o
                0x00026834                help_string
 .data          0x00026874        0x0 services.o
 .data          0x00026874        0x0 abort.o
 .data          0x00026874        0x0 faults.o
                0x00027000                . = ALIGN (0x1000)
 *fill*         0x00026874      0x78c 00

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
 .bss_heap      0x00028260        0x0 head.o
                0x00028260                bootloader_heap_start
                0x00028260                bootloader_heap_end
 *(.bss_stack)
 .bss_stack     0x00028260        0x0 head.o
                0x00028260                bootloader_stack_start
                0x00028260                bootloader_stack_end
                0x00029000                . = ALIGN (0x1000)
 *fill*         0x00028260      0xda0 00
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
