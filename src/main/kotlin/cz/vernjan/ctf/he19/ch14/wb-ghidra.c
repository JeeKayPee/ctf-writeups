encrypt() { // sub_400b8d
  puts("WhiteBox Test");
  printf("Enter Message to encrypt: ");
  
  char *plainText;
  fgets(plainText, 0x200, stdin); // 512
  plaintTextLength = strlen(plainText) - 1;

  // add padding (PKCS#7)
  uVar3 = (uint)(local_14 >> 0x1f) >> 0x1c;
  int paddingSize = 16 - ((plaintTextLength + uVar3 & 0xf) - uVar3);
  int i = 0;
  while (i < paddingSize) {
    plainText[ plaintTextLength + i ] = (char)paddingSize;
    i++;
  }
  
  // encrypt all blocks
  blockCount = (plaintTextLength / 16) + 1;
  int j = 0;
  while (j < blockCount) {
    encryptBlock(plainText + (j * 16));
    j++;
  }
  
  printHex(plainText, blockCount * 16);
  
  putchar(0xa); // new line
  return 0;
}

undefined8 encryptBlock(undefined8 *block) { // sub_400b0d
  undefined some [28];
  
  copyAndSwapRowsWithColumns(block, some); // sub_400735
  
  int round = 0;
  while (round < 9) { // 9 rounds
    shiftRows(some);
    FUN_00400947(round, some); // The real encryption here ..
    round++;
  }
  
  shiftRows(some);
  readFrom0x602060(some); // lookup encrypted bytes in the DATA section
  copyAndReverseSwapRowsWithColumns(some, block); // rewrites plain text with the encrypted version
  
  return block;
}

// byte by byte ..
// 0 -> 0
// 1 -> 4
// 2 -> 8
// 3 -> c

// 4 -> 1
// 5 -> 5
// 6 -> 9
// 7 -> d

// 8 -> 2
// 9 -> 6
// a -> a
// b -> e

// c -> 3
// d -> 7
// e -> b
// f -> f

// 0, 1, 2, 3
// 4, 5, 6, 7
// 8, 9, a, b
// c, d, e, f

// 0, 4, 8, c
// 1, 5, 9, d
// 2, 6, a, e
// 3, 7, b, f


void shiftRows(long *some) { // 400812

  undefined temp;

  // shift 2nd row by 1
  temp = *(some + 4);
  *(some + 4) = *(some + 5);
  *(some + 5) = *(some + 6);
  *(some + 6) = *(some + 7);
  *(some + 7) = temp;
  
  // shift 3rd row by 2
  temp = *(some + 8);
  *(some + 8) = *(some + 10);
  *(some + 10) = temp;
  temp = *(some + 9);
  *(some + 9) = *(some + 0xb);
  *(some + 0xb) = temp;
  
  // shift 4th row by 3
  temp = *(some + 0xc);
  *(some + 0xc) = *(some + 0xf);
  *(some + 0xf) = *(some + 0xe);
  *(some + 0xe) = *(some + 0xd);
  *(some + 0xd) = temp;
  
  return;
}

void FUN_00400947(int round,long *some) {

  undefined auStack56 [24];
  uint local_10; // UINT !!!

  int i = 0;
  while (i < 4) {
    local_10 = 0;

    int j = 0;
    while (j < 4) {
      local_10 = local_10 ^ // XOR !!!
      // 0x603060 - 0x603060 = 0x1000 = 4094 = 16 * 256
                 *(uint *) (&DAT_00603060 + // I READ UINT HERE !!!
                          ( (long)(int)(uint)*(byte *) (some + i + 4 * j) + (i + (round * 4 + j) * 4) * 0x100) * 4);

                          // DATA[256*i + some[i]]



      j++;
    }

//          *(some + i * 4 + j) = (&DAT_00602060) [*(byte *) (some + i * 4 + j) + (i * 4 + j) * 0x100];

    // DO SMTH with local_10 and put 16 bytes to auStack (swap COL and ROWS)
    j = 0;
    while (j < 4) { // SPLIT INT INTO ARRAY DOING SOME SHIFTING
      auStack56[i + j * 4] = (char)(local_10 >> ((byte)(j << 3) & 0x1f)); // local_10 / ((j * 8) & 0b00011111) ==> local_10 / 0, 8, 16, 24 (??)
      j++;
    }
    i++;
  }

  // copy auStack to some
  int i = 0;
  while (i < 4) {
    int j = 0;
    while (j < 4) {
      *(some + i * 4 + j) = auStack56[i * 4 + j];
      j++;
    }
    i++;
  }
}


// The last round
void readFrom0x602060(long *some) { // 400a7a
  int i = 0;
  while (i < 4) {
    int j = 0;
    while (j < 4) {
      *(some + i * 4 + j) = (&DAT_00602060) [ *(byte *)(some + i * 4 + j) + (i * 4 + j) * 0x100]; // 256 // DATA[256*i + some[i]]
      j++;
    }
    i++;
  }
}

void copyAndSwapRowsWithColumns(long *block,long *some) { // 400735
  int i = 0;
  while (i < 4) {
    int j = 0;
    while (j < 4) {
      *(some + i * 4 + j) = *(block + i + j * 4);
      j++;
    }
    i++;
  }
}

void copyAndReverseSwapRowsWithColumns(long *some,long *block) { // 4007a5
  int i = 0;
  while (i < 4) {
    int j = 0;
    while (j < 4) {
      *(block + i + j * 4) = *(some + i * 4 + j);
      j++;
    }
    i++;
  }
}

void printHex(long *plainText,int totalSize) { // 400677
  int i = 0;
  while (i < totalSize) {
    printf("%02x",(ulong)((int)*(char *)(plainText + (long)i) & 0xff));
    i++;
  }
  return;
}