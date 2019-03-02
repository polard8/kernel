
Allocating common symbols
Common symbol       size              file

g_fat16_fat_status  0x4               main.o
timerTicks          0x4               timer.o
prompt              0xfa              main.o
EDITBOX_LARGURA     0x4               main.o
partition           0x10              main.o
system_info         0x8               main.o
dma_addr            0x4               ide.o
g_initialized       0x4               main.o
ata_record_dev      0x1               main.o
bliTesting          0x4               main.o
g_driver_hdd_initialized
                    0x4               main.o
EDITBOX_BG_COLOR    0x4               main.o
shell_status        0x4               shell.o
current_dev         0x4               ide.o
STATUS_X            0x4               main.o
prompt_pos          0x4               main.o
ide_handler_address
                    0x4               main.o
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
ide_dma_prdt        0x20              ide.o
g_available_heap    0x4               main.o
alt_status          0x4               keyboard.o
ata_record_channel  0x1               main.o
heapCount           0x4               main.o
EDITBOX_ALTURA      0x4               main.o
g_lbf_va            0x4               main.o
LegacyCR3           0x4               main.o
g_proc_status       0x4               main.o
g_heap_pointer      0x4               main.o
gdefTesting         0x4               main.o
heapList            0x20              main.o
ata_pci             0x34              main.o
ATAFlag             0x4               main.o
procedure_info      0x10              main.o
EDITBOX_TEXT_COLOR  0x4               main.o
hddError            0x4               hdd.o
ide_ports           0x60              main.o
CURSOR_Y            0x4               main.o
EDITBOX_Y           0x4               main.o
IDE                 0x14              main.o
g_system_color      0x4               main.o
CURSOR_X            0x4               main.o
last_size           0x4               heap.o
useGUI              0x4               main.o
ready_queue_dev     0x4               ide.o
last_valid          0x4               heap.o
ret_string          0x4               shell.o
file_cluster_list   0x800             main.o
vesa_mode           0x10              main.o
escape_status       0x4               keyboard.o
mmblockList         0x400             main.o
ata_identify_dev_buf
                    0x4               main.o
g_next_app          0x4               main.o
bl_heap_end         0x4               main.o
dev_nport           0x20              main.o
ata                 0x18              main.o
tab_status          0x4               keyboard.o
VideoBlock          0x1c              main.o
g_cursor_y          0x4               main.o
g_cmd_status        0x4               main.o
ShellInitialized    0x4               shell.o
key_status          0x4               keyboard.o
g_file_system_type  0x4               main.o
mmblockCount        0x4               main.o
hddStatus           0x4               hdd.o
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

