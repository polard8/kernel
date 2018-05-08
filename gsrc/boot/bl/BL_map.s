
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
 .head_x86      0x00021000     0x14c7 head.o
                0x00021e5b                fault_N1
                0x00021ecb                fault_DOUBLE
                0x00021b3b                task1_stack
                0x0002204b                hd_buffer
                0x000211ab                SavedBPP
                0x000224bd                asm_shut_down
                0x000211af                SavedBootMode
                0x0002203b                fault_N31
                0x0002200b                fault_N28
                0x00022295                int56
                0x00021f9b                fault_N21
                0x00021f2b                fault_N14
                0x000222d0                int201
                0x00021efb                fault_N11
                0x00021e15                irq0
                0x0002228b                int54
                0x00021e7b                fault_N3
                0x0002227c                int51
                0x000222a9                int100
                0x00021fcb                fault_N24
                0x00021feb                fault_N26
                0x00022053                test_write
                0x00021e4b                fault_N0
                0x00022063                os_read_sector
                0x000224a9                softwarelibReboot
                0x0002202b                fault_N30
                0x00021b7d                setup_idt_vector
                0x00021f0b                fault_STACK
                0x00021b3f                task2_stack
                0x00021ffb                fault_N27
                0x00022272                int49
                0x00021b37                task0_stack
                0x00022286                int53
                0x000211a3                SavedX
                0x00021f4b                fault_N16
                0x00021f1b                fault_GP
                0x00021e1b                timer_test
                0x0002226d                int48
                0x00021f7b                fault_N19
                0x00021ebb                fault_N7
                0x00022277                int50
                0x0002229f                int58
                0x0002201b                fault_N29
                0x000222dc                my_buffer_load_bitmap_16x16
                0x00022290                int55
                0x000222d5                int213
                0x00021fbb                fault_N23
                0x000211a7                SavedY
                0x000222ae                int200
                0x00022458                refresh_screen
                0x00021eab                fault_INTRUCAO_INVALIDA
                0x0002119f                SavedLFB
                0x0002119b                SavedBootBlock
                0x00022372                background
                0x00021e8b                fault_N4
                0x00021e6b                fault_N2
                0x0002207d                os_write_sector
                0x00021f8b                fault_N20
                0x00022281                int52
                0x0002229a                int57
                0x00021fab                fault_N22
                0x00021eeb                fault_N10
                0x00021e2f                irq1
                0x00021f3b                fault_N15
                0x00021f5b                fault_N17
                0x00021f6b                fault_N18
                0x0002204f                hd_lba
                0x00021fdb                fault_N25
                0x000223ca                gui_buffer_putpixel
                0x000221d3                reset_ide0
                0x00021edb                fault_N9
                0x000222a4                int59
                0x00021000                bootloader_entry_point
                0x00021e9b                fault_N5
 *(.text)
 *fill*         0x000224c7        0x1 00
 .text          0x000224c8       0xf0 main.o
                0x00022582                BlKernelModuleMain
                0x0002256a                BlSetupPaging
                0x0002259b                die
                0x000224c8                BlMain
                0x0002251c                BlLoadKernel
                0x00022543                BlLoadFiles
                0x00022577                BlAbort
 .text          0x000225b8      0x220 loader.o
                0x000225b8                load_kernel
                0x00022672                load_files
 .text          0x000227d8      0x110 init.o
                0x00022851                init
                0x00022810                init_globals
                0x000227d8                set_up_color
                0x000227e5                set_up_text_color
 .text          0x000228e8       0xd0 ports.o
                0x0002291f                inport8
                0x0002295d                outport32
                0x000228e8                bloutportb
                0x00022969                inb
                0x0002299d                outportl
                0x0002298b                inportl
                0x00022913                outportb
                0x0002292b                outport8
                0x00022944                outport16
                0x00022937                inport16
                0x00022900                inportb
                0x00022951                inport32
                0x000228f4                outb
 .text          0x000229b8       0xd0 x86.o
                0x00022a5d                pushFlags
                0x00022a51                pushRegs
                0x00022a48                Pop
                0x000229db                farReturn
                0x000229e1                getFlags
                0x00022a63                popFlags
                0x000229ce                stopCpu
                0x000229f5                BlProcessorInPort8
                0x00022a73                setStackPointer
                0x00022a27                BlProcessorInPort32
                0x00022a01                BlProcessorOutPort8
                0x00022a57                popRegs
                0x00022a33                BlProcessorOutPort32
                0x00022a1a                BlProcessorOutPort16
                0x00022a3f                Push
                0x00022a0d                BlProcessorInPort16
                0x000229eb                setFlags
                0x00022a69                getStackPointer
                0x000229c3                disable
                0x000229d5                intReturn
                0x000229b8                enable
 .text          0x00022a88      0xb70 stdio.o
                0x00023137                putchar
                0x00023581                gui_inb
                0x000230f3                sprintf
                0x00022a88                panic
                0x000234ba                my_buffer_char_blt
                0x000235ba                get_cursor_y
                0x000235d1                carrega_bitmap_16x16
                0x00023354                input
                0x00022aa8                scroll
                0x0002334a                printf_main
                0x0002349c                my_buffer_put_pixel
                0x0002314d                outbyte
                0x00023466                my_buffer_horizontal_line
                0x00022b2f                kclear
                0x00022b89                kprintf
                0x000235a3                get_cursor_x
                0x00023272                _outbyte
                0x000230d8                printf
                0x00023543                vsync
 .text          0x000235f8      0x240 string.o
                0x000237bd                strcat
                0x000235f8                strcmp
                0x00023814                bzero
                0x0002372c                memcpy
                0x000237ed                bcopy
                0x0002378d                strcpy
                0x000236b1                str_cmp
                0x00023653                strncmp
                0x00023769                strlen
 .text          0x00023838      0x1d0 keyboard.o
                0x00023838                keyboardHandler
 .text          0x00023a08      0x290 pci.o
                0x00023b2c                pciCheckVendor
                0x00023a08                pciConfigReadWord
                0x00023bc1                pciInfo
                0x00023b82                pciGetClassCode
                0x00023c82                pciInit
                0x00023aae                pciCheckDevice
 .text          0x00023c98      0x100 hdd.o
                0x00023c98                my_read_hd_sector
                0x00023d12                limpa_fat
                0x00023cb5                my_write_hd_sector
                0x00023cd2                limpa_root
 .text          0x00023d98       0x30 timer.o
                0x00023d98                timer
                0x00023da3                BltimerInit
 .text          0x00023dc8      0x5a0 pages.o
                0x00023dc8                SetUpPaging
 .text          0x00024368       0x80 procedure.o
                0x00024368                bl_procedure
 .text          0x000243e8      0x990 fs.o
                0x00024474                fs_get_fat_entry
                0x000246ec                fsSearchFile
                0x00024d4b                fsInitFat
                0x000244f6                fs_set_fat_entry
                0x0002447e                fs_create_entry
                0x000244ce                fs_show_entry
                0x00024488                fsSaveFileName
                0x00024497                fs_set_entry
                0x000247de                fs_load_rootdirEx
                0x0002446f                fs_test_fat_vector
                0x00024bd9                fsCreateFile
                0x00024d50                fsInitStructures
                0x00024d55                fsInit
                0x0002482f                fs_load_fatEx
                0x00024447                fs_format
                0x00024519                fsLoadFile
                0x000247cb                fsSearchFileName
                0x000244e7                fs_set_entry_status
                0x00024cde                fsCheckFat
                0x000244b5                fsSaveRootDir
                0x000244c9                fs_save_entry_on_root
                0x0002450a                fs_relood_dir
                0x00024465                fs_find_not_empty_entry
                0x000249c4                read_lba
                0x0002448d                fs_save_entry_on_disc
                0x000244c4                fs_save_structure
                0x000244fb                fs_find_empty_entry
                0x000244ec                fs_makeboot
                0x0002450f                mostra
                0x0002445b                fs_search_empty_entry
                0x000244d3                fs_delete_entry
                0x0002449c                fs_get_entry
                0x000244a6                fs_show_dir
                0x000244dd                fs_get_entry_status
                0x00024a18                fsSaveFile
                0x000244ab                fs_check_cluster
                0x000244ba                fs_load_dir
                0x000244bf                fs_save_dir
                0x0002487e                fs_put_list_on_fat
                0x00024cd1                fsClearFat
                0x000244d8                fs_init_bootfile_struct
                0x0002440b                fatLoadCluster
                0x00024931                fs_find_n_empty_entries
                0x000244a1                fs_show_dir_entry
                0x00024492                fs_set_structures
                0x00024483                fsCreateFileName
                0x000249b7                fs_load_rootdir
                0x00024505                fs_install
                0x00024bbf                fsCreateDir
                0x000249ee                write_lba
                0x000243e8                fatClustToSect
 .text          0x00024d78      0x640 shell.o
                0x00024de0                shellProcedure
                0x00024d78                shellMain
                0x000252de                boot
                0x00025389                shellInit
                0x00024ee2                shellWaitCmd
                0x000252e3                debug
                0x00024efa                shellCompare
                0x000252fc                testa_mbr
                0x00024e62                shellInitializePrompt
                0x0002533c                testa_root
                0x0002537c                reboot
                0x000252ca                shellHelp
 .text          0x000253b8       0x10 services.o
                0x000253c2                system_services
                0x000253b8                blServices
 .text          0x000253c8       0x20 abort.o
                0x000253c8                abort
 .text          0x000253e8      0x100 faults.o
                0x000254d7                mostra_reg
                0x000253e8                cpu_falts
                0x00026000                . = ALIGN (0x1000)
 *fill*         0x000254e8      0xb18 00

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
