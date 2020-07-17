            

int execute_image ( char *file_name ){

    unsigned long xxx_buff;
			unsigned long xxx_buff_pa;
			struct process_d *xxxPPP;
			struct thread_d *xxxTTT;
			

			xxxPPP = (struct process_d *) sys_create_process ( NULL, NULL, NULL, 
			                    arg2, arg3, 0, (char *) a4, 
								RING3, (unsigned long ) CreatePageDirectory() ); 		
            
			
			xxx_buff = (unsigned long) malloc (1024*64); //64kb
			
			xxx_buff_pa = (unsigned long) virtual_to_physical ( xxx_buff, gKernelPageDirectoryAddress );
				
			CreatePageTable ( (unsigned long) xxxPPP->DirectoryVA, ENTRY_USERMODE_PAGES, xxx_buff_pa ); 
			
	
	        //#todo
	        //file_name   
	
            fsLoadFile ( VOLUME1_FAT_ADDRESS,
			 			 VOLUME1_ROOTDIR_ADDRESS, 
	                     "GRAMTEXTBIN", 
                         (unsigned long) xxx_buff );
			
			xxxTTT = (struct thread_d *) sys_create_thread ( 
			                NULL,             // w. station 
							NULL,             // desktop
							NULL,             // w.
							0x400000 + 0x1000,      // init eip
							0x400000 + (1024 *63),  // init stack
							xxxPPP->pid,            // pid (determinado)(provisório).
							"thread-NAME" );        // name
			
			xxxTTT->tss = current_tss;
			
			SelectForExecution (xxxTTT); 
			KiSpawnTask (xxxTTT->tid);
				
			return (void *) xxxPPP;
}



	