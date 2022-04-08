DWORD InputState()
{
    int state;
    wprintf(L"\nВведите состояние памяти(0 - COMMIT 1-RESERVE 2-FREE): ");
    scanf("%d",&state);
    switch (state)
    {
    case 0:
        return MEM_COMMIT;
    case 1:
        return MEM_RESERVE;
    case 2:
        return MEM_FREE;
    default:
        return NULL;
    }
}

DWORD InputStateFree()
{
   int state;
    wprintf(L"\nВведите состояние памяти(0 - DECOMMIT 1-RELEASE 2-COALESCE_PLACEHOLDERS 3-MEM_PRESERVE_PLACEHOLDER): ");
    scanf("%d",&state);
    switch (state)
    {
    case 0: 
        return MEM_DECOMMIT;
    case 1:
        return MEM_RELEASE;
    }
}

void AllocMemory(DWORD protect,DWORD state, PVOID id)
{
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    printf("%lx",si.dwPageSize);
    LPVOID newId = VirtualAlloc(id,si.dwPageSize,state,protect);
    if(newId)
    {
        printf("new - %lx ; ",newId);
        wprintf(L"Удачно");
    }
    else
    {
        wprintf(L"Не удачно");
    }
}

void FreeMemory(DWORD stateFree,PVOID id)
{
    MEMORY_BASIC_INFORMATION mbi;
    VirtualQuery(id, &mbi, sizeof(MEMORY_BASIC_INFORMATION));

    SYSTEM_INFO si;
    GetSystemInfo(&si);
    if(VirtualFree(id,mbi.RegionSize,stateFree))
    {
        wprintf(L"Удачно");
    }
    else
    {
        wprintf(L"Не удачно");
    }
}

void LockMemory(PVOID id)
{
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    VirtualLock(id,si.dwPageSize);
}

void UnLockMemory(PVOID id)
{
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    VirtualUnlock(id,si.dwPageSize);
}