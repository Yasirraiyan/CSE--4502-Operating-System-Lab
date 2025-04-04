void pdir_init(uint32_t pid) {
    // Clear all PDEs
    for (uint32_t i = 0; i < NPDENTRIES; i++) {
        rmv_pdir_entry(pid, i);
    }
    
    // Set up kernel portion (shared with process 0)
    for (uint32_t i = KERNBASE >> PDXSHIFT; i < NPDENTRIES; i++) {
        uint32_t pde = get_pdir_entry(0, i);
        set_pdir_entry(pid, i, pde);
    }
}

int alloc_ptbl(uint32_t pid, uint32_t va) {
    uint32_t pde_index = PDX(va);
    if (get_pdir_entry(pid, pde_index) & PTE_P) return 0; // Already exists
    
    uint32_t ptbl = (uint32_t)page_alloc();
    if (!ptbl) return -1;
    
    set_pdir_entry(pid, pde_index, ptbl | PTE_P | PTE_W | PTE_U);
    return 0;
}

void free_ptbl(uint32_t pid, uint32_t va) {
    uint32_t pde_index = PDX(va);
    uint32_t pde = get_pdir_entry(pid, pde_index);
    if (!(pde & PTE_P)) return;
    
    uint32_t ptbl = pde & 0xFFFFF000;
    page_free((void*)ptbl);
    rmv_pdir_entry(pid, pde_index);
}
