#pragma once

typedef struct LinkedListNode LinkedListNode;
typedef struct LinkedList LinkedList;

LinkedList* MakeLinkedList(void* Data, size_t DataSize); // Pass NULL to data to create an empty list
int AppendToLinkedList(LinkedList* List, void* Data, size_t DataSize); // 1 in success, 0 in failure
int InsertInLinkedList(LinkedList* List, void* Data, size_t DataSize, size_t Index); // 1 in success, 0 in failure

void PopLinkedList(LinkedList* List);
void RemoveFromLinkedList(LinkedList* List, size_t Index);
void DestroyLinkedList(LinkedList* List);

LinkedListNode* LinkedListFront(LinkedList* List);
LinkedListNode* LinkedListRear(LinkedList* List);
LinkedListNode* GetLinkedListNode(LinkedList* List, size_t Index);
LinkedListNode* GetNodeFromData(LinkedList* List, void* Data);

size_t GetLinkedListNodeIndex(LinkedList* List, LinkedListNode* Node); // Returns SIZE_MAX if not found

void SetLinkedListDataAtIndex(LinkedList* List, size_t Index, void* Data, size_t Size);
void* GetLinkedListDataAtIndex(LinkedList* List, size_t Index);

size_t GetLinkedListLength(LinkedList* List);

void* GetNodeData(LinkedListNode* Node);