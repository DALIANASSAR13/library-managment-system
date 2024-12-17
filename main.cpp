#include <iostream>
#include <string>
using namespace std;

class Book {
public:
    string title;
    string author;
    string ISBN;
    Book(string t, string a, string i) : title(t), author(a), ISBN(i) {}
    ~Book() {}
};

class Fiction : public Book {
public:
    Fiction(string t, string a, string i) : Book(t, a, i) {}
};

class NonFiction : public Book {
public:
    NonFiction(string t, string a, string i) : Book(t, a, i) {}
};

struct FictionNode {
    Fiction* book;
    FictionNode* next;

    FictionNode(Fiction* b) : book(b), next(NULL) {}
};

class FictionList {
private:
    FictionNode* head;
public:
    FictionList() : head(NULL) {}

    void AddBook(Fiction* book) {
        FictionNode* newNode = new FictionNode(book);
        newNode->next = head;
        head = newNode;
        cout << "Fiction Book \"" << book->title << "\" added.\n";
    }

    void RemoveBook(string isbn) {
        FictionNode* temp = head;
        FictionNode* prev = NULL;
        while (temp != NULL && temp->book->ISBN != isbn) {
            prev = temp;
            temp = temp->next;
        }

        if (temp == NULL) {
            cout << "Book with ISBN " << isbn << " not found.\n";
            return;
        }

        if (prev == NULL) {
            head = head->next;
        } else {
            prev->next = temp->next;
        }
        delete temp;
        cout << "Fiction Book with ISBN " << isbn << " removed.\n";
    }

    Fiction* SearchBook(string query) {
        FictionNode* temp = head;
        while (temp != NULL) {
            if (temp->book->title == query || temp->book->ISBN == query) {
                return temp->book;
            }
            temp = temp->next;
        }
        return NULL;
    }

    void Display() {
        FictionNode* temp = head;
        while (temp != NULL) {
            cout << temp->book->title << endl;
            temp = temp->next;
        }
    }
};

struct NonFictionNode {
    NonFiction* book;
    NonFictionNode* next;
    NonFictionNode* prev;

    NonFictionNode(NonFiction* b) : book(b), next(NULL), prev(NULL) {}
};

class NonFictionList {
private:
    NonFictionNode* head;
public:
    NonFictionList() : head(NULL) {}

    void AddBook(NonFiction* book) {
        NonFictionNode* newNode = new NonFictionNode(book);
        newNode->next = head;
        if (head != NULL) {
            head->prev = newNode;
        }
        head = newNode;
        cout << "Non-Fiction Book \"" << book->title << "\" added.\n";
    }

    void RemoveBook(string isbn) {
        NonFictionNode* temp = head;
        while (temp != NULL && temp->book->ISBN != isbn) {
            temp = temp->next;
        }

        if (temp == NULL) {
            cout << "Book with ISBN " << isbn << " not found.\n";
            return;
        }

        if (temp->prev != NULL) {
            temp->prev->next = temp->next;
        } else {
            head = temp->next;
        }

        if (temp->next != NULL) {
            temp->next->prev = temp->prev;
        }

        delete temp;
        cout << "Non-Fiction Book with ISBN " << isbn << " removed.\n";
    }

    NonFiction* SearchBook(string query) {
        NonFictionNode* temp = head;
        while (temp != NULL) {
            if (temp->book->title == query || temp->book->ISBN == query) {
                return temp->book;
            }
            temp = temp->next;
        }
        return NULL;
    }

    void Display() {
        NonFictionNode* temp = head;
        while (temp != NULL) {
            cout << temp->book->title << endl;
            temp = temp->next;
        }
    }
};

class RecentlyAddedStack {
private:
    static const int MAX = 5;
    Book* stack[MAX];
    int top;

public:
    RecentlyAddedStack() : top(-1) {}

    void pushBook(Book* book) {
        if (top == MAX - 1) {
            cout << "Stack overflow.\n";
            return;
        }
        stack[++top] = book;
    }

    void displayRecentBooks() {
        if (top == -1) {
            cout << "No recently added books.\n";
            return;
        }
        cout << "Recently Added Books:\n";
        for (int i = 0; i <= top; i++) {
            cout << stack[i]->title << endl;
        }
    }
};

class BorrowQueue {
private:
    static const int MAX = 10;
    Book* queue[MAX];
    int front, rear, size;

public:
    BorrowQueue() : front(0), rear(0), size(0) {}

