#pragma once

#include "externalInterfaces/IFileSystem.hpp"
#include "Entity/DirInfo.hpp"

#include <stdint.h>

#include <filesystem>
#include <vector>
#include <string>

using Domain::FT::Entity::DirInfo;

namespace Data {

	namespace FS {

		class FileSystem : public Domain::FT::externalInterfaces::IFileSystem {

		private:

			FileSystem() = delete;
			~FileSystem() = delete;

		public:

			static std::string getSeparator() {
				return std::filesystem::path("/").generic_string();
			}

			static std::string getWorkDir() {
				return std::filesystem::current_path().generic_string();
			}

			static std::string getFilename(const std::string& name) {
				std::filesystem::path path_(name);

				return path_.filename().generic_string();
			}

			static std::string getDirWithoutFilename(const std::string& name) {
				std::filesystem::path path_(name);

				return path_.parent_path().generic_string();
			}

			static bool exists(const std::string& name) {
				return std::filesystem::exists(name);
			}

			static std::string unitePaths(const std::string& path1, const std::string& path2) {

				std::filesystem::path _path(path1);

				if (path1 == "") { _path = getWorkDir(); }

				return (_path / path2).generic_string();
			}

			static bool isDirectory(const std::string& name) {
				return std::filesystem::is_directory(name);
			}

			static uint64_t sizeDir(const std::string directory) {

				uint64_t filesSize = 0;

				for (const auto& it : std::filesystem::recursive_directory_iterator(directory))
				{
					if (it.is_regular_file())
						filesSize += it.file_size();
				}

				return filesSize;
			}

			static DirInfo getDirInfo(const std::string directory) {

				DirInfo dirInfo;

				if (!isDirectory(directory)) {
					dirInfo.files.push_back(directory);
					dirInfo.size += std::filesystem::file_size(directory);
					return dirInfo;

				}

				for (const auto& it : std::filesystem::directory_iterator(directory))
				{
					if (it.is_regular_file()) {
						dirInfo.files.push_back(it.path().filename().generic_string());
						dirInfo.size += it.file_size();
					}
					else
					{
						dirInfo.directories.push_back((it.path().filename() / "").generic_string());
						getDirInfo__(directory + getSeparator(),
							("" / it.path().filename() / "").generic_string(),
							dirInfo);
					}
				}

				return dirInfo;
			}
			
			static void createDirs(const std::string& rootDir, const DirInfo& dirInfo) {

				std::filesystem::path path_ = rootDir;

				if (rootDir == "") { path_ = getWorkDir(); }

				std::string path = (path_ / "").generic_string();

				for (std::string dir : dirInfo.directories)
				{
					std::filesystem::create_directory(path + dir);
				}

				return;
			}

			static void createDir(const std::string& rootDir, const std::string& newDir) {

				std::filesystem::path path_ = rootDir;

				if (rootDir == "") { path_ = getWorkDir(); }

				std::string path = (path_ / "").generic_string();

				std::filesystem::create_directory(path + newDir);

				return;
			}

		private:

			static DirInfo getDirInfo__(const std::string directory, const std::string& relative, DirInfo& dirInfo) {



				for (const auto& it : std::filesystem::directory_iterator(directory + getSeparator() + relative))
				{
					if (it.is_regular_file()) {
						dirInfo.files.push_back((relative / it.path().filename()).generic_string());
						dirInfo.size += it.file_size();
					}
					else
					{
						dirInfo.directories.push_back((relative / it.path().filename() / "").generic_string());
						getDirInfo__(directory + getSeparator(),
							(relative / it.path().filename() / "").generic_string(),
							dirInfo);
					}
				}

				return dirInfo;

			}

		};

	}

}