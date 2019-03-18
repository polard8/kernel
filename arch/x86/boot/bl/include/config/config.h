




// USE PRIMARY MASTER!!

// Portas bases encontradas nas BARs.
//BAR0 = base port 1F0   HD primário
//BAR1 = base port 3F6	
//BAR2 = base port 170   HD secundário
//BAR3 = base port 376

//#importante: Isso é BAR e naõ porta.
#define  __IDE_PORT __IDE_BAR
#define __IDE_BAR 0

#define __IDE_SLAVE  0  // 0=master 1=slave


// #tests:

// + Funcionou BAR=0 slave=0.
// + Funcionou BAR=0 slave=1.

// + Funcionou BAR=2 slave=0. secondary master 
// + Funcionou BAR=2 slave=1. secondary slave

// #bugbug
// Ouve uma falha..
// Só temos o registro das portas 0 e 2.
// A porta 0 equivale ao canal primary.
// A porta 2 equivale ao canal secondary.
// Eram para as portas 0 e 1 representarem o canal primary.
// Eram para as portas 2 e 3 represerntarem o canal secondary.

// #importante:
// Na verdade só funcionam as portas 0 e 2 porque são 
// selecionadores das BARs 0 e 2, onde estão as portas de HD.
// #todo: rever o código nessa parte de configuração das BARs.

