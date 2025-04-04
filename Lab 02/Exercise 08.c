int alloc_page(uint32_t pid, uint32_t va, uint32_t perm) 
{
    void *page = page_alloc();
    if (!page) return -1;
    
    if (map_page(pid, va, (uint32_t)page, perm) < 0) {
        page_free(page);
        return -1;
    }
    
    return 0;
}
