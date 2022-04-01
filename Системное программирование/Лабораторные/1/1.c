#include <stdio.h> 
#include <errno.h> 
#include <windows.h> 

#define BUF_SIZE 256
int main (int argc, char *argv []) 
{ 
    SetConsoleCP (1251);
    SetConsoleOutputCP(1251);
    char *typeCopy, *firstFile, *secondFile;
    while(1)
    {
        printf("Введите тип:");
        scanf("%s",&typeCopy);
        if(typeCopy=="Cpc")
        {
            FILE *in_file, *out_file; char rec 
            [BUF_SIZE]; size_t bytes_in, 
            bytes_out; 
            printf("Введите первый файл:");
            scanf("%s",&firstFile);
            in_file = fopen (firstFile, "rb"); 
            if (in_file == NULL) 
            { 
                perror (firstFile) ; 
            } 
            else
            {
                printf("Введите второй файл:");
                scanf("%s",&secondFile);
                out_file = fopen (secondFile, "wb"); 
                if (out_file == NULL) 
                { 
                    perror (secondFile) ; 
                } 
                else
                {
                    /* Обрабатываем входной файл по одной записи. */ 
                    while ( (bytes_in = fread (rec, 1, BUF_SIZE, in_file) ) > 0) 
                    { 
                        bytes_out = fwrite (rec, 1, bytes_in, out_file) ; 
                        if (bytes_out != bytes_in) 
                        { 
                            perror ("Неисправимая ошибка записи."); 
                        } 
                    } 
                    fclose (in_file); 
                }
                fclose (out_file); 
            }
        }
        else if(typeCopy=="CpW")
        {
            HANDLE hIn, hOut; 
            DWORD nIn, nOut; 
            CHAR Buffer [BUF_SIZE]; 
            printf("Введите первый файл:");
            scanf("%s",&firstFile);
            hIn = CreateFile (firstFile, GENERIC_READ, 0, NULL, 
            OPEN_EXISTING, 0, NULL); 
            if (hIn == INVALID_HANDLE_VALUE) 
            { 
                printf ("Нельзя открыть входной файл. Ошибка: %х\n", GetLastError ()); 
            } 
            else
            {
                printf("Введите второй файл:");
                scanf("%s",&secondFile);
                hOut = CreateFile (secondFile, GENERIC_WRITE, 0, NULL, 
                CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL); 
                if (hOut == INVALID_HANDLE_VALUE) 
                { 
                    printf ("Нельзя открыть выходной файл. Ошибка: %х\n", GetLastError () ) ; 
                } 
                else
                {
                    while (ReadFile (hIn, Buffer, BUF_SIZE, &nIn, NULL) && nIn > 0) 
                    { 
                        WriteFile (hOut, Buffer, nIn, &nOut, NULL); 
                        if (nIn != nOut) 
                        { 
                            printf ("Неисправимая ошибка записи: %x\n", GetLastError ()); 
                        } 
                    } 
                    CloseHandle (hIn); 
                }
                CloseHandle (hOut); 
            }
        }
        else if (typeCopy=="cpCF")
        {
            scanf("%s",&firstFile);
            scanf("%s",&secondFile);
            if (!CopyFile (firstFile, secondFile, FALSE)) 
            { 
                printf ("Ошибка CopyFile: %x\n", GetLastError ()); 
            } 
        }
        else if (typeCopy=="exit")
        {
            break;
        }
        else
        {
            printf ("Использование: Cрc file1 File2\n");
            printf ("Использование: CpW file1 File2\n"); 
            printf ("Использование: cpCF file1 file2\n"); 
        }
    }
} 