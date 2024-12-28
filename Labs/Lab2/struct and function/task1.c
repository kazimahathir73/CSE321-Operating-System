#include <stdio.h>

struct item {
    int quantity;
    float unit_price;
};

float calculation(struct item i) {
    return i.quantity * i.unit_price;
}

int main()
{
    struct item paratha, vegetable, mineral_water;
    int num_people;
    float individual_bill;

    printf("Quantity Of Paratha: ");
    scanf("%d", &paratha.quantity);
    printf("Unit Price: ");
    scanf("%f", &paratha.unit_price);

    printf("Quantity Of Vegetables: ");
    scanf("%d", &vegetable.quantity);
    printf("Unit Price: ");
    scanf("%f", &vegetable.unit_price);

    printf("Quantity Of Mineral Water: ");
    scanf("%d", &mineral_water.quantity);
    printf("Unit Price: ");
    scanf("%f", &mineral_water.unit_price);
    
    printf("Number of People: ");
    scanf("%d", &num_people);
    
    individual_bill = (calculation(paratha)+calculation(vegetable)+calculation(mineral_water))/num_people;
    
    printf("Individual people will pay: %f tk\n", individual_bill);

    return 0;
}