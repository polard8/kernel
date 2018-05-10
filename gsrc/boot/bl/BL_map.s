
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
 .head_x86      0x00021000     0x15c1 head.o
                0x00021e83                fault_N1
                0x00021ef3                fault_DOUBLE
                0x00021b3b                task1_stack
                0x00022073                hd_buffer
                0x000211ab                SavedBPP
                0x000225b7                asm_shut_down
                0x000211af                SavedBootMode
                0x00022063                fault_N31
                0x00022033                fault_N28
                0x0002238f                int56
                0x00021fc3                fault_N21
                0x00021f53                fault_N14
                0x000223ca                int201
                0x00021f23                fault_N11
                0x00021e33                irq0
                0x00022385                int54
                0x00021ea3                fault_N3
                0x00022376                int51
                0x000223a3                int100
                0x00021ff3                fault_N24
                0x00022013                fault_N26
                0x0002207b                test_write
                0x00021e73                fault_N0
                0x0002208b                os_read_sector
                0x000225a3                softwarelibReboot
                0x00022053                fault_N30
                0x00021b7d                setup_idt_vector
                0x00021f33                fault_STACK
                0x00021b3f                task2_stack
                0x00022023                fault_N27
                0x0002236c                int49
                0x00021b37                task0_stack
                0x00022380                int53
                0x000211a3                SavedX
                0x00021f73                fault_N16
                0x00021f43                fault_GP
                0x00021e39                timer_test
                0x00022367                int48
                0x00021fa3                fault_N19
                0x00021ee3                fault_N7
                0x00022371                int50
                0x00022399                int58
                0x00022043                fault_N29
                0x000223d6                my_buffer_load_bitmap_16x16
                0x0002238a                int55
                0x000223cf                int213
                0x00021fe3                fault_N23
                0x000211a7                SavedY
                0x000223a8                int200
                0x00022552                refresh_screen
                0x00021ed3                fault_INTRUCAO_INVALIDA
                0x0002119f                SavedLFB
                0x0002119b                SavedBootBlock
                0x0002246c                background
                0x00021eb3                fault_N4
                0x00021e93                fault_N2
                0x000220a4                os_write_sector
                0x00021fb3                fault_N20
                0x0002237b                int52
                0x00022394                int57
                0x00021fd3                fault_N22
                0x00021f13                fault_N10
                0x00021e4d                irq1
                0x00021f63                fault_N15
                0x00021f83                fault_N17
                0x00021f93                fault_N18
                0x00022077                hd_lba
                0x00022003                fault_N25
                0x000224c4                gui_buffer_putpixel
                0x000222cd                reset_ide0
                0x00021f03                fault_N9
                0x0002239e                int59
                0x00021000                bootloader_entry_point
                0x00021ec3                fault_N5
 *(.text)
 *fill*         0x000225c1        0x3 00
 .text          0x000225c4      0x110 main.o
                0x00022694                BlKernelModuleMain
                0x0002267c                BlSetupPaging
                0x000226ad                die
                0x000225c4                BlMain
                0x0002262e                BlLoadKernel
                0x00022655                BlLoadFiles
                0x00022689                BlAbort
 .text          0x000226d4      0x220 loader.o
                0x000226d4                load_kernel
                0x0002278e                load_files
 .text          0x000228f4      0x110 init.o
                0x0002296d                init
                0x0002292c                init_globals
                0x000228f4                set_up_color
                0x00022901                set_up_text_color
 .text          0x00022a04       0xd0 ports.o
                0x00022a3b                inport8
                0x00022a79                outport32
                0x00022a04                bloutportb
                0x00022a85                inb
                0x00022ab9                outportl
                0x00022aa7                inportl
                0x00022a2f                outportb
                0x00022a47                outport8
                0x00022a60                outport16
                0x00022a53                inport16
                0x00022a1c                inportb
                0x00022a6d                inport32
                0x00022a10                outb
 .text          0x00022ad4       0xd0 x86.o
                0x00022b79                pushFlags
                0x00022b6d                pushRegs
                0x00022b64                Pop
                0x00022af7                farReturn
                0x00022afd                getFlags
                0x00022b7f                popFlags
                0x00022aea                stopCpu
                0x00022b11                BlProcessorInPort8
                0x00022b8f                setStackPointer
                0x00022b43                BlProcessorInPort32
                0x00022b1d                BlProcessorOutPort8
                0x00022b73                popRegs
                0x00022b4f                BlProcessorOutPort32
                0x00022b36                BlProcessorOutPort16
                0x00022b5b                Push
                0x00022b29                BlProcessorInPort16
                0x00022b07                setFlags
                0x00022b85                getStackPointer
                0x00022adf                disable
                0x00022af1                intReturn
                0x00022ad4                enable
 .text          0x00022ba4      0xb70 stdio.o
                0x00023253                putchar
                0x0002369d                gui_inb
                0x0002320f                sprintf
                0x00022ba4                panic
                0x000235d6                my_buffer_char_blt
                0x000236d6                get_cursor_y
                0x000236ed                carrega_bitmap_16x16
                0x00023470                input
                0x00022bc4                scroll
                0x00023466                printf_main
                0x000235b8                my_buffer_put_pixel
                0x00023269                outbyte
                0x00023582                my_buffer_horizontal_line
                0x00022c4b                kclear
                0x00022ca5                kprintf
                0x000236bf                get_cursor_x
                0x0002338e                _outbyte
                0x000231f4                printf
                0x0002365f                vsync
 .text          0x00023714      0x240 string.o
                0x000238d9                strcat
                0x00023714                strcmp
                0x00023930                bzero
                0x00023848                memcpy
                0x00023909                bcopy
                0x000238a9                strcpy
                0x000237cd                str_cmp
                0x0002376f                strncmp
                0x00023885                strlen
 .text          0x00023954      0x8e0 stdlib.o
                0x00023c0f                FreeHeap
                0x00023954                rtGetHeapStart
                0x00023e56                free
                0x00023df8                rand
                0x00023d6f                stdlibInitMM
                0x00023c19                heapInit
                0x00023968                rtGetHeapPointer
                0x00023972                rtGetAvailableHeap
                0x00023dcf                libcInitRT
                0x0002397c                heapSetLibcHeap
                0x00023e15                malloc
                0x00023bfc                AllocateHeapEx
                0x00023a23                AllocateHeap
                0x000241cd                stdlib_strncmp
                0x0002395e                rtGetHeapEnd
                0x00023e5b                system
 .text          0x00024234      0x1d0 keyboard.o
                0x00024234                keyboardHandler
 .text          0x00024404      0x290 pci.o
                0x00024528                pciCheckVendor
                0x00024404                pciConfigReadWord
                0x000245bd                pciInfo
                0x0002457e                pciGetClassCode
                0x0002467e                pciInit
                0x000244aa                pciCheckDevice
 .text          0x00024694     0x2560 hdd.o
                0x0002497e                ata_status_read
                0x00026aa3                write_pci_config_addr
                0x000269d8                ide_dma_stop
                0x000265ac                ide_write_sector
                0x00025d11                ata_pio_write
                0x0002478a                ata_wait
                0x00026afc                pci_scan_device
                0x000247b5                ata_wait_not_busy
                0x000248b1                ata_wait_irq
                0x0002602d                ide_read_sector
                0x00025920                ide_dev_init
                0x00025ce7                ata_pio_read
                0x00024ca8                read_sector
                0x000269a6                ide_dma_start
                0x00024e82                ata_initialize
                0x00024694                my_read_hd_sector
                0x00025d3b                atapi_read_sector
                0x00024db7                write_sector
                0x000247e8                ata_wait_busy
                0x00025c4d                nport_ajuste
                0x00024999                ata_cmd_write
                0x00024893                ata_irq_handler1
                0x00025887                ide_mass_storage_initialize
                0x00024857                ata_wait_drq
                0x0002492f                ata_soft_reset
                0x0002481b                ata_wait_no_drq
                0x000248a2                ata_irq_handler2
                0x00024a76                ide_identify_device
                0x0002470e                limpa_fat
                0x00026a36                ide_dma_read_status
                0x000250cd                set_ata_addr
                0x000268e1                ide_dma_data
                0x000246b1                my_write_hd_sector
                0x00026a51                read_pci_config_addr
                0x000246ce                limpa_root
                0x0002512a                ata_pci_configuration_space
                0x000249c9                ata_assert_dever
 .text          0x00026bf4       0x30 timer.o
                0x00026bf4                timer
                0x00026bff                BltimerInit
 .text          0x00026c24      0x5a0 pages.o
                0x00026c24                SetUpPaging
 .text          0x000271c4       0x80 procedure.o
                0x000271c4                bl_procedure
 .text          0x00027244      0x990 fs.o
                0x000272d0                fs_get_fat_entry
                0x00027548                fsSearchFile
                0x00027ba7                fsInitFat
                0x00027352                fs_set_fat_entry
                0x000272da                fs_create_entry
                0x0002732a                fs_show_entry
                0x000272e4                fsSaveFileName
                0x000272f3                fs_set_entry
                0x0002763a                fs_load_rootdirEx
                0x000272cb                fs_test_fat_vector
                0x00027a35                fsCreateFile
                0x00027bac                fsInitStructures
                0x00027bb1                fsInit
                0x0002768b                fs_load_fatEx
                0x000272a3                fs_format
                0x00027375                fsLoadFile
                0x00027627                fsSearchFileName
                0x00027343                fs_set_entry_status
                0x00027b3a                fsCheckFat
                0x00027311                fsSaveRootDir
                0x00027325                fs_save_entry_on_root
                0x00027366                fs_relood_dir
                0x000272c1                fs_find_not_empty_entry
                0x00027820                read_lba
                0x000272e9                fs_save_entry_on_disc
                0x00027320                fs_save_structure
                0x00027357                fs_find_empty_entry
                0x00027348                fs_makeboot
                0x0002736b                mostra
                0x000272b7                fs_search_empty_entry
                0x0002732f                fs_delete_entry
                0x000272f8                fs_get_entry
                0x00027302                fs_show_dir
                0x00027339                fs_get_entry_status
                0x00027874                fsSaveFile
                0x00027307                fs_check_cluster
                0x00027316                fs_load_dir
                0x0002731b                fs_save_dir
                0x000276da                fs_put_list_on_fat
                0x00027b2d                fsClearFat
                0x00027334                fs_init_bootfile_struct
                0x00027267                fatLoadCluster
                0x0002778d                fs_find_n_empty_entries
                0x000272fd                fs_show_dir_entry
                0x000272ee                fs_set_structures
                0x000272df                fsCreateFileName
                0x00027813                fs_load_rootdir
                0x00027361                fs_install
                0x00027a1b                fsCreateDir
                0x0002784a                write_lba
                0x00027244                fatClustToSect
 .text          0x00027bd4      0x640 shell.o
                0x00027c3c                shellProcedure
                0x00027bd4                shellMain
                0x0002813a                boot
                0x000281e5                shellInit
                0x00027d3e                shellWaitCmd
                0x0002813f                debug
                0x00027d56                shellCompare
                0x00028158                testa_mbr
                0x00027cbe                shellInitializePrompt
                0x00028198                testa_root
                0x000281d8                reboot
                0x00028126                shellHelp
 .text          0x00028214       0x10 services.o
                0x0002821e                system_services
                0x00028214                blServices
 .text          0x00028224       0x20 abort.o
                0x00028224                abort
 .text          0x00028244      0x100 faults.o
                0x00028333                mostra_reg
                0x00028244                cpu_falts
                0x00029000                . = ALIGN (0x1000)
 *fill*         0x00028344      0xcbc 00

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
