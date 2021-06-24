

#include <kernel.h>



// User Environment Manager (UEM)
// Segue uma lista de operações que poderão ser realizadas para configuração
// do ambiente gráfico do usuário. Obs: Nesse módulo, apenas chamaremos
// algumas funções primitivas. Todo o trabalho maior deve ficar para os
// servidores em user mode.

#define UEM_NULL 0
#define UEM_CHANGE_BACKGROUND 1
#define UEM_CHANGE_LOGO       2
#define UEM_CHANGE_COLORS     3
// ...



