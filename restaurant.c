#include <stdio.h>

int main() {
	int choice, quantity, i;
	float total, total1, total2, total3, total4;
	char more;
	char name[15];
	char menu[4][10] = {"Burger", "Pizza", "Taco", "Kebab"};
	char price[4][10] = {"Rp20.000", "Rp35.000", "Rp15.000", "Rp10.000"};
	
	FILE *fp = fopen("transaction.txt", "w");

	printf("Welcome to Le Voun Restaurant!\n");

	printf("Please enter your name: ");
	scanf("%s", name);
	printf("Hello, %s\n", name);
	fprintf(fp, "%s\n", name);

	do{
		printf("Here is our menu:\n");
    	for (i = 1; i <= 5; i++) {
    		if (i == 5) {
    			printf("%d. Exit order\n", i);
    			break;
			}
    		printf("%d. %s - %s\n", i, menu[i - 1], price[i - 1]);
		}
    	printf("Enter your choice (1-%d)\n", i);
    	scanf("%d", &choice);
    	fprintf(fp, "%d: ", choice);

    	if(choice == i){
    		break;
    	}

    	printf("Enter quantity :\n");
    	scanf("%d", &quantity);
    	fprintf(fp, "%d\n", quantity);

    	switch (choice){
    		case 1: total1 = 20000 * quantity; break;
			case 2: total2 = 35000 * quantity; break;
			case 3: total3 = 15000 * quantity; break;
			case 4: total4 = 10000 * quantity; break;
			default:
			printf("Invalid Choice!\n");
    	}

    	printf("Do you want to order more? (y/n) ");
    	scanf(" %c", &more);
    	total = total1 + total2 + total3 + total4;
	} while (more == 'y' || more == 'Y');

	printf("Your total is Rp%.2f", total);
	fprintf(fp, "Rp%.2f", total);
	
	fclose(fp);
  
	return 0;
}
