#include <stdio.h>
#include <stdbool.h>

#define TOTAL_BLOCKS 16
#define INODE_BLOCKS 8
#define DATA_BLOCKS (TOTAL_BLOCKS - INODE_BLOCKS)
#define BLOCK_SIZE 1024
#define MIN_FILE_SIZE 1024

struct Inode {
    bool allocated;
    int start_block;
    int num_blocks;
};

struct File {
    int size;
    struct Inode inode;
};

struct FileSystem {
    struct Inode inodes[INODE_BLOCKS];
    bool blocks[DATA_BLOCKS];
};

void initializeFileSystem(struct FileSystem *fs) {
    for (int i = 0; i < INODE_BLOCKS; i++) {
        fs->inodes[i].allocated = false;
        fs->inodes[i].start_block = -1;
        fs->inodes[i].num_blocks = 0;
    }

    for (int i = 0; i < DATA_BLOCKS; i++) {
        fs->blocks[i] = false;
    }
}

bool isContiguousBlocksAvailable(struct FileSystem *fs, int start_block, int num_blocks) {
    for (int i = start_block; i < start_block + num_blocks; i++) {
        if (fs->blocks[i]) {
            return false;
        }
    }
    return true;
}

void allocateContiguousBlocks(struct FileSystem *fs, int start_block, int num_blocks) {
    for (int i = start_block; i < start_block + num_blocks; i++) {
        fs->blocks[i] = true;
    }
}

bool allocateFile(struct FileSystem *fs, struct File *file) {
    int start_block = -1;
    int num_blocks = (file->size + BLOCK_SIZE - 1) / BLOCK_SIZE;

    for (int i = 0; i < DATA_BLOCKS - num_blocks + 1; i++) {
        if (isContiguousBlocksAvailable(fs, i, num_blocks)) {
            start_block = i;
            break;
        }
    }

    if (start_block == -1) {
        printf("Not enough contiguous blocks available for the file.\n");
        return false;
    }

    allocateContiguousBlocks(fs, start_block, num_blocks);

    int inode_index = -1;
    for (int i = 0; i < INODE_BLOCKS; i++) {
        if (!fs->inodes[i].allocated) {
            inode_index = i;
            break;
        }
    }

    if (inode_index == -1) {
        printf("No available inode to allocate the file.\n");
        return false;
    }

    fs->inodes[inode_index].allocated = true;
    fs->inodes[inode_index].start_block = start_block;
    fs->inodes[inode_index].num_blocks = num_blocks;
    file->inode = fs->inodes[inode_index];

    return true;
}

int main() {
    struct FileSystem fs;
    struct File file;

    initializeFileSystem(&fs);

    file.size = 5 * BLOCK_SIZE;  

    if (file.size < MIN_FILE_SIZE) {
        printf("File size should be at least 1 KB.\n");
        return 1;
    }

    if (allocateFile(&fs, &file)) {
        printf("File allocated successfully.\n");
        printf("Start Block: %d\n", file.inode.start_block);
        printf("Number of Blocks: %d\n", file.inode.num_blocks);
    } else {
        printf("File allocation failed.\n");
    }

    return 0;
}
