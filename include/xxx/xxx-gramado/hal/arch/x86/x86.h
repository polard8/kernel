
//x86.h 


//Ports and instructions.
int enable();
int disable();
int stopCpu();      
int intReturn();
int farReturn();
int getFlags(int variable);
int setFlags(int variable);
int kernelProcessorInPort8(int port,int data);
int kernelProcessorOutPort8(int port,int data);
int kernelProcessorInPort16(int port,int data);
int kernelProcessorOutPort16(int port,int data);
int kernelProcessorInPort32(int port,int data); 
int kernelProcessorOutPort32(int port,int data);
int Push(int value);
int Pop(int variable);
int pushRegs();
int popRegs();
int pushFlags();
int popFlags();
int getStackPointer(int addr);
int setStackPointer(int addr);



