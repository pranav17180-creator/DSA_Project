#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Item {
    int id;
    char type[10];
    char name[50];
    char category[30];
    char location[50];
    char date[20];
    char contact[20];
    int recovered;
    struct Item *next;
} Item;

Item *head = NULL;
int nextId = 1;

void saveData() {
    FILE *fp = fopen("items.dat", "wb");
    if (fp == NULL) {
        printf("File error!\n");
        return;
    }

    Item *temp = head;
    while (temp != NULL) {
        fwrite(temp, sizeof(Item), 1, fp);
        temp = temp->next;
    }

    fclose(fp);
}

void loadData() {
    FILE *fp = fopen("items.dat", "rb");
    if (fp == NULL)
        return;

    Item data;

    while (fread(&data, sizeof(Item), 1, fp) == 1) {
        Item *newNode = malloc(sizeof(Item));

        if (newNode == NULL)
            break;

        *newNode = data;
        newNode->next = NULL;

        if (head == NULL)
            head = newNode;
        else {
            Item *temp = head;
            while (temp->next != NULL)
                temp = temp->next;
            temp->next = newNode;
        }

        if (data.id >= nextId)
            nextId = data.id + 1;
    }

    fclose(fp);
}

void addItem() {
    Item *newNode = malloc(sizeof(Item));

    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    newNode->id = nextId++;
    newNode->recovered = 0;

    printf("Enter type (Lost/Found): ");
    scanf("%9s", newNode->type);

    printf("Enter item name: ");
    scanf(" %49[^\n]", newNode->name);

    printf("Enter category: ");
    scanf(" %29[^\n]", newNode->category);

    printf("Enter location: ");
    scanf(" %49[^\n]", newNode->location);

    printf("Enter date (DD-MM-YYYY): ");
    scanf("%19s", newNode->date);

    printf("Enter contact number: ");
    scanf("%19s", newNode->contact);

    newNode->next = NULL;

    if (head == NULL)
        head = newNode;
    else {
        Item *temp = head;

        while (temp->next != NULL)
            temp = temp->next;

        temp->next = newNode;
    }

    saveData();
    printf("Item added successfully! ID: %d\n",
           newNode->id);
}

void displayItems() {
    Item *temp = head;

    if (temp == NULL) {
        printf("No records found!\n");
        return;
    }

    while (temp != NULL) {
        printf("\nID: %d", temp->id);
        printf("\nType: %s", temp->type);
        printf("\nName: %s", temp->name);
        printf("\nCategory: %s", temp->category);
        printf("\nLocation: %s", temp->location);
        printf("\nDate: %s", temp->date);
        printf("\nContact: %s", temp->contact);
        printf("\nStatus: %s\n",
            temp->recovered ? "Recovered" : "Pending");

        temp = temp->next;
    }
}

void searchItem() {
    char key[50];
    int found = 0;

    printf("Enter item name to search: ");
    scanf(" %49[^\n]", key);

    Item *temp = head;

    while (temp != NULL) {
        if (strcmp(temp->name, key) == 0) {
            printf("\nItem Found!");
            printf("\nID: %d", temp->id);
            printf("\nType: %s", temp->type);
            printf("\nLocation: %s\n", temp->location);
            found = 1;
        }

        temp = temp->next;
    }

    if (!found)
        printf("Item not found!\n");
}

void sortItems() {
    if (head == NULL || head->next == NULL) {
        printf("Not enough records to sort!\n");
        return;
    }

    int swapped;
    Item *ptr;
    Item *last = NULL;

    do {
        swapped = 0;
        ptr = head;

        while (ptr->next != last) {
            if (strcmp(ptr->name,
                       ptr->next->name) > 0) {
                Item temp = *ptr;
                Item *nextNode = ptr->next;

                *ptr = *nextNode;
                *nextNode = temp;

                Item *after = nextNode->next;
                ptr->next = nextNode;
                nextNode->next = after;

                swapped = 1;
            }

            ptr = ptr->next;
        }

        last = ptr;

    } while (swapped);

    saveData();
    printf("Items sorted alphabetically!\n");
}

void markRecovered() {
    int id, found = 0;

    printf("Enter item ID: ");
    scanf("%d", &id);

    Item *temp = head;

    while (temp != NULL) {
        if (temp->id == id) {
            temp->recovered = 1;
            found = 1;
            break;
        }

        temp = temp->next;
    }

    if (found) {
        saveData();
        printf("Item marked as recovered!\n");
    } else {
        printf("Item ID not found!\n");
    }
}

int main() {
    int choice;

    loadData();

    do {
        printf("\n===== CAMPUS LOST & FOUND =====\n");
        printf("1. Report Lost/Found Item\n");
        printf("2. Display All Items\n");
        printf("3. Search Item\n");
        printf("4. Sort Items by Name\n");
        printf("5. Mark Item as Recovered\n");
        printf("6. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addItem(); break;
            case 2: displayItems(); break;
            case 3: searchItem(); break;
            case 4: sortItems(); break;
            case 5: markRecovered(); break;
            case 6:
                saveData();
                printf("Thank you!\n");
                break;
            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 6);

    return 0;
}