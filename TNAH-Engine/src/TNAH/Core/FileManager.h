#pragma once

#include <string>

namespace tnah {

	/**
	 * @enum	FileError
	 *
	 * @brief	Values that represent file errors
	 */

	enum class FileError
	{
		None,
		UserClosed,
		PathInvalid
	};

	/**
	 * @struct	ActiveFile
	 *
	 * @brief	An active file.
	 *
	 * @author	Dylan Blereau
	 * @date	7/09/2021
	 */

	struct ActiveFile
	{
		std::string FileName;
		std::string FilePath;
		bool IsValid = false;
		FileError FileOpenError;

		/**
		 * @fn	ActiveFile() :FileName(""), FilePath(""), FileOpenError(FileError::None)
		 *
		 * @brief	Default constructor
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 */

		ActiveFile()
			:FileName(""), FilePath(""), FileOpenError(FileError::None)
		{}
	};

	/**
	 * @class	FileManager
	 *
	 * @brief	Manager for files.
	 *
	 * @author	Dylan Blereau
	 * @date	7/09/2021
	 */

	class FileManager
	{
	public:

		/**
		 * @fn	static bool FileManager::NewScene();
		 *
		 * @brief	Creates a new scene
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @returns	True if it succeeds, false if it fails.
		 */

		static bool NewScene();

		/**
		 * @fn	static bool FileManager::OpenScene();
		 *
		 * @brief	Opens the scene
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @returns	True if it succeeds, false if it fails.
		 */

		static bool OpenScene();

		/**
		 * @fn	static bool FileManager::OpenAudio();
		 *
		 * @brief	Opens the audio
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @returns	True if it succeeds, false if it fails.
		 */

		static bool OpenAudio();

		/**
		 * @fn	static bool FileManager::OpenMesh();
		 *
		 * @brief	Opens the mesh
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @returns	True if it succeeds, false if it fails.
		 */

		static bool OpenMesh();

		/**
		 * @fn	static bool FileManager::SaveScene();
		 *
		 * @brief	Saves the scene
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @returns	True if it succeeds, false if it fails.
		 */

		static bool SaveScene();

		/**
		 * @fn	static bool FileManager::SaveSceneAs();
		 *
		 * @brief	Saves the scene as
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @returns	True if it succeeds, false if it fails.
		 */

		static bool SaveSceneAs();

		/**
		 * @fn	static ActiveFile* FileManager::GetActiveFile();
		 *
		 * @brief	Gets active file
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @returns	Null if it fails, else the active file.
		 */

		static ActiveFile* GetActiveFile();

	private:

		/**
		 * @fn	static bool FileManager::CheckValidFile(const std::string& filePath);
		 *
		 * @brief	Check valid file
		 *
		 * @author	Dylan Blereau
		 * @date	7/09/2021
		 *
		 * @param 	filePath	Full pathname of the file.
		 *
		 * @returns	True if it succeeds, false if it fails.
		 */

		static bool CheckValidFile(const std::string& filePath);


	private:


		/** @brief	The active file */
		static ActiveFile* s_ActiveFile;

	};

}

