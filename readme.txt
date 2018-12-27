===================================================
for developers:
    You're gonna need the folders /include and /lib.
===================================================


Isso será um conjunto de aplicativos em user mode.

+Não haverá código em ring0 em /gramado.
O Norax kernel poderá ser incluido no projeto em sua forma binária,
compilada em outro projeto.

+Não há bootloader pra esse projeto, ele rodará sobre o 
 kernel Norax e poderá ser instalado nele.
 os binários do Gramado podem ser instalados em Norax..
 

=========================================


    Main folders for Gramado Operating System.



//(relations of production)


//==============
/arch     
    Archtechture stuff.
    Here you can make th VHD file to run Gramado on a VM.


//==============
/bin      
    .bin compiled files.
    All the executable files are here.

//===============
/cmd 
    Console applications.

//===============
/docs    
    Documentation.
 

//================
/fasm
/fasm-win
    Trying to port fasm to Gramado.
    São duas tentativas diferentes de portar o fasm para o gramado.
    Uma delas é usando a interface do fasm com o windows.
    A outra é a interface com a linguagem C unix-like.
    A alternativa usando a libc parece ser a melhor opção.


//================
/gfe
    Gramado File Explorer

//================
/gramcc
    Gramado Compiler Collection.

//================
/gramcode
    Source code editor.

//================
/gramtext
     Text editor.

//================
/gwm
     Gramado Window Manager
     GUI in user mode.

//================
/include  
    Headers.
    libc headers.
    Use these header to create the applications.

//================
/init
     Gramado initialization stuff.

//================    
/lib      
    Libs.
    Compiled libs.
    Source codes for libs.

//================
/licenses
    Licenses

//================
/scripts  
    Scripts.





//(material productive forces)
*/tools    - Different tools. 



//(User ideas, human action)
*/user     - User ideas.
