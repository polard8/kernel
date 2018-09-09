


int mainTextEditor(int argc, char *argv[])
{
	
	printf("Welcome to the text editor ...\n");
    //printf("Press 'q' to quit .\n\n");
	
	int ch;
	
    //A file pointer to read a file
    FILE *fp;

    //Open a file for both reading and writing. The file must exist.
    fp = fopen( "init.txt", "r+");
    if( (void*) fp == NULL)
    {
        printf("fopen fail\n");
        goto fail;		
    }else{
		
		
	    while(1)
	    {
	        ch = (int) getchar();
	        if(ch != -1)
	        {
	            printf("%c",ch);
	    
	            //switch(ch)
                //{
			        //quit
			    //    case 'q':
			    //        goto hang;
				//        break;				 
		        //};		   
		    };
		    asm("pause");
	    };		
		
		//saiu.
		
	};
	
		

    
hang:	
    printf("exit.\n");
	while(1){
		asm("pause");
	}	
	return 0;
};