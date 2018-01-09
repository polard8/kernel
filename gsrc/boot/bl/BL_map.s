
Allocating common symbols
Common symbol       size              file

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
 .text          0x000224dc       0xd0 main.o
                0x00022578                BlKernelModuleMain
                0x00022560                BlSetupPaging
                0x00022591                die
                0x000224dc                BlMain
                0x00022512                BlLoadKernel
                0x00022539                BlLoadFiles
                0x0002256d                BlAbort
 .text          0x000225ac      0x200 loader.o
                0x000225ac                load_kernel
                0x0002263f                load_files
 .text          0x000227ac      0x110 init.o
                0x00022825                init
                0x000227e4                init_globals
                0x000227ac                set_up_color
                0x000227b9                set_up_text_color
 .text          0x000228bc       0xd0 ports.o
                0x000228f3                inport8
                0x00022931                outport32
                0x000228bc                bloutportb
                0x0002293d                inb
                0x00022971                outportl
                0x0002295f                inportl
                0x000228e7                outportb
                0x000228ff                outport8
                0x00022918                outport16
                0x0002290b                inport16
                0x000228d4                inportb
                0x00022925                inport32
                0x000228c8                outb
 .text          0x0002298c       0xd0 x86.o
                0x00022a31                pushFlags
                0x00022a25                pushRegs
                0x00022a1c                Pop
                0x000229af                farReturn
                0x000229b5                getFlags
                0x00022a37                popFlags
                0x000229a2                stopCpu
                0x000229c9                BlProcessorInPort8
                0x00022a47                setStackPointer
                0x000229fb                BlProcessorInPort32
                0x000229d5                BlProcessorOutPort8
                0x00022a2b                popRegs
                0x00022a07                BlProcessorOutPort32
                0x000229ee                BlProcessorOutPort16
                0x00022a13                Push
                0x000229e1                BlProcessorInPort16
                0x000229bf                setFlags
                0x00022a3d                getStackPointer
                0x00022997                disable
                0x000229a9                intReturn
                0x0002298c                enable
 .text          0x00022a5c      0xb70 stdio.o
                0x0002310b                putchar
                0x00023555                gui_inb
                0x000230c7                sprintf
                0x00022a5c                panic
                0x0002348e                my_buffer_char_blt
                0x0002358e                get_cursor_y
                0x000235a5                carrega_bitmap_16x16
                0x00023328                input
                0x00022a7c                scroll
                0x0002331e                printf_main
                0x00023470                my_buffer_put_pixel
                0x00023121                outbyte
                0x0002343a                my_buffer_horizontal_line
                0x00022b03                kclear
                0x00022b5d                kprintf
                0x00023577                get_cursor_x
                0x00023246                _outbyte
                0x000230ac                printf
                0x00023517                vsync
 .text          0x000235cc      0x240 string.o
                0x00023791                strcat
                0x000235cc                strcmp
                0x000237e8                bzero
                0x00023700                memcpy
                0x000237c1                bcopy
                0x00023761                strcpy
                0x00023685                str_cmp
                0x00023627                strncmp
                0x0002373d                strlen
 .text          0x0002380c      0x1d0 keyboard.o
                0x0002380c                keyboardHandler
 .text          0x000239dc      0x290 pci.o
                0x00023b00                pciCheckVendor
                0x000239dc                pciConfigReadWord
                0x00023b95                pciInfo
                0x00023b56                pciGetClassCode
                0x00023c56                pciInit
                0x00023a82                pciCheckDevice
 .text          0x00023c6c      0x100 hdd.o
                0x00023c6c                my_read_hd_sector
                0x00023ce6                limpa_fat
                0x00023c89                my_write_hd_sector
                0x00023ca6                limpa_root
 .text          0x00023d6c       0x30 timer.o
                0x00023d6c                timer
                0x00023d77                BltimerInit
 .text          0x00023d9c      0x5a0 pages.o
                0x00023d9c                SetUpPaging
 .text          0x0002433c       0x80 procedure.o
                0x0002433c                bl_procedure
 .text          0x000243bc      0x940 fs.o
                0x00024448                fs_get_fat_entry
                0x00024673                fsSearchFile
                0x00024cd2                fsInitFat
                0x000244ca                fs_set_fat_entry
                0x00024452                fs_create_entry
                0x000244a2                fs_show_entry
                0x0002445c                fsSaveFileName
                0x0002446b                fs_set_entry
                0x00024765                fs_load_rootdirEx
                0x00024443                fs_test_fat_vector
                0x00024b60                fsCreateFile
                0x00024cd7                fsInitStructures
                0x00024cdc                fsInit
                0x000247b6                fs_load_fatEx
                0x0002441b                fs_format
                0x000244ed                fsLoadFile
                0x00024752                fsSearchFileName
                0x000244bb                fs_set_entry_status
                0x00024c65                fsCheckFat
                0x00024489                fsSaveRootDir
                0x0002449d                fs_save_entry_on_root
                0x000244de                fs_relood_dir
                0x00024439                fs_find_not_empty_entry
                0x0002494b                read_lba
                0x00024461                fs_save_entry_on_disc
                0x00024498                fs_save_structure
                0x000244cf                fs_find_empty_entry
                0x000244c0                fs_makeboot
                0x000244e3                mostra
                0x0002442f                fs_search_empty_entry
                0x000244a7                fs_delete_entry
                0x00024470                fs_get_entry
                0x0002447a                fs_show_dir
                0x000244b1                fs_get_entry_status
                0x0002499f                fsSaveFile
                0x0002447f                fs_check_cluster
                0x0002448e                fs_load_dir
                0x00024493                fs_save_dir
                0x00024805                fs_put_list_on_fat
                0x00024c58                fsClearFat
                0x000244ac                fs_init_bootfile_struct
                0x000243df                fatLoadCluster
                0x000248b8                fs_find_n_empty_entries
                0x00024475                fs_show_dir_entry
                0x00024466                fs_set_structures
                0x00024457                fsCreateFileName
                0x0002493e                fs_load_rootdir
                0x000244d9                fs_install
                0x00024b46                fsCreateDir
                0x00024975                write_lba
                0x000243bc                fatClustToSect
 .text          0x00024cfc      0x640 shell.o
                0x00024d64                shellProcedure
                0x00024cfc                shellMain
                0x00025262                boot
                0x0002530d                shellInit
                0x00024e66                shellWaitCmd
                0x00025267                debug
                0x00024e7e                shellCompare
                0x00025280                testa_mbr
                0x00024de6                shellInitializePrompt
                0x000252c0                testa_root
                0x00025300                reboot
                0x0002524e                shellHelp
 .text          0x0002533c       0x10 services.o
                0x00025346                system_services
                0x0002533c                blServices
 .text          0x0002534c       0x20 abort.o
                0x0002534c                abort
 .text          0x0002536c      0x100 faults.o
                0x0002545b                mostra_reg
                0x0002536c                cpu_falts
                0x00026000                . = ALIGN (0x1000)
 *fill*         0x0002546c      0xb94 00

