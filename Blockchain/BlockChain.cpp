// implement Block Chain define
#include "BlockChain.h"

// If integer passed into constructor is 0, it the first node and creates the genesis block
BlockChain::BlockChain(int genesis)
{
    if (genesis == 0)
    {
        std::vector<std::string> v;
        v.push_back("Genesis Block!");
        // string header = to_string(0) + string("00000000000000") + getMerkleRoot(v);
        long long hash_nonce_pair = 0; // findHash(0,string("00000000000000"),v); no implemented
        /*
        this -> blockchain.push_back(std::make_unique<Block>(0,std::string("00000000000000"),
                                    hash_nonce_pair.first,
                                    hash_nonce_pair.second,
                                    v));
        */
        std::cout << "Created blockchain success!\n"
                  << std::endl;
    }
}
// Gets block based on the index
Block BlockChain::getBlock(int index)
{
    for (int i = 0; i < blockchain.size(); i++)
    {
        if (blockchain[i]->getIndex() == index)
        {
            return *(blockchain[i]);
        }
    }
    throw std::invalid_argument("Index does not exist.");
}

// returns number of blocks
int BlockChain::getNumOfBlocks(void)
{
    return this->blockchain.size();
}

// checks whether data fits with the right hash -> add block
int BlockChain::addBlock(int index, std::string prevHash, std::string hash, std::string nonce, std::vector<std::string> &merkle)
{
    std::string header = std::to_string(index) + prevHash + getMerkleRoot(merkle) + nonce;
    if ((!sha256(header).compare(hash)) && (hash.substr(0, 2) == "00") && (index == blockchain.size()))
    {
        std::cout << "Block hashes match --- Adding Block" << hash.c_str() << std::endl;
        this->blockchain.push_back(std::make_unique<Block>(index, prevHash, hash, nonce, merkle));
        return 1;
    }
    std::cout << "Hash doesn't match criteria\n";
    return 0;
}

// returns hash of the latest block, used for finding the previousHash when mining new block
std::string BlockChain::getLatestBlockHash(void)
{
    return this->blockchain[blockchain.size() - 1]->getHash();
}

// returns JSON string of JSON - used to send to network
/*
string BlockChain::toJSON()
{
    json j;
    j["length"] = this->blockchain.size();
    for (int i = 0; i < this->blockchain.size(); i++)
    {
        j["data"][this->blockchain[i]->getIndex()] = this->blockchain[i]->toJSON();
    }
    return j.dump(3);
}
*/

// replaces Chain with new chain represented by a JSON, used when node sends new blockchain
/*
int BlockChain::replaceChain(json chain)
{
    // remove all blocks except for the first block
    while (this->blockchain.size() > 1)
    {
        this->blockchain.pop_back();
    }
    for (int a = 1; a < chain["length"].get<int>(); a++)
    {
        auto block = chain["data"][a];
        std::vector<std::string> data = block["data"].get<std::vector<std::string>>();
        this->addBlock(block["index"], block["previousHash"], block["hash"], block["nonce"], data);
    }
    return 1;
}
*/