
// image.h
// Gerenciamento de informações sobre a imagem do processo.
// coisas como tamanho do arquivo, endereço base de carregamento,
// quantidade de páginas usadas pela imagem etc ...



struct image_info_d
{
    int used;
	int magic;
	
	unsigned long ImageBase;
	unsigned long ImageSize;
	
	unsigned long PagesPerImage;
	
	//ponteiro para o nome da imagem.
	char *name;
	
	//ponteiro par ao caminho.
	char *path;
	
	//In disk, in transition, in memory etc ...
	int Status;
	
	
	
	//...
};



