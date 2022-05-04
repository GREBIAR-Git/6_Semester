#include <windows.h>
#include <stdio.h>

HBITMAP CopyBitmap(HBITMAP hbmOn) {
    HDC hdcSrc = CreateCompatibleDC(NULL);
    HDC hdcDst = CreateCompatibleDC(NULL);
    HBITMAP hbmNew;
    BITMAP bm, bm1;

    GetObject(hbmOn, sizeof(bm), &bm);
    SelectObject(hdcSrc, hbmOn);
    hbmNew = CreateBitmap( bm.bmWidth, bm.bmHeight, bm.bmPlanes,bm.bmBitsPixel,NULL);
    SelectObject(hdcDst, hbmNew);
    BitBlt(hdcDst, 0, 0, bm.bmWidth, bm.bmHeight, hdcSrc, 0, 0, SRCCOPY);

    DeleteDC(hdcSrc);
    DeleteDC(hdcDst);

    return hbmNew;
}

int main()
{
   	HANDLE hMapFile;
   	LPVOID hBmpMapFileAddr;

    HANDLE pic = CreateFile("0.bmp",GENERIC_READ, FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
    if(pic==NULL)
    {
        printf("1");
    }
   	hMapFile = CreateFileMapping(pic,NULL,PAGE_READWRITE,0,0,TEXT("kat"));
   	hBmpMapFileAddr = MapViewOfFile(hMapFile,FILE_MAP_ALL_ACCESS, 0,0,0);
       
    BITMAPFILEHEADER *bFileHeader= (BITMAPFILEHEADER*)hBmpMapFileAddr; 

    BITMAPINFO *bInfo=(BITMAPINFO*)((char*)hBmpMapFileAddr+14); 
    HDC hdc=CreateCompatibleDC(NULL);
    pic=CreateDIBitmap(hdc,&(bInfo->bmiHeader), 
    CBM_INIT,(char*)hBmpMapFileAddr+bFileHeader->bfOffBits, 
    bInfo,DIB_PAL_COLORS); 
    HDC hMemDC=CreateCompatibleDC(hdc); 
    SelectObject(hMemDC,pic); 
    StretchBlt(hdc,0,0,rect.right,rect.bottom,hMemDC, 
    0,0,bInfo->bmiHeader.biWidth,bInfo->bmiHeader.biHeight, 
    SRCCOPY); 
    ReleaseDC(NULL,hdc); 
    DeleteDC(hMemDC); 
    DeleteObject(pic);

	system("pause");
	UnmapViewOfFile(hBmpMapFileAddr);
	CloseHandle(hMapFile);
	return 0;
}