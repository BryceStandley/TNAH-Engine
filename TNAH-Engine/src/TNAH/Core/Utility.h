#pragma once
#include <string>
#include <filesystem>
#include <map>
#include <set>


namespace tnah::Utility {

    static std::pair<std::string, std::string> SplitDirectoryAndFilePath(const std::string& filePath)
    {
        std::pair<std::string, std::string> split;

        auto lastSlash = filePath.find_last_of("/\\");
        lastSlash = lastSlash == std::string::npos ? 0 : lastSlash;

        split.first = filePath.substr(0, lastSlash + 1);
        auto count = filePath.size() - 1;
        split.second = filePath.substr(lastSlash + 1, count);
        return split;
        
    }

    static std::string FindFileNameFromPath(const std::string& filePath)
    {
        auto lastSlash = filePath.find_last_of("/\\");
        lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
        auto lastDot = filePath.rfind('.');
        auto count = lastDot == std::string::npos ? filePath.size() - lastSlash : lastDot - lastSlash;
        return filePath.substr(lastSlash, count);
    }

    static std::pair<std::string, std::string> SplitFileNameAndExtension(const std::string& fileName)
    {
        auto dot = fileName.find_first_of(".");
        std::pair<std::string, std::string> split;
        split.first = fileName.substr(0,dot);
        auto count = fileName.size() - 1;
        auto start = dot + 1;
        split.second = fileName.substr(start, count);
        return split;
    }



    static std::string RelativePathFromAbsolute(const std::string& absolutePath)
    {
        
        auto wd = std::filesystem::current_path();

        auto relative = absolutePath.find(wd.string());
        if(relative != std::string::npos)
        {
            return std::string(absolutePath.substr(relative, wd.string().length()));
        }
        return "null";
        
    }

    static std::string AbsolutePathFromRelative(const std::string& relativePath)
    {
        auto wd = std::filesystem::current_path();
        std::string out = wd.string() + "/" + relativePath;
        return out;
        
    }

    template<typename T>
    static bool Contains(const std::list<T>& list, const T& searchItem)
    {
        return (std::find(list.begin(), list.end(), searchItem) != list.end());
    }
   
    template<typename T>
    static bool Contains(const std::vector<T>& vector, const T& searchItem)
    {
        return (std::find(vector.begin(), vector.end(), searchItem) != vector.end());
    }

    template<typename T>
    static bool Contains(const std::set<T>& set, const T& searchItem)
    {
        return (std::find(set.begin(), set.end(), searchItem) != set.end());
    }

    template<typename T, typename J>
    static bool Contains(const std::map<T, J>& map, const T& searchItem)
    {
        return (std::find(map.begin(), map.end(), searchItem) != map.end());
    }
    
}
