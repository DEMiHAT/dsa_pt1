#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

// Singly Linked List node definition

typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Utility: safely read an integer from stdin with a prompt
static bool read_int(const char *prompt, int *out_value) {
    char buffer[256];
    if (prompt != NULL && prompt[0] != '\0') {
        printf("%s", prompt);
        fflush(stdout);
    }
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return false;
    }
    char *endptr = NULL;
    errno = 0;
    long value = strtol(buffer, &endptr, 10);
    if (errno != 0 || endptr == buffer) {
        return false;
    }
    while (*endptr == ' ' || *endptr == '\t' || *endptr == '\n' || *endptr == '\r') {
        endptr++;
    }
    if (*endptr != '\0') {
        return false;
    }
    if (value < INT_MIN || value > INT_MAX) {
        return false;
    }
    *out_value = (int)value;
    return true;
}

// Creation helper
static Node *create_node(int value) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "Error: memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = value;
    new_node->next = NULL;
    return new_node;
}

// Insertion operations
static void push_front(Node **head_ref, int value) {
    Node *new_node = create_node(value);
    new_node->next = *head_ref;
    *head_ref = new_node;
}

static void push_back(Node **head_ref, int value) {
    Node *new_node = create_node(value);
    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }
    Node *current = *head_ref;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
}

static bool insert_at(Node **head_ref, int index_one_based, int value) {
    if (index_one_based <= 0) {
        return false;
    }
    if (index_one_based == 1) {
        push_front(head_ref, value);
        return true;
    }
    Node *current = *head_ref;
    int current_index = 1;
    while (current != NULL && current_index < index_one_based - 1) {
        current = current->next;
        current_index++;
    }
    if (current == NULL) {
        return false;
    }
    Node *new_node = create_node(value);
    new_node->next = current->next;
    current->next = new_node;
    return true;
}

static bool insert_before_value(Node **head_ref, int target_value, int new_value) {
    if (*head_ref == NULL) {
        return false;
    }
    if ((*head_ref)->data == target_value) {
        push_front(head_ref, new_value);
        return true;
    }
    Node *prev = *head_ref;
    Node *curr = (*head_ref)->next;
    while (curr != NULL && curr->data != target_value) {
        prev = curr;
        curr = curr->next;
    }
    if (curr == NULL) {
        return false;
    }
    Node *new_node = create_node(new_value);
    new_node->next = curr;
    prev->next = new_node;
    return true;
}

static bool insert_after_value(Node **head_ref, int target_value, int new_value) {
    Node *curr = *head_ref;
    while (curr != NULL && curr->data != target_value) {
        curr = curr->next;
    }
    if (curr == NULL) {
        return false;
    }
    Node *new_node = create_node(new_value);
    new_node->next = curr->next;
    curr->next = new_node;
    return true;
}

// Deletion operations
static bool pop_front(Node **head_ref, int *removed_value) {
    if (*head_ref == NULL) {
        return false;
    }
    Node *temp = *head_ref;
    if (removed_value != NULL) {
        *removed_value = temp->data;
    }
    *head_ref = temp->next;
    free(temp);
    return true;
}

static bool pop_back(Node **head_ref, int *removed_value) {
    if (*head_ref == NULL) {
        return false;
    }
    if ((*head_ref)->next == NULL) {
        if (removed_value != NULL) {
            *removed_value = (*head_ref)->data;
        }
        free(*head_ref);
        *head_ref = NULL;
        return true;
    }
    Node *prev = NULL;
    Node *curr = *head_ref;
    while (curr->next != NULL) {
        prev = curr;
        curr = curr->next;
    }
    if (removed_value != NULL) {
        *removed_value = curr->data;
    }
    prev->next = NULL;
    free(curr);
    return true;
}

static bool delete_at(Node **head_ref, int index_one_based, int *removed_value) {
    if (index_one_based <= 0 || *head_ref == NULL) {
        return false;
    }
    if (index_one_based == 1) {
        return pop_front(head_ref, removed_value);
    }
    Node *prev = *head_ref;
    Node *curr = (*head_ref)->next;
    int current_index = 2;
    while (curr != NULL && current_index < index_one_based) {
        prev = curr;
        curr = curr->next;
        current_index++;
    }
    if (curr == NULL) {
        return false;
    }
    if (removed_value != NULL) {
        *removed_value = curr->data;
    }
    prev->next = curr->next;
    free(curr);
    return true;
}

static bool delete_value(Node **head_ref, int target_value) {
    if (*head_ref == NULL) {
        return false;
    }
    if ((*head_ref)->data == target_value) {
        Node *temp = *head_ref;
        *head_ref = temp->next;
        free(temp);
        return true;
    }
    Node *prev = *head_ref;
    Node *curr = (*head_ref)->next;
    while (curr != NULL && curr->data != target_value) {
        prev = curr;
        curr = curr->next;
    }
    if (curr == NULL) {
        return false;
    }
    prev->next = curr->next;
    free(curr);
    return true;
}

// Search
static int search_first(Node *head, int target_value) {
    int index = 1;
    for (Node *curr = head; curr != NULL; curr = curr->next) {
        if (curr->data == target_value) {
            return index;
        }
        index++;
    }
    return -1;
}

// Display and count
static void display(Node *head) {
    printf("[");
    for (Node *curr = head; curr != NULL; curr = curr->next) {
        printf("%d", curr->data);
        if (curr->next != NULL) {
            printf(" -> ");
        }
    }
    printf("]\n");
}

static int count(Node *head) {
    int n = 0;
    for (Node *curr = head; curr != NULL; curr = curr->next) {
        n++;
    }
    return n;
}

