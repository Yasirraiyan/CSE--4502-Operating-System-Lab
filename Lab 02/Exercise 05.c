uint32_t get_pdir_entry_by_va(uint32_t pid, uint32_t va) {
    uint32_t pde_index = PDX(va);
    return get_pdir_entry(pid, pde_index);
}

void set_pdir_entry_by_va(uint32_t pid, uint32_t va, uint32_t pde) {
    uint32_t pde_index = PDX(va);
    set_pdir_entry(pid, pde_index, pde);
}

void rmv_pdir_entry_by_va(uint32_t pid, uint32_t va) {
    uint32_t pde_index = PDX(va);
    rmv_pdir_entry(pid, pde_index);
}

uint32_t get_ptbl_entry_by_va(uint32_t pid, uint32_t va) {
    uint32_t pde_index = PDX(va);
    uint32_t pte_index = PTX(va);
    return get_ptbl_entry(pid, pde_index, pte_index);
}

void set_ptbl_entry_by_va(uint32_t pid, uint32_t va, uint32_t pte) {
    uint32_t pde_index = PDX(va);
    uint32_t pte_index = PTX(va);
    set_ptbl_entry(pid, pde_index, pte_index, pte);
}

void rmv_ptbl_entry_by_va(uint32_t pid, uint32_t va) {
    uint32_t pde_index = PDX(va);
    uint32_t pte_index = PTX(va);
    rmv_ptbl_entry(pid, pde_index, pte_index);
}

void idptbl_init(void) {
    // Initialize identity page table
    for (uint32_t i = 0; i < NPTENTRIES; i++) {
        set_ptbl_entry_identity(0, 0, i);
    }
}
