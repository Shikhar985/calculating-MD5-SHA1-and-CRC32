#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstring>
#include <openssl/md5.h>
#include <openssl/sha.h>
#include <zlib.h>

using namespace std;

void calc_checksums(const char* filename) {
    ifstream file(filename, ios::binary);
    if (!file) {
        cerr << "Error: failed to open file " << filename << endl;
        return;
    }

    stringstream buffer;
    buffer << file.rdbuf();

    
    unsigned char md5[MD5_DIGEST_LENGTH];
    MD5((unsigned char*)buffer.str().c_str(), buffer.str().length(), md5);
    stringstream md5_ss;
    for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
        md5_ss << hex << setw(2) << setfill('0') << (int)md5[i];
    }
    string md5_str = md5_ss.str();

   
    unsigned char sha1[SHA_DIGEST_LENGTH];
    SHA1((unsigned char*)buffer.str().c_str(), buffer.str().length(), sha1);
    stringstream sha1_ss;
    for (int i = 0; i < SHA_DIGEST_LENGTH; i++) {
        sha1_ss << hex << setw(2) << setfill('0') << (int)sha1[i];
    }
    string sha1_str = sha1_ss.str();

  
    uLong crc32 = crc32(0L, Z_NULL, 0);
    crc32 = crc32(buffer.str().c_str(), buffer.str().length());
    stringstream crc32_ss;
    crc32_ss << hex << crc32;
    string crc32_str = crc32_ss.str();


    cout << "MD5: " << md5_str << endl;
    cout << "SHA1: " << sha1_str << endl;
    cout << "CRC32: " << crc32_str << endl;
}

int main() {
    const char* filenames[] = {"file1.txt", "file2.txt", "file3.txt", "file4.txt", "file5.txt",
                               "file6.txt", "file7.txt", "file8.txt", "file9.txt", "file10.txt"};

    for (const char* filename : filenames) {
        cout << "Calculating checksums for " << filename << "..." << endl;
        calc_checksums(filename);
        cout << endl;
    }

    return 0;
}