    void enqueueBook(Book* book) {
        if (size == MAX) {
            dequeueBook();
        }
        queue[rear] = book;
        rear = (rear + 1) % MAX;
        size++;
    }

    void dequeueBook() {
        if (size == 0) {
            cout << "Queue underflow.\n";
            return;
        }
        front = (front + 1) % MAX;
        size--;
    }

    void displayBorrowedBooks() {
        if (size == 0) {
            cout << "No borrowed books.\n";
            return;
        }
        cout << "Borrowing History:\n";
        for (int i = 0; i < size; i++) {
            cout << queue[(front + i) % MAX]->title << endl;
        }
    }
};

class Library {
private:
    FictionList fictionList;
    NonFictionList nonFictionList;
    RecentlyAddedStack recentlyAddedStack;
    BorrowQueue borrowQueue;

public:
    void addBook(string title, string author, string ISBN, string type) {
        if (type == "Fiction") {
            Fiction* book = new Fiction(title, author, ISBN);
            fictionList.AddBook(book);
            recentlyAddedStack.pushBook(book);
        } else if (type == "NonFiction") {
            NonFiction* book = new NonFiction(title, author, ISBN);
            nonFictionList.AddBook(book);
            recentlyAddedStack.pushBook(book);
        } else {
            cout << "Invalid book type.\n";
        }
    }

    void removeBook(string ISBN) {
        if (fictionList.SearchBook(ISBN)) {
            fictionList.RemoveBook(ISBN);
        } else if (nonFictionList.SearchBook(ISBN)) {
            nonFictionList.RemoveBook(ISBN);
        } else {
            cout << "Book with ISBN " << ISBN << " not found.\n";
        }
    }

    void searchBook(string query) {
        Book* book = fictionList.SearchBook(query);
        if (book != nullptr) {
            cout << "Found in Fiction: " << book->title << " by " << book->author << endl;
            return;
        }

        book = nonFictionList.SearchBook(query);
        if (book != nullptr) {
            cout << "Found in NonFiction: " << book->title << " by " << book->author << endl;
            return;
        }

        cout << "Book not found.\n";
    }

    void borrowBook(string ISBN) {
        Book* book = fictionList.SearchBook(ISBN);
        if (book == NULL) {
            book = nonFictionList.SearchBook(ISBN);
        }

        if (book != NULL) {
            borrowQueue.enqueueBook(book);
            cout << "Borrowed: " << book->title << endl;
        } else {
            cout << "Book not found.\n";
        }
    }

    void viewRecentlyAddedBooks() {
        recentlyAddedStack.displayRecentBooks();
    }

    void viewBorrowingHistory() {
        borrowQueue.displayBorrowedBooks();
    }
};

int main() {
    Library library;
    int choice;
    char title[100], author[100], ISBN[20], type[20];

    do {
        printf("\nLibrary Management System\n");
        printf("1. Add Book\n2. Remove Book\n3. Search Book\n4. View Recently Added Books\n");
        printf("5. View Borrowing History\n6. Borrow Book\n7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();  // Consume newline

        if (choice == 1) {
            printf("Enter title: ");
            scanf("%99[^\n]", title);
            getchar();  // Consume newline

            printf("Enter author: ");
            scanf("%99[^\n]", author);
            getchar();  // Consume newline

            printf("Enter ISBN: ");
            scanf("%s", ISBN);

            printf("Enter type (Fiction/NonFiction): ");
            scanf("%s", type);

            library.addBook(title, author, ISBN, type);
        } else if (choice == 2) {
            printf("Enter ISBN to remove: ");
            scanf("%s", ISBN);
            library.removeBook(ISBN);
        } else if (choice == 3) {
            printf("Enter title or ISBN to search: ");
            scanf("%s", ISBN);
            library.searchBook(ISBN);
        } else if (choice == 4) {
            library.viewRecentlyAddedBooks();
        } else if (choice == 5) {
            library.viewBorrowingHistory();
        } else if (choice == 6) {
            printf("Enter ISBN to borrow: ");
            scanf("%s", ISBN);
            library.borrowBook(ISBN);
        } else if (choice == 7) {
            printf("Exiting...\n");
        } else {
            printf("Invalid choice.\n");
        }

    } while (choice != 7);

    return 0;
}

