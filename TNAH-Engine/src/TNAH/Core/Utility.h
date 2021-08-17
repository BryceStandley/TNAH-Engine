#pragma once
#include <string>

namespace tnah::utility {

    static std::string FindFileNameFromPath(const std::string& filePath)
    {
        auto lastSlash = filePath.find_last_of("/\\");
        lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
        auto lastDot = filePath.rfind('.');
        auto count = lastDot == std::string::npos ? filePath.size() - lastSlash : lastDot - lastSlash;
        return filePath.substr(lastSlash, count);
    }

    static std::string WStringToString(const std::wstring& str)
    {
        std::string out(str.begin(), str.end());
        return out;
    }


    
}
