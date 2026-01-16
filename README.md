# 🔗 Blockchain Implementation in C

A comprehensive educational blockchain implementation in C that demonstrates the fundamental concepts behind cryptocurrencies like Bitcoin and Ethereum.

## ✨ Features

- **SHA-256 Cryptographic Hashing** - Secure block hashing using OpenSSL
- **Proof-of-Work Mining** - Adjustable difficulty level mining algorithm
- **Merkle Tree Implementation** - Efficient transaction verification structure
- **Multi-Transaction Blocks** - Support for multiple transactions per block
- **Chain Validation** - Complete integrity checking and tamper detection
- **Transaction System** - Simple wallet-to-wallet transaction model

## 🎯 What You'll Learn

This project demonstrates:
- How blockchain data structures work at a low level
- Cryptographic hashing and its role in security
- Proof-of-work consensus mechanism
- Merkle trees for efficient data verification
- Chain immutability and tamper detection
- Why modifying historical blocks is computationally infeasible

## 🚀 Getting Started

### Prerequisites

You'll need:
- GCC compiler
- OpenSSL development libraries

**Install OpenSSL:**

```bash
# Ubuntu/Debian
sudo apt-get install libssl-dev

# macOS (usually pre-installed, or use Homebrew)
brew install openssl

# Fedora/RHEL
sudo dnf install openssl-devel
```

### Compilation

```bash
gcc -o blockchain blockchain.c -lssl -lcrypto
```

### Running

```bash
./blockchain
```

## 📖 How It Works

### Block Structure

Each block contains:
- **Index** - Position in the chain
- **Timestamp** - When the block was created
- **Transactions** - Array of transactions (sender, receiver, amount)
- **Merkle Root** - Root hash of the transaction Merkle tree
- **Previous Hash** - Hash of the previous block (creates the chain)
- **Hash** - This block's hash (calculated from all above data)
- **Nonce** - Number used for proof-of-work mining

### Mining Process

The mining algorithm implements proof-of-work:

1. Combine block data (index, timestamp, merkle root, previous hash, nonce)
2. Calculate SHA-256 hash
3. Check if hash starts with required number of zeros (difficulty)
4. If not, increment nonce and repeat
5. When valid hash found, block is "mined"

**Example:** With difficulty 4, the hash must start with `0000...`

### Merkle Tree

Transactions are organized in a binary Merkle tree:

```
        Root Hash
         /    \
        /      \
    Hash01    Hash23
     /  \      /  \
   H0   H1   H2   H3
   |    |    |    |
  Tx0  Tx1  Tx2  Tx3
```

Benefits:
- Verify single transaction without downloading all data
- Efficient proof that a transaction exists in a block
- Any transaction change invalidates the root hash

### Chain Validation

The validation process checks:
- Each block's hash is correctly calculated
- Each hash meets the difficulty requirement
- Merkle root matches the transactions
- Each block correctly references the previous block's hash
- No tampering has occurred

## 🔧 Configuration

Adjust these constants in the code:

```c
#define DIFFICULTY 4           // Mining difficulty (number of leading zeros)
#define MAX_TRANSACTIONS 8     // Maximum transactions per block
```

**Warning:** Increasing difficulty exponentially increases mining time!


## 🛡️ Security Demonstration

The program demonstrates blockchain's security by:

1. **Showing valid chain** - All blocks properly linked and validated
2. **Tampering attempt** - Modifies a transaction amount
3. **Detection** - Validation fails due to Merkle root mismatch

This proves why blockchain is tamper-resistant: changing any data invalidates the block and breaks the chain.

## 📚 Resources

To learn more about blockchain technology:
- [Bitcoin Whitepaper](https://bitcoin.org/bitcoin.pdf) by Satoshi Nakamoto
- [Mastering Bitcoin](https://github.com/bitcoinbook/bitcoinbook) by Andreas Antonopoulos
- [Ethereum Documentation](https://ethereum.org/en/developers/docs/)

## 🤝 Contributing

Contributions, issues, and feature requests are welcome! Feel free to fork and improve.

## 👨‍💻 Author

AKSHIT JOSHI - [Your GitHub](https://github.com/akshitj11)

---

**⭐ If you found this helpful, please star the repo!**
