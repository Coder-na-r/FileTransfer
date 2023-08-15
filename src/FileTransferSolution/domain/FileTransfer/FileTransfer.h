#pragma once

#include "externalInterfaces/IFileSystem.hpp"
#include "externalInterfaces/IParseFile.hpp"
#include "externalInterfaces/IP2PNode.hpp"

#include <memory>

namespace Domain {

	using namespace Domain::FT::externalInterfaces;

	namespace FT {

		class FileTransfer {

		public:

			FileTransfer(IFileSystem* fileSystem, IParseFile* parseFile, IP2PNode* p2pNode);



		private:
			
			std::unique_ptr<IFileSystem> fileSystem;
			std::unique_ptr<IParseFile> parseFile;
			std::unique_ptr<IP2PNode> p2pNode;

		};

	}

}