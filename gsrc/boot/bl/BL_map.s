
Allocating common symbols
Common symbol       size              file

g_fat16_fat_status  0x10              main.o
timerTicks          0x10              timer.o
prompt              0x100             main.o
EDITBOX_LARGURA     0x10              main.o
partition           0x10              main.o
system_info         0x10              main.o
dma_addr            0x10              hdd.o
g_initialized       0x10              main.o
ata_record_dev      0x10              main.o
bliTesting          0x10              main.o
EDITBOX_BG_COLOR    0x10              main.o
shell_status        0x10              shell.o
current_dev         0x10              hdd.o
STATUS_X            0x10              main.o
prompt_pos          0x10              main.o
current_mmblock     0x10              stdlib.o
g_fat16_root_status
                    0x10              main.o
STATUS_Y            0x10              main.o
mm_prev_pointer     0x10              stdlib.o
shell_string_buffer
                    0x400             shell.o
deslocamento        0x10              shell.o
buffer_dir_entry    0x200             main.o
BootLoaderCR3       0x10              main.o
heap_end            0x10              stdlib.o
next_address        0x10              main.o
shift_status        0x10              keyboard.o
ide_dma_prdt        0x20              hdd.o
g_available_heap    0x10              stdlib.o
alt_status          0x10              keyboard.o
ata_record_channel  0x10              main.o
heap_start          0x10              stdlib.o
heapCount           0x10              stdlib.o
EDITBOX_ALTURA      0x10              main.o
HEAP_START          0x10              stdlib.o
g_lbf_va            0x10              main.o
LegacyCR3           0x10              main.o
g_proc_status       0x10              main.o
g_heap_pointer      0x10              stdlib.o
gdefTesting         0x10              main.o
heapList            0x400             stdlib.o
proximo             0x10              main.o
ata_pci             0x40              main.o
procedure_info      0x10              main.o
EDITBOX_TEXT_COLOR  0x10              main.o
HEAP_SIZE           0x10              stdlib.o
CURSOR_Y            0x10              main.o
EDITBOX_Y           0x10              main.o
current_task        0x10              main.o
g_system_color      0x10              main.o
CURSOR_X            0x10              main.o
last_size           0x10              stdlib.o
useGUI              0x10              main.o
ready_queue_dev     0x10              hdd.o
last_valid          0x10              stdlib.o
ret_string          0x10              shell.o
file_cluster_list   0x800             main.o
vesa_mode           0x10              main.o
escape_status       0x10              keyboard.o
mmblockList         0x400             stdlib.o
ata_identify_dev_buf
                    0x10              main.o
g_next_app          0x10              main.o
dev_nport           0x20              main.o
ata                 0x20              main.o
tab_status          0x10              keyboard.o
libcHeap            0x10              stdlib.o
VideoBlock          0x20              main.o
g_cursor_y          0x10              main.o
Heap                0x10              stdlib.o
g_cmd_status        0x10              main.o
ShellInitialized    0x10              shell.o
key_status          0x10              keyboard.o
g_file_system_type  0x10              main.o
mmblockCount        0x10              stdlib.o
g_char_attrib       0x10              main.o
ctrl_status         0x10              keyboard.o
g_next_proc         0x10              main.o
g_lbf_pa            0x10              main.o
winkey_status       0x10              keyboard.o
g_nova_mensagem     0x10              main.o
EDITBOX_X           0x10              main.o
g_cursor_x          0x10              main.o
HEAP_END            0x10              stdlib.o

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

