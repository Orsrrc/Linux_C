// declar Block Chain define
#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>
#include "json.hh"
#include "Block.h"
#include "hash.h"
#include "statusCode.h"

class BlockChain
{
public:
    BlockChain(int genesis = 1)
    {
        ;
    }

    Block getBlock(int index);
    // getBlock(string hash); //not implemented
    int getNumOfBlocks(void);
    int addBlock(int index, std::string prevHash, std::string hash, std::string nonce, std::vector<std::string> &merkle);
    std::string getLatestBlockHash(void);
    // void toString(void);
    std::string toJSON(void);
    int replaceChain(std::string chain);

    //
    // block noded stroes message method
    //
    static int number_of_block;
    std::string random_string();                            // generate random string
    std::string generate_hash_SHA256(std::string toHasing); // generate hash

    //
    // the action of BlockChain
    //
    void addNode(std::string new_data);              // add block(node) to chain
    void traverseBlockChain(BlockChain &chain);      // traverse the Blockchain
    void get_number_of_block();                      // return ths number of block
    void check_chain_consistency(BlockChain &chain); // check if the data for each block has been modified
    void recalulcateChain(BlockChain &chain);        // recalculate hashes for each block of the chain after data injection into a data block
    void inject_data_in_Block(BlockChain &chain,
                              int injectToBlock,
                              std::string injectData); // data injection in certain block of chain

private:
    std::vector<std::unique_ptr<Block>> blockchain; // vector that is the blockchain
    Block *previous;
    Block *head;
};
