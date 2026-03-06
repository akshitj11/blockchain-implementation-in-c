#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <openssl/sha.h>

#define MAX_DATA 256
#define DIFFICULTY 4  //hash must start with 4 zeroes, harder difficulty means it will be harder to mine
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
    char merkle_root[SHA256_DIGEST_LENGTH*2+1];
    char prev_hash[SHA256_DIGEST_LENTGTH*2+1]; //links block cryptographically
    char hash[SHA256_DIGEST_LENGTH*2+1];
    int nounce; // finds valid hash
    struct Block* next; // next creates linke lists of blocks
}Block;
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

typedef struct{
   Block* head; 
   int length; //no for block
}Blochchain;
//binary hash to hex str
void to hash_to_string(unsigned char hash[SHA256_DIGEST_LENGTH],
                        char output [SHA256_DIGEST_LENGTH *2+1])
    {
      for (int i = 0;i<SHA256_DIGEST_LENGTH;i++){
         sprintf(output + (i*2), "%02x", hash[i]); //%02X formates byte as 2 digit hex
      }
      output[SHA256_DIGEST_LENGTH * 2] = '\0'
    } 
//hash a str, hello-> hashes it -> returns hex str
void sha256_string(const char* input,char output[SHA256_DIGEST_LENGTH * 2 + 1]){
   unsigned char hash[SHA256_DIGEST_LENGTH];  
   SHA256((unsigned char*)input,strlen(input,hash));  //openssl, do hashing
   hash_to_string (hash,output); //convert to hex str
} 

void hash_transaction(Transaction* tx,char output[SHAA256_DIGEST_LENGTH 8 2 +1]){
   char tx_string[512];

   sprintf(tx_string,"%s%s%.2f%ld",tx->from,tx->to,tx->amount,tx->timestamp);
   sha256_string(tx_string,output);
}


/*
Transaction: A→ B, 10.50, timestamp=1234567890
Concatenated: "AB10.501234567890"
                    ↓ SHA-256
Hash: "a35f12ffb8c3d4e5f6a7b8c9d0e1f2a3..."
*/

MerkleNode* create_merkle_leaf(Transaction* tx){
   MerkleNode* node = (MerkleNode*)malloc(sizeof(MerkleNode));
   hash_transaction(tx,node->hash);
   node -> left = NULL;
   node -> right = NULL;
   //both a leaf nodes 
   return node;
}

void combine_hashes(const char -> hash1, const char* hash2,
                   char output[SHA256_DIGEST-LENGTH*2+1]){
                     char combined[SHA256_DIGEST_LENGTH*4+2];
                     sprintf(combined,"%s%s",hash1,hash2);
                     sha256_string(combined,output);
                   }
/*
hash1 + hash2 -> combined -> sha256-> parenthash
*/                  

MerkleNode* create_merkle_parent(MerkleNode* left,MerkleNode* right){
   MerkleNode* node = (MerkleNode*)malloc(sizeof(MerkleNode));
   if (right ==  NULL){
      combine_hashes(left->hash,left->hash,node->hash); // here we have to duplicate the leaf in case of ODD coz it will result in an unbalanced tree(figured it out later myself)
   }else{
      combine_hashes(left->hash,right->hash,node->hash);
   }
   node ->left=left; // connect left leaf to the parent node and right also , then return the parent node
   node->right=right;
   return node;
}
 

MerkleNode* build_merkle_tree(Transaction transactions[], int tx_count){
  if (tx_count==0){
   MerkleNode* empty = (MerkleNode*)malloc(sizeof(MerkleNode));
   strcpy(empty->hash,"0") //no transaction  will create a dummy node with hash = 0
   empty->left=NULL;
   empty->right=NULL;
   return empty;
 } 
 MerkleNode** nodes = (MerkleNode**)malloc(sizeof(MerkleNode*)*tx_count);
 for(int i = 0;i<tx_count;i++){
   node[i]= create_merkle_leaf(&transactions[i]);
 }
 int count = tx_count;
 while(count>1){
   int new_count = (count +1)/2; //count of parent node, in case of odd leafs we have to duplicate the last leaf to make the tree balanced
   MerkleNode** new_level = (MerkleNode**)malloc(sizeof(MerkleNode*)*new_count);
   
 }
 