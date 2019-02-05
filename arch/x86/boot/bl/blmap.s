
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
current_mmblock     0x4               main.o
STATUS_Y            0x4               main.o
mm_prev_pointer     0x4               heap.o
shell_string_buffer
                    0x400             shell.o
deslocamento        0x4               shell.o
bl_heap_start       0x4               main.o
buffer_dir_entry    0x200             main.o
BootLoaderCR3       0x4               main.o
next_address        0x4               main.o
shift_status        0x4               keyboard.o
g_available_heap    0x4               main.o
alt_status          0x4               keyboard.o
heapCount           0x4               main.o
EDITBOX_ALTURA      0x4               main.o
g_lbf_va            0x4               main.o
LegacyCR3           0x4               main.o
g_proc_status       0x4               main.o
g_heap_pointer      0x4               main.o
gdefTesting         0x4               main.o
heapList            0x20              main.o
procedure_info      0x10              main.o
EDITBOX_TEXT_COLOR  0x4               main.o
CURSOR_Y            0x4               main.o
EDITBOX_Y           0x4               main.o
g_system_color      0x4               main.o
CURSOR_X            0x4               main.o
last_size           0x4               heap.o
useGUI              0x4               main.o
last_valid          0x4               heap.o
ret_string          0x4               shell.o
file_cluster_list   0x800             main.o
vesa_mode           0x10              main.o
escape_status       0x4               keyboard.o
mmblockList         0x400             main.o
g_next_app          0x4               main.o
bl_heap_end         0x4               main.o
tab_status          0x4               keyboard.o
VideoBlock          0x1c              main.o
g_cursor_y          0x4               main.o
g_cmd_status        0x4               main.o
ShellInitialized    0x4               shell.o
key_status          0x4               keyboard.o
g_file_system_type  0x4               main.o
mmblockCount        0x4               main.o
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
 .text          0x000000000002237a      0x110 main.o
                0x000000000002237a                BlMain
                0x00000000000223d9                BlLoadKernel
                0x0000000000022405                BlLoadFiles
                0x0000000000022431                BlSetupPaging
                0x000000000002243f                BlAbort
                0x000000000002244d                BlKernelModuleMain
                0x000000000002246b                die
 .text          0x000000000002248a      0x2a4 loader.o
                0x000000000002248a                load_kernel
                0x0000000000022569                load_files
 .text          0x000000000002272e      0x108 init.o
                0x000000000002272e                set_up_color
                0x000000000002273c                set_up_text_color
                0x0000000000022768                init_globals
                0x00000000000227a0                init
 .text          0x0000000000022836       0xd5 ports.o
                0x0000000000022836                bloutportb
                0x0000000000022843                outb
                0x0000000000022850                inportb
                0x0000000000022865                outportb
                0x0000000000022872                inport8
                0x0000000000022881                outport8
                0x000000000002288e                inport16
                0x000000000002289e                outport16
                0x00000000000228ac                inport32
                0x00000000000228bb                outport32
                0x00000000000228c8                inb
                0x00000000000228ea                inportl
                0x00000000000228fe                outportl
 .text          0x000000000002290b       0xd6 x86.o
                0x000000000002290b                enable
                0x0000000000022912                disable
                0x0000000000022919                stopCpu
                0x0000000000022921                intReturn
                0x0000000000022928                farReturn
                0x000000000002292f                getFlags
                0x000000000002293a                setFlags
                0x0000000000022945                BlProcessorInPort8
                0x0000000000022954                BlProcessorOutPort8
                0x0000000000022961                BlProcessorInPort16
                0x0000000000022971                BlProcessorOutPort16
                0x000000000002297f                BlProcessorInPort32
                0x000000000002298e                BlProcessorOutPort32
                0x000000000002299b                Push
                0x00000000000229a5                Pop
                0x00000000000229af                pushRegs
                0x00000000000229b6                popRegs
                0x00000000000229bd                pushFlags
                0x00000000000229c4                popFlags
                0x00000000000229cb                getStackPointer
                0x00000000000229d6                setStackPointer
 .text          0x00000000000229e1      0xb7d stdio.o
                0x00000000000229e1                panic
                0x0000000000022a02                scroll
                0x0000000000022a8d                bl_clear
                0x0000000000022ae7                kprintf
                0x0000000000022f3a                printf
                0x0000000000022f57                sprintf
                0x0000000000022fac                putchar
                0x0000000000022fc5                outbyte
                0x000000000002312c                _outbyte
                0x0000000000023202                printf_main
                0x000000000002320c                input
                0x000000000002333b                my_buffer_horizontal_line
                0x0000000000023365                my_buffer_put_pixel
                0x0000000000023437                my_buffer_char_blt
                0x00000000000234b3                vsync
                0x00000000000234f0                gui_inb
                0x0000000000023515                get_cursor_x
                0x000000000002352a                get_cursor_y
                0x000000000002353f                carrega_bitmap_16x16
 .text          0x000000000002355e       0x5b stdlib.o
                0x000000000002355e                malloc
                0x000000000002359a                free
 .text          0x00000000000235b9      0x25a string.o
                0x00000000000235b9                strcmp
                0x000000000002361e                strncmp
                0x0000000000023681                str_cmp
                0x00000000000236ff                memcpy
                0x000000000002373d                strlen
                0x0000000000023764                strcpy
                0x0000000000023798                strcat
                0x00000000000237c7                bcopy
                0x00000000000237f3                bzero
 .text          0x0000000000023813      0x1d6 keyboard.o
                0x0000000000023813                keyboardHandler
 .text          0x00000000000239e9      0x253 pci.o
                0x00000000000239e9                pciConfigReadWord
                0x0000000000023a90                pciCheckDevice
                0x0000000000023aea                pciCheckVendor
                0x0000000000023b2a                pciGetClassCode
                0x0000000000023b5b                pciInfo
                0x0000000000023c32                pciInit
 .text          0x0000000000023c3c       0x48 hdd.o
                0x0000000000023c3c                my_read_hd_sector
                0x0000000000023c5a                my_write_hd_sector
                0x0000000000023c78                limpa_root
                0x0000000000023c7e                limpa_fat
 .text          0x0000000000023c84       0x48 timer.o
                0x0000000000023c84                timer
                0x0000000000023cb0                BltimerInit
 .text          0x0000000000023ccc      0x588 pages.o
                0x0000000000023ccc                SetUpPaging
 .text          0x0000000000024254      0x3b7 heap.o
                0x0000000000024254                heapAllocateMemory
                0x000000000002442f                FreeHeap
                0x00000000000244ef                init_heap
 .text          0x000000000002460b       0x92 procedure.o
                0x000000000002460b                bl_procedure
 .text          0x000000000002469d      0x7cf fs.o
                0x000000000002469d                fatClustToSect
                0x00000000000246c4                fatLoadCluster
                0x0000000000024700                fs_format
                0x0000000000024719                fs_search_empty_entry
                0x0000000000024723                fs_find_not_empty_entry
                0x000000000002472d                fs_test_fat_vector
                0x0000000000024733                fs_get_fat_entry
                0x000000000002473d                fs_create_entry
                0x0000000000024743                fsCreateFileName
                0x0000000000024749                fsSaveFileName
                0x000000000002474f                fs_save_entry_on_disc
                0x0000000000024755                fs_set_structures
                0x000000000002475b                fs_set_entry
                0x0000000000024761                fs_get_entry
                0x0000000000024767                fs_show_dir_entry
                0x000000000002476d                fs_show_dir
                0x0000000000024773                fs_check_cluster
                0x000000000002477d                fsSaveRootDir
                0x0000000000024783                fs_load_dir
                0x0000000000024789                fs_save_dir
                0x000000000002478f                fs_save_structure
                0x0000000000024795                fs_save_entry_on_root
                0x000000000002479b                fs_show_entry
                0x00000000000247a1                fs_delete_entry
                0x00000000000247a7                fs_init_bootfile_struct
                0x00000000000247ad                fs_get_entry_status
                0x00000000000247b7                fs_set_entry_status
                0x00000000000247bd                fs_makeboot
                0x00000000000247c7                fs_set_fat_entry
                0x00000000000247cd                fs_find_empty_entry
                0x00000000000247d7                fs_install
                0x00000000000247dd                fs_relood_dir
                0x00000000000247e3                fsLoadFile
                0x000000000002499f                fsSearchFile
                0x0000000000024a71                fsSearchFileName
                0x0000000000024a87                fs_load_rootdirEx
                0x0000000000024ad8                fs_load_fatEx
                0x0000000000024b26                fs_put_list_on_fat
                0x0000000000024be9                fs_find_n_empty_entries
                0x0000000000024c6a                fs_load_rootdir
                0x0000000000024c78                read_lba
                0x0000000000024c93                write_lba
                0x0000000000024cae                fsSaveFile
                0x0000000000024cb8                fsCreateDir
                0x0000000000024cd1                fsCreateFile
                0x0000000000024dcc                fsClearFat
                0x0000000000024dda                fsCheckFat
                0x0000000000024e4c                fsInitFat
                0x0000000000024e52                fsInitStructures
                0x0000000000024e58                fsInit
 .text          0x0000000000024e6c      0x60b shell.o
                0x0000000000024e6c                shellMain
                0x0000000000024ed7                shellProcedure
                0x0000000000024f4c                shellInitializePrompt
                0x0000000000024fdb                shellWaitCmd
                0x0000000000024ff5                shellCompare
                0x00000000000253a9                shellHelp
                0x00000000000253c2                boot
                0x00000000000253c8                debug
                0x00000000000253e3                testa_mbr
                0x0000000000025414                testa_root
                0x0000000000025448                reboot
                0x0000000000025456                shellInit
 .text          0x0000000000025477       0x14 services.o
                0x0000000000025477                blServices
                0x0000000000025485                system_services
 .text          0x000000000002548b       0x1f abort.o
                0x000000000002548b                abort
 .text          0x00000000000254aa       0xc0 faults.o
                0x00000000000254aa                cpu_falts
                0x0000000000025564                faultsShowRegisters
                0x0000000000026000                . = ALIGN (0x1000)
 *fill*         0x000000000002556a      0xa96 