.text           0x00021000     0x8000
                0x00021000                code = .
                0x00021000                _code = .
                0x00021000                __code = .
 *(.head_x86)
 .head_x86      0x00021000     0x14ef head.o
                0x00021e83                fault_N1
                0x00021ef3                fault_DOUBLE
                0x00021b3b                task1_stack
                0x00022073                hd_buffer
                0x000211ab                SavedBPP
                0x000224e5                asm_shut_down
                0x000211af                SavedBootMode
                0x00022063                fault_N31
                0x00022033                fault_N28
                0x000222bd                int56
                0x00021fc3                fault_N21
                0x00021f53                fault_N14
                0x000222f8                int201
                0x00021f23                fault_N11
                0x00021e33                irq0
                0x000222b3                int54
                0x00021ea3                fault_N3
                0x000222a4                int51
                0x000222d1                int100
                0x00021ff3                fault_N24
                0x00022013                fault_N26
                0x0002207b                test_write
                0x00021e73                fault_N0
                0x0002208b                os_read_sector
                0x000224d1                softwarelibReboot
                0x00022053                fault_N30
                0x00021b7d                setup_idt_vector
                0x00021f33                fault_STACK
                0x00021b3f                task2_stack
                0x00022023                fault_N27
                0x0002229a                int49
                0x00021b37                task0_stack
                0x000222ae                int53
                0x000211a3                SavedX
                0x00021f73                fault_N16
                0x00021f43                fault_GP
                0x00021e39                timer_test
                0x00022295                int48
                0x00021fa3                fault_N19
                0x00021ee3                fault_N7
                0x0002229f                int50
                0x000222c7                int58
                0x00022043                fault_N29
                0x00022304                my_buffer_load_bitmap_16x16
                0x000222b8                int55
                0x000222fd                int213
                0x00021fe3                fault_N23
                0x000211a7                SavedY
                0x000222d6                int200
                0x00022480                refresh_screen
                0x00021ed3                fault_INTRUCAO_INVALIDA
                0x0002119f                SavedLFB
                0x0002119b                SavedBootBlock
                0x0002239a                background
                0x00021eb3                fault_N4
                0x00021e93                fault_N2
                0x000220a5                os_write_sector
                0x00021fb3                fault_N20
                0x000222a9                int52
                0x000222c2                int57
                0x00021fd3                fault_N22
                0x00021f13                fault_N10
                0x00021e4d                irq1
                0x00021f63                fault_N15
                0x00021f83                fault_N17
                0x00021f93                fault_N18
                0x00022077                hd_lba
                0x00022003                fault_N25
                0x000223f2                gui_buffer_putpixel
                0x000221fb                reset_ide0
                0x00021f03                fault_N9
                0x000222cc                int59
                0x00021000                bootloader_entry_point
                0x00021ec3                fault_N5
 *(.text)
 *fill*         0x000224ef        0x1 00
 .text          0x000224f0      0x110 main.o
                0x000225c0                BlKernelModuleMain
                0x000225a8                BlSetupPaging
                0x000225d9                die
                0x000224f0                BlMain
                0x0002255a                BlLoadKernel
                0x00022581                BlLoadFiles
                0x000225b5                BlAbort
 .text          0x00022600      0x220 loader.o
                0x00022600                load_kernel
                0x000226ba                load_files
 .text          0x00022820      0x110 init.o
                0x00022899                init
                0x00022858                init_globals
                0x00022820                set_up_color
                0x0002282d                set_up_text_color
 .text          0x00022930       0xd0 ports.o
                0x00022967                inport8
                0x000229a5                outport32
                0x00022930                bloutportb
                0x000229b1                inb
                0x000229e5                outportl
                0x000229d3                inportl
                0x0002295b                outportb
                0x00022973                outport8
                0x0002298c                outport16
                0x0002297f                inport16
                0x00022948                inportb
                0x00022999                inport32
                0x0002293c                outb
 .text          0x00022a00       0xd0 x86.o
                0x00022aa5                pushFlags
                0x00022a99                pushRegs
                0x00022a90                Pop
                0x00022a23                farReturn
                0x00022a29                getFlags
                0x00022aab                popFlags
                0x00022a16                stopCpu
                0x00022a3d                BlProcessorInPort8
                0x00022abb                setStackPointer
                0x00022a6f                BlProcessorInPort32
                0x00022a49                BlProcessorOutPort8
                0x00022a9f                popRegs
                0x00022a7b                BlProcessorOutPort32
                0x00022a62                BlProcessorOutPort16
                0x00022a87                Push
                0x00022a55                BlProcessorInPort16
                0x00022a33                setFlags
                0x00022ab1                getStackPointer
                0x00022a0b                disable
                0x00022a1d                intReturn
                0x00022a00                enable
 .text          0x00022ad0      0xb70 stdio.o
                0x0002317f                putchar
                0x000235c9                gui_inb
                0x0002313b                sprintf
                0x00022ad0                panic
                0x00023502                my_buffer_char_blt
                0x00023602                get_cursor_y
                0x00023619                carrega_bitmap_16x16
                0x0002339c                input
                0x00022af0                scroll
                0x00023392                printf_main
                0x000234e4                my_buffer_put_pixel
                0x00023195                outbyte
                0x000234ae                my_buffer_horizontal_line
                0x00022b77                kclear
                0x00022bd1                kprintf
                0x000235eb                get_cursor_x
                0x000232ba                _outbyte
                0x00023120                printf
                0x0002358b                vsync
 .text          0x00023640      0x240 string.o
                0x00023805                strcat
                0x00023640                strcmp
                0x0002385c                bzero
                0x00023774                memcpy
                0x00023835                bcopy
                0x000237d5                strcpy
                0x000236f9                str_cmp
                0x0002369b                strncmp
                0x000237b1                strlen
 .text          0x00023880      0x8e0 stdlib.o
                0x00023b3b                FreeHeap
                0x00023880                rtGetHeapStart
                0x00023d82                free
                0x00023d24                rand
                0x00023c9b                stdlibInitMM
                0x00023b45                heapInit
                0x00023894                rtGetHeapPointer
                0x0002389e                rtGetAvailableHeap
                0x00023cfb                libcInitRT
                0x000238a8                heapSetLibcHeap
                0x00023d41                malloc
                0x00023b28                AllocateHeapEx
                0x0002394f                AllocateHeap
                0x000240f9                stdlib_strncmp
                0x0002388a                rtGetHeapEnd
                0x00023d87                system
 .text          0x00024160      0x1d0 keyboard.o
                0x00024160                keyboardHandler
 .text          0x00024330      0x290 pci.o
                0x00024454                pciCheckVendor
                0x00024330                pciConfigReadWord
                0x000244e9                pciInfo
                0x000244aa                pciGetClassCode
                0x000245aa                pciInit
                0x000243d6                pciCheckDevice
 .text          0x000245c0     0x2580 hdd.o
                0x000248c6                ata_status_read
                0x000269eb                write_pci_config_addr
                0x00026920                ide_dma_stop
                0x000264f4                ide_write_sector
                0x00025c59                ata_pio_write
                0x000246d2                ata_wait
                0x00026a44                pci_scan_device
                0x000246fd                ata_wait_not_busy
                0x000247f9                ata_wait_irq
                0x00025f75                ide_read_sector
                0x00025868                ide_dev_init
                0x00025c2f                ata_pio_read
                0x00024bf0                read_sector
                0x000268ee                ide_dma_start
                0x00024dca                ata_initialize
                0x000245c0                my_read_hd_sector
                0x00025c83                atapi_read_sector
                0x00024cff                write_sector
                0x00024730                ata_wait_busy
                0x00025b95                nport_ajuste
                0x000248e1                ata_cmd_write
                0x000247db                ata_irq_handler1
                0x000257cf                ide_mass_storage_initialize
                0x0002479f                ata_wait_drq
                0x00024877                ata_soft_reset
                0x00024763                ata_wait_no_drq
                0x000247ea                ata_irq_handler2
                0x000249be                ide_identify_device
                0x00024656                limpa_fat
                0x0002697e                ide_dma_read_status
                0x00025015                set_ata_addr
                0x00026829                ide_dma_data
                0x000245f9                my_write_hd_sector
                0x00026999                read_pci_config_addr
                0x00024616                limpa_root
                0x00025072                ata_pci_configuration_space
                0x00024911                ata_assert_dever
 .text          0x00026b40       0x30 timer.o
                0x00026b40                timer
                0x00026b4b                BltimerInit
 .text          0x00026b70      0x5a0 pages.o
                0x00026b70                SetUpPaging
 .text          0x00027110       0x80 procedure.o
                0x00027110                bl_procedure
 .text          0x00027190      0x990 fs.o
                0x0002721c                fs_get_fat_entry
                0x00027494                fsSearchFile
                0x00027af3                fsInitFat
                0x0002729e                fs_set_fat_entry
                0x00027226                fs_create_entry
                0x00027276                fs_show_entry
                0x00027230                fsSaveFileName
                0x0002723f                fs_set_entry
                0x00027586                fs_load_rootdirEx
                0x00027217                fs_test_fat_vector
                0x00027981                fsCreateFile
                0x00027af8                fsInitStructures
                0x00027afd                fsInit
                0x000275d7                fs_load_fatEx
                0x000271ef                fs_format
                0x000272c1                fsLoadFile
                0x00027573                fsSearchFileName
                0x0002728f                fs_set_entry_status
                0x00027a86                fsCheckFat
                0x0002725d                fsSaveRootDir
                0x00027271                fs_save_entry_on_root
                0x000272b2                fs_relood_dir
                0x0002720d                fs_find_not_empty_entry
                0x0002776c                read_lba
                0x00027235                fs_save_entry_on_disc
                0x0002726c                fs_save_structure
                0x000272a3                fs_find_empty_entry
                0x00027294                fs_makeboot
                0x000272b7                mostra
                0x00027203                fs_search_empty_entry
                0x0002727b                fs_delete_entry
                0x00027244                fs_get_entry
                0x0002724e                fs_show_dir
                0x00027285                fs_get_entry_status
                0x000277c0                fsSaveFile
                0x00027253                fs_check_cluster
                0x00027262                fs_load_dir
                0x00027267                fs_save_dir
                0x00027626                fs_put_list_on_fat
                0x00027a79                fsClearFat
                0x00027280                fs_init_bootfile_struct
                0x000271b3                fatLoadCluster
                0x000276d9                fs_find_n_empty_entries
                0x00027249                fs_show_dir_entry
                0x0002723a                fs_set_structures
                0x0002722b                fsCreateFileName
                0x0002775f                fs_load_rootdir
                0x000272ad                fs_install
                0x00027967                fsCreateDir
                0x00027796                write_lba
                0x00027190                fatClustToSect
 .text          0x00027b20      0x640 shell.o
                0x00027b88                shellProcedure
                0x00027b20                shellMain
                0x00028086                boot
                0x00028131                shellInit
                0x00027c8a                shellWaitCmd
                0x0002808b                debug
                0x00027ca2                shellCompare
                0x000280a4                testa_mbr
                0x00027c0a                shellInitializePrompt
                0x000280e4                testa_root
                0x00028124                reboot
                0x00028072                shellHelp
 .text          0x00028160       0x10 services.o
                0x0002816a                system_services
                0x00028160                blServices
 .text          0x00028170       0x20 abort.o
                0x00028170                abort
 .text          0x00028190      0x100 faults.o
                0x0002827f                mostra_reg
                0x00028190                cpu_falts
                0x00029000                . = ALIGN (0x1000)
 *fill*         0x00028290      0xd70 00

