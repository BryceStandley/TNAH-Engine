#pragma once

#include <string>

namespace tnah {

	enum class FileError
	{
		None,
		UserClosed,
		PathInvalid
	};
	
	struct ActiveFile
	{
		std::string FileName;
		std::string FilePath;
		bool IsValid = false;
		FileError FileOpenError;

		ActiveFile()
			:FileName(""), FilePath(""), FileOpenError(FileError::None)
		{}
	};

	class FileManager
	{
	public:
		static bool NewScene();
		static bool OpenScene();
		static bool OpenAudio();
		static bool SaveScene();
		static bool SaveSceneAs();

		static ActiveFile* GetActiveFile();

	private:
		static bool CheckValidFile(const std::string& filePath);


	private:
		static ActiveFile* s_ActiveFile;

	};

}

