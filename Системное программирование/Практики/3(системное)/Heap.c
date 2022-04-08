LPVOID heapMemory;
HANDLE heap;
void NewHeap()
{
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    if(heap == NULL)
    {
        heap = HeapCreate(HEAP_NO_SERIALIZE,si.dwPageSize,si.dwPageSize);
        if(heap!=NULL)
        {
            wprintf(L"Успех\n");
        }
        else
        {
            wprintf(L"Неудача\n");
        }
    }
    else
    {
        wprintf(L"Куча уже создана\n");
    }
}

void DelHeap()
{
    if (heap != NULL) 
    { 
        if(HeapDestroy(heap)!=0)
        {
            wprintf(L"Успех\n");
            heap = NULL;
        }
        else
        {
            wprintf(L"Неудача\n");
        }
    } 
    else
    {
        wprintf(L"Куча ещё не создана\n");
    }
}

void FreeHeap()
{
    if(heap!=NULL)
    {
        if(HeapFree(heap,0,heapMemory)!=0)
        {
            wprintf(L"Успех\n");
        }
        else
        {
            wprintf(L"Неудача\n");
        }
    }
    else
    {
        wprintf(L"Куча ещё не создана\n");
    }
}

void AllocHeap()
{
    if (heap != NULL) 
    { 
        heapMemory=HeapAlloc(heap,0,1024);
        if(heapMemory!=NULL)
        {
            wprintf(L"Успех\n");
        }
        else
        {
            wprintf(L"Неудача\n");
        }
    } 
    else
    {
        wprintf(L"Куча ещё не создана\n");
    }
}