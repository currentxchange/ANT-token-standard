# Atomic Stake

Atomic Stake is a smart contract for EOSIO blockchains that enables users to stake tokens and earn rewards. This repository houses the source code and documentation for this smart contract.

Atomic Stake is based on [ezstake](https://github.com/benjiewheeler/ezstake) 

It is designed to provide a secure, efficient, and straightforward method for earning rewards through token staking.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. You can call actions from [bloks](https://wax.bloks.io/) on main networks and some testnets.

### Prerequisites

To use Atomic Stake, you will need:

1. An EOSIO or Antelope-based blockchain.
2. An account on the blockchain.
3. EOSIO.CDT (Contract Development Toolkit).

### Installation

1. Clone the repository:
   ```
   git clone https://github.com/yourusername/Atomic-Stake.git
   ```

2. Navigate to the project directory:
   ```
   cd Atomic-Stake
   ```

3. Compile the smart contract using EOSIO.CDT:
   ```
   eosio-cpp -l eosio -o src/atomic-stake/deploy/aastake.wasm src/atomic-stake/aastake.cpp --abigen --contract aastake
   ```

4. Deploy the contract to the blockchain:
   ```
   cleos set contract stakeaccount ./aastake -p stakeaccount@active
   ```

## Usage

After deployment, you can interact with the Atomic Stake contract through the following actions:

### `stake`

The stake action is used when a user wants to lock up (or "stake") their tokens in the contract. This is usually done with the expectation of earning rewards over time. For example, if a user stakes "10.0000 EOS", they are essentially depositing this amount into the contract to start accumulating rewards based on the set rate for EOS.


**Parameters:**

- `from`: Account staking the tokens.
- `quantity`: The amount and type of token to stake.

**Example:**

```
cleos push action stakeaccount stake '["user", "10.0000 EOS"]' -p user@active
```

### `unstake`

The unstake action is used when a user wants to retrieve (or "unstake") their tokens from the contract. For instance, if a user unstakes "5.0000 EOS", they are withdrawing this amount from their staked balance. Note that this action might affect the user's accumulated rewards, depending on the specific rules set by the contract.

**Parameters:**

- `from`: Account unstaking the tokens.
- `quantity`: The amount and type of token to unstake.

**Example:**

```
cleos push action stakeaccount unstake '["user", "5.0000 EOS"]' -p user@active
```

### `claim`

The claim action is used when a user wants to collect their earned rewards. This can be done at any time and will transfer the accumulated rewards to the user's account. The rewards are based on the amount of staked tokens and the duration of staking, according to the reward rate set for each token.

**Parameters:**

- `owner`: Account claiming the rewards.

**Example:**

```
cleos push action stakeaccount claim '["user"]' -p user@active
```

### `addcol`

The addcol action is used to add a new Atomic Assets collection to the contract. This enables the tokens in the added collection to interact with the staking contract. For instance, if you have a collection of NFTs, adding your collection allows those NFTs to be staked.

**Parameters:**

- `account`: Account adding the collection.
- `collection_name`: The name of the Atomic Assets collection.

**Example:**

```
cleos push action stakeaccount addcol '["user", "collection_name"]' -p user@active
```

### `remcol`

The remcol action is used to remove an Atomic Assets collection from the contract. This means the tokens in the removed collection will no longer be able to interact with the staking contract.

**Parameters:**

- `account`: Account removing the collection.
- `collection_name`: The name of the Atomic Assets collection.

**Example:**

```
cleos push action stakeaccount remcol '["user", "collection_name"]' -p user@active
```

### `trans`

The trans action is used to transfer staked tokens from one account to another. For example, if a user transfers "5.0000 EOS" to another account, the staked balance and associated rewards will be transferred to the receiving account.

**Parameters:**

- `from`: Account transferring the tokens.
- `to`: Account receiving the tokens.
- `quantity`: The amount and type of token to transfer.

**Example:**

```
cleos push action stakeaccount trans '["user", "receiver", "5.0000 EOS"]' -p user@active
```

### `del`

The del action is used when a user wants to remove their account from the contract. This action unstakes all tokens and claims all rewards, effectively exiting the staking contract.

**Parameters:**

- `account`: Account to be deleted.

**Example:**

```
cleos push action stakeaccount del '["user"]' -p user@active
```

### `setrate`

The setrate action is used to set the reward rate for a specific token. This rate determines how much reward a user can earn per token staked over a certain period. For example, setting a rate of "0.05" for EOS means that for every EOS token staked, the user will earn 0.05 EOS as a reward per time period defined by the contract. This could be per day, per week, per month, etc., depending on the contract's settings.

**Parameters:**

- `token_symbol`: The symbol of the token.
- `rate`: The new reward rate.

**Example:**

```
cleos push action stakeaccount setrate '["EOS", "0.05"]' -p user@active
```

## Contributing

Please read [CONTRIBUTING.md](https://github.com/dougbutner/Ant-Token-Standard/blob/main/CONTRIBUTING.md) for details on our code of conduct, and the process for submitting pull requests.

## License

This project is licensed under the MIT License - see the [LICENSE.md](https://github.com/dougbutner/Ant-Token-Standard/blob/main/LICENSE.md) file for details.

## Acknowledgments

- Thanks to [benjiewheeler](https://github.com/benjiewheeler) for the initial work on this project.

## Notes on fork

The ability to freeze the contract was removed from this version. Ants can be opinionated. If you'd like to include that functionality, use Benjie's original [aastake](https://github.com/benjiewheeler/aastake).