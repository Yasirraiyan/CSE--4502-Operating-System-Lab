void pdir_init_kern(uint32_t pid) {
    pdir_init(pid);
    
    // Map kernel portion
    for (uint32_t va = KERNBASE; va < KERNBASE + KERNSIZE; va += PGSIZE) {
        map_page(pid, va, va, PTE_P | PTE_W);
    }
}

int map_page(uint32_t pid, uint32_t va, uint32_t pa, uint32_t perm) {
    if (alloc_ptbl(pid, va) < 0) return -1;
    
    uint32_t pte = (pa & 0xFFFFF000) | perm;
    set_ptbl_entry_by_va(pid, va, pte);
    return 0;
}

void unmap_page(uint32_t pid, uint32_t va) {
    rmv_ptbl_entry_by_va(pid, va);
    
    // Check if page table is now empty
    uint32_t pde_index = PDX(va);
    uint32_t *ptbl = (uint32_t*)(get_pdir_entry(pid, pde_index) & 0xFFFFF000);
    bool empty = TRUE;
    for (uint32_t i = 0; i < NPTENTRIES; i++) {
        if (ptbl[i] & PTE_P) {
            empty = FALSE;
            break;
        }
    }
    
    if (empty) free_ptbl(pid, va);
}
