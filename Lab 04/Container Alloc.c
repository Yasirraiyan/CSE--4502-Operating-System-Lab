int container_alloc(unsigned int id) 
{
    if (container[id].usage < container[id].quota) 
    {
        container[id].usage++;  // Allocate a page
        return 0;  // Success
    }
    return -1;  // Allocation failed (exceeds quota)
}
