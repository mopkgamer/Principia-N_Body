#include <stdlib.h>
#include <string.h>

#include "..\include\linkedlist.h"

typedef unsigned long long size_t;

struct LinkedListNode   {
    void* Data;
    size_t Size;

    LinkedListNode* Next;
    LinkedListNode* Previous;
};

struct LinkedList   {
    size_t Length;

    LinkedListNode* Front;
    LinkedListNode* Rear;
};

LinkedList* MakeLinkedList(void* Data, size_t Size) {
    LinkedList* List = (LinkedList*) malloc(sizeof(LinkedList)); 

    if (!List) return NULL;

    List->Front = NULL;
    List->Rear = NULL;
    List->Length = 0;

    if (Data && Size)   {
        LinkedListNode* Node = (LinkedListNode*) malloc(sizeof(LinkedListNode) + Size);
        if (!Node)  {
            free(List);
            return NULL;
        }

        Node->Data = (void*)(Node + 1);
        Node->Size = Size;
        Node->Previous = NULL;
        Node->Next = NULL;

        memcpy(Node->Data, Data, Size);

        List->Front = Node;
        List->Rear = Node;
        List->Length = 1;
    }

    return List;
}

int AppendToLinkedList(LinkedList* List, void* Data, size_t Size) {
    if (!Data || Size == 0)
        return 0;

    LinkedListNode* Node = malloc(sizeof(LinkedListNode) + Size);
    if (!Node)
        return 0;

    Node->Data = (void*)(Node + 1);
    Node->Size = Size;
    memcpy(Node->Data, Data, Size);

    Node->Next = NULL;
    Node->Previous = List->Rear;

    if (List->Rear)
        List->Rear->Next = Node;
    else
        List->Front = Node;

    List->Rear = Node;
    List->Length++;

    return 1;
}

int InsertInLinkedList(LinkedList* List, void* Data, size_t Size, size_t Index) {
    if (Index == List->Length)  {
        AppendToLinkedList(List, Data, Size);
        return 1;
    }

    LinkedListNode* NodeAtIndex = GetLinkedListNode(List, Index);
    LinkedListNode* Node = (LinkedListNode*) malloc(sizeof(LinkedListNode)+Size);

    if (!NodeAtIndex || !Node) return 0;

    LinkedListNode* Previous = NodeAtIndex->Previous;

    Node->Data = &Node[1];
    Node->Size = Size;

    NodeAtIndex->Previous = Node;
    Node->Next = NodeAtIndex;

    if (Previous)   Previous->Next = Node;
    else List->Front = Node;

    Node->Previous = Previous;

    memcpy(Node->Data, Data, Size);

    List->Length++;

    return 1;
}

void PopLinkedList(LinkedList* List)    {
    if (List->Length > 0)   {
        LinkedListNode* End = List->Rear;

        List->Rear = End->Previous;
        
        if (List->Rear) {
            List->Rear->Next = NULL;
        } else {
            List->Front = NULL;
        }

        List->Length--;
        free(End);
    }
}

void RemoveFromLinkedList(LinkedList* List, size_t Index) {
    LinkedListNode* NodeAtIndex = GetLinkedListNode(List, Index);

    if (!NodeAtIndex) return;

    if (NodeAtIndex == List->Rear)  {
        PopLinkedList(List);
        return;
    }
    else if (NodeAtIndex == List->Front) {
        List->Front = NodeAtIndex->Next;
        free(NodeAtIndex);
        List->Length--;
        return;
    }
    else    {
        LinkedListNode* Next = NodeAtIndex->Next;
        LinkedListNode* Previous = NodeAtIndex->Previous;

        Next->Previous = Previous;
        Previous->Next = Next;

        free(NodeAtIndex);

        List->Length--;
    }
}

void DestroyLinkedList(LinkedList* List)    {
    LinkedListNode* End = List->Rear;

    while (End != List->Front) {
        LinkedListNode* Previous = End->Previous;
        free(End);
        End = Previous;
    }

    free(End);
    free(List);
}

LinkedListNode* LinkedListFront(LinkedList* List)   {
    return List->Front;
}

LinkedListNode* LinkedListRear(LinkedList* List)    {
    return List->Rear;
}

LinkedListNode* GetLinkedListNode(LinkedList* List, size_t Index)   {
    if (Index >= List->Length) return NULL;

    LinkedListNode* Node = NULL;

    if (Index > List->Length / 2) {
        Node = List->Rear;
        for (size_t idx = List->Length - 1; idx > Index && Node != NULL; idx--) {
            Node = Node->Previous;
        }
    } else {
        Node = List->Front;
        for (size_t idx = 0; idx < Index && Node != NULL; idx++) {
            Node = Node->Next;
        }
    }

    return Node;
}

size_t GetLinkedListNodeIndex(LinkedList* List, LinkedListNode* Node)   {
    size_t index = 0;
    LinkedListNode* Iterator = List->Front;

    while (Iterator != NULL)    {
        if (Iterator == Node)   {
            break;
        }
        index++;

        Iterator = Iterator->Next;
    }

    if (Iterator == NULL) return SIZE_MAX;
    else return index;
}

LinkedListNode* GetNodeFromData(LinkedList* List, void* Data)  {
    LinkedListNode* Iterator = List->Front;

    while (Iterator != NULL)    {
        if (memcmp(Data, Iterator->Data, Iterator->Size) == 0)  {
            return Iterator;
        }

        Iterator = Iterator->Next;
    }

    return NULL;
}

void SetLinkedListDataAtIndex(LinkedList* List, size_t Index, void* Data, size_t Size)  {
    LinkedListNode* Node = GetLinkedListNode(List, Index);

    if (!Node) return;

    if (Node->Size < Size)  {
        LinkedListNode* Previous = Node->Previous;
        LinkedListNode* Next = Node->Next;

        Node = (LinkedListNode*) realloc(Node, sizeof(LinkedListNode)+Size);
        Node->Size = Size;

        memcpy(Node->Data, Data, Size);

        Node->Previous = Previous;
        Node->Next = Next;
    }
}

void* GetLinkedListDataAtIndex(LinkedList* List, size_t Index)  {
    LinkedListNode* Node = GetLinkedListNode(List, Index);
    if (Node) return Node->Data;
    else return NULL;
}

size_t GetLinkedListLength(LinkedList* List)    {
    return List->Length;
}

void* GetNodeData(LinkedListNode* Node) {
    return Node->Data;
}