.rdata          0x00029000      0xe20
 .rdata         0x00029000       0xa0 faults.o
 .rdata         0x000290a0       0x20 abort.o
 .rdata         0x000290c0      0x1c0 shell.o
 .rdata         0x00029280      0x1e0 fs.o
 .rdata         0x00029460       0x10 procedure.o
 .rdata         0x00029470      0x350 hdd.o
 .rdata         0x000297c0       0x50 pci.o
 .rdata         0x00029810      0x420 stdlib.o
 .rdata         0x00029c30       0x40 stdio.o
 .rdata         0x00029c70       0x20 init.o
 .rdata         0x00029c90      0x110 loader.o
 .rdata         0x00029da0       0x80 main.o

.data           0x00029e20     0x11e0
                0x00029e20                data = .
                0x00029e20                _data = .
                0x00029e20                __data = .
 *(.data)
 .data          0x00029e20        0x2 head.o
                0x00029e20                data_start
 *fill*         0x00029e22        0x2 00
 .data          0x00029e24        0x0 main.o
 .data          0x00029e24        0x0 loader.o
 .data          0x00029e24        0x0 init.o
 .data          0x00029e24        0x0 ports.o
 .data          0x00029e24        0x0 x86.o
 .data          0x00029e24        0x0 stdio.o
 .data          0x00029e24        0x0 string.o
 .data          0x00029e24       0x10 stdlib.o
 .data          0x00029e34      0x1a0 keyboard.o
                0x00029e34                destroy_window
                0x00029e38                quit_message
 .data          0x00029fd4        0x0 pci.o
 .data          0x00029fd4      0x440 hdd.o
                0x0002a014                pci_classes
                0x00029ff4                dev_type
 .data          0x0002a414        0x0 timer.o
 .data          0x0002a414        0x0 pages.o
 .data          0x0002a414        0x0 procedure.o
 .data          0x0002a414        0x0 fs.o
 .data          0x0002a414       0x40 shell.o
                0x0002a414                help_string
 .data          0x0002a454        0x0 services.o
 .data          0x0002a454        0x0 abort.o
 .data          0x0002a454        0x0 faults.o
                0x0002b000                . = ALIGN (0x1000)
 *fill*         0x0002a454      0xbac 00

