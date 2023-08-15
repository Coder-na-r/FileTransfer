#pragma once

#include "externalInterfaces/IHashCalc.hpp"

#include <stdint.h>

namespace Data {

    namespace Hash {

        class Hash : public Data::externalInterfaces::IHashCalc {

        public:

            // crc32 hash implementation
            virtual uint32_t calcHash(const char* data, const uint64_t size) override
            {

                static bool isInitTable = false;

                if (!isInitTable) {

                    initTable__();

                    isInitTable = true;

                }

                uint32_t crc = 0xFFFFFFFFUL;

                for (uint64_t i(0); i < size; ++i) {

                    crc = crc_table[(crc ^ data[i]) & 0xFF] ^ (crc >> 8);
                }

                return crc ^ 0xFFFFFFFFUL;
            }

        private:

            static uint32_t crc_table[256];

            static void initTable__() {

                uint32_t crc;

                for (int i = 0; i < 256; i++)
                {
                    crc = i;
                    for (int j = 0; j < 8; j++)
                        crc = crc & 1 ? (crc >> 1) ^ 0xEDB88320UL : crc >> 1;

                    crc_table[i] = crc;
                }

            }

        };

    }

}