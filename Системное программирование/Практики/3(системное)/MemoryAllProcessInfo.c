char * GetState(DWORD state)
{
    switch (state)
    {
        case MEM_COMMIT:
            return "COMMIT";
            break;
        case MEM_FREE:
            return "FREE";
            break;
        case MEM_RESERVE:
            return "RESERVE";
            break;
        default:
            return "UNKNOWN";
            break;
    }
}

char * GetType(DWORD type)
{
    switch (type)
    {
        case MEM_IMAGE:
            return "IMAGE";
            break;
        case MEM_MAPPED:
            return "MAPPED";
            break;
        case MEM_PRIVATE:
            return "PRIVATE";
            break;
        default:
            return "UNKNOWN";
            break;
    }
}

char * GetProtect(DWORD protect)
{
    switch (protect)
    {
        case PAGE_NOACCESS:
            return "NOACCESS";
            break;
        case PAGE_READONLY :
            return "READONLY";
            break;
        case PAGE_READWRITE:
            return "READWRITE";
            break;
        case PAGE_EXECUTE:
            return "EXECUTE";
            break;
        case PAGE_EXECUTE_READ:
            return "EXECUTE_READ";
            break;
        case PAGE_EXECUTE_READWRITE:
            return "EXECUTE_READWRITE";
            break;
        case PAGE_GUARD:
            return "GUARD";
            break;
        case PAGE_NOCACHE:
            return "NOCACHE";
            break;
        case PAGE_WRITECOPY:
            return "WRITECOPY";
            break;
        case PAGE_EXECUTE_WRITECOPY:
            return "EXECUTE_WRITECOPY";
            break;
        default:
            return "UNKNOWN";
            break;
    }
}

void PrintAllProcess()
{
    unsigned short columnWidth = 20;

    printf("%*s\t", columnWidth, "Base Address (0x)");
    printf("%*s\t", columnWidth, "Type");
    printf("%*s\t", columnWidth, "State");
    printf("%*s\t", columnWidth, "Protect");
    printf("\n");

    MEMORY_BASIC_INFORMATION mbi;
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    LPCVOID offset=0;
    while(offset< si.lpMaximumApplicationAddress)
    {
        VirtualQuery((LPCVOID)(0 + offset), &mbi, sizeof(MEMORY_BASIC_INFORMATION));
        printf("%*lx\t", columnWidth, mbi.BaseAddress);
        printf("%*s\t", columnWidth, GetType(mbi.Type));
        printf("%*s\t", columnWidth, GetState(mbi.State));
        printf("%*s\t", columnWidth, GetProtect(mbi.Protect));
        printf("\n");        
        offset+=mbi.RegionSize;
    }
}