// que2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTACTS 100

// Structure to represent a contact
struct Contact {
    char name[50];
    char phone[20];
    char email[50];
};

// Function prototypes
void createAddressBook(struct Contact contacts[], int *numContacts);
void viewAddressBook(struct Contact contacts[], int numContacts);
void insertRecord(struct Contact contacts[], int *numContacts);
void deleteRecord(struct Contact contacts[], int *numContacts);
void modifyRecord(struct Contact contacts[], int numContacts);

int main() {
    struct Contact contacts[MAX_CONTACTS];
    int numContacts = 0;
    char option;

    do {
        printf("\nOptions:\n");
        printf("a) Create address book\n");
        printf("b) View address book\n");
        printf("c) Insert a record\n");
        printf("d) Delete a record\n");
        printf("e) Modify a record\n");
        printf("f) Exit\n");
        printf("Enter your choice: ");
        scanf(" %c", &option);

        switch (option) {
            case 'a':
                createAddressBook(contacts, &numContacts);
                break;
            case 'b':
                viewAddressBook(contacts, numContacts);
                break;
            case 'c':
                insertRecord(contacts, &numContacts);
                break;
            case 'd':
                deleteRecord(contacts, &numContacts);
                break;
            case 'e':
                modifyRecord(contacts, numContacts);
                break;
            case 'f':
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid option. Please try again.\n");
        }
    } while (option != 'f');

    return 0;
}

void createAddressBook(struct Contact contacts[], int *numContacts) {
    *numContacts = 0;
    printf("Address book created.\n");
}

void viewAddressBook(struct Contact contacts[], int numContacts) {
    if (numContacts == 0) {
        printf("Address book is empty.\n");
        return;
    }
    printf("Address Book:\n");
    for (int i = 0; i < numContacts; i++) {
        printf("Name: %s\nPhone: %s\nEmail: %s\n\n", contacts[i].name, contacts[i].phone, contacts[i].email);
    }
}

void insertRecord(struct Contact contacts[], int *numContacts) {
    if (*numContacts >= MAX_CONTACTS) {
        printf("Address book is full. Cannot insert more records.\n");
        return;
    }
    printf("Enter name: ");
    scanf("%s", contacts[*numContacts].name);
    printf("Enter phone: ");
    scanf("%s", contacts[*numContacts].phone);
    printf("Enter email: ");
    scanf("%s", contacts[*numContacts].email);
    (*numContacts)++;
    printf("Record inserted successfully.\n");
}

void deleteRecord(struct Contact contacts[], int *numContacts) {
    if (*numContacts == 0) {
        printf("Address book is empty. No records to delete.\n");
        return;
    }
    char name[50];
    printf("Enter the name of the contact to delete: ");
    scanf("%s", name);
    int found = 0;
    for (int i = 0; i < *numContacts; i++) {
        if (strcmp(contacts[i].name, name) == 0) {
            for (int j = i; j < *numContacts - 1; j++) {
                contacts[j] = contacts[j + 1];
            }
            (*numContacts)--;
            found = 1;
            printf("Record deleted successfully.\n");
            break;
        }
    }
    if (!found) {
        printf("Contact not found.\n");
    }
}

void modifyRecord(struct Contact contacts[], int numContacts) {
    if (numContacts == 0) {
        printf("Address book is empty. No records to modify.\n");
        return;
    }
    char name[50];
    printf("Enter the name of the contact to modify: ");
    scanf("%s", name);
    int found = 0;
    for (int i = 0; i < numContacts; i++) {
        if (strcmp(contacts[i].name, name) == 0) {
            printf("Enter new phone: ");
            scanf("%s", contacts[i].phone);
            printf("Enter new email: ");
            scanf("%s", contacts[i].email);
            found = 1;
            printf("Record modified successfully.\n");
            break;
        }
    }
    if (!found) {
        printf("Contact not found.\n");
    }
}

// que6

#include <stdio.h>
#include <stdbool.h>

#define FRAME_SIZE 3
#define MAX_REFERENCES 20

// Function prototypes
void displayFrames(int frames[], int numFrames);
bool isPageInFrames(int frames[], int numFrames, int page);
int getOldestPageIndex(int pages[], int numPages, int frameIndex);

int main() {
    int referenceString[MAX_REFERENCES] = {1, 2, 3, 4, 5, 1, 2, 6, 7, 8, 7, 8, 9, 7, 8, 9, 5, 4, 5, 4};
    int frames[FRAME_SIZE] = {0}; // Initialize frames with 0 (indicating empty)

    int numReferences = sizeof(referenceString) / sizeof(referenceString[0]);
    int numFaults = 0;

    printf("Reference String: ");
    for (int i = 0; i < numReferences; i++) {
        printf("%d ", referenceString[i]);
    }
    printf("\n\n");

    printf("Frames:\n");
    for (int i = 0; i < numReferences; i++) {
        int page = referenceString[i];
        if (!isPageInFrames(frames, FRAME_SIZE, page)) {
            numFaults++;
            // Find the index of the oldest page in frames
            int oldestPageIndex = getOldestPageIndex(referenceString, i, FRAME_SIZE);
            // Replace the oldest page with the current page
            frames[oldestPageIndex] = page;
        }
        displayFrames(frames, FRAME_SIZE);
    }

    printf("\nTotal Page Faults: %d\n", numFaults);

    return 0;
}