.rodata         0x0000000000026000      0x7d8
 .rodata        0x0000000000026000       0x5f main.o
 *fill*         0x000000000002605f        0x1 
 .rodata        0x0000000000026060       0xf3 loader.o
 .rodata        0x0000000000026153       0x11 init.o
 .rodata        0x0000000000026164       0x37 stdio.o
 *fill*         0x000000000002619b        0x1 
 .rodata        0x000000000002619c       0x44 pci.o
 .rodata        0x00000000000261e0      0x1c1 heap.o
 .rodata        0x00000000000263a1        0xc procedure.o
 *fill*         0x00000000000263ad        0x3 
 .rodata        0x00000000000263b0      0x1c8 fs.o
 .rodata        0x0000000000026578      0x1b2 shell.o
 .rodata        0x000000000002672a        0xd abort.o
 *fill*         0x0000000000026737        0x1 
 .rodata        0x0000000000026738       0xa0 faults.o

.eh_frame       0x0000000000027000     0x16e0
 .eh_frame      0x0000000000027000       0xf4 main.o
 .eh_frame      0x00000000000270f4       0x58 loader.o
 .eh_frame      0x000000000002714c       0x98 init.o
 .eh_frame      0x00000000000271e4      0x1b8 ports.o
 .eh_frame      0x000000000002739c      0x2b8 x86.o
 .eh_frame      0x0000000000027654      0x32c stdio.o
 .eh_frame      0x0000000000027980       0x58 stdlib.o
 .eh_frame      0x00000000000279d8      0x138 string.o
 .eh_frame      0x0000000000027b10       0x38 keyboard.o
 .eh_frame      0x0000000000027b48       0xe0 pci.o
 .eh_frame      0x0000000000027c28       0x98 hdd.o
 .eh_frame      0x0000000000027cc0       0x58 timer.o
 .eh_frame      0x0000000000027d18       0x38 pages.o
 .eh_frame      0x0000000000027d50       0x78 heap.o
 .eh_frame      0x0000000000027dc8       0x38 procedure.o
 .eh_frame      0x0000000000027e00      0x658 fs.o
 .eh_frame      0x0000000000028458      0x198 shell.o
 .eh_frame      0x00000000000285f0       0x58 services.o
 .eh_frame      0x0000000000028648       0x34 abort.o
 .eh_frame      0x000000000002867c       0x58 faults.o

