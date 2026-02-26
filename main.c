#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <openssl/sha.h>

#define MAX_DATA 256
#define DIFFICULTY 4
#define MAX_TRANSACTION 8

// TRANSN STRUCT

typedef struct{
    char from[64];
    char to[64];
    double amount;
    time_t timestamp;
} Transaction;

//merkletree
typedef struct MerkleNode {
    char hash[SHA256];
    struct MerkleNode* left;
    struct MerkleNode* right;
}MerkleNode;

//block struct for merkle root
typedef struct Block{
    int index;
    time_t timestamp;
    Transaction transactions[MAX_TRANSCATIONS];
    int tx_count;
    char merkle_root[SHA256_DIGEST_LENGTH*2+1]

}
/*
Input: "Hello Blockchain"
   ↓
SHA-256 Algorithm
   ↓
Binary Output (32 bytes):
[185, 77, 39, 185, 147, 77, 62, 8, 165, ...]
   ↓
Convert to Hex String (64 chars):
"b94d27b9934d3e08a52e..."
   ↓
Add Null Terminator (65 total):
"b94d27b9934d3e08a52e...\0"

Array allocation:
char merkle_root[SHA256_DIGEST_LENGTH * 2 + 1];
                      32          * 2   + 1
                      └─────┬─────┘     └─ null terminator
                         64 hex chars
*/

