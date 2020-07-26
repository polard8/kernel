
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
 .text          0x000000000002240e      0x24f main.o
                0x000000000002240e                BlMain
                0x00000000000224aa                BlLoadKernel
                0x00000000000224dd                BlSetupPaging
                0x00000000000224eb                BlAbort
                0x00000000000224f9                BlKernelModuleMain
                0x0000000000022517                init_testing_memory_size
                0x000000000002263e                die
 .text          0x000000000002265d      0x127 loader.o
                0x000000000002265d                load_kernel
 .text          0x0000000000022784      0x107 init.o
                0x0000000000022784                set_up_color
                0x0000000000022792                set_up_text_color
                0x00000000000227be                init_globals
                0x00000000000227f6                init
 .text          0x000000000002288b       0x7d ports.o
                0x000000000002288b                in8
                0x00000000000228a0                in16
                0x00000000000228b7                in32
                0x00000000000228cb                out8
                0x00000000000228e2                out16
                0x00000000000228fb                out32
 .text          0x0000000000022908       0x6f x86.o
                0x0000000000022908                enable
                0x000000000002290f                disable
                0x0000000000022916                stopCpu
                0x000000000002291e                intReturn
                0x0000000000022925                farReturn
                0x000000000002292c                getFlags
                0x0000000000022937                setFlags
                0x0000000000022942                Push
                0x0000000000022948                Pop
                0x000000000002294e                pushRegs
                0x0000000000022954                popRegs
                0x000000000002295a                pushFlags
                0x0000000000022960                popFlags
                0x0000000000022966                getStackPointer
                0x0000000000022971                setStackPointer
 .text          0x0000000000022977      0xb7d stdio.o
                0x0000000000022977                panic
                0x0000000000022998                scroll
                0x0000000000022a23                bl_clear
                0x0000000000022a7d                kprintf
                0x0000000000022ed0                printf
                0x0000000000022eed                sprintf
                0x0000000000022f42                putchar
                0x0000000000022f5b                outbyte
                0x00000000000230c2                _outbyte
                0x0000000000023198                printf_main
                0x00000000000231a2                input
                0x00000000000232d1                my_buffer_horizontal_line
                0x00000000000232fb                my_buffer_put_pixel
                0x00000000000233cd                my_buffer_char_blt
                0x0000000000023449                vsync
                0x0000000000023486                gui_inb
                0x00000000000234ab                get_cursor_x
                0x00000000000234c0                get_cursor_y
                0x00000000000234d5                carrega_bitmap_16x16
 .text          0x00000000000234f4       0x5b stdlib.o
                0x00000000000234f4                malloc
                0x0000000000023530                free
 .text          0x000000000002354f      0x258 string.o
                0x000000000002354f                strcmp
                0x00000000000235b4                strncmp
                0x0000000000023617                str_cmp
                0x0000000000023694                memcpy
                0x00000000000236d1                strlen
                0x00000000000236f8                strcpy
                0x000000000002372c                strcat
                0x000000000002375b                bcopy
                0x0000000000023787                bzero
 .text          0x00000000000237a7      0x1d6 keyboard.o
                0x00000000000237a7                keyboardHandler
 .text          0x000000000002397d      0x252 pci.o
                0x000000000002397d                pciConfigReadWord
                0x0000000000023a24                pciCheckDevice
                0x0000000000023a7e                pciCheckVendor
                0x0000000000023abe                pciGetClassCode
                0x0000000000023aef                pciInfo
                0x0000000000023bc5                pciInit
 .text          0x0000000000023bcf      0x469 hdd.o
                0x0000000000023c05                hdd_ata_pio_write
                0x0000000000023c3b                hdd_ata_status_read
                0x0000000000023c69                hdd_ata_wait_not_busy
                0x0000000000023ca9                hdd_ata_cmd_write
                0x0000000000023cfd                hdd_ata_wait_no_drq
                0x0000000000023d43                pio_rw_sector
                0x0000000000023fb8                my_read_hd_sector
                0x0000000000023fe1                my_write_hd_sector
                0x000000000002400a                init_hdd
 .text          0x0000000000024038     0x1c41 ide.o
                0x0000000000024038                disk_get_ata_irq_invoked
                0x0000000000024042                disk_reset_ata_irq_invoked
                0x0000000000024052                ata_wait
                0x0000000000024084                ata_wait_not_busy
                0x00000000000240b2                ata_wait_busy
                0x00000000000240e0                ata_wait_no_drq
                0x0000000000024114                ata_wait_drq
                0x0000000000024148                ata_wait_irq
                0x00000000000241bf                ata_soft_reset
                0x0000000000024218                ata_status_read
                0x0000000000024234                ata_cmd_write
                0x000000000002426e                ata_assert_dever
                0x0000000000024313                ide_identify_device
                0x000000000002476b                set_ata_addr
                0x00000000000247c1                ide_mass_storage_initialize
                0x0000000000024866                ide_dev_init
                0x0000000000024c2b                nport_ajuste
                0x0000000000024c83                ata_pio_read
                0x0000000000024ca8                ata_pio_write
                0x0000000000024ccd                ide_dma_data
                0x0000000000024da8                ide_dma_start
                0x0000000000024de2                ide_dma_stop
                0x0000000000024e51                ide_dma_read_status
                0x0000000000024e70                diskReadPCIConfigAddr
                0x0000000000024ecf                diskWritePCIConfigAddr
                0x0000000000024f33                diskATAPCIConfigurationSpace
                0x000000000002560a                diskPCIScanDevice
                0x0000000000025717                diskATAInitialize
                0x0000000000025a78                diskATADialog
                0x0000000000025abc                diskATAIRQHandler1
                0x0000000000025acc                diskATAIRQHandler2
                0x0000000000025adc                show_ide_info
                0x0000000000025bff                disk_ata_wait_irq
 .text          0x0000000000025c79       0x48 timer.o
                0x0000000000025c79                timer
                0x0000000000025ca5                BltimerInit
 .text          0x0000000000025cc1      0x588 pages.o
                0x0000000000025cc1                SetUpPaging
 .text          0x0000000000026249      0x3b7 heap.o
                0x0000000000026249                heapAllocateMemory
                0x0000000000026424                FreeHeap
                0x00000000000264e4                init_heap
 .text          0x0000000000026600       0x95 procedure.o
                0x0000000000026600                bl_procedure
 .text          0x0000000000026695      0xb56 fs.o
                0x0000000000026695                fatClustToSect
                0x00000000000266bc                fatLoadCluster
                0x00000000000266f8                fs_format
                0x00000000000266fe                fs_search_empty_entry
                0x0000000000026708                fs_find_not_empty_entry
                0x0000000000026712                fs_test_fat_vector
                0x0000000000026718                fs_get_fat_entry
                0x0000000000026722                fs_create_entry
                0x0000000000026728                fsCreateFileName
                0x000000000002672e                fsSaveFileName
                0x0000000000026734                fs_save_entry_on_disc
                0x000000000002673a                fs_set_structures
                0x0000000000026740                fs_set_entry
                0x0000000000026746                fs_get_entry
                0x000000000002674c                fs_show_dir_entry
                0x0000000000026752                fs_show_dir
                0x0000000000026758                fs_check_cluster
                0x0000000000026762                fsSaveRootDir
                0x0000000000026768                fs_load_dir
                0x000000000002676e                fs_save_dir
                0x0000000000026774                fs_save_structure
                0x000000000002677a                fs_save_entry_on_root
                0x0000000000026780                fs_show_entry
                0x0000000000026786                fs_delete_entry
                0x000000000002678c                fs_init_bootfile_struct
                0x0000000000026792                fs_get_entry_status
                0x000000000002679c                fs_set_entry_status
                0x00000000000267a2                fs_makeboot
                0x00000000000267ac                fs_set_fat_entry
                0x00000000000267b2                fs_find_empty_entry
                0x00000000000267bc                fs_install
                0x00000000000267c2                fs_relood_dir
                0x00000000000267c8                fsLoadFile
                0x00000000000269ad                path_count
                0x0000000000026a00                load_path
                0x0000000000026d1e                fsSearchFile
                0x0000000000026df0                fsSearchFileName
                0x0000000000026e06                fs_load_rootdirEx
                0x0000000000026e57                fs_load_fatEx
                0x0000000000026ea5                fs_put_list_on_fat
                0x0000000000026f68                fs_find_n_empty_entries
                0x0000000000026fe9                fs_load_rootdir
                0x0000000000026ff7                read_lba
                0x0000000000027012                write_lba
                0x000000000002702d                fsSaveFile
                0x0000000000027037                fsCreateDir
                0x0000000000027050                fsCreateFile
                0x000000000002714b                fsClearFat
                0x0000000000027159                fsCheckFat
                0x00000000000271cb                fsInitFat
                0x00000000000271d1                fsInitStructures
                0x00000000000271d7                fsInit
 .text          0x00000000000271eb      0x607 shell.o
                0x00000000000271eb                blShellMain
                0x0000000000027256                shellProcedure
                0x00000000000272c7                shellInitializePrompt
                0x0000000000027356                shellWaitCmd
                0x0000000000027370                shellCompare
                0x0000000000027724                shellHelp
                0x000000000002773d                boot
                0x0000000000027743                debug
                0x000000000002775e                testa_mbr
                0x000000000002778f                testa_root
                0x00000000000277c3                reboot
                0x00000000000277d1                shellInit
 .text          0x00000000000277f2       0x17 services.o
                0x00000000000277f2                blServices
                0x0000000000027803                system_services
 .text          0x0000000000027809       0x1f abort.o
                0x0000000000027809                abort
 .text          0x0000000000027828      0x10c faults.o
                0x0000000000027828                cpu_faults
                0x000000000002792e                faultsShowRegisters
                0x0000000000028000                . = ALIGN (0x1000)
 *fill*         0x0000000000027934      0x6cc 

