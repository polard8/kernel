/*
 *  File: gdevice.h
 *
 * Definição: 
 * Informações globais sobre o dispositivo onde o sistema operacional foi instalado.
 * Informações sobre o host device.
 * Não é a qui o lugar para se detalhar todos os dispositivos instalados na máquina.
 * Aqui é lugar de classificar a plataforma alvo para o sistema operacional. Para
 * que as aplicações possam se adaptar às características do dispositivo que suporta
 * o sistema operacional.
 *
 * Versão 1.0, 2016 - Created.   
 */
 
 
 
//Classes mais comuns de dispositivos.
//Outras poderão ser incluídas futuramente. 
typedef enum {
	HostDeviceTypePC,        //PC.
	HostDeviceTypeMobile,    //Mobile.
	HostDeviceTypeIOT,       //Iot.
	//...
}host_device_type_t; 
 
typedef struct host_device_info_d host_device_info_t; 
struct host_device_info_d
{
	//Type.
    host_device_type_t type;
	
	
	//Screen size.
	unsigned long host_device_screen_width;
	unsigned long host_device_screen_height;

    //Continua ...
	
};
host_device_info_t *HostDeviceInfo; 
//
 
// 
// Globais de fácil acesso.
// devem refletir os valores armazenados na estrutura.
//

//Screen sizes.
unsigned long g_device_screen_width; 
unsigned long g_device_screen_height; 

 
//
// End.
//

