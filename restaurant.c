#include <stdio.h>
#include <string.h>

struct Customer {
	char name[50];
	float total;
};

void savePurchase(char name[], float total) {
	FILE *fp = fopen("Top Spender.txt", "a");
    if (fp == NULL) return;
    fprintf(fp, "%s %.2f\n", name, total);
    fclose(fp);
}

void displaySpender() {
    struct Customer customers[100];
    int count = 0;
    FILE *fp = fopen("Top Spender.txt", "r");

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

void searchCustomer(char searchName[]) {
    struct Customer p;
    FILE *fp = fopen("Top Spender.txt", "r");
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
	int mainMenu, choice, quantity, z, keepOrdering = 1;
	float total1, total2, total3, total4, currentTotal = 0;
	char more;
	char customerName[50];
	char itemName[4][10];
	char menu[4][10] = {"Burger", "Pizza", "Taco", "Kebab"};
	char price[4][10] = {"Rp20.000", "Rp35.000", "Rp15.000", "Rp10.000"};	

	while (keepOrdering) {
		printf("=== Welcome to Le Voun Restaurant! ===\n");
		printf("1. Start Ordering\n");
		printf("2. Top Spender\n");
		printf("3. Search Customer\n");
		printf("4. Exit\n");
		printf("Choice: ");
		scanf("%d", &mainMenu);

		if (mainMenu == 1) {
			total1 = total2 = total3 = total4 = 0;
			printf("Please enter your name: ");
			scanf("%s", customerName);
			printf("Hello, %s\n", customerName);

			do{
				order:
				printf("Here is our menu:\n");
    			for (z = 1; z <= 5; z++) {
    				if (z == 5) {
    					printf("%d. Exit order\n", z);
    					break;
					}
    				printf("%d. %s - %s\n", z, menu[z - 1], price[z - 1]);
				}
    			printf("Enter your choice (1-%d)\n", z);
    			scanf("%d", &choice);
    	
    			if (choice == z) {
    				break;
				}
				else if (choice > z) {
					printf("Invalid Choice!\n\n");
					goto order;
				}

    			printf("Enter quantity :\n");
    			scanf("%d", &quantity);

    			switch (choice){
    				case 1: total1 += 20000 * quantity; break;
					case 2: total2 += 35000 * quantity; break;
					case 3: total3 += 15000 * quantity; break;
					case 4: total4 += 10000 * quantity; break;
					default:
					printf("Invalid Choice!\n");
    			}

    			printf("Do you want to order more? (y/n) ");
    			scanf(" %c", &more);
    			currentTotal = total1 + total2 + total3 + total4;
			} while (more == 'y' || more == 'Y');

			printf("Your total is Rp%.2f", currentTotal);
			savePurchase(customerName, currentTotal);
			keepOrdering = 0;
		}
		else if (mainMenu == 2) {
			displaySpender();
			printf("\n");
		}
		else if (mainMenu == 3) {
			char sName[50];
			printf("Enter customer name: ");
			scanf("%s", sName);
			searchCustomer(sName);
			printf("\n");
		}
		else if (mainMenu == 4) {
			return 0;
		}
		else {
			printf("Invalid Choice!\n\n");
		}
	}
  
	return 0;
}
