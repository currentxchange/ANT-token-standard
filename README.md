# ANT Token Standards

The ANT (Antelope) Token Standards is an unofficial token contrac collection that seeks to replace the EOSIO.token contract on WAX, Telos, EOS + UX blockchains, and anyone else using [Antelope](https://github.com/AntelopeIO). I've nicknamed the collection of standards ANT as it's the beginning of Antelope and I'm writing this in Medellin, ANTioquia, Colombia. 

This standard, by default, provides features such as token transfers, many tokens per contract, token symbols unique to the contract, control over the RAM payer, the ability to close accounts (delete rows) with zero balance [new], and, of course, the process for creating and issuing tokens. The base implementation is split into a .cpp file (token.cpp) and a header file (token.hpp), and additional standards follow the same format with different file names.

> Here's more [information](https://developers.eos.io/welcome/v2.2/tutorials/eosio_token/#token) about the eosio.token standard this is based on. 

## Table of Tokenomics
 Each individual contract has a README which will explain how to use the contract. 

| Contract | Description |
| --- | --- |
| [token](https://github.com/currentxchange/ANT-token-standard/tree/main/src/token) |  Basic Token contract (Based on eosio.token) | 
| [atomic-stake](https://github.com/currentxchange/ANT-token-standard/tree/main/src/atomic-stake) | Stake Atomic Assets. Simple contract allows a single reward token for staking a collection of Atomic Assets NFTs | 


## Disclaimer of Liability

Please read this Disclaimer of Liability carefully before using any smart contracts located at https://github.com/currentxchange/ANT-token-standard (the "Contracts").

The Contracts are provided on an "as is" basis. Neither Douglas Butner, the original authors, Current X Change LLC, nor any other parties associated with the development and maintenance of the Contracts make any warranties or representations, express or implied, as to the suitability, completeness, quality, appropriateness, or operation of the Contracts.

The Contracts have not been audited for security vulnerabilities. As such, use of the Contracts is at your own risk. You are solely responsible for any damage, liability, or loss that you may incur as a result of or in connection with your use of the Contracts. You should make sure you understand the workings and intricacies of blockchain technologies before using the Contracts.

The Contracts contain code that has been ported from other repositories. It is your responsibility to respect any and all applicable licenses attached to that code. You must review these licenses and ensure that your use of the Contracts does not violate them.

By using the Contracts, you agree to this Disclaimer of Liability, and you waive any right to hold Douglas Butner, the original authors, Current X Change LLC, or any other parties associated with the Contracts liable for any damage, liability, or loss that you may incur in connection with your use of the Contracts.

YOUR USE OF THE CONTRACTS INCLUDING MODIFICATION AND USE CONSTITUTES YOUR AGREEMENT TO THIS DISCLAIMER OF LIABILITY.