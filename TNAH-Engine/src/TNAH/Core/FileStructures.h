#pragma once
#include <unordered_map>
#include "Utility.h"

namespace tnah {
	//Structure of a file, contains a name and a extension
	struct File
	{
		std::string FileName;
		std::string Extension;
		std::string FullFile;

		File() = default;
		File(const std::string& name, const std::string& extension)
			:FileName(name), Extension(extension) { FullFile = FileName + Extension; }
		operator std::string&() { return FullFile; }
	};

	//Structure of a directory, contains a path
	typedef std::string Directory;

	//Structure of a Folder, contains a vector of files inside a root folder path
	struct Folder
	{
		std::vector<File> FilesInFolder;
		Directory FolderRoot;

		Folder() = default;
	};

	//Structure of a Project, contains a root directory and vector of sub directories
	struct Project
	{
		std::string Name;
		Directory RootDirectory;
		std::vector<Directory> SubDirectories;
		std::unordered_map<Directory, Folder> ProjectFiles;

		Project(const Directory& root)
			:RootDirectory(root) {}

		operator std::string&() { return RootDirectory; }
		operator std::vector<Directory>&() { return SubDirectories; }
		operator std::unordered_map<Directory, Folder>&() { return ProjectFiles; }
	};

	enum class RType
	{
		EMPTY, Unknown, Model, Image, Texture, Shader, Audio, Material
	};

	enum class RSubType
	{
		EMPTY, ILLEGAL_SUBTYPE,
		PBR_Material,
		Heightmap, UI_Image, Texture_2D, Texture_3D,
		Vertex_Shader, Fragment_Shader,
		Audio_Clip
	};

	struct ResourceType
	{
		RType Type = RType::EMPTY;
		RSubType SubType = RSubType::EMPTY;

		ResourceType() = default;
		ResourceType(const RType& type, const RSubType& subType)
			:Type(type)
		{
			if(type != RType::EMPTY && subType != RSubType::EMPTY)
			{
				switch (type)
				{
					case RType::Model: // No Subtype for models yet
						break;
					case RType::Image:
						if(subType != RSubType::Heightmap && subType != RSubType::UI_Image)
							SubType = RSubType::ILLEGAL_SUBTYPE;
						else
							SubType = subType;
						break;
					case RType::Texture:
						if(subType != RSubType::Texture_2D && subType != RSubType::Texture_3D)
							SubType = RSubType::ILLEGAL_SUBTYPE;
						else
							SubType = subType;
						break;
					case RType::Shader:
						if(subType != RSubType::Vertex_Shader && subType != RSubType::Fragment_Shader)
							SubType = RSubType::ILLEGAL_SUBTYPE;
						else
							SubType = subType;
						break;
					case RType::Audio:
						if(subType != RSubType::Audio_Clip)
							SubType = RSubType::ILLEGAL_SUBTYPE;
						else
							SubType = subType;
						break;
					case RType::Material:
						if(subType != RSubType::PBR_Material)
							SubType = RSubType::ILLEGAL_SUBTYPE;
						else
							SubType = subType;
						break;
					default:
						SubType = RSubType::EMPTY;
						break;
				}
			}
		}

		static RType GuessType(const std::string& fileExtension)
		{
			std::string modelGuess[] = {
				"fbx", "obj", "c4d", "3ds",
				"dae"
			};

			std::string imageGuess[] = {
				"jpg", "png", "tga", "gif", "tiff",
				"raw", "bmp", "jpeg", "tif"
			};

			std::string audioGuess[] = {
				"mp3", "wav"
			};

			std::string shaderGuess[] = {
				"glsl", "vert", "frag",
				"txt"
			};

			std::string materialGuess[] = {
				"material", "mat", "pbr"
			};

			for(auto s : modelGuess)
			{
				if(fileExtension.find(s) != std::string::npos)
					return RType::Model;
			}

			for(auto s : imageGuess)
			{
				if(fileExtension.find(s) != std::string::npos)
					return RType::Image;
			}
			for(auto s : audioGuess)
			{
				if(fileExtension.find(s) != std::string::npos)
					return RType::Audio;
			}
			for(auto s : shaderGuess)
			{
				if(fileExtension.find(s) != std::string::npos)
					return RType::Shader;
			}
			for(auto s : materialGuess)
			{
				if(fileExtension.find(s) != std::string::npos)
					return RType::Material;
			}

			return RType::Unknown;
		}
	};

	struct Resource
	{
		Directory RootDirectory = Directory("");
		Directory AbsoluteDirectory = Directory("");
		File FileName = File("", "");
		ResourceType Type = ResourceType(RType::EMPTY, RSubType::EMPTY);

		Resource() = default;
		Resource(const Directory& fileDirectory, const File& fileName, const ResourceType& resourceType)
			:RootDirectory(fileDirectory), FileName(fileName), Type(resourceType)
		{
			AbsoluteDirectory = RootDirectory + "/" + FileName.FullFile;
		}

		Resource(const std::string& fileDirectory, const std::string& fileName, const ResourceType& resourceType)
			:RootDirectory(fileDirectory), Type(resourceType)
		{
			auto n = Utility::SplitFileNameAndExtension(fileName);
			FileName.FileName = n.first;
			FileName.Extension = n.second;
			FileName.FullFile = fileName;
			AbsoluteDirectory = RootDirectory + "/" + fileName;
		}

		Resource(const std::string& filePath)
		{
			auto dirSplit = Utility::SplitDirectoryAndFilePath(filePath);
			RootDirectory = dirSplit.first;
			FileName.FullFile = dirSplit.second;
			auto nameSplit = Utility::SplitFileNameAndExtension(dirSplit.second);
			FileName.FileName = nameSplit.first;
			FileName.Extension = nameSplit.second;
			Type.Type = ResourceType::GuessType(FileName.Extension);
			AbsoluteDirectory = filePath;
		}


		
		
	};
}