.text           0x0000000000021000     0x7000
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
 .text          0x000000000002237a      0x15f main.o
                0x000000000002237a                BlMain
                0x0000000000022428                BlLoadKernel
                0x0000000000022454                BlLoadFiles
                0x0000000000022480                BlSetupPaging
                0x000000000002248e                BlAbort
                0x000000000002249c                BlKernelModuleMain
                0x00000000000224ba                die
 .text          0x00000000000224d9      0x3fb loader.o
                0x00000000000224d9                load_kernel
                0x0000000000022628                load_files
 .text          0x00000000000228d4      0x177 init.o
                0x00000000000228d4                set_up_color
                0x00000000000228e2                set_up_text_color
                0x000000000002290e                init_globals
                0x0000000000022946                init
 .text          0x0000000000022a4b       0xd5 ports.o
                0x0000000000022a4b                bloutportb
                0x0000000000022a58                outb
                0x0000000000022a65                inportb
                0x0000000000022a7a                outportb
                0x0000000000022a87                inport8
                0x0000000000022a96                outport8
                0x0000000000022aa3                inport16
                0x0000000000022ab3                outport16
                0x0000000000022ac1                inport32
                0x0000000000022ad0                outport32
                0x0000000000022add                inb
                0x0000000000022aff                inportl
                0x0000000000022b13                outportl
 .text          0x0000000000022b20       0xd6 x86.o
                0x0000000000022b20                enable
                0x0000000000022b27                disable
                0x0000000000022b2e                stopCpu
                0x0000000000022b36                intReturn
                0x0000000000022b3d                farReturn
                0x0000000000022b44                getFlags
                0x0000000000022b4f                setFlags
                0x0000000000022b5a                BlProcessorInPort8
                0x0000000000022b69                BlProcessorOutPort8
                0x0000000000022b76                BlProcessorInPort16
                0x0000000000022b86                BlProcessorOutPort16
                0x0000000000022b94                BlProcessorInPort32
                0x0000000000022ba3                BlProcessorOutPort32
                0x0000000000022bb0                Push
                0x0000000000022bba                Pop
                0x0000000000022bc4                pushRegs
                0x0000000000022bcb                popRegs
                0x0000000000022bd2                pushFlags
                0x0000000000022bd9                popFlags
                0x0000000000022be0                getStackPointer
                0x0000000000022beb                setStackPointer
 .text          0x0000000000022bf6      0xb7d stdio.o
                0x0000000000022bf6                panic
                0x0000000000022c17                scroll
                0x0000000000022ca2                bl_clear
                0x0000000000022cfc                kprintf
                0x000000000002314f                printf
                0x000000000002316c                sprintf
                0x00000000000231c1                putchar
                0x00000000000231da                outbyte
                0x0000000000023341                _outbyte
                0x0000000000023417                printf_main
                0x0000000000023421                input
                0x0000000000023550                my_buffer_horizontal_line
                0x000000000002357a                my_buffer_put_pixel
                0x000000000002364c                my_buffer_char_blt
                0x00000000000236c8                vsync
                0x0000000000023705                gui_inb
                0x000000000002372a                get_cursor_x
                0x000000000002373f                get_cursor_y
                0x0000000000023754                carrega_bitmap_16x16
 .text          0x0000000000023773       0x5b stdlib.o
                0x0000000000023773                malloc
                0x00000000000237af                free
 .text          0x00000000000237ce      0x25a string.o
                0x00000000000237ce                strcmp
                0x0000000000023833                strncmp
                0x0000000000023896                str_cmp
                0x0000000000023914                memcpy
                0x0000000000023952                strlen
                0x0000000000023979                strcpy
                0x00000000000239ad                strcat
                0x00000000000239dc                bcopy
                0x0000000000023a08                bzero
 .text          0x0000000000023a28      0x1d6 keyboard.o
                0x0000000000023a28                keyboardHandler
 .text          0x0000000000023bfe      0x253 pci.o
                0x0000000000023bfe                pciConfigReadWord
                0x0000000000023ca5                pciCheckDevice
                0x0000000000023cff                pciCheckVendor
                0x0000000000023d3f                pciGetClassCode
                0x0000000000023d70                pciInfo
                0x0000000000023e47                pciInit
 .text          0x0000000000023e51      0x442 hdd.o
                0x0000000000023e87                hdd_ata_pio_write
                0x0000000000023ebd                hdd_ata_status_read
                0x0000000000023eeb                hdd_ata_wait_not_busy
                0x0000000000023f2b                hdd_ata_cmd_write
                0x0000000000023f7b                hdd_ata_wait_no_drq
                0x0000000000023fc1                pio_rw_sector
                0x0000000000024225                my_read_hd_sector
                0x0000000000024245                my_write_hd_sector
                0x0000000000024265                init_hdd
 .text          0x0000000000024293     0x1c2c ide.o
                0x0000000000024293                disk_get_ata_irq_invoked
                0x000000000002429d                disk_reset_ata_irq_invoked
                0x00000000000242ad                ata_wait
                0x00000000000242df                ata_wait_not_busy
                0x000000000002430d                ata_wait_busy
                0x000000000002433b                ata_wait_no_drq
                0x000000000002436f                ata_wait_drq
                0x00000000000243a3                ata_wait_irq
                0x000000000002441a                ata_soft_reset
                0x0000000000024473                ata_status_read
                0x000000000002448f                ata_cmd_write
                0x00000000000244c4                ata_assert_dever
                0x0000000000024569                ide_identify_device
                0x00000000000249bd                set_ata_addr
                0x0000000000024a13                ide_mass_storage_initialize
                0x0000000000024ab9                ide_dev_init
                0x0000000000024e7e                nport_ajuste
                0x0000000000024ed7                ata_pio_read
                0x0000000000024efc                ata_pio_write
                0x0000000000024f21                ide_dma_data
                0x0000000000024ff9                ide_dma_start
                0x0000000000025033                ide_dma_stop
                0x000000000002509e                ide_dma_read_status
                0x00000000000250bd                diskReadPCIConfigAddr
                0x000000000002511c                diskWritePCIConfigAddr
                0x0000000000025180                diskATAPCIConfigurationSpace
                0x0000000000025857                diskPCIScanDevice
                0x0000000000025964                diskATAInitialize
                0x0000000000025cc1                diskATADialog
                0x0000000000025d02                diskATAIRQHandler1
                0x0000000000025d12                diskATAIRQHandler2
                0x0000000000025d22                show_ide_info
                0x0000000000025e45                disk_ata_wait_irq
 .text          0x0000000000025ebf       0x48 timer.o
                0x0000000000025ebf                timer
                0x0000000000025eeb                BltimerInit
 .text          0x0000000000025f07      0x588 pages.o
                0x0000000000025f07                SetUpPaging
 .text          0x000000000002648f      0x3b7 heap.o
                0x000000000002648f                heapAllocateMemory
                0x000000000002666a                FreeHeap
                0x000000000002672a                init_heap
 .text          0x0000000000026846       0x92 procedure.o
                0x0000000000026846                bl_procedure
 .text          0x00000000000268d8      0xa8a fs.o
                0x00000000000268d8                fatClustToSect
                0x00000000000268ff                fatLoadCluster
                0x000000000002693b                fs_format
                0x0000000000026954                fs_search_empty_entry
                0x000000000002695e                fs_find_not_empty_entry
                0x0000000000026968                fs_test_fat_vector
                0x000000000002696e                fs_get_fat_entry
                0x0000000000026978                fs_create_entry
                0x000000000002697e                fsCreateFileName
                0x0000000000026984                fsSaveFileName
                0x000000000002698a                fs_save_entry_on_disc
                0x0000000000026990                fs_set_structures
                0x0000000000026996                fs_set_entry
                0x000000000002699c                fs_get_entry
                0x00000000000269a2                fs_show_dir_entry
                0x00000000000269a8                fs_show_dir
                0x00000000000269ae                fs_check_cluster
                0x00000000000269b8                fsSaveRootDir
                0x00000000000269be                fs_load_dir
                0x00000000000269c4                fs_save_dir
                0x00000000000269ca                fs_save_structure
                0x00000000000269d0                fs_save_entry_on_root
                0x00000000000269d6                fs_show_entry
                0x00000000000269dc                fs_delete_entry
                0x00000000000269e2                fs_init_bootfile_struct
                0x00000000000269e8                fs_get_entry_status
                0x00000000000269f2                fs_set_entry_status
                0x00000000000269f8                fs_makeboot
                0x0000000000026a02                fs_set_fat_entry
                0x0000000000026a08                fs_find_empty_entry
                0x0000000000026a12                fs_install
                0x0000000000026a18                fs_relood_dir
                0x0000000000026a1e                fsLoadFile
                0x0000000000026c18                load_path
                0x0000000000026e4c                fsSearchFile
                0x0000000000026f1e                fsSearchFileName
                0x0000000000026f34                fs_load_rootdirEx
                0x0000000000026f85                fs_load_fatEx
                0x0000000000026fd3                fs_put_list_on_fat
                0x0000000000027096                fs_find_n_empty_entries
                0x0000000000027117                fs_load_rootdir
                0x0000000000027125                read_lba
                0x0000000000027140                write_lba
                0x000000000002715b                fsSaveFile
                0x0000000000027165                fsCreateDir
                0x000000000002717e                fsCreateFile
                0x000000000002728f                fsClearFat
                0x000000000002729d                fsCheckFat
                0x000000000002731f                fsInitFat
                0x0000000000027325                fsInitStructures
                0x000000000002732b                fsInit
 .text          0x0000000000027362      0x61b shell.o
                0x0000000000027362                shellMain
                0x00000000000273cd                shellProcedure
                0x0000000000027442                shellInitializePrompt
                0x00000000000274d1                shellWaitCmd
                0x00000000000274eb                shellCompare
                0x000000000002789f                shellHelp
                0x00000000000278b8                boot
                0x00000000000278be                debug
                0x00000000000278e9                testa_mbr
                0x000000000002791a                testa_root
                0x000000000002794e                reboot
                0x000000000002795c                shellInit
 .text          0x000000000002797d       0x14 services.o
                0x000000000002797d                blServices
                0x000000000002798b                system_services
 .text          0x0000000000027991       0x1f abort.o
                0x0000000000027991                abort
 .text          0x00000000000279b0       0xc0 faults.o
                0x00000000000279b0                cpu_falts
                0x0000000000027a6a                faultsShowRegisters
                0x0000000000028000                . = ALIGN (0x1000)
 *fill*         0x0000000000027a70      0x590 

