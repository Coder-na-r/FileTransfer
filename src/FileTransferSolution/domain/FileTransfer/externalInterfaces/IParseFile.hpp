#pragma once

namespace Domain {

	namespace FT {

		namespace externalInterfaces {

			class IParseFile {

			public:

				enum class Type
				{
					INPUT,
					OUTPUT,
					ERROR,
				};

			};

		}

	}

}