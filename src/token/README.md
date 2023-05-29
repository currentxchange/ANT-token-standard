# Token Contract 🐜
The Token contract is a generalized smart contract for the EOSIO and Antelope blockchains that enables the creation and management of tokens. It supports a variety of actions that allow users to create, issue, and transfer tokens, as well as get balance information.


This standard, by default, provides features such as token transfers, many tokens per contract, token symbols unique to the contract, control over the RAM payer, the ability to close accounts (delete rows) with zero balance, and, of course, the process for creating and issuing tokens. The base implementation is split into a .cpp file (token.cpp) and a header file (token.hpp), and additional standards follow the same format with different file names.

> Here's more [information](https://developers.eos.io/welcome/v2.2/tutorials/eosio_token/#token) about the eosio.token standard this is based on. 

## Features

- Fork of eosio.token contract
- Control over freeing RAM given to contract   
    **This is a change from the eosio.token standard**, previously only token owner with blank balance could clear their row. This feature was added so that a contract has the ability to maintain a more accurate list of holders. 
- Contract + owner can close accounts with zero balance, freeing up RAM
    - Be aware this means the token may dissapear from the wallet in user interfaces + next transfer will require RAM to be paid again
- More explicit error messages for easier debugging
- Differences in the authorization process for creating and issuing tokens

## Changes from eosio.token
- Ability to delete rows has been given to contract in addition to the token holder, allowing your contract to free up RAM for users.

## Basic Token for EOS, WAX, Telos, etc
- Find the slightly-upgraded token contract as src/token/token.cpp and src/token/token.hpp


# Token Standard Overview

## Actions

- `create`: Creates a new token with a specified issuer and maximum supply
- `issue`: Issues a specified quantity of tokens to the issuer account with an optional memo
- `retire`: Retires a specified quantity of tokens, reducing the supply with an optional memo
- `transfer`: Transfers a specified quantity of tokens from one account to another with an optional memo
- `open`: Opens a balance row for an account with zero balance for a specified symbol, with the specified RAM payer
- `close`: Closes a balance row for an account with zero balance for a specified symbol

## Data Structures

The ANT Token Standard uses two data structures: `account` and `currency_stats`. These data structures are stored in multi-index tables called `accounts` and `stats`, respectively.

### Account

The `account` structure represents a token balance for a specific account. It contains a single member:

- `balance`: An `eosio::asset` representing the balance of tokens held by the account. The `primary_key()` function for the `account` structure returns the raw symbol code of the `balance`, making each balance row unique within the `accounts` table.

```c++
struct [[eosio::table]] account {
    eosio::asset balance;
    uint64_t primary_key()const { return balance.symbol.code().raw(); }
};
```

### Currency Stats

The `currency_stats` structure holds information about a specific token, such as its current supply, maximum supply, and the issuer. It contains the following members:

- `supply`: An `eosio::asset` representing the current supply of the token.
- `max_supply`: An `eosio::asset` representing the maximum supply of the token that can be issued.
- `issuer`: An `eosio::name` representing the account that is allowed to issue and retire the token.

```c++
struct [[eosio::table]] currency_stats {
    eosio::asset supply;
    eosio::asset max_supply;
    eosio::name issuer;
    uint64_t primary_key()const { return supply.symbol.code().raw(); }
};
```

These data structures are used to store information about the token balances and token metadata. They are managed using the `eosio::multi_index` class, which enables the efficient querying and modification of the data stored in the multi-index tables. The `accounts` and `stats` tables are instances of the `eosio::multi_index` class, with the respective `account` and `currency_stats` structures as template arguments:

```c++
typedef eosio::multi_index< "accounts"_n, account > accounts;
typedef eosio::multi_index< "stat"_n, currency_stats > stats;
```

## How to Build and Deploy

### Prerequisites

- EOSIO software installed
- [EOSIO](https://github.com/EOSIO/eosio.cdt) or [Antelope](https://github.com/AntelopeIO/cdt/) cdt (Contract Development Toolkit) installed
- An EOSIO / Antelope account with enough resources (RAM, CPU, and NET) to deploy contract.

### Steps

1. Compile the contract:
Using EOSIO cdt
```bash
eosio-cpp -l eosio -o src/token/deploy/token.wasm src/token/token.cpp --abigen --contract token
```

Using Antelope cdt 
```bash
cdt-cpp -l eosio -o src/token/deploy/token.wasm src/token/token.cpp --abigen --contract token
```



2. Deploy the contract to the EOSIO blockchain:

```bash
cleos set contract <your_account_name> <path_to_contract_directory> token.wasm token.abi
```

Replace `<your_account_name>` with your EOSIO account name and `<path_to_contract_directory>` with the path to the directory containing the compiled contract files (`ant_token.wasm` and `ant_token.abi`).

3. Create a new token:

```bash
cleos push action <your_account_name> create '["<issuer_account_name>", "1000000000.0000 ANT"]' -p <your_account_name>
```

Replace `<your_account_name>` with your EOSIO account name and `<issuer_account_name>` with the desired issuer account name for the ANT token.

4. Issue tokens to the issuer account:

```bash
cleos push action <your_account_name> issue '["<issuer_account_name>", "1000.0000 ANT", "Initial issuance"]' -p <issuer_account_name>
```

Replace `<your_account_name>` with your EOSIO account name and `<issuer_account_name>` with the issuer account name for the ANT token.

Now, the ANT token is ready to use. You can perform actions like `transfer`, `retire`, `open`, and `close` as needed.

## License

This project is a fork from Antelope and is licensed under their original [MIT License](LICENSE) and additionally licensed under the [MIT License](LICENSE changes) by Current X Change LLC where applicable. 