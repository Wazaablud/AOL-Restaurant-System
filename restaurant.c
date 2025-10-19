#include <stdio.h>

int main() {
  int choice, quantity;
  float total, total1, total2, total3;
  char more;

  printf("Welcome to Nevan bau Restaurant!\n");

  do{
      printf("Here is our menu :\n");
      printf("1. Burger - Rp20.000\n");
      printf("2. Pizza - Rp.35.000\n");
      printf("3. Taco - Rp.15.000\n");
      printf("4. Exit order\n");
      printf("Enter your choice (1-4)\n");
      scanf("%d", &choice); 

      if(choice == 4){
        break;
        }

      printf("Enter quantity :\n");
      scanf("%d", &quantity);

      switch (choice){
      case 1: total1 = 20000 * quantity; break;
      case 2: total2 = 35000 * quantity; break;
      case 3: total3 = 15000 * quantity; break;
      default:
          printf("Invalid Choice!\n");
      }

      printf("Do you want to order more? (y/n) ");
      scanf(" %c", &more);
      total = total1 + total2 + total3;
    } while (more == 'y' || more == 'Y');

  printf("Your total is Rp%.2f", total);
