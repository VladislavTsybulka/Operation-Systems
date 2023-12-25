#include <iostream>
#include <cassert>

using namespace std;

struct ListNode {
    int value;
    ListNode* next;
};

ListNode* reverseLinkedList(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }

    ListNode* reversed = reverseLinkedList(head->next);

    head->next->next = head;
    head->next = nullptr;

    return reversed;
}

void testReverseLinkedList() {

    ListNode* head = nullptr;
    ListNode* reversed = reverseLinkedList(head);
    assert(reversed == nullptr);

    head = new ListNode{ 42, nullptr };
    reversed = reverseLinkedList(head);
    assert(reversed == head);
    assert(reversed->value == 42);
    assert(reversed->next == nullptr);

    head = new ListNode{ 1, nullptr };
    head->next = new ListNode{ 2, nullptr };
    head->next->next = new ListNode{ 3, nullptr };

    reversed = reverseLinkedList(head);
    assert(reversed->value == 3);
    assert(reversed->next->value == 2);
    assert(reversed->next->next->value == 1);
    assert(reversed->next->next->next == nullptr);

    ListNode* current = reversed;
    while (current != nullptr) {
        ListNode* next = current->next;
        delete current;
        current = next;
    }
    cout << "Testing is OK." << endl;
}

int main() {
    setlocale(LC_ALL, "Rus");
    testReverseLinkedList();

    ListNode* head = new ListNode{ 1, nullptr };
    head->next = new ListNode{ 2, nullptr };
    head->next->next = new ListNode{ 3, nullptr };
    head->next->next->next = new ListNode{ 4, nullptr };
    head->next->next->next->next = new ListNode{ 5, nullptr };

    cout << "Исходный список: ";
    ListNode* current = head;
    while (current != nullptr) {
        cout << current->value << " ";
        current = current->next;
    }
    cout << endl;

    head = reverseLinkedList(head);

    cout << "Развернутый список: ";
    current = head;
    while (current != nullptr) {
        cout << current->value << " ";
        current = current->next;
    }
    cout << endl;

    current = head;
    while (current != nullptr) {
        ListNode* next = current->next;
        delete current;
        current = next;
    }

    return 0;
}

