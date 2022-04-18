#include <iostream> 
using namespace std;
#include <errno.h> 
#include <windows.h> 
#define BUF_SIZE 256
int main()
{
    string typeCopy;
    char firstFile[100], secondFile[100];
    cout << "use: Cpc file1 file2\n";
    cout << "use: CpW file1 file2\n"; 
    cout << "use: cpCF file1 file2\n"; 

    cout << "Enter a string: "; 
    getline(cin, typeCopy);
    if(typeCopy=="Cpc")
    {
        FILE *in_file, *out_file; 
        char rec[BUF_SIZE]; 
        size_t bytes_in, bytes_out; 
        cout << "1 file: "; 
        cin >> firstFile;
        in_file = fopen (firstFile, "rb"); 
        if (in_file == NULL) 
        { 
            perror (firstFile) ; 
        } 
        else
        {
            cout << "2 file: "; 
            cin >> secondFile;
            out_file = fopen (secondFile, "wb"); 
            if (out_file == NULL) 
            { 
                perror (secondFile) ; 
            } 
            else
            {
                while ( (bytes_in = fread (rec, 1, BUF_SIZE, in_file) ) > 0) 
                { 
                    bytes_out = fwrite (rec, 1, bytes_in, out_file) ; 
                    if (bytes_out != bytes_in) 
                    { 
                        perror ("Error."); 
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
        cout << "1 file: "; 
        cin >> firstFile;
        hIn = CreateFile (firstFile, GENERIC_READ, 0, NULL, 
        OPEN_EXISTING, 0, NULL); 
        if (hIn == INVALID_HANDLE_VALUE) 
        { 
            wprintf (L"Error: %х\n", GetLastError ()); 
        } 
        else
        {
            cout << "2 file: "; 
            cin >> secondFile;
            hOut = CreateFile (secondFile, GENERIC_WRITE, 0, NULL, 
            CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL); 
            if (hOut == INVALID_HANDLE_VALUE) 
            { 
                wprintf (L"Error: %х\n", GetLastError () ) ; 
            } 
            else
            {
                while (ReadFile (hIn, Buffer, BUF_SIZE, &nIn, NULL) && nIn > 0) 
                { 
                    WriteFile (hOut, Buffer, nIn, &nOut, NULL); 
                    if (nIn != nOut) 
                    { 
                        wprintf (L"Error: %x\n", GetLastError ()); 
                    } 
                } 
                CloseHandle (hIn); 
            }
            CloseHandle (hOut); 
        }
    }
    else if (typeCopy=="cpCF")
    {
        cout << "1 file: "; 
        cin >> firstFile;
        cout << "2 file: "; 
        cin >> secondFile;
        if (!CopyFile (firstFile, secondFile, FALSE)) 
        { 
            wprintf (L"Error CopyFile: %x\n", GetLastError ()); 
        }
    }
    else
    {
        wprintf (L"use: Cpc file1 File2\n");
        wprintf (L"use: CpW file1 File2\n"); 
        wprintf (L"use: cpCF file1 file2\n"); 
    }
}