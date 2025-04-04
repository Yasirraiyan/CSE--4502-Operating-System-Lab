void container_init(void) {
    // Initialize all containers as unused
    for (int i = 0; i < NUM_IDS; i++) {
        containers[i].used = FALSE;
    }
    // Set up container 0 (kernel)
    containers[0].used = TRUE;
    containers[0].quota = total_pages;
    containers[0].usage = 0;
    containers[0].parent = 0;
    containers[0].nchildren = 0;
}

pid_t container_get_parent(pid_t id) {
    if (!containers[id].used) return 0;
    return containers[id].parent;
}

unsigned int container_get_nchildren(pid_t id) {
    if (!containers[id].used) return 0;
    return containers[id].nchildren;
}

unsigned int container_get_quota(pid_t id) {
    if (!containers[id].used) return 0;
    return containers[id].quota;
}

unsigned int container_get_usage(pid_t id) {
    if (!containers[id].used) return 0;
    return containers[id].usage;
}

bool container_can_consume(pid_t id, unsigned int n) {
    if (!containers[id].used) return FALSE;
    return (containers[id].quota - containers[id].usage) >= n;
}

int container_split(pid_t id, pid_t child, unsigned int quota) {
    if (!containers[id].used || containers[child].used) return -1;
    if (!container_can_consume(id, quota)) return -1;
    
    containers[child].used = TRUE;
    containers[child].quota = quota;
    containers[child].usage = 0;
    containers[child].parent = id;
    containers[child].nchildren = 0;
    
    containers[id].usage += quota;
    containers[id].nchildren++;
    
    return 0;
}

int container_alloc(pid_t id, unsigned int n) {
    if (!containers[id].used) return -1;
    if (!container_can_consume(id, n)) return -1;
    
    containers[id].usage += n;
    return 0;
}

int container_free(pid_t id, unsigned int n) {
    if (!containers[id].used) return -1;
    if (containers[id].usage < n) return -1;
    
    containers[id].usage -= n;
    return 0;
}
