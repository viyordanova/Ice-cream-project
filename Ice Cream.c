#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char code[3];
    char name[21];
    int weight;
    float price;
} IceCream;

IceCream* createIceCreamArray(int n) {
    IceCream* iceCreams = (IceCream*)malloc(n * sizeof(IceCream));
    if (iceCreams == NULL) {
        printf("Грешка при заделянето на памет!\n");
        return NULL;
    }
    for (int i = 0; i < n; i++) {
        printf("Сладолед %d:\n", i + 1);
        printf("Уникален код (например A2): ");
        scanf("%s", iceCreams[i].code);
        printf("Име на продукта: ");
        scanf("%s", iceCreams[i].name);
        printf("Тегло в кг: ");
        scanf("%d", &iceCreams[i].weight);
        printf("Цена на килограм: ");
        scanf("%f", &iceCreams[i].price);
        printf("\n");
    }
    return iceCreams;
}

float calculateTotalPriceByLetter(IceCream* iceCreams, int n, char letter) {
    float totalPrice = 0.0;
    for (int i = 0; i < n; i++) {
        if (iceCreams[i].name[0] == letter) {
            totalPrice += iceCreams[i].weight * iceCreams[i].price;
        }
    }
    return totalPrice;
}

int saveIceCreamsToFile(IceCream* iceCreams, int n, float maxPrice, int minWeight) {
    FILE* file = fopen("info.txt", "w");
    if (file == NULL) {
        printf("Грешка при отварянето на файл!\n");
        return 0;
    }
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (iceCreams[i].price < maxPrice && iceCreams[i].weight > minWeight) {
            fprintf(file, "%s;%s;%d;%.2fleva\n", iceCreams[i].code, iceCreams[i].name, iceCreams[i].weight, iceCreams[i].price);
            count++;
        }
    }
    fclose(file);
    return count;
}

void printIceCreamByCode(char* code) {
    FILE* file = fopen("icecream.bin", "rb");
    if (file == NULL) {
        printf("Грешка при отварянето на файл!\n");
        return;
    }
    int found = 0;
    IceCream iceCream;
    while (fread(&iceCream, sizeof(IceCream), 1, file) == 1) {
        if (strcmp(iceCream.code, code) == 0) {
            printf("=====================\n");
            printf("Icecream - %s\n", iceCream.name);
            printf("Price - %.2f BGN\n", iceCream.price);
            printf("=====================\n");
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Сладолед с код %s не е намерен!\n", code);
    }
    fclose(file);
}

int main() {
//1
    system("chcp 65001>nul");
    int n;
    printf("Въведете брой сладоледи: ");
    scanf("%d", &n);

    if (n <= 5 || n >= 15) {
        printf("Броят на сладоледите трябва да е по-голям от 5 и по-малък от 15!\n");
        return 0;
    }

    IceCream* iceCreams = createIceCreamArray(n);
    if (iceCreams == NULL) {
        return 0;
    }
//2
    char letter;
    printf("Въведете буква: ");
    scanf(" %c", &letter);
    fflush(stdin);

    float totalPrice = calculateTotalPriceByLetter(iceCreams, n, letter);
    printf("Общата цена на сладоледите с име, започващо с буквата '%c', е: %.2f\n", letter, totalPrice);
//3
    float maxPrice;
    int minWeight;
    printf("Въведете максимална цена: ");
    scanf("%f", &maxPrice);
    printf("Въведете минимално тегло: ");
    scanf("%d", &minWeight);

    int savedCount = saveIceCreamsToFile(iceCreams, n, maxPrice, minWeight);
    printf("Записани са %d сладоледа във файла info.txt\n", savedCount);
//4
    char code[3];
    printf("Въведете уникален код: ");
    scanf("%s", code);
    fflush(stdin);

    printIceCreamByCode(code);

    free(iceCreams);

    system("pause>nul");
    return 0;
}
