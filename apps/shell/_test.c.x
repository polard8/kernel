
/*
 * shellASCII:
 *     Mostrar os caracteres da tabela ascii padrão.
 *     O padrão tem 128 chars.
 *     Obs: Na fonte ROM BIOS temos esse padrão.
 *     #suspenso .. tempos um aplicativo para esse teste.
 *     tascii.bin
 */
/* 
void shellASCII()
{
    unsigned char count;
	unsigned char standard_ascii_max = 128;
	
	
	printf("shellASCII:\n");
	
    for( count=0; count<standard_ascii_max; count++ )
    {
		printf(" %d - %c",count,count);
        if( count % 4 == 0 ){
            printf("\n");
		}
    };	
};
*/