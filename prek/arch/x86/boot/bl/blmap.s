
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
g_current_ide_channel
                    0x4               main.o
g_heap_pointer      0x4               main.o
gdefTesting         0x4               main.o
heapList            0x20              main.o
ata_pci             0x34              main.o
ATAFlag             0x4               main.o
procedure_info      0x10              main.o
EDITBOX_TEXT_COLOR  0x4               main.o
____testing_memory_size_flag
                    0x4               main.o
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
__last_valid_address
                    0x4               main.o
ata                 0x18              main.o
tab_status          0x4               keyboard.o
VideoBlock          0x1c              main.o
g_cursor_y          0x4               main.o
idechannelList      0xc0              main.o
g_cmd_status        0x4               main.o
g_current_ide_device
                    0x4               main.o
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
 .head_x86      0x0000000000021000     0x140e head.o
                0x0000000000021000                bootloader_entry_point
                0x00000000000211fd                SavedBootBlock
                0x0000000000021201                SavedLFB
                0x0000000000021205                SavedX
                0x0000000000021209                SavedY
                0x000000000002120d                SavedBPP
                0x0000000000021211                SavedBootMode
                0x0000000000021b99                task0_stack
                0x0000000000021b9d                task1_stack
                0x0000000000021ba1                task2_stack
                0x0000000000021bd9                setup_idt_vector
                0x0000000000021e71                irq0
                0x0000000000021e77                timer_test
                0x0000000000021e7f                irq1
                0x0000000000021eab                fault_N0
                0x0000000000021eb5                fault_N1
                0x0000000000021ebf                fault_N2
                0x0000000000021ec9                fault_N3
                0x0000000000021ed3                fault_N4
                0x0000000000021edd                fault_N5
                0x0000000000021ee7                fault_INTRUCAO_INVALIDA
                0x0000000000021ef1                fault_N7
                0x0000000000021efb                fault_DOUBLE
                0x0000000000021f05                fault_N9
                0x0000000000021f0f                fault_N10
                0x0000000000021f19                fault_N11
                0x0000000000021f23                fault_STACK
                0x0000000000021f2d                fault_GP
                0x0000000000021f37                fault_N14
                0x0000000000021f41                fault_N15
                0x0000000000021f4b                fault_N16
                0x0000000000021f55                fault_N17
                0x0000000000021f5f                fault_N18
                0x0000000000021f69                fault_N19
                0x0000000000021f73                fault_N20
                0x0000000000021f7d                fault_N21
                0x0000000000021f87                fault_N22
                0x0000000000021f91                fault_N23
                0x0000000000021f9b                fault_N24
                0x0000000000021fa5                fault_N25
                0x0000000000021faf                fault_N26
                0x0000000000021fb9                fault_N27
                0x0000000000021fc3                fault_N28
                0x0000000000021fcd                fault_N29
                0x0000000000021fd7                fault_N30
                0x0000000000021fe1                fault_N31
                0x0000000000021feb                hd_buffer
                0x0000000000021fef                hd_lba
                0x0000000000021ff3                test_write
                0x0000000000022003                os_read_sector
                0x000000000002201c                os_write_sector
                0x000000000002212b                reset_ide0
                0x00000000000221ca                int48
                0x00000000000221cf                int49
                0x00000000000221d4                int50
                0x00000000000221d9                int51
                0x00000000000221de                int52
                0x00000000000221e3                int53
                0x00000000000221e8                int54
                0x00000000000221ed                int55
                0x00000000000221f2                int56
                0x00000000000221f7                int57
                0x00000000000221fc                int58
                0x0000000000022201                int59
                0x0000000000022206                int100
                0x000000000002220b                int200
                0x000000000002222a                int201
                0x000000000002222f                int213
                0x0000000000022236                my_buffer_load_bitmap_16x16
                0x00000000000222c8                background
                0x000000000002231d                gui_buffer_putpixel
                0x00000000000223ab                refresh_screen
                0x00000000000223fc                softwarelibReboot
                0x000000000002240a                asm_shut_down
 *(.text)
 .text          0x000000000002240e      0x237 main.o
                0x000000000002240e                BlMain
                0x00000000000224aa                BlLoadKernel
                0x00000000000224d6                BlSetupPaging
                0x00000000000224e4                BlAbort
                0x00000000000224f2                BlKernelModuleMain
                0x0000000000022510                init_testing_memory_size
                0x0000000000022626                die
 .text          0x0000000000022645      0x12b loader.o
                0x0000000000022645                load_kernel
 .text          0x0000000000022770      0x107 init.o
                0x0000000000022770                set_up_color
                0x000000000002277e                set_up_text_color
                0x00000000000227aa                init_globals
                0x00000000000227e2                init
 .text          0x0000000000022877       0xd5 ports.o
                0x0000000000022877                bloutportb
                0x0000000000022884                outb
                0x0000000000022891                inportb
                0x00000000000228a6                outportb
                0x00000000000228b3                inport8
                0x00000000000228c2                outport8
                0x00000000000228cf                inport16
                0x00000000000228df                outport16
                0x00000000000228ed                inport32
                0x00000000000228fc                outport32
                0x0000000000022909                inb
                0x000000000002292b                inportl
                0x000000000002293f                outportl
 .text          0x000000000002294c       0xc5 x86.o
                0x000000000002294c                enable
                0x0000000000022953                disable
                0x000000000002295a                stopCpu
                0x0000000000022962                intReturn
                0x0000000000022969                farReturn
                0x0000000000022970                getFlags
                0x000000000002297b                setFlags
                0x0000000000022986                BlProcessorInPort8
                0x0000000000022995                BlProcessorOutPort8
                0x00000000000229a2                BlProcessorInPort16
                0x00000000000229b2                BlProcessorOutPort16
                0x00000000000229c0                BlProcessorInPort32
                0x00000000000229cf                BlProcessorOutPort32
                0x00000000000229dc                Push
                0x00000000000229e2                Pop
                0x00000000000229e8                pushRegs
                0x00000000000229ee                popRegs
                0x00000000000229f4                pushFlags
                0x00000000000229fa                popFlags
                0x0000000000022a00                getStackPointer
                0x0000000000022a0b                setStackPointer
 .text          0x0000000000022a11      0xb7d stdio.o
                0x0000000000022a11                panic
                0x0000000000022a32                scroll
                0x0000000000022abe                bl_clear
                0x0000000000022b18                kprintf
                0x0000000000022f6b                printf
                0x0000000000022f88                sprintf
                0x0000000000022fdd                putchar
                0x0000000000022ff6                outbyte
                0x0000000000023159                _outbyte
                0x000000000002322f                printf_main
                0x0000000000023239                input
                0x0000000000023368                my_buffer_horizontal_line
                0x0000000000023393                my_buffer_put_pixel
                0x0000000000023465                my_buffer_char_blt
                0x00000000000234e2                vsync
                0x0000000000023520                gui_inb
                0x0000000000023545                get_cursor_x
                0x000000000002355a                get_cursor_y
                0x000000000002356f                carrega_bitmap_16x16
 .text          0x000000000002358e       0x5b stdlib.o
                0x000000000002358e                malloc
                0x00000000000235ca                free
 .text          0x00000000000235e9      0x25a string.o
                0x00000000000235e9                strcmp
                0x000000000002364e                strncmp
                0x00000000000236b1                str_cmp
                0x000000000002372e                memcpy
                0x000000000002376b                strlen
                0x0000000000023792                strcpy
                0x00000000000237c6                strcat
                0x00000000000237f5                bcopy
                0x0000000000023822                bzero
 .text          0x0000000000023843      0x1d6 keyboard.o
                0x0000000000023843                keyboardHandler
 .text          0x0000000000023a19      0x24e pci.o
                0x0000000000023a19                pciConfigReadWord
                0x0000000000023abc                pciCheckDevice
                0x0000000000023b16                pciCheckVendor
                0x0000000000023b56                pciGetClassCode
                0x0000000000023b87                pciInfo
                0x0000000000023c5d                pciInit
 .text          0x0000000000023c67      0x454 hdd.o
                0x0000000000023c9d                hdd_ata_pio_write
                0x0000000000023cd3                hdd_ata_status_read
                0x0000000000023d01                hdd_ata_wait_not_busy
                0x0000000000023d41                hdd_ata_cmd_write
                0x0000000000023d91                hdd_ata_wait_no_drq
                0x0000000000023dd7                pio_rw_sector
                0x000000000002403b                my_read_hd_sector
                0x0000000000024064                my_write_hd_sector
                0x000000000002408d                init_hdd
 .text          0x00000000000240bb     0x1c37 ide.o
                0x00000000000240bb                disk_get_ata_irq_invoked
                0x00000000000240c5                disk_reset_ata_irq_invoked
                0x00000000000240d5                ata_wait
                0x0000000000024108                ata_wait_not_busy
                0x0000000000024136                ata_wait_busy
                0x0000000000024164                ata_wait_no_drq
                0x0000000000024198                ata_wait_drq
                0x00000000000241cc                ata_wait_irq
                0x0000000000024243                ata_soft_reset
                0x000000000002429c                ata_status_read
                0x00000000000242b8                ata_cmd_write
                0x00000000000242ed                ata_assert_dever
                0x0000000000024395                ide_identify_device
                0x00000000000247e9                set_ata_addr
                0x000000000002483f                ide_mass_storage_initialize
                0x00000000000248e5                ide_dev_init
                0x0000000000024cad                nport_ajuste
                0x0000000000024d05                ata_pio_read
                0x0000000000024d2a                ata_pio_write
                0x0000000000024d4f                ide_dma_data
                0x0000000000024e27                ide_dma_start
                0x0000000000024e61                ide_dma_stop
                0x0000000000024ecc                ide_dma_read_status
                0x0000000000024eeb                diskReadPCIConfigAddr
                0x0000000000024f4a                diskWritePCIConfigAddr
                0x0000000000024fae                diskATAPCIConfigurationSpace
                0x0000000000025685                diskPCIScanDevice
                0x0000000000025792                diskATAInitialize
                0x0000000000025af3                diskATADialog
                0x0000000000025b34                diskATAIRQHandler1
                0x0000000000025b44                diskATAIRQHandler2
                0x0000000000025b54                show_ide_info
                0x0000000000025c78                disk_ata_wait_irq
 .text          0x0000000000025cf2       0x48 timer.o
                0x0000000000025cf2                timer
                0x0000000000025d1e                BltimerInit
 .text          0x0000000000025d3a      0x588 pages.o
                0x0000000000025d3a                SetUpPaging
 .text          0x00000000000262c2      0x3b7 heap.o
                0x00000000000262c2                heapAllocateMemory
                0x000000000002649d                FreeHeap
                0x000000000002655d                init_heap
 .text          0x0000000000026679       0x98 procedure.o
                0x0000000000026679                bl_procedure
 .text          0x0000000000026711      0xa31 fs.o
                0x0000000000026711                fatClustToSect
                0x0000000000026738                fatLoadCluster
                0x0000000000026775                fs_format
                0x000000000002677b                fs_search_empty_entry
                0x0000000000026785                fs_find_not_empty_entry
                0x000000000002678f                fs_test_fat_vector
                0x0000000000026795                fs_get_fat_entry
                0x000000000002679f                fs_create_entry
                0x00000000000267a5                fsCreateFileName
                0x00000000000267ab                fsSaveFileName
                0x00000000000267b1                fs_save_entry_on_disc
                0x00000000000267b7                fs_set_structures
                0x00000000000267bd                fs_set_entry
                0x00000000000267c3                fs_get_entry
                0x00000000000267c9                fs_show_dir_entry
                0x00000000000267cf                fs_show_dir
                0x00000000000267d5                fs_check_cluster
                0x00000000000267df                fsSaveRootDir
                0x00000000000267e5                fs_load_dir
                0x00000000000267eb                fs_save_dir
                0x00000000000267f1                fs_save_structure
                0x00000000000267f7                fs_save_entry_on_root
                0x00000000000267fd                fs_show_entry
                0x0000000000026803                fs_delete_entry
                0x0000000000026809                fs_init_bootfile_struct
                0x000000000002680f                fs_get_entry_status
                0x0000000000026819                fs_set_entry_status
                0x000000000002681f                fs_makeboot
                0x0000000000026829                fs_set_fat_entry
                0x000000000002682f                fs_find_empty_entry
                0x0000000000026839                fs_install
                0x000000000002683f                fs_relood_dir
                0x0000000000026845                fsLoadFile
                0x0000000000026a2a                load_path
                0x0000000000026c6c                fsSearchFile
                0x0000000000026d45                fsSearchFileName
                0x0000000000026d5b                fs_load_rootdirEx
                0x0000000000026dad                fs_load_fatEx
                0x0000000000026dfc                fs_put_list_on_fat
                0x0000000000026ebf                fs_find_n_empty_entries
                0x0000000000026f40                fs_load_rootdir
                0x0000000000026f4e                read_lba
                0x0000000000026f69                write_lba
                0x0000000000026f84                fsSaveFile
                0x0000000000026f8e                fsCreateDir
                0x0000000000026fa7                fsCreateFile
                0x00000000000270a2                fsClearFat
                0x00000000000270b0                fsCheckFat
                0x0000000000027122                fsInitFat
                0x0000000000027128                fsInitStructures
                0x000000000002712e                fsInit
 .text          0x0000000000027142      0x603 shell.o
                0x0000000000027142                blShellMain
                0x00000000000271ad                shellProcedure
                0x000000000002721b                shellInitializePrompt
                0x00000000000272aa                shellWaitCmd
                0x00000000000272c3                shellCompare
                0x0000000000027677                shellHelp
                0x0000000000027690                boot
                0x0000000000027696                debug
                0x00000000000276b1                testa_mbr
                0x00000000000276e2                testa_root
                0x0000000000027716                reboot
                0x0000000000027724                shellInit
 .text          0x0000000000027745       0x14 services.o
                0x0000000000027745                blServices
                0x0000000000027753                system_services
 .text          0x0000000000027759       0x1f abort.o
                0x0000000000027759                abort
 .text          0x0000000000027778      0x10c faults.o
                0x0000000000027778                cpu_faults
                0x000000000002787e                faultsShowRegisters
                0x0000000000028000                . = ALIGN (0x1000)
 *fill*         0x0000000000027884      0x77c 

