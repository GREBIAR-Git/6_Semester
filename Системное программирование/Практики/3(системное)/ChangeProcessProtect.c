PVOID InputIdProcess()
{
    PVOID id;
    wprintf(L"Введите id процесса: ");
    scanf("%p",&id);
    return id;
}

DWORD InputProtect()
{
    int protect;
    wprintf(L"\nВведите степень защиты(0 - NOACCESS 1-READONLY 2-READWRITE 3-EXECUTE 4-EXECUTE_READ 5-EXECUTE_READWRITE 6-GUARD 7-NOCACHE 8-WRITECOPY 9-EXECUTE_WRITECOPY): ");
    scanf("%d",&protect);
    switch (protect)
    {
    case 0:
        return PAGE_NOACCESS;
    case 1:
        return PAGE_READONLY;
    case 2:
        return PAGE_READWRITE;
    case 3:
        return PAGE_EXECUTE;
    case 4:
        return PAGE_EXECUTE_READ;
    case 5:
        return PAGE_EXECUTE_READWRITE;
    case 6:
        return PAGE_GUARD;
    case 7:
        return PAGE_NOCACHE;
    case 8:
        return PAGE_WRITECOPY;
    case 9:
        return PAGE_EXECUTE_WRITECOPY;
    default:
        return NULL;
    }
}

void ChangeProcessProtect(DWORD protect,PVOID id)
{
    MEMORY_BASIC_INFORMATION mbi;

    VirtualQuery(id, &mbi, sizeof(MEMORY_BASIC_INFORMATION));

    if(VirtualProtect(id, mbi.RegionSize, protect, NULL))
    {
        wprintf(L"Удачно;");
    }
    else
    {
        wprintf(L"Не удачно;");
    }
}