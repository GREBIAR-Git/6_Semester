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
    /*case 2:
        return (MEM_RELEASE|MEM_COALESCE_PLACEHOLDERS);
    case 3:
        return (MEM_RELEASE|MEM_PRESERVE_PLACEHOLDER);*/
    }
}

void AllocMemory(DWORD protect,DWORD state, PVOID id)
{
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    if(VirtualAlloc(id,si.dwPageSize,state,protect))
    {
        wprintf(L"Удачно");
    }
    else
    {
        wprintf(L"Не удачно");
    }
}

void FreeMemory(DWORD stateFree,PVOID id)
{
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    if(VirtualFree(id,si.dwPageSize,stateFree))
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