.bss            0x0002b000    0x43000
                0x0002b000                bss = .
                0x0002b000                _bss = .
                0x0002b000                __bss = .
 *(.bss)
 .bss           0x0002b000        0x0 head.o
                0x0002b000                bss_start
 .bss           0x0002b000        0x0 main.o
 .bss           0x0002b000        0x0 loader.o
 .bss           0x0002b000        0x0 init.o
 .bss           0x0002b000        0x0 ports.o
 .bss           0x0002b000        0x0 x86.o
 .bss           0x0002b000       0x10 stdio.o
 .bss           0x0002b010        0x0 string.o
 .bss           0x0002b010    0x40000 stdlib.o
 .bss           0x0006b010       0x10 keyboard.o
                0x0006b010                ambiente
 .bss           0x0006b020        0x0 pci.o
 .bss           0x0006b020       0x70 hdd.o
                0x0006b020                dev_next_pid
 .bss           0x0006b090        0x0 timer.o
 .bss           0x0006b090        0x0 pages.o
 .bss           0x0006b090        0x0 procedure.o
 .bss           0x0006b090        0x0 fs.o
 .bss           0x0006b090        0x0 shell.o
 .bss           0x0006b090        0x0 services.o
 .bss           0x0006b090        0x0 abort.o
 .bss           0x0006b090        0x0 faults.o
 *(COMMON)
 COMMON         0x0006b090      0xe30 main.o
                0x0006b090                g_fat16_fat_status
                0x0006b0a0                prompt
                0x0006b1a0                EDITBOX_LARGURA
                0x0006b1b0                partition
                0x0006b1c0                system_info
                0x0006b1d0                g_initialized
                0x0006b1e0                ata_record_dev
                0x0006b1f0                bliTesting
                0x0006b200                EDITBOX_BG_COLOR
                0x0006b210                STATUS_X
                0x0006b220                prompt_pos
                0x0006b230                g_fat16_root_status
                0x0006b240                STATUS_Y
                0x0006b250                buffer_dir_entry
                0x0006b450                BootLoaderCR3
                0x0006b460                next_address
                0x0006b470                ata_record_channel
                0x0006b480                EDITBOX_ALTURA
                0x0006b490                g_lbf_va
                0x0006b4a0                LegacyCR3
                0x0006b4b0                g_proc_status
                0x0006b4c0                gdefTesting
                0x0006b4d0                proximo
                0x0006b4e0                ata_pci
                0x0006b520                procedure_info
                0x0006b530                EDITBOX_TEXT_COLOR
                0x0006b540                CURSOR_Y
                0x0006b550                EDITBOX_Y
                0x0006b560                current_task
                0x0006b570                g_system_color
                0x0006b580                CURSOR_X
                0x0006b590                useGUI
                0x0006b5a0                file_cluster_list
                0x0006bda0                vesa_mode
                0x0006bdb0                ata_identify_dev_buf
                0x0006bdc0                g_next_app
                0x0006bdd0                dev_nport
                0x0006bdf0                ata
                0x0006be10                VideoBlock
                0x0006be30                g_cursor_y
                0x0006be40                g_cmd_status
                0x0006be50                g_file_system_type
                0x0006be60                g_char_attrib
                0x0006be70                g_next_proc
                0x0006be80                g_lbf_pa
                0x0006be90                g_nova_mensagem
                0x0006bea0                EDITBOX_X
                0x0006beb0                g_cursor_x
 COMMON         0x0006bec0      0x8f0 stdlib.o
                0x0006bec0                current_mmblock
                0x0006bed0                mm_prev_pointer
                0x0006bee0                heap_end
                0x0006bef0                g_available_heap
                0x0006bf00                heap_start
                0x0006bf10                heapCount
                0x0006bf20                HEAP_START
                0x0006bf30                g_heap_pointer
                0x0006bf40                heapList
                0x0006c340                HEAP_SIZE
                0x0006c350                last_size
                0x0006c360                last_valid
                0x0006c370                mmblockList
                0x0006c770                libcHeap
                0x0006c780                Heap
                0x0006c790                mmblockCount
                0x0006c7a0                HEAP_END
 COMMON         0x0006c7b0       0x70 keyboard.o
                0x0006c7b0                shift_status
                0x0006c7c0                alt_status
                0x0006c7d0                escape_status
                0x0006c7e0                tab_status
                0x0006c7f0                key_status
                0x0006c800                ctrl_status
                0x0006c810                winkey_status
 COMMON         0x0006c820       0x50 hdd.o
                0x0006c820                dma_addr
                0x0006c830                current_dev
                0x0006c840                ide_dma_prdt
                0x0006c860                ready_queue_dev
 COMMON         0x0006c870       0x10 timer.o
                0x0006c870                timerTicks
 COMMON         0x0006c880      0x440 shell.o
                0x0006c880                shell_status
                0x0006c890                shell_string_buffer
                0x0006cc90                deslocamento
                0x0006cca0                ret_string
                0x0006ccb0                ShellInitialized
 *(.bss_heap)
 .bss_heap      0x0006ccc0      0x400 head.o
                0x0006ccc0                bootloader_heap_start
                0x0006d0c0                bootloader_heap_end
 *(.bss_stack)
 .bss_stack     0x0006d0c0      0x400 head.o
                0x0006d4c0                bootloader_stack_start
                0x0006d0c0                bootloader_stack_end
                0x0006e000                . = ALIGN (0x1000)
 *fill*         0x0006d4c0      0xb40 00
                0x0006e000                end = .
                0x0006e000                _end = .
                0x0006e000                __end = .
                0x0006e000                _bootloader_end = .
LOAD head.o
LOAD main.o
LOAD loader.o
LOAD init.o
LOAD ports.o
LOAD x86.o
LOAD stdio.o
LOAD string.o
LOAD stdlib.o
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
