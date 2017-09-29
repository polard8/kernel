/*
 * File: sm\logon.h
 *
 * Descrição:
 *     Header de suporte à criação do Logon.
 *  
 * OBS:
 *     O Logon está na WindowStation0 e no Desktop0. 
 *     Existirá um processo em user mode para gerenciamento de Logon e esse 
 * processo poderá chamar rotinas de logon presentes nesse módulo.
 *
 * History:
 *     2015 - Created by Fred Nora.
 *     ...
 */
 

//
// Variáveis globais.
// 
 
//flag, usar ou naõ o default user. 
int g_use_default_user; 
 
 

//
// Protótipos.
// 
 
//Cria.
void create_logon(); 

//Inicializa.
int init_logon(int argc, char *argv[]); 	


/*
 * SetLogonParameters:
 *     Configura alguns parâmetros para a tela de logon.
 *
 */
void SetLogonParameters( int refresh,         // Flag. Colocar ou não o backbuffer na tela.
int screen,          // Tela do computador.
int background,      // Background da area de trabalho. 
int logo,            // Logo, Janela para imagem da area de trabalho.
int taskbar,         // Barra de tarefas.(icones para programas)
int main,            // Janela principal.( Desktop, ou Kernel Setup Utility ) 
int menu,            // Control menu da Área de trabalho.
int infobox,         // Janelinha no canto, para alerta sobre sobre eventos ocorridos no sistema.
int messagebox,      // O message box do kernel.(cada app cria seu messagebox.) 
int debug,           // Janela do debug do kernel.(sonda por problemas)
int navigationbar,   // Janela de navegação(semelhante a navigation bar dos dispositivos mobile) 
int grid             // Grid da janela principal.
//limites ...
);



/*
 * LogonProcedure:
 *     Procedimento de janela do LOGON.
 */ 
unsigned long LogonProcedure( struct window_d *window, 
                              int msg, 
							  unsigned long long1, 
							  unsigned long long2 );
							  
							  
//
//fim.
//

