
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
 .text          0x000000000002237a      0x115 main.o
                0x000000000002237a                BlMain
                0x00000000000223de                BlLoadKernel
                0x000000000002240a                BlLoadFiles
                0x0000000000022436                BlSetupPaging
                0x0000000000022444                BlAbort
                0x0000000000022452                BlKernelModuleMain
                0x0000000000022470                die
 .text          0x000000000002248f      0x2d7 loader.o
                0x000000000002248f                load_kernel
                0x0000000000022592                load_files
 .text          0x0000000000022766      0x108 init.o
                0x0000000000022766                set_up_color
                0x0000000000022774                set_up_text_color
                0x00000000000227a0                init_globals
                0x00000000000227d8                init
 .text          0x000000000002286e       0xd5 ports.o
                0x000000000002286e                bloutportb
                0x000000000002287b                outb
                0x0000000000022888                inportb
                0x000000000002289d                outportb
                0x00000000000228aa                inport8
                0x00000000000228b9                outport8
                0x00000000000228c6                inport16
                0x00000000000228d6                outport16
                0x00000000000228e4                inport32
                0x00000000000228f3                outport32
                0x0000000000022900                inb
                0x0000000000022922                inportl
                0x0000000000022936                outportl
 .text          0x0000000000022943       0xd6 x86.o
                0x0000000000022943                enable
                0x000000000002294a                disable
                0x0000000000022951                stopCpu
                0x0000000000022959                intReturn
                0x0000000000022960                farReturn
                0x0000000000022967                getFlags
                0x0000000000022972                setFlags
                0x000000000002297d                BlProcessorInPort8
                0x000000000002298c                BlProcessorOutPort8
                0x0000000000022999                BlProcessorInPort16
                0x00000000000229a9                BlProcessorOutPort16
                0x00000000000229b7                BlProcessorInPort32
                0x00000000000229c6                BlProcessorOutPort32
                0x00000000000229d3                Push
                0x00000000000229dd                Pop
                0x00000000000229e7                pushRegs
                0x00000000000229ee                popRegs
                0x00000000000229f5                pushFlags
                0x00000000000229fc                popFlags
                0x0000000000022a03                getStackPointer
                0x0000000000022a0e                setStackPointer
 .text          0x0000000000022a19      0xb7d stdio.o
                0x0000000000022a19                panic
                0x0000000000022a3a                scroll
                0x0000000000022ac5                bl_clear
                0x0000000000022b1f                kprintf
                0x0000000000022f72                printf
                0x0000000000022f8f                sprintf
                0x0000000000022fe4                putchar
                0x0000000000022ffd                outbyte
                0x0000000000023164                _outbyte
                0x000000000002323a                printf_main
                0x0000000000023244                input
                0x0000000000023373                my_buffer_horizontal_line
                0x000000000002339d                my_buffer_put_pixel
                0x000000000002346f                my_buffer_char_blt
                0x00000000000234eb                vsync
                0x0000000000023528                gui_inb
                0x000000000002354d                get_cursor_x
                0x0000000000023562                get_cursor_y
                0x0000000000023577                carrega_bitmap_16x16
 .text          0x0000000000023596       0x5b stdlib.o
                0x0000000000023596                malloc
                0x00000000000235d2                free
 .text          0x00000000000235f1      0x25a string.o
                0x00000000000235f1                strcmp
                0x0000000000023656                strncmp
                0x00000000000236b9                str_cmp
                0x0000000000023737                memcpy
                0x0000000000023775                strlen
                0x000000000002379c                strcpy
                0x00000000000237d0                strcat
                0x00000000000237ff                bcopy
                0x000000000002382b                bzero
 .text          0x000000000002384b      0x1d6 keyboard.o
                0x000000000002384b                keyboardHandler
 .text          0x0000000000023a21      0x253 pci.o
                0x0000000000023a21                pciConfigReadWord
                0x0000000000023ac8                pciCheckDevice
                0x0000000000023b22                pciCheckVendor
                0x0000000000023b62                pciGetClassCode
                0x0000000000023b93                pciInfo
                0x0000000000023c6a                pciInit
 .text          0x0000000000023c74      0x442 hdd.o
                0x0000000000023caa                hdd_ata_pio_write
                0x0000000000023ce0                hdd_ata_status_read
                0x0000000000023d0e                hdd_ata_wait_not_busy
                0x0000000000023d4e                hdd_ata_cmd_write
                0x0000000000023d9e                hdd_ata_wait_no_drq
                0x0000000000023de4                pio_rw_sector
                0x0000000000024048                my_read_hd_sector
                0x0000000000024068                my_write_hd_sector
                0x0000000000024088                init_hdd
 .text          0x00000000000240b6     0x1c2c ide.o
                0x00000000000240b6                disk_get_ata_irq_invoked
                0x00000000000240c0                disk_reset_ata_irq_invoked
                0x00000000000240d0                ata_wait
                0x0000000000024102                ata_wait_not_busy
                0x0000000000024130                ata_wait_busy
                0x000000000002415e                ata_wait_no_drq
                0x0000000000024192                ata_wait_drq
                0x00000000000241c6                ata_wait_irq
                0x000000000002423d                ata_soft_reset
                0x0000000000024296                ata_status_read
                0x00000000000242b2                ata_cmd_write
                0x00000000000242e7                ata_assert_dever
                0x000000000002438c                ide_identify_device
                0x00000000000247e0                set_ata_addr
                0x0000000000024836                ide_mass_storage_initialize
                0x00000000000248dc                ide_dev_init
                0x0000000000024ca1                nport_ajuste
                0x0000000000024cfa                ata_pio_read
                0x0000000000024d1f                ata_pio_write
                0x0000000000024d44                ide_dma_data
                0x0000000000024e1c                ide_dma_start
                0x0000000000024e56                ide_dma_stop
                0x0000000000024ec1                ide_dma_read_status
                0x0000000000024ee0                diskReadPCIConfigAddr
                0x0000000000024f3f                diskWritePCIConfigAddr
                0x0000000000024fa3                diskATAPCIConfigurationSpace
                0x000000000002567a                diskPCIScanDevice
                0x0000000000025787                diskATAInitialize
                0x0000000000025ae4                diskATADialog
                0x0000000000025b25                diskATAIRQHandler1
                0x0000000000025b35                diskATAIRQHandler2
                0x0000000000025b45                show_ide_info
                0x0000000000025c68                disk_ata_wait_irq
 .text          0x0000000000025ce2       0x48 timer.o
                0x0000000000025ce2                timer
                0x0000000000025d0e                BltimerInit
 .text          0x0000000000025d2a      0x588 pages.o
                0x0000000000025d2a                SetUpPaging
 .text          0x00000000000262b2      0x3b7 heap.o
                0x00000000000262b2                heapAllocateMemory
                0x000000000002648d                FreeHeap
                0x000000000002654d                init_heap
 .text          0x0000000000026669       0x92 procedure.o
                0x0000000000026669                bl_procedure
 .text          0x00000000000266fb      0xa2c fs.o
                0x00000000000266fb                fatClustToSect
                0x0000000000026722                fatLoadCluster
                0x000000000002675e                fs_format
                0x0000000000026777                fs_search_empty_entry
                0x0000000000026781                fs_find_not_empty_entry
                0x000000000002678b                fs_test_fat_vector
                0x0000000000026791                fs_get_fat_entry
                0x000000000002679b                fs_create_entry
                0x00000000000267a1                fsCreateFileName
                0x00000000000267a7                fsSaveFileName
                0x00000000000267ad                fs_save_entry_on_disc
                0x00000000000267b3                fs_set_structures
                0x00000000000267b9                fs_set_entry
                0x00000000000267bf                fs_get_entry
                0x00000000000267c5                fs_show_dir_entry
                0x00000000000267cb                fs_show_dir
                0x00000000000267d1                fs_check_cluster
                0x00000000000267db                fsSaveRootDir
                0x00000000000267e1                fs_load_dir
                0x00000000000267e7                fs_save_dir
                0x00000000000267ed                fs_save_structure
                0x00000000000267f3                fs_save_entry_on_root
                0x00000000000267f9                fs_show_entry
                0x00000000000267ff                fs_delete_entry
                0x0000000000026805                fs_init_bootfile_struct
                0x000000000002680b                fs_get_entry_status
                0x0000000000026815                fs_set_entry_status
                0x000000000002681b                fs_makeboot
                0x0000000000026825                fs_set_fat_entry
                0x000000000002682b                fs_find_empty_entry
                0x0000000000026835                fs_install
                0x000000000002683b                fs_relood_dir
                0x0000000000026841                fsLoadFile
                0x0000000000026a26                load_path
                0x0000000000026c5a                fsSearchFile
                0x0000000000026d2c                fsSearchFileName
                0x0000000000026d42                fs_load_rootdirEx
                0x0000000000026d93                fs_load_fatEx
                0x0000000000026de1                fs_put_list_on_fat
                0x0000000000026ea4                fs_find_n_empty_entries
                0x0000000000026f25                fs_load_rootdir
                0x0000000000026f33                read_lba
                0x0000000000026f4e                write_lba
                0x0000000000026f69                fsSaveFile
                0x0000000000026f73                fsCreateDir
                0x0000000000026f8c                fsCreateFile
                0x0000000000027087                fsClearFat
                0x0000000000027095                fsCheckFat
                0x0000000000027107                fsInitFat
                0x000000000002710d                fsInitStructures
                0x0000000000027113                fsInit
 .text          0x0000000000027127      0x60b shell.o
                0x0000000000027127                shellMain
                0x0000000000027192                shellProcedure
                0x0000000000027207                shellInitializePrompt
                0x0000000000027296                shellWaitCmd
                0x00000000000272b0                shellCompare
                0x0000000000027664                shellHelp
                0x000000000002767d                boot
                0x0000000000027683                debug
                0x000000000002769e                testa_mbr
                0x00000000000276cf                testa_root
                0x0000000000027703                reboot
                0x0000000000027711                shellInit
 .text          0x0000000000027732       0x14 services.o
                0x0000000000027732                blServices
                0x0000000000027740                system_services
 .text          0x0000000000027746       0x1f abort.o
                0x0000000000027746                abort
 .text          0x0000000000027765       0xc0 faults.o
                0x0000000000027765                cpu_falts
                0x000000000002781f                faultsShowRegisters
                0x0000000000028000                . = ALIGN (0x1000)
 *fill*         0x0000000000027825      0x7db 

