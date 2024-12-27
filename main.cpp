#include <iostream>

// Class Node holds a value and the address of the next node
class Node
{
    int val{0};
    Node* nextNode = nullptr;
public:
    // Method to get the value
    int getVal()
    {
        return val;
    }

    // Method to get the nextNode value
    Node* getNext()
    {
        return nextNode;
    }


    // Method used by Linked List to link the Nodes together
    void setNext(Node* nextPtr)
    {
        nextNode = nextPtr;
    }


    // Default constructor
    Node() = default;
    // Constructor that takes a value and the address of the next Node(optional)
    Node(int value, Node* nextPtr = nullptr)
    {
        val = value;
        nextNode = nextPtr;
    }
    // No memory cleanup in this destructor, LinkedList class handles memory
    ~Node() = default;
};

// Class to manage the Node objects
class LinkedList
{
    // The address of the first node
    Node* head = nullptr;

    // The address of the last node
    Node* tail = nullptr;

    // The address of the last node created
    Node* previousNode = nullptr;

public:
    LinkedList() = default;

    // Destructor, iterates until the end of the list and releases memory used by Node instances
    ~LinkedList()
    {
        while (head != nullptr)
        {
            Node* temp = head;
            head = head->getNext();
            delete temp;
        }
    }

    // Method to create and link a new Node instance
    void createNode(int passedValue)
    {
        if (head == nullptr)
        {
            // If first Node, set it to be the head
            head = new Node(passedValue);

            // Last created Node address is the current Node
            previousNode = head;
        }

        // If second node, special method to connect the head Node to this one
        else if (tail == nullptr)
        {
            // create Node
            tail = new Node(passedValue);

            // setting head's next pointer to point to this current Node instance
            head->setNext(tail);

            // Last created Node address is the current Node
            previousNode = tail;
        }

        else if (previousNode != nullptr)
        {
            previousNode->setNext(new Node(passedValue));
            previousNode = previousNode->getNext();
            tail = previousNode;
        }
    }

    // Method to iterate through the list and return the nth value (counter)
    int getNodeValue(int counter)
    {
        Node* requestedNode = nullptr;

        for (int i = 0; i <= counter; i++)
        {
            // If we've reached the end of the list, want to throw an error here (need to learn that first)
            if (requestedNode == tail && i != counter)
            {
                std::cout << "\nERROR: Reached end of list before requested index: " << counter << ". End of list found at index pos: ";
                return i;
            }

            // If the first position (0) is requested, we return head
            if (counter == 0 )
                return head->getVal();
            // If we get to this line, counter must not be 0, so we start our ptr as the 2d position (1)

            if (i == counter)
                return requestedNode->getVal();

            if (i != counter)
            {
                if (requestedNode == nullptr)
                    requestedNode = head->getNext();
                else requestedNode = requestedNode->getNext();
            }
        }
    }
};

int main()
{
    // Simple use case, creates 10 notes with values 0-9, then prints out to console
    LinkedList testList;
    for (int i = 0; i < 10; i++)
    {
        testList.createNode(i);
    }
    // DEBUG printing of node values
    for (int i = 0; i < 10; i++)
    {
        std::cout << "\n[DEBUG] index " << i << ": " << testList.getNodeValue(i);
    }
}