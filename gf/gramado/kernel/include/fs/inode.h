

// inode support.
// it's a test yet.


struct inode_d
{
    int id;
    
    int used;
    int magic;
    
    // fat16, ext2 ...
    int type;
    
    //int mode;
    
    // ...
    
    //fat16
    struct fat16_directory_entry_d *fat16_dirent;

    //ext2
    
    struct inode_d *next;
};


unsigned long inode_table[32];




