#include "library.c"
//-----------------------------------------------------------THE MENU--------------------------------------------------------//
void clear_screen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    }
//-------------------------------------------------------//
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
//-------------------------------------------------------//
void print_colored(const char* text, const char* color) {
    printf("%s%s\033[0m", color, text);
}
//-------------------------------------------------------//
void display_books(bkptr head) {
    clear_screen();
    if (head == NULL) {
        print_colored("+------------------------------------+\n", "\033[1;31m");
        print_colored("|         No books in database!      |\n", "\033[1;31m");
        print_colored("+------------------------------------+\n", "\033[1;31m");
        return;
    }
    print_colored("\n+---------------------------------------------------------------+-------+\n", "\033[1;34m");
    print_colored("|                         Book Catalog                          |       |\n", "\033[1;34m");
    print_colored("+-------+--------------------------------+----------------------+-------+\n", "\033[1;34m");
    printf("| %-5s | %-30s | %-20s | %-5s|\n", "ID", "Title", "Author", "Copies");
    print_colored("+-------+--------------------------------+----------------------+-------+\n", "\033[1;34m");
    bkptr current = head;
    while (current != NULL) {
        printf("| %-5d | %-30.30s | %-20.20s | %-5d |\n", id_bk(current), title(current), author(current), copies(current));
        current = next_bk(current);
    }
    print_colored("+-------+--------------------------------+----------------------+-------+\n", "\033[1;34m");
}
//-------------------------------------------------------//
void display_borrowers(brptr head) {
    clear_screen();
    if (head == NULL) {
        print_colored("+------------------------------------+\n", "\033[1;31m");
        print_colored("|       No borrowers found!          |\n", "\033[1;31m");
        print_colored("+------------------------------------+\n", "\033[1;31m");
        return;
    }
    print_colored("\n+-------------------------------------------------------+\n", "\033[1;34m");
    print_colored("|                     Borrowers List                    |\n", "\033[1;34m");
    print_colored("+-------+-----------------------------------------------+\n", "\033[1;34m");
    printf("| %-5s | %-45s |\n", "ID", "Name");
    print_colored("+-------+-----------------------------------------------+\n", "\033[1;34m");
    brptr current = head;
    while (current != NULL) {
        printf("| %-5d | %-45s |\n", id_br(current), name(current));
        current = next_br(current);
    }
    print_colored("+-------+-----------------------------------------------+\n", "\033[1;34m");
}
//-------------------------------------------------------//
void display_queue(queue q) {
    clear_screen();
    if (empty_queue(q)) {
        print_colored("+------------------------------------+\n", "\033[1;31m");
        print_colored("|       No active loans found!       |\n", "\033[1;31m");
        print_colored("+------------------------------------+\n", "\033[1;31m");
        return;
    }
    print_colored("\n+-------------------------------------------------------------+\n", "\033[1;34m");
    print_colored("|                         Active Loans                        |\n", "\033[1;34m");
    print_colored("+-------+-------+------------+--------------------------------+\n", "\033[1;34m");
    printf("| %-5s | %-5s | %-10s | %-30s |\n", "Book", "User", "Due Date", "Priority");
    print_colored("+-------+-------+------------+--------------------------------+\n", "\033[1;34m");
    loan *current = q.head;
    while (current != NULL) {
        char prio_color[20];
        switch(priority(current)) {
            case 'O': strcpy(prio_color, "\033[1;31m"); break; // Red for overdue
            case 'H': strcpy(prio_color, "\033[1;33m"); break; // Yellow for high
            case 'M': strcpy(prio_color, "\033[1;32m"); break; // Green for medium
            case 'L': strcpy(prio_color, "\033[1;36m"); break; // Cyan for low
            default: strcpy(prio_color, "\033[0m");
        }
        printf("| %-5d | %-5d | %-10s | %s%-30c\033[0m |\n", idbk_q(current), idbr_q(current), date_q(current), prio_color, priority(current));
        current = next_q(current);
    }
    print_colored("+-------+-------+------------+--------------------------------+\n", "\033[1;34m");
}
//-------------------------------------------------------//
void display_overdue(queue q) {
    clear_screen();
    if (empty_queue(q)) {
        print_colored("+------------------------------------+\n", "\033[1;31m");
        print_colored("|       No loans in the system.      |\n", "\033[1;31m");
        print_colored("+------------------------------------+\n", "\033[1;31m");
        return;
    }
    print_colored("\n+---------------------------------------------------+\n", "\033[1;31m");
    print_colored("|                     Overdue Books                 |\n", "\033[1;31m");
    print_colored("+-------+-------+------------+----------------------+\n", "\033[1;31m");
    printf("| %-5s | %-5s | %-10s | %-20s |\n", "Book", "User", "Due Date", "Status");
    print_colored("+-------+-------+------------+----------------------+\n", "\033[1;31m");
    loan *current = q.head;
    int found = 0;
    while (current) {
        if (priority(current) == 'O') {
            printf("| %-5d | %-5d | %-10s | %-20s |\n", idbk_q(current), idbr_q(current), date_q(current), "Overdue");
            found = 1;
        }
        current = next_q(current);
    }
    if (!found) {
        print_colored("|               No overdue books found.                    |\n", "\033[1;32m");
    }
    print_colored("+-------+-------+------------+----------------------+\n", "\033[1;31m");
}
//-------------------------------------------------------//
void display_menu(bkptr headb, brptr headbr, queue return_q, queue q) {
    int choice;
    while(1) {
        clear_screen();
        print_colored("\n+---------------------------------------+\n", "\033[1;36m");
        print_colored("|           Display Options             |\n", "\033[1;36m");
        print_colored("+---------------------------------------+\n", "\033[1;36m");
        print_colored("|  1. Display All Books                 |\n", "\033[1;37m");
        print_colored("|  2. Display All Borrowers             |\n", "\033[1;37m");
        print_colored("|  3. Display Active Loans              |\n", "\033[1;37m");
        print_colored("|  4. Display Return History            |\n", "\033[1;37m");
        print_colored("|  5. Display Overdue Books             |\n", "\033[1;37m");
        print_colored("|  0. Back to Main Menu                 |\n", "\033[1;37m");
        print_colored("+---------------------------------------+\n", "\033[1;36m");
        print_colored("\nEnter your choice: ", "\033[1;33m");
        if(scanf("%d", &choice) != 1) {
            print_colored("Invalid input!\n", "\033[1;31m");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();
        switch(choice) {
            case 1:
                display_books(headb);
                break;
            case 2:
                display_borrowers(headbr);
                break;
            case 3:
                display_queue(q);
                break;
            case 4:
                date_sort(&return_q);
                display_queue(return_q);
                break;
            break;
            case 5:
                display_overdue(q);
                break;
            case 0:
                return;
            default:
                print_colored("Invalid choice!\n", "\033[1;31m");
        }
        printf("\nPress Enter to continue...");
        getchar();
    }
}
//-------------------------------------------------------//
void search_book_menu(bkptr head) {
    int choice, id;
    char string[64];
    clear_screen();
    print_colored("\n+---------------------------------------+\n", "\033[1;36m");
    print_colored("|             Search Book               |\n", "\033[1;36m");
    print_colored("+---------------------------------------+\n", "\033[1;36m");
    print_colored("|  1. Search by ID                      |\n", "\033[1;37m");
    print_colored("|  2. Search by Title                   |\n", "\033[1;37m");
    print_colored("+---------------------------------------+\n", "\033[1;36m");
    print_colored("\nEnter your choice: ", "\033[1;33m");
    scanf("%d", &choice);
    clear_input_buffer();
    switch(choice) {
        case 1:
            print_colored("\n+---------------------------------------+\n", "\033[1;34m");
            print_colored("|             Search by ID              |\n", "\033[1;34m");
            print_colored("+---------------------------------------+\n", "\033[1;34m");
            printf("Enter book ID: ");
            scanf("%d", &id);
            clear_input_buffer();
            bkptr result = search_bk_id(head, id);
            if(result) {
                print_colored("\n+---------------------------------------+\n", "\033[1;32m");
                print_colored("|               Book Found              |\n", "\033[1;32m");
                print_colored("+---------------------------------------+\n", "\033[1;32m");
                printf("ID: %d\nTitle: %s\nAuthor: %s\nCopies: %d\n", id_bk(result), title(result), author(result), copies(result));
            } else {
                print_colored("\n+---------------------------------------+\n", "\033[1;31m");
                print_colored("|             Book Not Found            |\n", "\033[1;31m");
                print_colored("+---------------------------------------+\n", "\033[1;31m");
            }
            break;
        case 2:
            print_colored("\n+---------------------------------------+\n", "\033[1;34m");
            print_colored("|            Search by Title            |\n", "\033[1;34m");
            print_colored("+---------------------------------------+\n", "\033[1;34m");
            printf("Enter book title: ");
            fgets(string, sizeof(string), stdin);
            string[strcspn(string, "\n")] = 0;
            result = search_bk_title(head, string);
            if(result) {
                print_colored("\n+---------------------------------------+\n", "\033[1;32m");
                print_colored("|               Book Found              |\n", "\033[1;32m");
                print_colored("+---------------------------------------+\n", "\033[1;32m");
                printf("ID: %d\nTitle: %s\nAuthor: %s\nCopies: %d\n", id_bk(result), title(result), author(result), copies(result));
            } else {
                print_colored("\n+---------------------------------------+\n", "\033[1;31m");
                print_colored("|             Book Not Found            |\n", "\033[1;31m");
                print_colored("+---------------------------------------+\n", "\033[1;31m");
            }
            break;
        default:
            print_colored("\n+---------------------------------------+\n", "\033[1;31m");
            print_colored("|             Invalid Choice            |\n", "\033[1;31m");
            print_colored("+---------------------------------------+\n", "\033[1;31m");
    }
}
//-------------------------------------------------------//
void search_borrower_menu(brptr head) {
    int choice, id;
    char string[32];
    clear_screen();
    print_colored("\n+---------------------------------------+\n", "\033[1;36m");
    print_colored("|           Search Borrower             |\n", "\033[1;36m");
    print_colored("+---------------------------------------+\n", "\033[1;36m");
    print_colored("|  1. Search by ID                      |\n", "\033[1;37m");
    print_colored("|  2. Search by Name                    |\n", "\033[1;37m");
    print_colored("+---------------------------------------+\n", "\033[1;36m");
    print_colored("\nEnter your choice: ", "\033[1;33m");
    scanf("%d", &choice);
    clear_input_buffer();
    switch(choice) {
        case 1:
            print_colored("\n+---------------------------------------+\n", "\033[1;34m");
            print_colored("|           Search by ID                |\n", "\033[1;34m");
            print_colored("+---------------------------------------+\n", "\033[1;34m");
            printf("Enter borrower ID: ");
            scanf("%d", &id);
            clear_input_buffer();
            brptr result = search_br_id(head, id);
            if(result) {
                print_colored("\n+---------------------------------------+\n", "\033[1;32m");
                print_colored("|           Borrower Found              |\n", "\033[1;32m");
                print_colored("+---------------------------------------+\n", "\033[1;32m");
                printf("ID: %d\nName: %s\n", id_br(result), name(result));
            } else {
                print_colored("\n+---------------------------------------+\n", "\033[1;31m");
                print_colored("|         Borrower Not Found            |\n", "\033[1;31m");
                print_colored("+---------------------------------------+\n", "\033[1;31m");
            }
            break;
        case 2:
            print_colored("\n+---------------------------------------+\n", "\033[1;34m");
            print_colored("|          Search by Name               |\n", "\033[1;34m");
            print_colored("+---------------------------------------+\n", "\033[1;34m");
            printf("Enter borrower name: ");
            fgets(string, sizeof(string), stdin);
            string[strcspn(string, "\n")] = 0;
            result = search_br_name(head, string);
            if(result) {
                print_colored("\n+---------------------------------------+\n", "\033[1;32m");
                print_colored("|           Borrower Found              |\n", "\033[1;32m");
                print_colored("+---------------------------------------+\n", "\033[1;32m");
                printf("ID: %d\nName: %s\n", id_br(result), name(result));
            } else {
                print_colored("\n+---------------------------------------+\n", "\033[1;31m");
                print_colored("|         Borrower Not Found            |\n", "\033[1;31m");
                print_colored("+---------------------------------------+\n", "\033[1;31m");
            }
            break;
        default:
            print_colored("\n+---------------------------------------+\n", "\033[1;31m");
            print_colored("|           Invalid Choice              |\n", "\033[1;31m");
            print_colored("+---------------------------------------+\n", "\033[1;31m");
    }
}
//-------------------------------------------------------//
void print_menu() {
    clear_screen();
    print_colored("\n+---------------------------------------+\n", "\033[1;36m");
    print_colored("|       Library Management System       |\n", "\033[1;36m");
    print_colored("+---------------------------------------+\n", "\033[1;36m");
    print_colored("|  1. File Operations                   |\n", "\033[1;37m");
    print_colored("|  2. Book Management                   |\n", "\033[1;37m");
    print_colored("|  3. Borrower Management               |\n", "\033[1;37m");
    print_colored("|  4. Loan Management                   |\n", "\033[1;37m");
    print_colored("|  5. Display Options                   |\n", "\033[1;37m");
    print_colored("|  6. Generate Statistics               |\n", "\033[1;37m");
    print_colored("|  7. About                             |\n", "\033[1;37m");
    print_colored("|  0. Exit                              |\n", "\033[1;37m");
    print_colored("+---------------------------------------+\n", "\033[1;36m");
    print_colored("\nEnter your choice: ", "\033[1;33m");
}
//-------------------------------------------------------//
void file_menu(bkptr *headb, brptr *headbr, queue *q, queue *return_q) {
    while(1)
    {
    clear_screen();
    int choice;
    char filename[100];
    print_colored("+---------------------------------------------+\n", "\033[1;36m");
    print_colored("|               File Operations               |\n", "\033[1;36m");
    print_colored("+---------------------------------------------+\n", "\033[1;36m");
    print_colored("|  1. Read Books from File                    |\n", "\033[1;37m");
    print_colored("|  2. Read Borrowers from File                |\n", "\033[1;37m");
    print_colored("|  3. Read Borrowing Transactions from File   |\n", "\033[1;37m");
    print_colored("|  4. Read Returning Transactions from File   |\n", "\033[1;37m");
    print_colored("|  0. Back to Main Menu                       |\n", "\033[1;37m");
    print_colored("+---------------------------------------------+\n", "\033[1;36m");
    print_colored("\nEnter your choice: ", "\033[1;33m");
    if(scanf("%d", &choice) != 1) {
        print_colored("\nInvalid input! Please enter a valid number.\n", "\033[1;31m");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();
    if(choice >= 1 && choice <= 4) {
        print_colored("\nEnter filename: ", "\033[1;33m");
        if(fgets(filename, sizeof(filename), stdin)) {
            filename[strcspn(filename, "\n")] = 0;
            switch(choice) {
                case 1:
                    if(add_books_file(headb, filename))
                        print_colored("\nBooks loaded successfully!\n", "\033[1;32m");
                    else
                        print_colored("\nFailed to load books from file.\n", "\033[1;31m");
                    break;
                case 2:
                    if(add_borrowers_file(headbr, filename))
                        print_colored("\nBorrowers loaded successfully!\n", "\033[1;32m");
                    else
                        print_colored("\nFailed to load borrowers from file.\n", "\033[1;31m");
                    break;
                case 3:
                    if(borrow_file(q, filename))
                        print_colored("\nLoan transactions loaded successfully!\n", "\033[1;32m");
                    else
                        print_colored("\nFailed to load loan transactions from file.\n", "\033[1;31m");
                    break;
                case 4:
                    if(return_file(return_q, filename))
                        print_colored("\nLoan transactions loaded successfully!\n", "\033[1;32m");
                    else
                        print_colored("\nFailed to load loan transactions from file.\n", "\033[1;31m");
                    break;
                default: print_colored("\nInvalid choice! Please select a valid option.\n", "\033[1;31m");
                    break;
            }
            printf("\nPress Enter to continue...");
            getchar();
        }
    } else if (choice == 0) {
            return;
    } else {
        print_colored("\nInvalid choice! Please select a valid option.\n", "\033[1;31m");
        printf("\nPress Enter to continue...");
        getchar();
    }
    }
    printf("\nPress Enter to continue...");
    getchar();
}
//-------------------------------------------------------//
void generate_statistics(bkptr headb, brptr headbr, queue q) {
    // Count books and total copies
    int book_count = 0, total_copies = 0;
    bkptr temp_book = headb;
    while(temp_book) {
        book_count++;
        total_copies += copies(temp_book);
        temp_book = next_bk(temp_book);
    }

    // Count borrowers
    int borrower_count = 0;
    brptr temp_borr = headbr;
    while(temp_borr) {
        borrower_count++;
        temp_borr = next_br(temp_borr);
    }

    // Count loans by priority
    int loan_count = 0, overdue = 0, high_prio = 0, med_prio = 0, low_prio = 0;
    loan *temp_loan = q.head;
    while(temp_loan != NULL) {
        loan_count++;
        if (priority(temp_loan) == 'O') overdue++;
            if (priority(temp_loan) == 'H') high_prio++;
            if (priority(temp_loan) == 'M') med_prio++;
            if (priority(temp_loan) == 'L') low_prio++;
        temp_loan = next_q(temp_loan);
    }

    // Generate SVG visualization of statistics
    FILE *graph = fopen("library_statistics.svg", "w");
    if (graph == NULL) {
        print_colored("Error creating SVG statistics file!\n", "\033[1;31m");
        fclose(graph);
        return;
    }

    fprintf(graph, "<svg width='2000' height='1600' xmlns='http://www.w3.org/2000/svg'>\n");

    // Write main title
    fprintf(graph, "<text x='850' y='30' font-family='Arial' font-size='30' text-anchor='middle' fill='black'>Library Management System Statistics</text>\n");

    // Graph 1: Books and Borrowers
    fprintf(graph, "<text x='850' y='80' font-family='Arial' font-size='20' text-anchor='middle' fill='black'>1. Books and Borrowers</text>\n");

    // Calculate bar heights (proportional)
    int max_count = (book_count > borrower_count) ? book_count : borrower_count;
    if (max_count == 0) max_count = 1; // Avoid division by zero

    float book_height = ((float)book_count / max_count) * 275;
    float borrower_height = ((float)borrower_count / max_count) * 275;
    book_height = (book_height == 0) ? 5 : book_height;
    borrower_height = (borrower_height == 0) ? 5 : borrower_height;

    // Draw bars
    fprintf(graph, "<rect x='750' y='%.2f' width='50' height='%.2f' fill='blue' />\n", 400 - book_height, book_height);
    fprintf(graph, "<rect x='850' y='%.2f' width='50' height='%.2f' fill='green' />\n", 400 - borrower_height, borrower_height);

    // Add values
    fprintf(graph, "<text x='760' y='%.2f' font-size='18' fill='black'>%d</text>\n", 400 - book_height - 10, book_count);
    fprintf(graph, "<text x='860' y='%.2f' font-size='18' fill='black'>%d</text>\n", 400 - borrower_height - 10, borrower_count);

    // Labels
    fprintf(graph, "<text x='760' y='420' font-size='18' fill='black'>Books</text>\n");
    fprintf(graph, "<text x='860' y='420' font-size='18' fill='black'>Borrowers</text>\n");

    // Graph 2: Loan Priorities
    fprintf(graph, "<text x='850' y='450' font-family='Arial' font-size='20' text-anchor='middle' fill='black'>2. Loan Priority Distribution</text>\n");

    int priorities[4] = {overdue, high_prio, med_prio, low_prio};
    char *colors[4] = {"red", "yellow", "green", "cyan"};
    char *labels[4] = {"Overdue", "High", "Medium", "Low"};

    for (int i = 0; i < 4; i++) {
        float height = ((float)priorities[i] / (loan_count > 0 ? loan_count : 1)) * 300;
        height = (height == 0) ? 5 : height;
        int x = 650 + i * 100;

        fprintf(graph, "<rect x='%d' y='%.2f' width='50' height='%.2f' fill='%s' />\n", x, 800 - height, height, colors[i]);
        fprintf(graph, "<text x='%d' y='%.2f' font-size='18' fill='black'>%d</text>\n", x + 10, 800 - height - 10, priorities[i]);
        fprintf(graph, "<text x='%d' y='820' font-size='18' fill='black'>%s</text>\n", x + 10, labels[i]);
    }

    // Graph 3: Copies vs. Loans
    fprintf(graph, "<text x='850' y='850' font-family='Arial' font-size='20' text-anchor='middle' fill='black'>3. Total Copies vs. Active Loans</text>\n");

    max_count = (total_copies > loan_count) ? total_copies : loan_count;
    if (max_count == 0) max_count = 1; // Avoid division by zero

    float copies_height = ((float)total_copies / max_count) * 300;
    float loans_height = ((float)loan_count / max_count) * 300;
    copies_height = (copies_height == 0) ? 5 : copies_height;
    loans_height = (loans_height == 0) ? 5 : loans_height;

    fprintf(graph, "<rect x='750' y='%.2f' width='50' height='%.2f' fill='orange' />\n", 1200 - copies_height, copies_height);
    fprintf(graph, "<rect x='850' y='%.2f' width='50' height='%.2f' fill='purple' />\n", 1200 - loans_height, loans_height);

    fprintf(graph, "<text x='760' y='%.2f' font-size='18' fill='black'>%d</text>\n", 1200 - copies_height - 10, total_copies);
    fprintf(graph, "<text x='860' y='%.2f' font-size='18' fill='black'>%d</text>\n", 1200 - loans_height - 10, loan_count);

    fprintf(graph, "<text x='760' y='1220' font-size='18' fill='black'>Copies</text>\n");
    fprintf(graph, "<text x='860' y='1220' font-size='18' fill='black'>Loans</text>\n");

    fprintf(graph, "</svg>\n");
    fclose(graph);
    //console
    clear_screen();
    print_colored("\n+-----------------------------------------------+ \n", "\033[1;32m");
    print_colored("|            Library Statistics                 | \n", "\033[1;32m");
    print_colored("+-----------------------------------------------+ \n", "\033[1;32m");
    printf("|  Total Books: %-30d  |\n", book_count);
    printf("|  Total Copies: %-29d  |\n", total_copies);
    printf("|  Registered Borrowers: %-22d |\n", borrower_count);
    printf("|  Active Loans: %-29d  |\n", loan_count);
    printf("|  Overdue Books: %-28d  |\n", overdue);
    printf("|  High Priority Loans: %-24d|\n", high_prio);
    printf("|  Medium Priority Loans: %-22d|\n", med_prio);
    printf("|  Low Priority Loans: %-25d|\n", low_prio);
    print_colored("+-----------------------------------------------+ \n", "\033[1;32m");
    print_colored("Visual statistics generated in library_statistics.svg\n", "\033[1;32m");
}
//-------------------------------------------------------//
void book_management_menu(bkptr *head) {
    int choice, n, id;
    char title[64];
    while(1) {
        clear_screen();
        print_colored("\n+---------------------------------------+\n", "\033[1;36m");
        print_colored("|           Book Management             |\n", "\033[1;36m");
        print_colored("+---------------------------------------+\n", "\033[1;36m");
        print_colored("|  1. Add Books                         |\n", "\033[1;37m");
        print_colored("|  2. Remove Book by ID                 |\n", "\033[1;37m");
        print_colored("|  3. Remove Book by Title              |\n", "\033[1;37m");
        print_colored("|  4. Search Book                       |\n", "\033[1;37m");
        print_colored("|  5. Display Books                     |\n", "\033[1;37m");
        print_colored("|  0. Back to Main Menu                 |\n", "\033[1;37m");
        print_colored("+---------------------------------------+\n", "\033[1;36m");
        print_colored("\nEnter your choice: ", "\033[1;33m");
        if(scanf("%d", &choice) != 1) {
            print_colored("\nInvalid input! Please enter a valid number.\n", "\033[1;31m");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();
        switch(choice) {
            case 1:
                print_colored("\n+---------------------------------------+\n", "\033[1;34m");
                print_colored("|              Add Books                |\n", "\033[1;34m");
                print_colored("+---------------------------------------+\n", "\033[1;34m");
                printf("How many books to add? ");
                scanf("%d", &n);
                clear_input_buffer();
                if(add_book(head, n))
                    print_colored("\nBooks added successfully!\n", "\033[1;32m");
                break;
            case 2:
                print_colored("\n+---------------------------------------+\n", "\033[1;34m");
                print_colored("|           Remove Book by ID           |\n", "\033[1;34m");
                print_colored("+---------------------------------------+\n", "\033[1;34m");
                printf("Enter book ID to remove: ");
                scanf("%d", &id);
                clear_input_buffer();
                remove_bk_id(head, id);
                print_colored("\nBook removed if found!\n", "\033[1;32m");
                break;
            case 3:
                print_colored("\n+---------------------------------------+\n", "\033[1;34m");
                print_colored("|         Remove Book by Title          |\n", "\033[1;34m");
                print_colored("+---------------------------------------+\n", "\033[1;34m");
                printf("Enter book title to remove: ");
                fgets(title, sizeof(title), stdin);
                title[strcspn(title, "\n")] = 0;
                remove_bk_title(head, title);
                print_colored("\nBook removed if found!\n", "\033[1;32m");
                break;
            case 4:
                print_colored("\n+---------------------------------------+\n", "\033[1;34m");
                print_colored("|             Search Book               |\n", "\033[1;34m");
                print_colored("+---------------------------------------+\n", "\033[1;34m");
                search_book_menu(*head);
                break;
            case 5:
                print_colored("\n+---------------------------------------+\n", "\033[1;34m");
                print_colored("|            Display Books              |\n", "\033[1;34m");
                print_colored("+---------------------------------------+\n", "\033[1;34m");
                display_books(*head);
                break;
            case 0:
                print_colored("\nReturning to main menu...\n", "\033[1;32m");
                return;
            default:
                print_colored("\nInvalid choice! Please select a valid option.\n", "\033[1;31m");
        }
        printf("\nPress Enter to continue...");
        getchar();
    }
}
//-------------------------------------------------------//
void borrower_management_menu(brptr *head) {
    int choice, n, id;
    char name[32];
    while(1) {
        clear_screen();
        print_colored("\n+---------------------------------------+\n", "\033[1;36m");
        print_colored("|         Borrower Management           |\n", "\033[1;36m");
        print_colored("+---------------------------------------+\n", "\033[1;36m");
        print_colored("|  1. Add Borrowers                     |\n", "\033[1;37m");
        print_colored("|  2. Remove Borrower by ID             |\n", "\033[1;37m");
        print_colored("|  3. Remove Borrower by Name           |\n", "\033[1;37m");
        print_colored("|  4. Search Borrower                   |\n", "\033[1;37m");
        print_colored("|  5. Display Borrowers                 |\n", "\033[1;37m");
        print_colored("|  0. Back to Main Menu                 |\n", "\033[1;37m");
        print_colored("+---------------------------------------+\n", "\033[1;36m");
        print_colored("\nEnter your choice: ", "\033[1;33m");
        if(scanf("%d", &choice) != 1) {
            print_colored("\nInvalid input! Please enter a valid number.\n", "\033[1;31m");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();
        switch(choice) {
            case 1:
                print_colored("\n+---------------------------------------+\n", "\033[1;34m");
                print_colored("|              Add Borrowers            |\n", "\033[1;34m");
                print_colored("+---------------------------------------+\n", "\033[1;34m");
                printf("How many borrowers to add? ");
                scanf("%d", &n);
                clear_input_buffer();
                if(add_borrower(head, n))
                    print_colored("\nBorrowers added successfully!\n", "\033[1;32m");
                break;
            case 2:
                print_colored("\n+---------------------------------------+\n", "\033[1;34m");
                print_colored("|          Remove Borrower by ID        |\n", "\033[1;34m");
                print_colored("+---------------------------------------+\n", "\033[1;34m");
                printf("Enter borrower ID to remove: ");
                scanf("%d", &id);
                clear_input_buffer();
                remove_br_id(head, id);
                print_colored("\nBorrower removed if found!\n", "\033[1;32m");
                break;
            case 3:
                print_colored("\n+---------------------------------------+\n", "\033[1;34m");
                print_colored("|        Remove Borrower by Name        |\n", "\033[1;34m");
                print_colored("+---------------------------------------+\n", "\033[1;34m");
                printf("Enter borrower name to remove: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0;
                remove_br_title(head, name);
                print_colored("\nBorrower removed if found!\n", "\033[1;32m");
                break;
            case 4:
                print_colored("\n+---------------------------------------+\n", "\033[1;34m");
                print_colored("|            Search Borrower            |\n", "\033[1;34m");
                print_colored("+---------------------------------------+\n", "\033[1;34m");
                search_borrower_menu(*head);
                break;
            case 5:
                print_colored("\n+---------------------------------------+\n", "\033[1;34m");
                print_colored("|           Display Borrowers           |\n", "\033[1;34m");
                print_colored("+---------------------------------------+\n", "\033[1;34m");
                display_borrowers(*head);
                break;
            case 0:
                print_colored("\nReturning to main menu...\n", "\033[1;32m");
                return;
            default:
                print_colored("\nInvalid choice! Please select a valid option.\n", "\033[1;31m");
        }
        printf("\nPress Enter to continue...");
        getchar();
    }
}
//-------------------------------------------------------//
void loan_management_menu(queue *q, queue *return_q, bkptr headb, brptr headbr) {
    int choice;
    while(1) {
        clear_screen();
        print_colored("\n+---------------------------------------+\n", "\033[1;36m");
        print_colored("|           Loan Management             |\n", "\033[1;36m");
        print_colored("+---------------------------------------+\n", "\033[1;36m");
        print_colored("|  1. Borrow Book                       |\n", "\033[1;37m");
        print_colored("|  2. Return Book                       |\n", "\033[1;37m");
        print_colored("|  3. Display Active Loans              |\n", "\033[1;37m");
        print_colored("|  4. Display Overdue Books             |\n", "\033[1;37m");
        print_colored("|  5. Display Return History            |\n", "\033[1;37m");
        print_colored("|  0. Back to Main Menu                 |\n", "\033[1;37m");
        print_colored("+---------------------------------------+\n", "\033[1;36m");
        print_colored("\nEnter your choice: ", "\033[1;33m");
        if(scanf("%d", &choice) != 1) {
            print_colored("\nInvalid input! Please enter a valid number.\n", "\033[1;31m");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();
        switch(choice) {
            case 1:
                if(borrow_enqueue(q, headb, headbr))
                    print_colored("\nBook borrowed successfully!\n", "\033[1;32m");
                break;
            case 2: {
                if(dequeue_borrow(q, return_q))
                    print_colored("\nBook returned successfully!\n", "\033[1;32m");
                else print_colored("\nNo one has borrowed a book :(","\033[1;31m");
                break;
            }
            case 3:
                display_queue(*q);
                break;
            case 4:
                display_overdue(*q);
                break;
            case 5:
                date_sort(return_q);
                display_queue(*return_q);
                break;
            case 0:
                print_colored("\nReturning to main menu...\n", "\033[1;32m");
                return;
            default:
                print_colored("\nInvalid choice! Please select a valid option.\n", "\033[1;31m");
        }
        printf("\nPress Enter to continue...");
        getchar();
    }
}
//-------------------------------------------------------//
int main() {
    bkptr headb = NULL;
    brptr headbr = NULL;
    queue q, return_q;
    create_queue(&q);
    create_queue(&return_q);
    int choice;
    while(1) {
        print_menu();
        if(scanf("%d", &choice) != 1)
        {
            print_colored("Invalid input!\n", "\033[1;31m");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();
        switch(choice) {
            case 1: // File Operations
                file_menu(&headb, &headbr, &q , &return_q);
                break;
            case 2: // Book Management
                book_management_menu(&headb);
                break;
            case 3: // Borrower Management
                borrower_management_menu(&headbr);
                break;
            case 4: // Loan Management
                loan_management_menu(&q, &return_q, headb, headbr);
                break;
            case 5: // Display Options
                display_menu(headb, headbr, return_q, q);
                break;
            case 6: // Generate Statistics
                generate_statistics(headb, headbr, q);
                printf("\nPress Enter to continue...");
                getchar();
                break;
            case 7: //About
                clear_screen();
                printf("Made by:");
                print_colored("\nSidAli BEGGAR   ", "\033[31m");
                printf("&");
                print_colored("   Souhail EL FRAIHI", "\033[34m");
                printf("\n   1CP G14              1CP G01");
                printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nHint: use Konami code :)");
                int konami_code[] = {UP, UP, DOWN, DOWN, LEFT, RIGHT, LEFT, RIGHT, B_KEY, A_KEY};
                int konami_length = 10;
                int input_sequence[10];  // To store user input
                int index = 0;
                while (index < konami_length) {
                    int ch = _getch();  // Read a single key press
                    if (ch == 13) break;
                    if (ch == 0 || ch == 224) {
                        ch = _getch();
                    }
                    input_sequence[index] = ch;
                    index++;
                    for (int i = 0; i < index; i++) {
                        if (input_sequence[i] != konami_code[i]) {
                        index = 0;  // Reset input
                        break;
                        }
                    }
                    if (index == konami_length) {
                        char filename[] = ".\\bin\\chocolate-doom-3.1.0-win64\\chocolate-doom.exe";
                        clear_screen();
                        print_colored("\nLaunching DOOM...\n", "\033[1;32m");
                        system(filename);
                        break;
                    }
                }
                break;
            case 0: // Exit
                clear_screen();
                print_colored("Thank you for using the Library Management System!\n", "\033[1;32m");
                return 0;
            default:
                print_colored("Invalid choice!\n", "\033[1;31m");
                break;
        }
    }
    return 0;
}