.rodata         0x0000000000028000      0xe40
 .rodata        0x0000000000028000      0x13b main.o
 *fill*         0x000000000002813b        0x1 
 .rodata        0x000000000002813c       0x8f loader.o
 .rodata        0x00000000000281cb       0x11 init.o
 .rodata        0x00000000000281dc       0x3f stdio.o
 *fill*         0x000000000002821b        0x1 
 .rodata        0x000000000002821c       0x44 pci.o
 .rodata        0x0000000000028260       0x33 hdd.o
 *fill*         0x0000000000028293        0x1 
 .rodata        0x0000000000028294      0x46b ide.o
 *fill*         0x00000000000286ff        0x1 
 .rodata        0x0000000000028700      0x1b1 heap.o
 .rodata        0x00000000000288b1        0xc procedure.o
 *fill*         0x00000000000288bd        0x3 
 .rodata        0x00000000000288c0      0x2d0 fs.o
 .rodata        0x0000000000028b90      0x196 shell.o
 .rodata        0x0000000000028d26        0xd abort.o
 *fill*         0x0000000000028d33        0x1 
 .rodata        0x0000000000028d34      0x10c faults.o

.eh_frame       0x0000000000029000     0x1c40
 .eh_frame      0x0000000000029000       0xf4 main.o
 .eh_frame      0x00000000000290f4       0x38 loader.o
 .eh_frame      0x000000000002912c       0x98 init.o
 .eh_frame      0x00000000000291c4      0x1b8 ports.o
 .eh_frame      0x000000000002937c      0x2b8 x86.o
 .eh_frame      0x0000000000029634      0x32c stdio.o
 .eh_frame      0x0000000000029960       0x58 stdlib.o
 .eh_frame      0x00000000000299b8      0x138 string.o
 .eh_frame      0x0000000000029af0       0x38 keyboard.o
 .eh_frame      0x0000000000029b28       0xe0 pci.o
 .eh_frame      0x0000000000029c08      0x160 hdd.o
 .eh_frame      0x0000000000029d68      0x494 ide.o
 .eh_frame      0x000000000002a1fc       0x58 timer.o
 .eh_frame      0x000000000002a254       0x38 pages.o
 .eh_frame      0x000000000002a28c       0x78 heap.o
 .eh_frame      0x000000000002a304       0x38 procedure.o
 .eh_frame      0x000000000002a33c      0x678 fs.o
 .eh_frame      0x000000000002a9b4      0x198 shell.o
 .eh_frame      0x000000000002ab4c       0x58 services.o
 .eh_frame      0x000000000002aba4       0x34 abort.o
 .eh_frame      0x000000000002abd8       0x58 faults.o