.rodata         0x0000000000028000      0xea8
 .rodata        0x0000000000028000      0x13b main.o
 *fill*         0x000000000002813b        0x1 
 .rodata        0x000000000002813c       0xa3 loader.o
 .rodata        0x00000000000281df       0x11 init.o
 .rodata        0x00000000000281f0       0x3f stdio.o
 *fill*         0x000000000002822f        0x1 
 .rodata        0x0000000000028230       0x44 pci.o
 .rodata        0x0000000000028274       0x33 hdd.o
 *fill*         0x00000000000282a7        0x1 
 .rodata        0x00000000000282a8      0x46b ide.o
 *fill*         0x0000000000028713        0x1 
 .rodata        0x0000000000028714      0x1b1 heap.o
 .rodata        0x00000000000288c5        0xc procedure.o
 *fill*         0x00000000000288d1        0x3 
 .rodata        0x00000000000288d4      0x324 fs.o
 .rodata        0x0000000000028bf8      0x196 shell.o
 .rodata        0x0000000000028d8e        0xd abort.o
 *fill*         0x0000000000028d9b        0x1 
 .rodata        0x0000000000028d9c      0x10c faults.o

.eh_frame       0x0000000000029000     0x1ac0
 .eh_frame      0x0000000000029000       0xf4 main.o
 .eh_frame      0x00000000000290f4       0x38 loader.o
 .eh_frame      0x000000000002912c       0x98 init.o
 .eh_frame      0x00000000000291c4       0xd8 ports.o
 .eh_frame      0x000000000002929c      0x1f8 x86.o
 .eh_frame      0x0000000000029494      0x32c stdio.o
 .eh_frame      0x00000000000297c0       0x58 stdlib.o
 .eh_frame      0x0000000000029818      0x138 string.o
 .eh_frame      0x0000000000029950       0x38 keyboard.o
 .eh_frame      0x0000000000029988       0xe0 pci.o
 .eh_frame      0x0000000000029a68      0x160 hdd.o
 .eh_frame      0x0000000000029bc8      0x494 ide.o
 .eh_frame      0x000000000002a05c       0x58 timer.o
 .eh_frame      0x000000000002a0b4       0x38 pages.o
 .eh_frame      0x000000000002a0ec       0x78 heap.o
 .eh_frame      0x000000000002a164       0x38 procedure.o
 .eh_frame      0x000000000002a19c      0x698 fs.o
 .eh_frame      0x000000000002a834      0x198 shell.o
 .eh_frame      0x000000000002a9cc       0x58 services.o
 .eh_frame      0x000000000002aa24       0x34 abort.o
 .eh_frame      0x000000000002aa58       0x58 faults.o

