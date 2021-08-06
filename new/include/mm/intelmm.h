
//
// tables support
//

//PDE - Page Directory Entry
struct intel_pde_d
{
    unsigned long Present              :1;
    unsigned long ReadWrite            :1;
    unsigned long UserSupervisor       :1;
    unsigned long WriteThrough         :1;
    unsigned long CacheDisabled        :1;
    unsigned long Accessed             :1;
    unsigned long Reserved             :1;
    unsigned long PageSize             :1;
    unsigned long GlobalPage           :1;
    unsigned long Available1           :1;
    unsigned long Available2           :1;
    unsigned long Available3           :1;
    unsigned long PageTableBaseAddress :20;
};


//PTE - Page Table Entry
struct intel_pte_d
{
    unsigned long Present         :1;
    unsigned long ReadWrite       :1;
    unsigned long UserSupervisor  :1;
    unsigned long WriteThrough    :1;
    unsigned long CacheDisabled   :1;
    unsigned long Accessed        :1;
    unsigned long Reserved        :1;
    unsigned long PAT             :1;  // Page Table Attribute Index.
    unsigned long GlobalPage      :1;
    unsigned long Available1      :1;
    unsigned long Available2      :1;
    unsigned long Available3      :1;
    unsigned long PageBaseAddress :20;
}; 