void displayFrames(int frames[], int numFrames) {
    for (int i = 0; i < numFrames; i++) {
        printf("%d ", frames[i]);
    }
    printf("\n");
}

bool isPageInFrames(int frames[], int numFrames, int page) {
    for (int i = 0; i < numFrames; i++) {
        if (frames[i] == page) {
            return true;
        }
    }
    return false;
}

int getOldestPageIndex(int pages[], int numPages, int frameIndex) {
    int oldestIndex = 0;
    int oldestReference = numPages; // Initialize with a large number

    for (int i = 0; i < frameIndex; i++) {
        int currentPage = pages[i];
        int j;
        for (j = numPages - 1; j >= 0; j--) {
            if (pages[j] == currentPage) {
                break;
            }
        }
        if (j < oldestReference) {
            oldestIndex = i;
            oldestReference = j;
        }
    }

    return oldestIndex;
}
// que 10 
#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 100

// Function prototypes
void cLook(int requests[], int numRequests, int initialPosition);

int main() {
    int requests[MAX_REQUESTS];
    int numRequests, initialPosition;

    // Input number of requests
    printf("Enter the number of requests: ");
    scanf("%d", &numRequests);

    // Input requests
    printf("Enter the requests:\n");
    for (int i = 0; i < numRequests; i++) {
        scanf("%d", &requests[i]);
    }

    // Input initial position of the head
    printf("Enter the initial position of the head: ");
    scanf("%d", &initialPosition);

    // Perform C-Look scheduling
    cLook(requests, numRequests, initialPosition);

    return 0;
}

void cLook(int requests[], int numRequests, int initialPosition) {
    int totalMovement = 0;
    int currentPos = initialPosition;

    // Sort requests in ascending order
    for (int i = 0; i < numRequests - 1; i++) {
        for (int j = 0; j < numRequests - i - 1; j++) {
            if (requests[j] > requests[j + 1]) {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }

    // Find the index of the first request that is greater than the initial position
    int i;
    for (i = 0; i < numRequests; i++) {
        if (requests[i] >= initialPosition) {
            break;
        }
    }

    // Move towards the last request greater than or equal to the initial position
    for (; i < numRequests; i++) {
        printf("Servicing track %d\n", requests[i]);
        totalMovement += abs(requests[i] - currentPos);
        currentPos = requests[i];
    }

    // Move to the first request
    for (i = 0; i < numRequests && requests[i] < initialPosition; i++) {
        printf("Servicing track %d\n", requests[i]);
        totalMovement += abs(requests[i] - currentPos);
        currentPos = requests[i];
    }

    printf("Total head movement: %d\n", totalMovement);
    }

    //que 13 

#include <stdio.h>
#include <stdbool.h>

#define FRAME_SIZE 3
#define MAX_REFERENCES 20

// Function prototypes
void displayFrames(int frames[], int numFrames);
bool isPageInFrames(int frames[], int numFrames, int page);
int findOptimalPage(int referenceString[], int numReferences, int frames[], int numFrames, int startIndex);

int main() {
    int referenceString[MAX_REFERENCES] = {1, 2, 3, 4, 5, 1, 2, 6, 7, 8, 7, 8, 9, 7, 8, 9, 5, 4, 5, 4};
    int frames[FRAME_SIZE] = {0}; // Initialize frames with 0 (indicating empty)

    int numReferences = sizeof(referenceString) / sizeof(referenceString[0]);
    int numFaults = 0;

    printf("Reference String: ");
    for (int i = 0; i < numReferences; i++) {
        printf("%d ", referenceString[i]);
    }
    printf("\n\n");

    printf("Frames:\n");
    for (int i = 0; i < numReferences; i++) {
        int page = referenceString[i];
        if (!isPageInFrames(frames, FRAME_SIZE, page)) {
            numFaults++;
            // Find the page to replace using the Optimal algorithm
            int index = findOptimalPage(referenceString, numReferences, frames, FRAME_SIZE, i);
            frames[index] = page;
        }
        displayFrames(frames, FRAME_SIZE);
    }

    printf("\nTotal Page Faults: %d\n", numFaults);

    return 0;
}

void displayFrames(int frames[], int numFrames) {
    for (int i = 0; i < numFrames; i++) {
        printf("%d ", frames[i]);
    }
    printf("\n");
}

bool isPageInFrames(int frames[], int numFrames, int page) {
    for (int i = 0; i < numFrames; i++) {
        if (frames[i] == page) {
            return true;
        }
    }
    return false;
}

int findOptimalPage(int referenceString[], int numReferences, int frames[], int numFrames, int startIndex) {
    int index = -1;
    int farthest = -1;

    for (int i = 0; i < numFrames; i++) {
        int j;
        for (j = startIndex; j < numReferences; j++) {
            if (frames[i] == referenceString[j]) {
                if (j > farthest) {
                    farthest = j;
                    index = i;
                }
                break;
            }
        }
        if (j == numReferences) {
            return i; // If a page is not referenced in the future, replace it
        }
    }

    return index;
}
