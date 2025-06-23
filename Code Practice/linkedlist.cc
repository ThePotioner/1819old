#include <iostream>
#include <string>

struct Node
{
    std::string data;
    int n;
    Node* nextNode;
};

void justStrcpy(char *dest, const char *src)
{
    // for (char *save = dest; *dest++ = *src++; );
    // *dest++ ... ?
    // *(dest = dest + 1)...
    // is *dest++ equal *(dest++)?
    for (int i = 0;; ++i)
    {
        if(!*dest) return;
        *dest = *src;
        dest++;
        src++;
    }
}

Node* useNode(std::string data)
{
    Node* newNode = new Node();
    newNode->data = data;
    newNode->n = 0;
    newNode->nextNode = NULL;

    return newNode;
}

Node* insertNode(Node* head, std::string data)
{
    Node* insNode = useNode(data);
    insNode->nextNode = head->nextNode;
    head->nextNode = insNode;

    return insNode;
}

void printNode(Node* head)
{
    for (Node* curr = head; curr; curr = curr->nextNode)
    {
        std::cout << curr->data << std::endl;
    }
}

int main()
{
    char ppap[] = "ppap";
    char bbab[] = "bbab";

    justStrcpy(ppap, bbab);
    std::cout << ppap << std::endl;

    Node* header = useNode("Header Node!");
    Node* A = insertNode(header, "A");
    Node* B = insertNode(A, "B");
    Node* C = insertNode(B, "C");
    Node* D = insertNode(header, "D");
    printNode(header);

    return 0;
}