#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int id;       
    double value;    
    double weight;   
    double ratio;    
} Item;

int compareItems(const void *a, const void *b) {
    Item *itemA = (Item *)a;
    Item *itemB = (Item *)b;

    if (itemA->ratio < itemB->ratio) {
        return 1; 
    } else if (itemA->ratio > itemB->ratio) {
        return -1; 
    } else {
        return 0; 
    }
}

double greedyKnapsack(Item *items, int n, double capacity_W) {
    if (capacity_W <= 0 || n <= 0) {
        return 0.0;
    }

    for (int i = 0; i < n; i++) {
        if (items[i].weight > 0) {
            items[i].ratio = items[i].value / items[i].weight;
        } else {
            items[i].ratio = INFINITY; 
        }
    }

    qsort(items, n, sizeof(Item), compareItems);

    double total_value = 0.0;
    double current_weight = 0.0;

    printf("\n--- Knapsack Filling Process ---\n");

    for (int i = 0; i < n; i++) {
        double v = items[i].value;
        double w = items[i].weight;
        double ratio = items[i].ratio;
        int id = items[i].id;

        if (current_weight + w <= capacity_W) {
            current_weight += w;
            total_value += v;
            printf("Item %d (V=%.2f, W=%.2f, Ratio=%.2f): Took 100%% (Weight Added: %.2f).\n", id, v, w, ratio, w);
        } 
        else if (current_weight < capacity_W) {
            double remaining_capacity = capacity_W - current_weight;
            
            double fraction = remaining_capacity / w;
            
            double value_to_add = v * fraction;
            
            total_value += value_to_add;
            current_weight = capacity_W; 
            
            printf("Item %d (V=%.2f, W=%.2f, Ratio=%.2f): Took %.2f%% (Weight Added: %.2f).\n", id, v, w, ratio, fraction * 100.0, remaining_capacity);
            
            break;
        }
    }

    printf("------------------------------\n");
    printf("Total Weight in Knapsack: %.2f\n", current_weight);

    return total_value;
}

int main() {
    double capacity;
    int num_items;

    while (1) {
        printf("Enter the maximum knapsack capacity (W): ");
        if (scanf("%lf", &capacity) != 1 || capacity <= 0) {
            printf("Invalid input. Capacity must be a positive number.\n");
            while (getchar() != '\n'); 
        } else {
            break;
        }
    }

    while (1) {
        printf("Enter the number of items (n): ");
        if (scanf("%d", &num_items) != 1 || num_items <= 0) {
            printf("Invalid input. The number of items must be a positive integer.\n");
            while (getchar() != '\n');
        } else {
            break;
        }
    }

    Item *items = (Item *)malloc(num_items * sizeof(Item));
    if (items == NULL) {
        perror("Failed to allocate memory");
        return 1;
    }

    printf("\nEnter details for each item (Value V, Weight W):\n");
    for (int i = 0; i < num_items; i++) {
        items[i].id = i + 1;
        while (1) {
            printf("Item %d (Value Weight): ", i + 1);
            if (scanf("%lf %lf", &items[i].value, &items[i].weight) == 2 && items[i].weight > 0) {
                break;
            } else {
                printf("Invalid input. Please enter two positive numerical values (Value and Weight).\n");
                while (getchar() != '\n');
            }
        }
    }

    double max_value = greedyKnapsack(items, num_items, capacity);

    printf("\nMaximum Value in Knapsack: %.2f\n", max_value);

    free(items);

    return 0;
}