// Reverse
static void reverse(Node **head_ref) {
    Node *prev = NULL;
    Node *curr = *head_ref;
    while (curr != NULL) {
        Node *next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    *head_ref = prev;
}

// Sort (ascending) using stable bubble sort
static void sort_ascending(Node **head_ref) {
    if (*head_ref == NULL || (*head_ref)->next == NULL) {
        return;
    }
    bool swapped;
    do {
        swapped = false;
        Node *curr = *head_ref;
        Node *prev = NULL;
        while (curr != NULL && curr->next != NULL) {
            if (curr->data > curr->next->data) {
                Node *next = curr->next;
                curr->next = next->next;
                next->next = curr;
                if (prev == NULL) {
                    *head_ref = next;
                } else {
                    prev->next = next;
                }
                prev = next;
                swapped = true;
            } else {
                prev = curr;
                curr = curr->next;
            }
        }
    } while (swapped);
}

// Clear entire list
static void clear_list(Node **head_ref) {
    Node *curr = *head_ref;
    while (curr != NULL) {
        Node *next = curr->next;
        free(curr);
        curr = next;
    }
    *head_ref = NULL;
}

static void print_menu(void) {
    printf("\nLinked List Operations (Singly Linked List)\n");
    printf("------------------------------------------\n");
    printf(" 1. Push Front (Insert at beginning)\n");
    printf(" 2. Push Back (Insert at end)\n");
    printf(" 3. Insert At Position (1-based)\n");
    printf(" 4. Insert Before Value (first occurrence)\n");
    printf(" 5. Insert After Value (first occurrence)\n");
    printf(" 6. Pop Front (Delete from beginning)\n");
    printf(" 7. Pop Back (Delete from end)\n");
    printf(" 8. Delete At Position (1-based)\n");
    printf(" 9. Delete By Value (first occurrence)\n");
    printf("10. Search (first occurrence)\n");
    printf("11. Display\n");
    printf("12. Count\n");
    printf("13. Reverse\n");
    printf("14. Sort Ascending\n");
    printf("15. Clear List\n");
    printf(" 0. Exit\n");
}

int main(void) {
    Node *head = NULL;

    while (true) {
        print_menu();
        int choice;
        if (!read_int("Enter your choice: ", &choice)) {
            printf("Invalid input. Please enter a number.\n");
            continue;
        }
        if (choice == 0) {
            break;
        }
        int value, value2, position, removed;
        bool ok;
        switch (choice) {
            case 1:
                if (read_int("Enter value: ", &value)) {
                    push_front(&head, value);
                    printf("Inserted %d at the beginning.\n", value);
                } else {
                    printf("Invalid value.\n");
                }
                break;
            case 2:
                if (read_int("Enter value: ", &value)) {
                    push_back(&head, value);
                    printf("Inserted %d at the end.\n", value);
                } else {
                    printf("Invalid value.\n");
                }
                break;
            case 3:
                if (read_int("Enter position (1-based): ", &position) && read_int("Enter value: ", &value)) {
                    ok = insert_at(&head, position, value);
                    printf(ok ? "Inserted %d at position %d.\n" : "Failed to insert at position %d.\n", value, position);
                } else {
                    printf("Invalid input.\n");
                }
                break;
            case 4:
                if (read_int("Enter target value: ", &value) && read_int("Enter new value: ", &value2)) {
                    ok = insert_before_value(&head, value, value2);
                    if (ok) printf("Inserted %d before %d.\n", value2, value);
                    else printf("Value %d not found.\n", value);
                } else {
                    printf("Invalid input.\n");
                }
                break;
            case 5:
                if (read_int("Enter target value: ", &value) && read_int("Enter new value: ", &value2)) {
                    ok = insert_after_value(&head, value, value2);
                    if (ok) printf("Inserted %d after %d.\n", value2, value);
                    else printf("Value %d not found.\n", value);
                } else {
                    printf("Invalid input.\n");
                }
                break;
            case 6:
                ok = pop_front(&head, &removed);
                if (ok) printf("Deleted from beginning: %d.\n", removed);
                else printf("List is empty.\n");
                break;
            case 7:
                ok = pop_back(&head, &removed);
                if (ok) printf("Deleted from end: %d.\n", removed);
                else printf("List is empty.\n");
                break;
            case 8:
                if (read_int("Enter position (1-based): ", &position)) {
                    ok = delete_at(&head, position, &removed);
                    if (ok) printf("Deleted %d from position %d.\n", removed, position);
                    else printf("Invalid position or list is empty.\n");
                } else {
                    printf("Invalid input.\n");
                }
                break;
            case 9:
                if (read_int("Enter value to delete: ", &value)) {
                    ok = delete_value(&head, value);
                    if (ok) printf("Deleted value %d (first occurrence).\n", value);
                    else printf("Value %d not found.\n", value);
                } else {
                    printf("Invalid input.\n");
                }
                break;
            case 10:
                if (read_int("Enter value to search: ", &value)) {
                    position = search_first(head, value);
                    if (position == -1) printf("Value %d not found.\n", value);
                    else printf("Value %d found at position %d.\n", value, position);
                } else {
                    printf("Invalid input.\n");
                }
                break;
            case 11:
                printf("List: ");
                display(head);
                break;
            case 12:
                printf("Count: %d\n", count(head));
                break;
            case 13:
                reverse(&head);
                printf("List reversed.\n");
                break;
            case 14:
                sort_ascending(&head);
                printf("List sorted in ascending order.\n");
                break;
            case 15:
                clear_list(&head);
                printf("List cleared.\n");
                break;
            default:
                printf("Unknown choice. Please select a valid option.\n");
                break;
        }
    }

    clear_list(&head);
    printf("Exiting. Goodbye!\n");
    return 0;
}