.data           0x000000000002ac40     0x13c0
                0x000000000002ac40                data = .
                0x000000000002ac40                _data = .
                0x000000000002ac40                __data = .
 *(.data)
 .data          0x000000000002ac40        0x2 head.o
                0x000000000002ac40                data_start
 .data          0x000000000002ac42        0x0 main.o
 .data          0x000000000002ac42        0x0 loader.o
 .data          0x000000000002ac42        0x0 init.o
 .data          0x000000000002ac42        0x0 ports.o
 .data          0x000000000002ac42        0x0 x86.o
 .data          0x000000000002ac42        0x0 stdio.o
 .data          0x000000000002ac42        0x0 stdlib.o
 .data          0x000000000002ac42        0x0 string.o
 *fill*         0x000000000002ac42       0x1e 
 .data          0x000000000002ac60      0x1a0 keyboard.o
                0x000000000002ac60                destroy_window
                0x000000000002ac64                quit_message
 .data          0x000000000002ae00        0x0 pci.o
 .data          0x000000000002ae00        0x0 hdd.o
 .data          0x000000000002ae00      0x440 ide.o
                0x000000000002ae1c                dev_type
                0x000000000002ae40                pci_classes
 .data          0x000000000002b240        0x0 timer.o
 .data          0x000000000002b240        0x0 pages.o
 .data          0x000000000002b240        0x0 heap.o
 .data          0x000000000002b240        0x0 procedure.o
 .data          0x000000000002b240        0x0 fs.o
 .data          0x000000000002b240       0x2c shell.o
                0x000000000002b240                help_string
 .data          0x000000000002b26c        0x0 services.o
 .data          0x000000000002b26c        0x0 abort.o
 .data          0x000000000002b26c        0x0 faults.o
                0x000000000002c000                . = ALIGN (0x1000)
 *fill*         0x000000000002b26c      0xd94 

