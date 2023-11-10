#include "Clipboard.h"
#include "Base.h"

CClipboard::CClipboard() : m_opened(OpenClipboard(gBase.hwnd)) { }
CClipboard::~CClipboard()
{
    if (m_opened)
        CloseClipboard();
}

std::optional<std::string> CClipboard::CopyAscii()
{
    CClipboard cb;
    if (!cb.m_opened)
        return std::nullopt;

    HANDLE data_handle = GetClipboardData(CF_TEXT);
    if (data_handle == NULL)
        return std::nullopt;

    void* data_ptr = GlobalLock(data_handle);
    std::string result = (const char*)data_ptr;
    GlobalUnlock(data_ptr);
    
    return result;
}

void CClipboard::Paste(const char* text)
{
    CClipboard cb;
    if (!cb.m_opened)
        return;
    
    size_t len = strlen(text) + 1; // Include the null-terminator
    HANDLE copy_handle = GlobalAlloc(GMEM_MOVEABLE, len);
    if (copy_handle == NULL)
        return;
    
    void* copy_buffer = GlobalLock(copy_handle);
    memcpy(copy_buffer, text, len);
    GlobalUnlock(copy_buffer);

    EmptyClipboard();
    SetClipboardData(CF_TEXT, copy_handle); // This frees copy_handle for us
}