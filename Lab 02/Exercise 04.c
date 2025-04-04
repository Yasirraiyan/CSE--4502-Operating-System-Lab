void set_pdir_base(uint32_t pid, uint32_t pdir) {
    pdirs[pid] = pdir;
}

uint32_t get_pdir_entry(uint32_t pid, uint32_t pde_index) {
    uint32_t *pdir = (uint32_t*)pdirs[pid];
    return pdir[pde_index];
}

void set_pdir_entry(uint32_t pid, uint32_t pde_index, uint32_t pde) {
    uint32_t *pdir = (uint32_t*)pdirs[pid];
    pdir[pde_index] = pde;
}

void set_pdir_entry_identity(uint32_t pid, uint32_t pde_index) {
    uint32_t ptbl = pde_index << 22;
    set_pdir_entry(pid, pde_index, ptbl | PTE_P | PTE_W | PTE_U);
}

void rmv_pdir_entry(uint32_t pid, uint32_t pde_index) {
    set_pdir_entry(pid, pde_index, 0);
}

uint32_t get_ptbl_entry(uint32_t pid, uint32_t pde_index, uint32_t pte_index) {
    uint32_t pde = get_pdir_entry(pid, pde_index);
    if (!(pde & PTE_P)) return 0;
    
    uint32_t *ptbl = (uint32_t*)(pde & 0xFFFFF000);
    return ptbl[pte_index];
}

void set_ptbl_entry(uint32_t pid, uint32_t pde_index, uint32_t pte_index, uint32_t pte) {
    uint32_t pde = get_pdir_entry(pid, pde_index);
    if (!(pde & PTE_P)) return;
    
    uint32_t *ptbl = (uint32_t*)(pde & 0xFFFFF000);
    ptbl[pte_index] = pte;
}

void set_ptbl_entry_identity(uint32_t pid, uint32_t pde_index, uint32_t pte_index) {
    uint32_t page = (pde_index << 22) | (pte_index << 12);
    set_ptbl_entry(pid, pde_index, pte_index, page | PTE_P | PTE_W | PTE_U);
}

void rmv_ptbl_entry(uint32_t pid, uint32_t pde_index, uint32_t pte_index) {
    set_ptbl_entry(pid, pde_index, pte_index, 0);
}
