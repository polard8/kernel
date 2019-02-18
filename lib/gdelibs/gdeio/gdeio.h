

    //retorna o valor.
	unsigned char gde_inport8 (unsigned short port);
	unsigned short gde_inport16 (unsigned short port);
	unsigned long gde_inport32 (unsigned short port);
	
    //o retorno é status.
	//0=funcionou. 1=falhou;
    int gde_outport8 ( unsigned short port, unsigned char value);
	int gde_outport16 ( unsigned short port, unsigned short value);
	int gde_outport32 ( unsigned short port, unsigned long value);