.bss            0x000000000002c000     0x2000
                0x000000000002c000                bss = .
                0x000000000002c000                _bss = .
                0x000000000002c000                __bss = .
 *(.bss)
 .bss           0x000000000002c000        0x0 head.o
                0x000000000002c000                bss_start
 .bss           0x000000000002c000        0x0 main.o
 .bss           0x000000000002c000        0x0 loader.o
 .bss           0x000000000002c000        0x0 init.o
 .bss           0x000000000002c000        0x0 ports.o
 .bss           0x000000000002c000        0x0 x86.o
 .bss           0x000000000002c000        0x1 stdio.o
 .bss           0x000000000002c001        0x0 stdlib.o
 .bss           0x000000000002c001        0x0 string.o
 *fill*         0x000000000002c001        0x3 
 .bss           0x000000000002c004        0x4 keyboard.o
                0x000000000002c004                ambiente
 .bss           0x000000000002c008        0x0 pci.o
 .bss           0x000000000002c008        0x0 hdd.o
 .bss           0x000000000002c008       0x20 ide.o
                0x000000000002c008                dev_next_pid
 .bss           0x000000000002c028        0x0 timer.o
 .bss           0x000000000002c028        0x0 pages.o
 .bss           0x000000000002c028        0x0 heap.o
 .bss           0x000000000002c028        0x0 procedure.o
 .bss           0x000000000002c028        0x0 fs.o
 .bss           0x000000000002c028        0x0 shell.o
 .bss           0x000000000002c028        0x0 services.o
 .bss           0x000000000002c028        0x0 abort.o
 .bss           0x000000000002c028        0x0 faults.o
 *(COMMON)
 *fill*         0x000000000002c028       0x18 
 COMMON         0x000000000002c040     0x1268 main.o
                0x000000000002c040                g_fat16_fat_status
                0x000000000002c060                prompt
                0x000000000002c15c                EDITBOX_LARGURA
                0x000000000002c160                partition
                0x000000000002c170                system_info
                0x000000000002c178                g_initialized
                0x000000000002c17c                ata_record_dev
                0x000000000002c180                bliTesting
                0x000000000002c184                g_driver_hdd_initialized
                0x000000000002c188                EDITBOX_BG_COLOR
                0x000000000002c18c                STATUS_X
                0x000000000002c190                prompt_pos
                0x000000000002c194                ide_handler_address
                0x000000000002c198                g_fat16_root_status
                0x000000000002c19c                current_mmblock
                0x000000000002c1a0                STATUS_Y
                0x000000000002c1a4                bl_heap_start
                0x000000000002c1c0                buffer_dir_entry
                0x000000000002c3c0                BootLoaderCR3
                0x000000000002c3c4                next_address
                0x000000000002c3c8                g_available_heap
                0x000000000002c3cc                ata_record_channel
                0x000000000002c3d0                heapCount
                0x000000000002c3d4                EDITBOX_ALTURA
                0x000000000002c3d8                g_lbf_va
                0x000000000002c3dc                LegacyCR3
                0x000000000002c3e0                g_proc_status
                0x000000000002c3e4                g_current_ide_channel
                0x000000000002c3e8                g_heap_pointer
                0x000000000002c3ec                gdefTesting
                0x000000000002c400                heapList
                0x000000000002c420                ata_pci
                0x000000000002c454                ATAFlag
                0x000000000002c458                procedure_info
                0x000000000002c468                EDITBOX_TEXT_COLOR
                0x000000000002c46c                ____testing_memory_size_flag
                0x000000000002c480                ide_ports
                0x000000000002c4e0                CURSOR_Y
                0x000000000002c4e4                EDITBOX_Y
                0x000000000002c4e8                IDE
                0x000000000002c4fc                g_system_color
                0x000000000002c500                CURSOR_X
                0x000000000002c504                useGUI
                0x000000000002c520                file_cluster_list
                0x000000000002cd20                vesa_mode
                0x000000000002cd40                mmblockList
                0x000000000002d140                ata_identify_dev_buf
                0x000000000002d144                g_next_app
                0x000000000002d148                bl_heap_end
                0x000000000002d160                dev_nport
                0x000000000002d180                __last_valid_address
                0x000000000002d184                ata
                0x000000000002d19c                VideoBlock
                0x000000000002d1b8                g_cursor_y
                0x000000000002d1c0                idechannelList
                0x000000000002d280                g_cmd_status
                0x000000000002d284                g_current_ide_device
                0x000000000002d288                g_file_system_type
                0x000000000002d28c                mmblockCount
                0x000000000002d290                g_char_attrib
                0x000000000002d294                g_next_proc
                0x000000000002d298                g_lbf_pa
                0x000000000002d29c                g_nova_mensagem
                0x000000000002d2a0                EDITBOX_X
                0x000000000002d2a4                g_cursor_x
 COMMON         0x000000000002d2a8       0x1c keyboard.o
                0x000000000002d2a8                shift_status
                0x000000000002d2ac                alt_status
                0x000000000002d2b0                escape_status
                0x000000000002d2b4                tab_status
                0x000000000002d2b8                key_status
                0x000000000002d2bc                ctrl_status
                0x000000000002d2c0                winkey_status
 COMMON         0x000000000002d2c4        0x8 hdd.o
                0x000000000002d2c4                hddError
                0x000000000002d2c8                hddStatus
 *fill*         0x000000000002d2cc       0x14 
 COMMON         0x000000000002d2e0       0x44 ide.o
                0x000000000002d2e0                dma_addr
                0x000000000002d2e4                current_dev
                0x000000000002d300                ide_dma_prdt
                0x000000000002d320                ready_queue_dev
 COMMON         0x000000000002d324        0x4 timer.o
                0x000000000002d324                timerTicks
 COMMON         0x000000000002d328        0xc heap.o
                0x000000000002d328                mm_prev_pointer
                0x000000000002d32c                last_size
                0x000000000002d330                last_valid
 *fill*         0x000000000002d334        0xc 
 COMMON         0x000000000002d340      0x42c shell.o
                0x000000000002d340                shell_status
                0x000000000002d360                shell_string_buffer
                0x000000000002d760                deslocamento
                0x000000000002d764                ret_string
                0x000000000002d768                ShellInitialized
 *(.bss_heap)
 .bss_heap      0x000000000002d76c      0x400 head.o
                0x000000000002d76c                bootloader_heap_start
                0x000000000002db6c                bootloader_heap_end
 *(.bss_stack)
 .bss_stack     0x000000000002db6c      0x400 head.o
                0x000000000002db6c                bootloader_stack_end
                0x000000000002df6c                bootloader_stack_start
                0x000000000002e000                . = ALIGN (0x1000)
 *fill*         0x000000000002df6c       0x94 
                0x000000000002e000                end = .
                0x000000000002e000                _end = .
                0x000000000002e000                __end = .
                0x000000000002e000                _bootloader_end = .
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

