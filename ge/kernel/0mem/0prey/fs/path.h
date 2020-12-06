

    // path.h
    // path support.
    
    
#define  FS_MAX_NAME_LENGHT (8+3)
#define  WORKINGDIRECTORY_STRING_MAX 32   //64
// ...



// pathname separator and terminator.
#define  FS_PATHNAME_SEPARATOR   "/"
#define  FS_PATHNAME_SEPARATOR2   "\\"
#define  FS_PATHNAME_TERMINATOR  "\0"

// string separator and terminator.
#define  FS_STRING_SEPARATOR    "/"
#define  FS_STRING_SEPARATOR2   "\\"
#define  FS_STRING_TERMINATOR   "\0" 


// volume support
#define  FS_ROOT_STRING           "root:"
#define  FS_VOLUME0_STRING        "volume0"   //vfs
#define  FS_VOLUME1_STRING        "volume1"   //boot volume
#define  FS_VOLUME2_STRING        "volume2"   //system volume.
#define  FS_UNKNOWNVOLUME_STRING  "unknown-volume"

#define  FS_VFSWORKINGDIRECTORY_STRING      "volume1"
#define  FS_BOOTWORKINGDIRECTORY_STRING     "volume1"
#define  FS_SYSTEMWORKINGDIRECTORY_STRING   "volume2"
#define  FS_UNKNOWNWORKINGDIRECTORY_STRING  "unknown-directory"


// pathname support.
// Rethink this.

// O inicializador 'root:' poderá ser ignorado.
#define  FS_DIR_VFS          'root:/volume0'  
#define  FS_DIR_BOOT         'root:/volume1'  
#define  FS_DIR_SYSTEM       'root:/volume2'  
#define  FS_DIR_BM           'root:/volume1/BM.BIN'       
#define  FS_DIR_BL           'root:/volume1/BL.BIN'       
#define  FS_DIR_KERNEL       'root:/volume1/KERNEL.BIN'   
#define  FS_DIR_INIT         'root:/volume1/INIT.BIN'     
//#define  FS_DIR_SHELL        'root:/volume1/SHELL.BIN'    
//#define  FS_DIR_TASKMAN      'root:/volume1/TASKMAN.BIN' 
#define  FS_DIR_INITTXT      'root:/volume1/INIT.TXT'      
#define  FS_DIR_BIN          'root:/volume2/bin'   
#define  FS_DIR_DEV          'root:/volume2/dev'    
#define  FS_DIR_LIB          'root:/volume2/lib'     
#define  FS_DIR_USER         'root:/volume2/user' 
#define  FS_DIR_DEFAULTUSER  'root:/volume2/user/default'
// ...





