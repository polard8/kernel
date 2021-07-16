
//
// Process and threads priorities.
//

/*
 * Constantes para níveis de prioridade.
 * Se um processo quiser alterar a prioridade de outro processo.
 * Qualquer processo pode obter sua prioridade e analizar através 
 * dessas definições.
 */
 
//Definições principais. 
#define PRIORITY_LOW4      1  //4
#define PRIORITY_LOW3      2  //3
#define PRIORITY_LOW2      3  //2
#define PRIORITY_LOW1      4  //1 
#define PRIORITY_NORMAL    5  // 0 (Normal).
#define PRIORITY_HIGH1     6  //1
#define PRIORITY_HIGH2     7  //2
#define PRIORITY_HIGH3     8  //3
#define PRIORITY_HIGH4     9  //4
//Definições secundárias.
#define PRIORITY_LOW        PRIORITY_LOW1
#define PRIORITY_SUPERLOW   PRIORITY_LOW4
#define PRIORITY_MIN        PRIORITY_SUPERLOW
#define PRIORITY_HIGH       PRIORITY_HIGH1
#define PRIORITY_SUPERHIGH  PRIORITY_HIGH4
#define PRIORITY_MAX        PRIORITY_SUPERHIGH
//Definição especial.
#define PRIORITY_REALTIME  10    

