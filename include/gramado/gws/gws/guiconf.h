
/*

    guiconf.h
	
	Header para configurações da biblioteca de recursos gráficos.
	As configurações devem ser feitas na hora da inicialização 
	da /gui 

    salvar configurações de esquema de cores, estilo de design, tamanhos 
dos elementos etc ...

    Cada rotina de criação deverá considerar as escolhas configuradas aqui.
	
    a estrutura principla conterá os ponteiros para as outras estruturas 
    de configuração	
	
	
	obs: muitas estruturas secundárias estão em window.h 
	outras estão aqui.
	
	a estrutura principal para configuração será gui_config_d.
*/


//
// Poderíamos ter apenas uma estrutura de configuração de estilo 
// contemplando o estilo selecionado para todos os elementos 
// ao invés de uma estrutura para cada elemento.
//

//
// #importante
// Essas serão as configurações padrão do sistema.
// haverá uma maneira de aplicativos personalizarem 
// seus próprios elementos, mas as configurações do sistema 
// só serão configuradas por gerenciadores do sistema.
// talvez precisem de credencial de administrador.
//





typedef struct gui_config_d gui_config_t;
struct gui_config_d
{
	//Configuração geral de estilo de design.
    int design_style;	
	
	//partes principais da interface gráfica.
	int screen_style;         //a tela(dimensões do monitor)
	int background_style;     //o pano de fundo.
	int logo_style;           //o logo centralizado.
	int main_style;           //a janela principal. (desktop ??)
	int navigationbar_style;  //barra de navegação.
	int menu_style;           //menus ?? 
	int taskbar_style;        // barra de tarefas ( a que tem o start menu ) 
	int statusbar_style;	
	int infobox_style;
	int messagebox_style;
	int debug_style;
	int grid_style;
    //...
	
	//partes secundárias da interface gráfica.
    // detalhes como botões cantos arredondados etc ...      
    int startmenu_style;
	  
	// estrutura principal. windows.h
    struct gui_d *gui;	
};
struct gui_config_d GUI_CONFIG;