.data           0x000000000002aac0     0x1540
                0x000000000002aac0                data = .
                0x000000000002aac0                _data = .
                0x000000000002aac0                __data = .
 *(.data)
 .data          0x000000000002aac0        0x2 head.o
                0x000000000002aac0                data_start
 .data          0x000000000002aac2        0x0 main.o
 .data          0x000000000002aac2        0x0 loader.o
 .data          0x000000000002aac2        0x0 init.o
 .data          0x000000000002aac2        0x0 ports.o
 .data          0x000000000002aac2        0x0 x86.o
 .data          0x000000000002aac2        0x0 stdio.o
 .data          0x000000000002aac2        0x0 stdlib.o
 .data          0x000000000002aac2        0x0 string.o
 *fill*         0x000000000002aac2       0x1e 
 .data          0x000000000002aae0      0x1a0 keyboard.o
                0x000000000002aae0                destroy_window
                0x000000000002aae4                quit_message
 .data          0x000000000002ac80        0x0 pci.o
 .data          0x000000000002ac80        0x0 hdd.o
 .data          0x000000000002ac80      0x440 ide.o
                0x000000000002ac9c                dev_type
                0x000000000002acc0                pci_classes
 .data          0x000000000002b0c0        0x0 timer.o
 .data          0x000000000002b0c0        0x0 pages.o
 .data          0x000000000002b0c0        0x0 heap.o
 .data          0x000000000002b0c0        0x0 procedure.o
 .data          0x000000000002b0c0        0x0 fs.o
 .data          0x000000000002b0c0       0x2c shell.o
                0x000000000002b0c0                help_string
 .data          0x000000000002b0ec        0x0 services.o
 .data          0x000000000002b0ec        0x0 abort.o
 .data          0x000000000002b0ec        0x0 faults.o
                0x000000000002c000                . = ALIGN (0x1000)
 *fill*         0x000000000002b0ec      0xf14 

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

