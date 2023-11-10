#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <string>
#include <optional>

class CClipboard
{
public:
    static std::optional<std::string> CopyAscii();
    static void Paste(const char* text);

protected:
    CClipboard();
    ~CClipboard();

private:
    const bool m_opened;
};