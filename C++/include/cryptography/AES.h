#pragma once

#include <PCH.h>

#include "StateArray.h"


namespace QPP {
    class AES {
    public:

    /**
     * Encrypt a string called plain text using a string key.
     *
     * @param plain_text
     * @param key
     * @param key_size
     * @return
     */
    std::string encrypt(std::string& plain_text, std::string& key, int key_size);



    private:

    };


}