.comment        0x0000000000000000      0x374
 .comment       0x0000000000000000       0x2a main.o
 .comment       0x000000000000002a       0x2a loader.o
 .comment       0x0000000000000054       0x2a init.o
 .comment       0x000000000000007e       0x2a ports.o
 .comment       0x00000000000000a8       0x2a x86.o
 .comment       0x00000000000000d2       0x2a stdio.o
 .comment       0x00000000000000fc       0x2a stdlib.o
 .comment       0x0000000000000126       0x2a string.o
 .comment       0x0000000000000150       0x2a keyboard.o
 .comment       0x000000000000017a       0x2a pci.o
 .comment       0x00000000000001a4       0x2a hdd.o
 .comment       0x00000000000001ce       0x2a ide.o
 .comment       0x00000000000001f8       0x2a timer.o
 .comment       0x0000000000000222       0x2a pages.o
 .comment       0x000000000000024c       0x2a heap.o
 .comment       0x0000000000000276       0x2a procedure.o
 .comment       0x00000000000002a0       0x2a fs.o
 .comment       0x00000000000002ca       0x2a shell.o
 .comment       0x00000000000002f4       0x2a services.o
 .comment       0x000000000000031e       0x2a abort.o
 .comment       0x0000000000000348       0x2a faults.o

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
