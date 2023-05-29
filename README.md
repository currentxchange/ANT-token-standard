# ANT Token Standards

The ANT (Antelope) Token Standards is an unofficial token contrac collection that seeks to replace the EOSIO.token contract on WAX, Telos, EOS + UX blockchains, and anyone else using [Antelope](https://github.com/AntelopeIO). I've nicknamed the collection of standards ANT as it's the beginning of Antelope and I'm writing this in Medellin, ANTioquia, Colombia. 

This standard, by default, provides features such as token transfers, many tokens per contract, token symbols unique to the contract, control over the RAM payer, the ability to close accounts (delete rows) with zero balance [new], and, of course, the process for creating and issuing tokens. The base implementation is split into a .cpp file (token.cpp) and a header file (token.hpp), and additional standards follow the same format with different file names.

> Here's more [information](https://developers.eos.io/welcome/v2.2/tutorials/eosio_token/#token) about the eosio.token standard this is based on. 

## Table of Tokenomics

