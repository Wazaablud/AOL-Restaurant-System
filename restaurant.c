#include <stdio.h>
#include <string.h>

struct Customer {
    char name[50];
    float total;
};

/*
savePurchase:
Function ini menyimpan history pembelian customer ke file bernama "Top_Spender.txt"
yang disimpan adalah nama dan total spending customer.
*/
void savePurchase(char name[], float total) {
    FILE *fp = fopen("Top_Spender.txt", "a");
    if (fp == NULL) return;
    fprintf(fp, "%s %.2f\n", name, total);
    fclose(fp);
}

/*
displaySpender : 
Function ini membaca semua semua history pembelian dari "Top_Spender.txt" 
lalu disorting dari yang terbesar ke terkecil (descending) menggunakan bubblesort
lalu akan di print leaderboard semua customer berdasarkan pembelian
*/
void displaySpender() {
    struct Customer customers[100];
    int count = 0;
    FILE *fp = fopen("Top_Spender.txt", "r");

    if (fp == NULL) {
        printf("No history found.\n");
        return;
    }

    while (count < 100 && fscanf(fp, "%s %f", customers[count].name, &customers[count].total) == 2) {
        count++;
    }
    fclose(fp);

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (customers[j].total < customers[j + 1].total) {
                struct Customer temp = customers[j];
                customers[j] = customers[j + 1];
                customers[j + 1] = temp;
            }
        }
    }

    printf("\n--- TOP SPENDER ---\n");
    for (int i = 0; i < count; i++) {
        printf("%d. %s - Rp%.2f\n", i + 1, customers[i].name, customers[i].total);
    }
}

/*
searchCustomer : Function ini mencari nama customer di "Top_Spender.txt" jika ketemu maka total spending akan di tampilkan
jika tidak maka akan print not found
*/
void searchCustomer(char searchName[]) {
    struct Customer p;
    FILE *fp = fopen("Top_Spender.txt", "r");
    int found = 0;

    if (fp == NULL) return;

    while (fscanf(fp, "%s %f", p.name, &p.total) != EOF) {
        if (strcmp(p.name, searchName) == 0) {
            printf("Customer found: %s has total spend of Rp%.2f\n", p.name, p.total);
            found = 1;
        }
    }
    if (!found) printf("Customer not found\n");
    fclose(fp);
}

int main() {
    // Deklarasi variable variable yang akan digunakan
    int mainMenu, choice, quantity, z, keepOrdering = 1;
    float total1, total2, total3, total4, currentTotal = 0;
    char more;
    char customerName[50];
    char itemName[4][10];
    char menu[4][10] = {"Burger", "Pizza", "Taco", "Kebab"};
    char price[4][10] = {"Rp20.000", "Rp35.000", "Rp15.000", "Rp10.000"};    

    // Main program akan loop terus sampai customer exit atau selesai
    while (keepOrdering) {
        // Displays the main menu
        printf("=== Welcome to Le Voun Restaurant! ===\n");
        printf("1. Start Ordering\n");
        printf("2. Top Spender\n");
        printf("3. Search Customer\n");
        printf("4. Exit\n");
        printf("Choice: ");
        scanf("%d", &mainMenu);

        // Option 1: Start ordering food
        if (mainMenu == 1) {
            // Reset totals untuk setiap menu item
            total1 = total2 = total3 = total4 = 0;

            // Tanya nama customer
            printf("Please enter your name: ");
            scanf("%s", customerName);
            printf("Hello, %s\n", customerName);

            // Ordering loop: Loop selama user masih ingin order
            do {
                order:
                // Display the menu
                printf("Here is our menu:\n");
                for (z = 1; z <= 5; z++) {
                    if (z == 5) {
                        printf("%d. Exit order\n", z);
                        break;
                    }
                    printf("%d. %s - %s\n", z, menu[z - 1], price[z - 1]);
                }

                // Tanya pilihan customer
                printf("Enter your choice (1-%d)\n", z);
                scanf("%d", &choice);

                // jika customer memilih exit
                if (choice == z) {
                    break;
                }
                // jika nomor yang di berikan invalid
                else if (choice > z) {
                    printf("Invalid Choice!\n\n");
                    goto order;
                }

                // Tanya customer jumlah menu yang dipilih
                printf("Enter quantity :\n");
                scanf("%d", &quantity);

                // Update total cost berdasarkan pilihan dan jumlah menu
                switch (choice) {
                    case 1: total1 += 20000 * quantity; break;
                    case 2: total2 += 35000 * quantity; break;
                    case 3: total3 += 15000 * quantity; break;
                    case 4: total4 += 10000 * quantity; break;
                    default:
                        printf("Invalid Choice!\n");
                }

                // Tanya apakah customer ingin order lagi
                printf("Do you want to order more? (y/n) ");
                scanf(" %c", &more);

                // Update total
                currentTotal = total1 + total2 + total3 + total4;

            } while (more == 'y' || more == 'Y');

            // Menunjukan Final total ke customer
            printf("Your total is Rp%.2f", currentTotal);

            // Menyimpan pembelian ke file "Top_Spender"
            savePurchase(customerName, currentTotal);

            // Selesai ordering
            keepOrdering = 0;
        }

        // Option 2: Menunjukan top spenders list dari file "Top_Spender.txt"
        else if (mainMenu == 2) {
            displaySpender();
            printf("\n");
        }

        // Option 3: Mencari customer spending total dari file "Top_Spender.txt"
        else if (mainMenu == 3) {
            char sName[50];
            printf("Enter customer name: ");
            scanf("%s", sName);
            searchCustomer(sName);
            printf("\n");
        }

        // Option 4: Exit dari program
        else if (mainMenu == 4) {
            return 0;
        }

        // Handle input invalid
        else {
            printf("Invalid Choice!\n\n");
        }
    }

    return 0;
}

