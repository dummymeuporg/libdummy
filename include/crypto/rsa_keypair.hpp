#pragma once

class RSAKeyPair {
    public:
        RSAKeyPair(const std::string&, const std::string&); // paths
        RSAKeyPair(EVP_PKEY*, EVP_PKEY*);
        RSAKeyPair(FILE*, FILE*);

};