.data           0x00000000000286e0      0x920
                0x00000000000286e0                data = .
                0x00000000000286e0                _data = .
                0x00000000000286e0                __data = .
 *(.data)
 .data          0x00000000000286e0        0x2 head.o
                0x00000000000286e0                data_start
 .data          0x00000000000286e2        0x0 main.o
 .data          0x00000000000286e2        0x0 loader.o
 .data          0x00000000000286e2        0x0 init.o
 .data          0x00000000000286e2        0x0 ports.o
 .data          0x00000000000286e2        0x0 x86.o
 .data          0x00000000000286e2        0x0 stdio.o
 .data          0x00000000000286e2        0x0 stdlib.o
 .data          0x00000000000286e2        0x0 string.o
 *fill*         0x00000000000286e2       0x1e 
 .data          0x0000000000028700      0x1a0 keyboard.o
                0x0000000000028700                destroy_window
                0x0000000000028704                quit_message
 .data          0x00000000000288a0        0x0 pci.o
 .data          0x00000000000288a0        0x0 hdd.o
 .data          0x00000000000288a0        0x0 timer.o
 .data          0x00000000000288a0        0x0 pages.o
 .data          0x00000000000288a0        0x0 heap.o
 .data          0x00000000000288a0        0x0 procedure.o
 .data          0x00000000000288a0        0x0 fs.o
 .data          0x00000000000288a0       0x2c shell.o
                0x00000000000288a0                help_string
 .data          0x00000000000288cc        0x0 services.o
 .data          0x00000000000288cc        0x0 abort.o
 .data          0x00000000000288cc        0x0 faults.o
                0x0000000000029000                . = ALIGN (0x1000)
 *fill*         0x00000000000288cc      0x734 

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
 .bss           0x0000000000029001        0x0 stdlib.o
 .bss           0x0000000000029001        0x0 string.o
 *fill*         0x0000000000029001        0x3 
 .bss           0x0000000000029004        0x4 keyboard.o
                0x0000000000029004                ambiente
 .bss           0x0000000000029008        0x0 pci.o
 .bss           0x0000000000029008        0x0 hdd.o
 .bss           0x0000000000029008        0x0 timer.o
 .bss           0x0000000000029008        0x0 pages.o
 .bss           0x0000000000029008        0x0 heap.o
 .bss           0x0000000000029008        0x0 procedure.o
 .bss           0x0000000000029008        0x0 fs.o
 .bss           0x0000000000029008        0x0 shell.o
 .bss           0x0000000000029008        0x0 services.o
 .bss           0x0000000000029008        0x0 abort.o
 .bss           0x0000000000029008        0x0 faults.o
 *(COMMON)
 *fill*         0x0000000000029008       0x18 
 COMMON         0x0000000000029020     0x106c main.o
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
                0x0000000000029170                current_mmblock
                0x0000000000029174                STATUS_Y
                0x0000000000029178                bl_heap_start
                0x0000000000029180                buffer_dir_entry
                0x0000000000029380                BootLoaderCR3
                0x0000000000029384                next_address
                0x0000000000029388                g_available_heap
                0x000000000002938c                heapCount
                0x0000000000029390                EDITBOX_ALTURA
                0x0000000000029394                g_lbf_va
                0x0000000000029398                LegacyCR3
                0x000000000002939c                g_proc_status
                0x00000000000293a0                g_heap_pointer
                0x00000000000293a4                gdefTesting
                0x00000000000293c0                heapList
                0x00000000000293e0                procedure_info
                0x00000000000293f0                EDITBOX_TEXT_COLOR
                0x00000000000293f4                CURSOR_Y
                0x00000000000293f8                EDITBOX_Y
                0x00000000000293fc                g_system_color
                0x0000000000029400                CURSOR_X
                0x0000000000029404                useGUI
                0x0000000000029420                file_cluster_list
                0x0000000000029c20                vesa_mode
                0x0000000000029c40                mmblockList
                0x000000000002a040                g_next_app
                0x000000000002a044                bl_heap_end
                0x000000000002a048                VideoBlock
                0x000000000002a064                g_cursor_y
                0x000000000002a068                g_cmd_status
                0x000000000002a06c                g_file_system_type
                0x000000000002a070                mmblockCount
                0x000000000002a074                g_char_attrib
                0x000000000002a078                g_next_proc
                0x000000000002a07c                g_lbf_pa
                0x000000000002a080                g_nova_mensagem
                0x000000000002a084                EDITBOX_X
                0x000000000002a088                g_cursor_x
 COMMON         0x000000000002a08c       0x1c keyboard.o
                0x000000000002a08c                shift_status
                0x000000000002a090                alt_status
                0x000000000002a094                escape_status
                0x000000000002a098                tab_status
                0x000000000002a09c                key_status
                0x000000000002a0a0                ctrl_status
                0x000000000002a0a4                winkey_status
 COMMON         0x000000000002a0a8        0x4 timer.o
                0x000000000002a0a8                timerTicks
 COMMON         0x000000000002a0ac        0xc heap.o
                0x000000000002a0ac                mm_prev_pointer
                0x000000000002a0b0                last_size
                0x000000000002a0b4                last_valid
 *fill*         0x000000000002a0b8        0x8 
 COMMON         0x000000000002a0c0      0x42c shell.o
                0x000000000002a0c0                shell_status
                0x000000000002a0e0                shell_string_buffer
                0x000000000002a4e0                deslocamento
                0x000000000002a4e4                ret_string
                0x000000000002a4e8                ShellInitialized
 *(.bss_heap)
 .bss_heap      0x000000000002a4ec      0x400 head.o
                0x000000000002a4ec                bootloader_heap_start
                0x000000000002a8ec                bootloader_heap_end
 *(.bss_stack)
 .bss_stack     0x000000000002a8ec      0x400 head.o
                0x000000000002a8ec                bootloader_stack_end
                0x000000000002acec                bootloader_stack_start
                0x000000000002b000                . = ALIGN (0x1000)
 *fill*         0x000000000002acec      0x314 
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
LOAD stdlib.o
LOAD string.o
LOAD keyboard.o
LOAD pci.o
LOAD hdd.o
LOAD timer.o
LOAD pages.o
LOAD heap.o
LOAD procedure.o
LOAD fs.o
LOAD shell.o
LOAD services.o
LOAD abort.o
LOAD faults.o
OUTPUT(BL.BIN pe-i386)