.rodata         0x0000000000028000     0x10ec
 .rodata        0x0000000000028000       0xcb main.o
 *fill*         0x00000000000280cb        0x1 
 .rodata        0x00000000000280cc      0x26b loader.o
 *fill*         0x0000000000028337        0x1 
 .rodata        0x0000000000028338       0x8e init.o
 *fill*         0x00000000000283c6        0x2 
 .rodata        0x00000000000283c8       0x3f stdio.o
 *fill*         0x0000000000028407        0x1 
 .rodata        0x0000000000028408       0x44 pci.o
 .rodata        0x000000000002844c       0x33 hdd.o
 *fill*         0x000000000002847f        0x1 
 .rodata        0x0000000000028480      0x4cd ide.o
 *fill*         0x000000000002894d        0x3 
 .rodata        0x0000000000028950      0x1c1 heap.o
 .rodata        0x0000000000028b11        0xc procedure.o
 *fill*         0x0000000000028b1d        0x3 
 .rodata        0x0000000000028b20      0x35c fs.o
 .rodata        0x0000000000028e7c      0x1c0 shell.o
 .rodata        0x000000000002903c        0xd abort.o
 *fill*         0x0000000000029049        0x3 
 .rodata        0x000000000002904c       0xa0 faults.o

.eh_frame       0x000000000002a000     0x1c60
 .eh_frame      0x000000000002a000       0xf4 main.o
 .eh_frame      0x000000000002a0f4       0x58 loader.o
 .eh_frame      0x000000000002a14c       0x98 init.o
 .eh_frame      0x000000000002a1e4      0x1b8 ports.o
 .eh_frame      0x000000000002a39c      0x2b8 x86.o
 .eh_frame      0x000000000002a654      0x32c stdio.o
 .eh_frame      0x000000000002a980       0x58 stdlib.o
 .eh_frame      0x000000000002a9d8      0x138 string.o
 .eh_frame      0x000000000002ab10       0x38 keyboard.o
 .eh_frame      0x000000000002ab48       0xe0 pci.o
 .eh_frame      0x000000000002ac28      0x160 hdd.o
 .eh_frame      0x000000000002ad88      0x494 ide.o
 .eh_frame      0x000000000002b21c       0x58 timer.o
 .eh_frame      0x000000000002b274       0x38 pages.o
 .eh_frame      0x000000000002b2ac       0x78 heap.o
 .eh_frame      0x000000000002b324       0x38 procedure.o
 .eh_frame      0x000000000002b35c      0x678 fs.o
 .eh_frame      0x000000000002b9d4      0x198 shell.o
 .eh_frame      0x000000000002bb6c       0x58 services.o
 .eh_frame      0x000000000002bbc4       0x34 abort.o
 .eh_frame      0x000000000002bbf8       0x58 faults.o

