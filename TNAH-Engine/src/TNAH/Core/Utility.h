#pragma once
#include <string>
#include <filesystem>
#include <map>
#include <set>


namespace tnah::Utility {

    /**
     * @fn	static std::pair<std::string, std::string> SplitDirectoryAndFilePath(const std::string& filePath)
     *
     * @brief	Splits directory and file path
     *
     * @author	Dylan Blereau
     * @date	7/09/2021
     *
     * @param 	filePath	Full pathname of the file.
     *
     * @returns	A std::pair&lt;std::string,std::string&gt;
     */

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

    /**
     * @fn	static std::string FindFileNameFromPath(const std::string& filePath)
     *
     * @brief	Searches for the first file name from path
     *
     * @author	Dylan Blereau
     * @date	7/09/2021
     *
     * @param 	filePath	Full pathname of the file.
     *
     * @returns	The found file name from path.
     */

    static std::string FindFileNameFromPath(const std::string& filePath)
    {
        auto lastSlash = filePath.find_last_of("/\\");
        lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
        auto lastDot = filePath.rfind('.');
        auto count = lastDot == std::string::npos ? filePath.size() - lastSlash : lastDot - lastSlash;
        return filePath.substr(lastSlash, count);
    }

    /**
     * @fn	static std::pair<std::string, std::string> SplitFileNameAndExtension(const std::string& fileName)
     *
     * @brief	Splits file name and extension
     *
     * @author	Dylan Blereau
     * @date	7/09/2021
     *
     * @param 	fileName	Filename of the file.
     *
     * @returns	A std::pair&lt;std::string,std::string&gt;
     */

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

    /**
     * @fn	static std::string RelativePathFromAbsolute(const std::string& absolutePath)
     *
     * @brief	Relative path from absolute
     *
     * @author	Dylan Blereau
     * @date	7/09/2021
     *
     * @param 	absolutePath	Full pathname of the absolute file.
     *
     * @returns	A std::string.
     */

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

    /**
     * @fn	static std::string AbsolutePathFromRelative(const std::string& relativePath)
     *
     * @brief	Absolute path from relative
     *
     * @author	Dylan Blereau
     * @date	7/09/2021
     *
     * @param 	relativePath	Full pathname of the relative file.
     *
     * @returns	A std::string.
     */

    static std::string AbsolutePathFromRelative(const std::string& relativePath)
    {
        auto wd = std::filesystem::current_path();
        std::string out = wd.string() + "/" + relativePath;
        return out;
        
    }

    /**
     * @fn	template<typename T> static bool Contains(const std::list<T>& list, const T& searchItem)
     *
     * @brief	Query if the search item is contained within the given list
     *
     *@author Bryce Standley
     * 
     * @tparam	T	Generic type parameter.
     * @param 	list	  	The list.
     * @param 	searchItem	The search item.
     *
     * @returns	True if the object is in this list, false if not.
     */

    template<typename T>
    static bool Contains(const std::list<T>& list, const T& searchItem)
    {
        return (std::find(list.begin(), list.end(), searchItem) != list.end());
    }

	/**
	* @fn	template<typename T, typename S> static bool Contains(const std::list<T>& list, const S& searchItem)
	*
	* @brief	Query if the search item of a given type is contained within the given list. Used for sub-searches.
	*
	*@author Bryce Standley
	* 
	* @tparam	T	Generic type parameter.
	* @tparam	S	Generic type parameter.
	* @param 	list	  	The list.
	* @param 	searchItem	The search item.
	*
	* @returns	True if the object is in this list, false if not.
	*/

	template<typename T, typename S>
	static bool Contains(const std::list<T>& list, const S& searchItem)
    {
    	return (std::find(list.begin(), list.end(), searchItem) != list.end());
    }

    /**
     * @fn	template<typename T> static bool Contains(const std::vector<T>& vector, const T& searchItem)
     *
     * @brief	Query if the search item is contained within the given vector
     *
     * @tparam	T	Generic type parameter.
     * @param 	vector	  	The vector.
     * @param 	searchItem	The search item.
     *
     * @returns	True if the object is in this collection, false if not.
     */

    template<typename T>
    static bool Contains(const std::vector<T>& vector, const T& searchItem)
    {
        return (std::find(vector.begin(), vector.end(), searchItem) != vector.end());
    }

    /**
     * @fn	template<typename T> static bool Contains(const std::set<T>& set, const T& searchItem)
     *
     * @brief	Query if the search item is contained within the given set
     *
     * @tparam	T	Generic type parameter.
     * @param 	set		  	The set.
     * @param 	searchItem	The search item.
     *
     * @returns	True if the object is in this collection, false if not.
     */

    template<typename T>
    static bool Contains(const std::set<T>& set, const T& searchItem)
    {
        return (std::find(set.begin(), set.end(), searchItem) != set.end());
    }

    /**
     * @fn	template<typename T, typename J> static bool Contains(const std::map<T, J>& map, const T& searchItem)
     *
     * @brief	Query if the searchItem is contained within the given map
     *
     * @tparam	T	Generic type parameter.
     * @tparam	J	Generic type parameter.
     * @param 	map		  	The map.
     * @param 	searchItem	The search item.
     *
     * @returns	True if the object is in this collection, false if not.
     */

    template<typename T, typename J>
    static bool Contains(const std::map<T, J>& map, const T& searchItem)
    {
        return (std::find(map.begin(), map.end(), searchItem) != map.end());
    }
    
}
