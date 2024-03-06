//implement block class
#include "BlockNode.h"
//
// Constructor
//
Block::Block(int index, std::string prevHash, std::string hash, std::string nonce, std::vector<std::string> data)
    : prev_hash(prevHash), data(data), nonce(nonce), local_hash(hash)
{
    std::cout << "Initializing Block:" << index << " ---- Hash:" << hash.c_str() << std::endl;
}

int Block::getIndex(void)
{
    return this->index;
}

std::string Block::getPreviousHash(void)
{
    return this->prev_hash;
}

std::string Block::getHash(void)
{
    return this->local_hash;
}

std::vector<std::string> Block::getData(void)
{
    return this->data;
}

// Prints Block data
void Block::toString(void)
{
    std::string dataString;
    for (int i = 0; i < data.size(); i++)
    {
        dataString += data[i] + ", ";
    }
    std::cout << "\n-------------------------------" << std::endl;
    std::cout << "Block" << index << std::endl;
    std::cout << "\nHash:" << this->local_hash.c_str() << std::endl;
    std::cout << "Previous Hash:" << this->prev_hash.c_str() << std::endl;
    std::cout << "\nContents:" << dataString.c_str() << std::endl;
    std::cout << "----------------------------------" << std::endl;
}