.data           0x000000000002bc60     0x13a0
                0x000000000002bc60                data = .
                0x000000000002bc60                _data = .
                0x000000000002bc60                __data = .
 *(.data)
 .data          0x000000000002bc60        0x2 head.o
                0x000000000002bc60                data_start
 .data          0x000000000002bc62        0x0 main.o
 .data          0x000000000002bc62        0x0 loader.o
 .data          0x000000000002bc62        0x0 init.o
 .data          0x000000000002bc62        0x0 ports.o
 .data          0x000000000002bc62        0x0 x86.o
 .data          0x000000000002bc62        0x0 stdio.o
 .data          0x000000000002bc62        0x0 stdlib.o
 .data          0x000000000002bc62        0x0 string.o
 *fill*         0x000000000002bc62       0x1e 
 .data          0x000000000002bc80      0x1a0 keyboard.o
                0x000000000002bc80                destroy_window
                0x000000000002bc84                quit_message
 .data          0x000000000002be20        0x0 pci.o
 .data          0x000000000002be20        0x0 hdd.o
 .data          0x000000000002be20      0x440 ide.o
                0x000000000002be3c                dev_type
                0x000000000002be60                pci_classes
 .data          0x000000000002c260        0x0 timer.o
 .data          0x000000000002c260        0x0 pages.o
 .data          0x000000000002c260        0x0 heap.o
 .data          0x000000000002c260        0x0 procedure.o
 .data          0x000000000002c260        0x0 fs.o
 .data          0x000000000002c260       0x2c shell.o
                0x000000000002c260                help_string
 .data          0x000000000002c28c        0x0 services.o
 .data          0x000000000002c28c        0x0 abort.o
 .data          0x000000000002c28c        0x0 faults.o
                0x000000000002d000                . = ALIGN (0x1000)
 *fill*         0x000000000002c28c      0xd74 

