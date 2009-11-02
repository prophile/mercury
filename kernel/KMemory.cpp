#include "KMemory.h"
#include "KForward.h"
#include "KSpinLock.h"

namespace
{

const KWord BLOCK_FLAG_USED = 1;
const KWord BLOCK_ALLOCATION_ACCURACY = 16;
const KWord BLOCK_SPLIT_THRESHOLD = BLOCK_ALLOCATION_ACCURACY * 2;

struct Block
{
	KWord length;
	KWord flags;
	Block* next;
	Block* prev;
	
	void Claim ( KWord claimLength );
	void Release ();
	
	void* Data () { return ((unsigned char*)this + sizeof(Block)); }
	bool IsFree () { return !(flags & BLOCK_FLAG_USED); }
	
	Block* PhysicalSuccessor () { return (Block*)((unsigned char*)this + sizeof(Block) + length); }
	
	Block* PreviousBlock () { return prev; }
	Block* NextBlock () { return next; }
	
	bool IsBackwardsSparse () { return !PreviousBlock() || PreviousBlock()->PhysicalSuccessor() != this; }
	bool IsForwardsSparse () { return NextBlock() != PhysicalSuccessor(); }
};

const KWord BLOCK_SIZE = 8192 - sizeof(Block);

Block* firstBlock = (Block*)KHeapBase;
//Block* lastBlock = firstBlock;

unsigned char* nextBlockTarget = (unsigned char*)KHeapBase + sizeof(Block) + BLOCK_SIZE;

KSpinLock memlock;

void block_try_merge ( Block* blk );
Block* block_perform_merge ( Block* left, Block* right );

Block* block_try_merge_right ( Block* blk )
{
	while (blk && !blk->IsForwardsSparse() && blk->NextBlock()->IsFree())
	{
		blk = block_perform_merge(blk, blk->NextBlock());
	}
	return blk;
}

Block* block_try_merge_left ( Block* blk )
{
	while (blk && !blk->IsBackwardsSparse() && blk->PreviousBlock()->IsFree())
	{
		blk = block_perform_merge(blk->PreviousBlock(), blk);
	}
	return blk;
}

void block_try_merge ( Block* blk )
{
	blk = block_try_merge_right(blk);
	blk = block_try_merge_left(blk);
}

Block* block_perform_merge ( Block* left, Block* right )
{
	left->length += right->length + sizeof(Block);
	left->next = right->next;
	return left;
}

void Block::Claim ( KWord claimLength )
{
	if (length - claimLength > BLOCK_SPLIT_THRESHOLD)
	{
		// split the block
		Block* newBlock = (Block*)((unsigned char*)this + sizeof(Block) + claimLength);
		newBlock->next = next;
		newBlock->prev = this;
		next = newBlock;
		newBlock->length = length - claimLength - sizeof(Block);
		length = claimLength;
	}
	flags |= BLOCK_FLAG_USED;
}

void Block::Release ()
{
	flags &= ~BLOCK_FLAG_USED;
	// do merging
	block_try_merge(this);
}

}

void kmeminit ()
{
	firstBlock->length = BLOCK_SIZE;
	firstBlock->flags = 0;
	firstBlock->next = NULL;
	firstBlock->prev = NULL;
}

void* kmalloc ( KWord length )
{
	void* returnVal;
	memlock.Lock();
	length += BLOCK_ALLOCATION_ACCURACY - 1;
	length /= BLOCK_ALLOCATION_ACCURACY;
	length *= BLOCK_ALLOCATION_ACCURACY;
	// assert length < BLOCK_SIZE?
	// TODO: something more efficient than a linear search
	Block* block = firstBlock;
	while (block->NextBlock() && (block->length < length || !block->IsFree())) block = block->NextBlock();
	if (block->length >= length && block->IsFree())
	{
		// we've hit a winner
		returnVal = block->Data();
		block->Claim(length);
	}
	else
	{
		// allocate a new block
		Block* newBlock = (Block*)nextBlockTarget;
		newBlock->next = NULL;
		newBlock->prev = block;
		block->next = newBlock;
		newBlock->length = BLOCK_SIZE;
		nextBlockTarget += BLOCK_SIZE + sizeof(Block);
		newBlock->flags = 0;
		newBlock = block_try_merge_left(newBlock);
		returnVal = newBlock->Data();
		newBlock->Claim(length);
	}
	memlock.Unlock();
	return returnVal;
}

void kfree ( void* ptr )
{
	unsigned char* data = (unsigned char*)ptr;
	Block* block = (Block*)(data - sizeof(Block));
	memlock.Lock();
	block->Release();
	memlock.Unlock();
}