.comment        0x0000000000000000      0x17c
 .comment       0x0000000000000000       0x12 main.o
 .comment       0x0000000000000012       0x12 loader.o
 .comment       0x0000000000000024       0x12 init.o
 .comment       0x0000000000000036       0x12 ports.o
 .comment       0x0000000000000048       0x12 x86.o
 .comment       0x000000000000005a       0x12 stdio.o
 .comment       0x000000000000006c       0x12 stdlib.o
 .comment       0x000000000000007e       0x12 string.o
 .comment       0x0000000000000090       0x12 keyboard.o
 .comment       0x00000000000000a2       0x12 pci.o
 .comment       0x00000000000000b4       0x12 hdd.o
 .comment       0x00000000000000c6       0x12 ide.o
 .comment       0x00000000000000d8       0x12 timer.o
 .comment       0x00000000000000ea       0x12 pages.o
 .comment       0x00000000000000fc       0x12 heap.o
 .comment       0x000000000000010e       0x12 procedure.o
 .comment       0x0000000000000120       0x12 fs.o
 .comment       0x0000000000000132       0x12 shell.o
 .comment       0x0000000000000144       0x12 services.o
 .comment       0x0000000000000156       0x12 abort.o
 .comment       0x0000000000000168       0x12 faults.o

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