.bss            0x000000000002d000     0x2000
                0x000000000002d000                bss = .
                0x000000000002d000                _bss = .
                0x000000000002d000                __bss = .
 *(.bss)
 .bss           0x000000000002d000        0x0 head.o
                0x000000000002d000                bss_start
 .bss           0x000000000002d000        0x0 main.o
 .bss           0x000000000002d000        0x0 loader.o
 .bss           0x000000000002d000        0x0 init.o
 .bss           0x000000000002d000        0x0 ports.o
 .bss           0x000000000002d000        0x0 x86.o
 .bss           0x000000000002d000        0x1 stdio.o
 .bss           0x000000000002d001        0x0 stdlib.o
 .bss           0x000000000002d001        0x0 string.o
 *fill*         0x000000000002d001        0x3 
 .bss           0x000000000002d004        0x4 keyboard.o
                0x000000000002d004                ambiente
 .bss           0x000000000002d008        0x0 pci.o
 .bss           0x000000000002d008        0x0 hdd.o
 .bss           0x000000000002d008       0x20 ide.o
                0x000000000002d008                dev_next_pid
 .bss           0x000000000002d028        0x0 timer.o
 .bss           0x000000000002d028        0x0 pages.o
 .bss           0x000000000002d028        0x0 heap.o
 .bss           0x000000000002d028        0x0 procedure.o
 .bss           0x000000000002d028        0x0 fs.o
 .bss           0x000000000002d028        0x0 shell.o
 .bss           0x000000000002d028        0x0 services.o
 .bss           0x000000000002d028        0x0 abort.o
 .bss           0x000000000002d028        0x0 faults.o
 *(COMMON)
 *fill*         0x000000000002d028       0x18 
 COMMON         0x000000000002d040     0x119c main.o
                0x000000000002d040                g_fat16_fat_status
                0x000000000002d060                prompt
                0x000000000002d15c                EDITBOX_LARGURA
                0x000000000002d160                partition
                0x000000000002d170                system_info
                0x000000000002d178                g_initialized
                0x000000000002d17c                ata_record_dev
                0x000000000002d180                bliTesting
                0x000000000002d184                g_driver_hdd_initialized
                0x000000000002d188                EDITBOX_BG_COLOR
                0x000000000002d18c                STATUS_X
                0x000000000002d190                prompt_pos
                0x000000000002d194                ide_handler_address
                0x000000000002d198                g_fat16_root_status
                0x000000000002d19c                current_mmblock
                0x000000000002d1a0                STATUS_Y
                0x000000000002d1a4                bl_heap_start
                0x000000000002d1c0                buffer_dir_entry
                0x000000000002d3c0                BootLoaderCR3
                0x000000000002d3c4                next_address
                0x000000000002d3c8                g_available_heap
                0x000000000002d3cc                ata_record_channel
                0x000000000002d3d0                heapCount
                0x000000000002d3d4                EDITBOX_ALTURA
                0x000000000002d3d8                g_lbf_va
                0x000000000002d3dc                LegacyCR3
                0x000000000002d3e0                g_proc_status
                0x000000000002d3e4                g_heap_pointer
                0x000000000002d3e8                gdefTesting
                0x000000000002d400                heapList
                0x000000000002d420                ata_pci
                0x000000000002d454                ATAFlag
                0x000000000002d458                procedure_info
                0x000000000002d468                EDITBOX_TEXT_COLOR
                0x000000000002d480                ide_ports
                0x000000000002d4e0                CURSOR_Y
                0x000000000002d4e4                EDITBOX_Y
                0x000000000002d4e8                IDE
                0x000000000002d4fc                g_system_color
                0x000000000002d500                CURSOR_X
                0x000000000002d504                useGUI
                0x000000000002d520                file_cluster_list
                0x000000000002dd20                vesa_mode
                0x000000000002dd40                mmblockList
                0x000000000002e140                ata_identify_dev_buf
                0x000000000002e144                g_next_app
                0x000000000002e148                bl_heap_end
                0x000000000002e160                dev_nport
                0x000000000002e180                ata
                0x000000000002e198                VideoBlock
                0x000000000002e1b4                g_cursor_y
                0x000000000002e1b8                g_cmd_status
                0x000000000002e1bc                g_file_system_type
                0x000000000002e1c0                mmblockCount
                0x000000000002e1c4                g_char_attrib
                0x000000000002e1c8                g_next_proc
                0x000000000002e1cc                g_lbf_pa
                0x000000000002e1d0                g_nova_mensagem
                0x000000000002e1d4                EDITBOX_X
                0x000000000002e1d8                g_cursor_x
 COMMON         0x000000000002e1dc       0x1c keyboard.o
                0x000000000002e1dc                shift_status
                0x000000000002e1e0                alt_status
                0x000000000002e1e4                escape_status
                0x000000000002e1e8                tab_status
                0x000000000002e1ec                key_status
                0x000000000002e1f0                ctrl_status
                0x000000000002e1f4                winkey_status
 COMMON         0x000000000002e1f8        0x8 hdd.o
                0x000000000002e1f8                hddError
                0x000000000002e1fc                hddStatus
 COMMON         0x000000000002e200       0x44 ide.o
                0x000000000002e200                dma_addr
                0x000000000002e204                current_dev
                0x000000000002e220                ide_dma_prdt
                0x000000000002e240                ready_queue_dev
 COMMON         0x000000000002e244        0x4 timer.o
                0x000000000002e244                timerTicks
 COMMON         0x000000000002e248        0xc heap.o
                0x000000000002e248                mm_prev_pointer
                0x000000000002e24c                last_size
                0x000000000002e250                last_valid
 *fill*         0x000000000002e254        0xc 
 COMMON         0x000000000002e260      0x42c shell.o
                0x000000000002e260                shell_status
                0x000000000002e280                shell_string_buffer
                0x000000000002e680                deslocamento
                0x000000000002e684                ret_string
                0x000000000002e688                ShellInitialized
 *(.bss_heap)
 .bss_heap      0x000000000002e68c      0x400 head.o
                0x000000000002e68c                bootloader_heap_start
                0x000000000002ea8c                bootloader_heap_end
 *(.bss_stack)
 .bss_stack     0x000000000002ea8c      0x400 head.o
                0x000000000002ea8c                bootloader_stack_end
                0x000000000002ee8c                bootloader_stack_start
                0x000000000002f000                . = ALIGN (0x1000)
 *fill*         0x000000000002ee8c      0x174 
                0x000000000002f000                end = .
                0x000000000002f000                _end = .
                0x000000000002f000                __end = .
                0x000000000002f000                _bootloader_end = .
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
LOAD ide.o
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

.comment        0x0000000000000000      0x238
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
 .comment       0x0000000000000129       0x1b ide.o
 .comment       0x0000000000000144       0x1b timer.o
 .comment       0x000000000000015f       0x1b pages.o
 .comment       0x000000000000017a       0x1b heap.o
 .comment       0x0000000000000195       0x1b procedure.o
 .comment       0x00000000000001b0       0x1b fs.o
 .comment       0x00000000000001cb       0x1b shell.o
 .comment       0x00000000000001e6       0x1b services.o
 .comment       0x0000000000000201       0x1b abort.o
 .comment       0x000000000000021c       0x1b faults.o

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
                0x0000000000000000        0x0 ide.o
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
