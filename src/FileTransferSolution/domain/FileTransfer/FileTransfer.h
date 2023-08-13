#pragma once

#include "externalInterfaces/IFileSystem.hpp"
#include "externalInterfaces/IParseFile.hpp"
#include "externalInterfaces/IP2PNode.hpp"

namespace Domain {

	using namespace Domain::FT::externalInterfaces;

	namespace FT {

		class FileTransfer {

		public:

			FileTransfer(IFileSystem* fileSystem, IParseFile* parseFile, IP2PNode* p2pNode);



		private:
			
			IFileSystem* fileSystem;
			IParseFile* parseFile;
			IP2PNode* p2pNode;

		};

	}

}