.comment        0x0000000000000000      0x21c
 .comment       0x0000000000000000       0x1b main.o
 .comment       0x000000000000001b       0x1b loader.o
 .comment       0x0000000000000036       0x1b init.o
 .comment       0x0000000000000051       0x1b ports.o
 .comment       0x000000000000006c       0x1b x86.o
 .comment       0x0000000000000087       0x1b stdio.o
 .comment       0x00000000000000a2       0x1b stdlib.o
 .comment       0x00000000000000bd       0x1b string.o
 .comment       0x00000000000000d8       0x1b keyboard.o
 .comment       0x00000000000000f3       0x1b pci.o
 .comment       0x000000000000010e       0x1b hdd.o
 .comment       0x0000000000000129       0x1b timer.o
 .comment       0x0000000000000144       0x1b pages.o
 .comment       0x000000000000015f       0x1b heap.o
 .comment       0x000000000000017a       0x1b procedure.o
 .comment       0x0000000000000195       0x1b fs.o
 .comment       0x00000000000001b0       0x1b shell.o
 .comment       0x00000000000001cb       0x1b services.o
 .comment       0x00000000000001e6       0x1b abort.o
 .comment       0x0000000000000201       0x1b faults.o

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
                0x0000000000000000        0x0 stdlib.o
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
                0x0000000000000000        0x0 heap.o
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