.rodata         0x0000000000028000      0xe28
 .rodata        0x0000000000028000       0x67 main.o
 *fill*         0x0000000000028067        0x1 
 .rodata        0x0000000000028068      0x113 loader.o
 .rodata        0x000000000002817b       0x11 init.o
 .rodata        0x000000000002818c       0x3f stdio.o
 *fill*         0x00000000000281cb        0x1 
 .rodata        0x00000000000281cc       0x44 pci.o
 .rodata        0x0000000000028210       0x33 hdd.o
 *fill*         0x0000000000028243        0x1 
 .rodata        0x0000000000028244      0x4cd ide.o
 *fill*         0x0000000000028711        0x3 
 .rodata        0x0000000000028714      0x1c1 heap.o
 .rodata        0x00000000000288d5        0xc procedure.o
 *fill*         0x00000000000288e1        0x3 
 .rodata        0x00000000000288e4      0x2e4 fs.o
 .rodata        0x0000000000028bc8      0x1b2 shell.o
 .rodata        0x0000000000028d7a        0xd abort.o
 *fill*         0x0000000000028d87        0x1 
 .rodata        0x0000000000028d88       0xa0 faults.o

.eh_frame       0x0000000000029000     0x1c60
 .eh_frame      0x0000000000029000       0xf4 main.o
 .eh_frame      0x00000000000290f4       0x58 loader.o
 .eh_frame      0x000000000002914c       0x98 init.o
 .eh_frame      0x00000000000291e4      0x1b8 ports.o
 .eh_frame      0x000000000002939c      0x2b8 x86.o
 .eh_frame      0x0000000000029654      0x32c stdio.o
 .eh_frame      0x0000000000029980       0x58 stdlib.o
 .eh_frame      0x00000000000299d8      0x138 string.o
 .eh_frame      0x0000000000029b10       0x38 keyboard.o
 .eh_frame      0x0000000000029b48       0xe0 pci.o
 .eh_frame      0x0000000000029c28      0x160 hdd.o
 .eh_frame      0x0000000000029d88      0x494 ide.o
 .eh_frame      0x000000000002a21c       0x58 timer.o
 .eh_frame      0x000000000002a274       0x38 pages.o
 .eh_frame      0x000000000002a2ac       0x78 heap.o
 .eh_frame      0x000000000002a324       0x38 procedure.o
 .eh_frame      0x000000000002a35c      0x678 fs.o
 .eh_frame      0x000000000002a9d4      0x198 shell.o
 .eh_frame      0x000000000002ab6c       0x58 services.o
 .eh_frame      0x000000000002abc4       0x34 abort.o
 .eh_frame      0x000000000002abf8       0x58 faults.o