.rdata          0x00026000      0x650
 .rdata         0x00026000       0xa0 faults.o
 .rdata         0x000260a0       0x20 abort.o
 .rdata         0x000260c0      0x1c0 shell.o
 .rdata         0x00026280      0x1a0 fs.o
 .rdata         0x00026420       0x10 procedure.o
 .rdata         0x00026430       0x50 pci.o
 .rdata         0x00026480       0x40 stdio.o
 .rdata         0x000264c0       0x20 init.o
 .rdata         0x000264e0      0x110 loader.o
 .rdata         0x000265f0       0x60 main.o

.data           0x00026650      0x9b0
                0x00026650                data = .
                0x00026650                _data = .
                0x00026650                __data = .
 *(.data)
 .data          0x00026650        0x2 head.o
                0x00026650                data_start
 *fill*         0x00026652        0x2 00
 .data          0x00026654        0x0 main.o
 .data          0x00026654        0x0 loader.o
 .data          0x00026654        0x0 init.o
 .data          0x00026654        0x0 ports.o
 .data          0x00026654        0x0 x86.o
 .data          0x00026654        0x0 stdio.o
 .data          0x00026654        0x0 string.o
 .data          0x00026654      0x1a0 keyboard.o
                0x00026654                destroy_window
                0x00026658                quit_message
 .data          0x000267f4        0x0 pci.o
 .data          0x000267f4        0x0 hdd.o
 .data          0x000267f4        0x0 timer.o
 .data          0x000267f4        0x0 pages.o
 .data          0x000267f4        0x0 procedure.o
 .data          0x000267f4        0x0 fs.o
 .data          0x000267f4       0x40 shell.o
                0x000267f4                help_string
 .data          0x00026834        0x0 services.o
 .data          0x00026834        0x0 abort.o
 .data          0x00026834        0x0 faults.o
                0x00027000                . = ALIGN (0x1000)
 *fill*         0x00026834      0x7cc 00

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
 COMMON         0x00027020      0xd60 main.o
                0x00027020                prompt
                0x00027120                EDITBOX_LARGURA
                0x00027130                partition
                0x00027140                system_info
                0x00027150                g_initialized
                0x00027160                bliTesting
                0x00027170                EDITBOX_BG_COLOR
                0x00027180                STATUS_X
                0x00027190                prompt_pos
                0x000271a0                STATUS_Y
                0x000271b0                buffer_dir_entry
                0x000273b0                BootLoaderCR3
                0x000273c0                next_address
                0x000273d0                EDITBOX_ALTURA
                0x000273e0                g_lbf_va
                0x000273f0                LegacyCR3
                0x00027400                g_proc_status
                0x00027410                gdefTesting
                0x00027420                proximo
                0x00027430                procedure_info
                0x00027440                EDITBOX_TEXT_COLOR
                0x00027450                CURSOR_Y
                0x00027460                EDITBOX_Y
                0x00027470                current_task
                0x00027480                g_system_color
                0x00027490                CURSOR_X
                0x000274a0                useGUI
                0x000274b0                file_cluster_list
                0x00027cb0                vesa_mode
                0x00027cc0                g_next_app
                0x00027cd0                VideoBlock
                0x00027cf0                g_cursor_y
                0x00027d00                g_cmd_status
                0x00027d10                g_file_system_type
                0x00027d20                g_char_attrib
                0x00027d30                g_next_proc
                0x00027d40                g_lbf_pa
                0x00027d50                g_nova_mensagem
                0x00027d60                EDITBOX_X
                0x00027d70                g_cursor_x
 COMMON         0x00027d80       0x70 keyboard.o
                0x00027d80                shift_status
                0x00027d90                alt_status
                0x00027da0                escape_status
                0x00027db0                tab_status
                0x00027dc0                key_status
                0x00027dd0                ctrl_status
                0x00027de0                winkey_status
 COMMON         0x00027df0       0x10 timer.o
                0x00027df0                timerTicks
 COMMON         0x00027e00      0x440 shell.o
                0x00027e00                shell_status
                0x00027e10                shell_string_buffer
                0x00028210                deslocamento
                0x00028220                ret_string
                0x00028230                ShellInitialized
 *(.bss_heap)
 .bss_heap      0x00028240        0x0 head.o
                0x00028240                bootloader_heap_start
                0x00028240                bootloader_heap_end
 *(.bss_stack)
 .bss_stack     0x00028240        0x0 head.o
                0x00028240                bootloader_stack_start
                0x00028240                bootloader_stack_end
                0x00029000                . = ALIGN (0x1000)
 *fill*         0x00028240      0xdc0 00
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