.data           0x000000000002ac60     0x13a0
                0x000000000002ac60                data = .
                0x000000000002ac60                _data = .
                0x000000000002ac60                __data = .
 *(.data)
 .data          0x000000000002ac60        0x2 head.o
                0x000000000002ac60                data_start
 .data          0x000000000002ac62        0x0 main.o
 .data          0x000000000002ac62        0x0 loader.o
 .data          0x000000000002ac62        0x0 init.o
 .data          0x000000000002ac62        0x0 ports.o
 .data          0x000000000002ac62        0x0 x86.o
 .data          0x000000000002ac62        0x0 stdio.o
 .data          0x000000000002ac62        0x0 stdlib.o
 .data          0x000000000002ac62        0x0 string.o
 *fill*         0x000000000002ac62       0x1e 
 .data          0x000000000002ac80      0x1a0 keyboard.o
                0x000000000002ac80                destroy_window
                0x000000000002ac84                quit_message
 .data          0x000000000002ae20        0x0 pci.o
 .data          0x000000000002ae20        0x0 hdd.o
 .data          0x000000000002ae20      0x440 ide.o
                0x000000000002ae3c                dev_type
                0x000000000002ae60                pci_classes
 .data          0x000000000002b260        0x0 timer.o
 .data          0x000000000002b260        0x0 pages.o
 .data          0x000000000002b260        0x0 heap.o
 .data          0x000000000002b260        0x0 procedure.o
 .data          0x000000000002b260        0x0 fs.o
 .data          0x000000000002b260       0x2c shell.o
                0x000000000002b260                help_string
 .data          0x000000000002b28c        0x0 services.o
 .data          0x000000000002b28c        0x0 abort.o
 .data          0x000000000002b28c        0x0 faults.o
                0x000000000002c000                . = ALIGN (0x1000)
 *fill*         0x000000000002b28c      0xd74 

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
 COMMON         0x000000000002c040     0x119c main.o
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
                0x000000000002c3e4                g_heap_pointer
                0x000000000002c3e8                gdefTesting
                0x000000000002c400                heapList
                0x000000000002c420                ata_pci
                0x000000000002c454                ATAFlag
                0x000000000002c458                procedure_info
                0x000000000002c468                EDITBOX_TEXT_COLOR
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
                0x000000000002d180                ata
                0x000000000002d198                VideoBlock
                0x000000000002d1b4                g_cursor_y
                0x000000000002d1b8                g_cmd_status
                0x000000000002d1bc                g_file_system_type
                0x000000000002d1c0                mmblockCount
                0x000000000002d1c4                g_char_attrib
                0x000000000002d1c8                g_next_proc
                0x000000000002d1cc                g_lbf_pa
                0x000000000002d1d0                g_nova_mensagem
                0x000000000002d1d4                EDITBOX_X
                0x000000000002d1d8                g_cursor_x
 COMMON         0x000000000002d1dc       0x1c keyboard.o
                0x000000000002d1dc                shift_status
                0x000000000002d1e0                alt_status
                0x000000000002d1e4                escape_status
                0x000000000002d1e8                tab_status
                0x000000000002d1ec                key_status
                0x000000000002d1f0                ctrl_status
                0x000000000002d1f4                winkey_status
 COMMON         0x000000000002d1f8        0x8 hdd.o
                0x000000000002d1f8                hddError
                0x000000000002d1fc                hddStatus
 COMMON         0x000000000002d200       0x44 ide.o
                0x000000000002d200                dma_addr
                0x000000000002d204                current_dev
                0x000000000002d220                ide_dma_prdt
                0x000000000002d240                ready_queue_dev
 COMMON         0x000000000002d244        0x4 timer.o
                0x000000000002d244                timerTicks
 COMMON         0x000000000002d248        0xc heap.o
                0x000000000002d248                mm_prev_pointer
                0x000000000002d24c                last_size
                0x000000000002d250                last_valid
 *fill*         0x000000000002d254        0xc 
 COMMON         0x000000000002d260      0x42c shell.o
                0x000000000002d260                shell_status
                0x000000000002d280                shell_string_buffer
                0x000000000002d680                deslocamento
                0x000000000002d684                ret_string
                0x000000000002d688                ShellInitialized
 *(.bss_heap)
 .bss_heap      0x000000000002d68c      0x400 head.o
                0x000000000002d68c                bootloader_heap_start
                0x000000000002da8c                bootloader_heap_end
 *(.bss_stack)
 .bss_stack     0x000000000002da8c      0x400 head.o
                0x000000000002da8c                bootloader_stack_end
                0x000000000002de8c                bootloader_stack_start
                0x000000000002e000                . = ALIGN (0x1000)
 *fill*         0x000000000002de8c      0x174 
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
