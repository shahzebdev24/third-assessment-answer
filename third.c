#include <stdio.h>
#include <string.h>

#define MAX_TRADES 100000
#define MAX_TRADERS 100000
#define MAX_ID_LEN 50

typedef struct {
    char id[MAX_ID_LEN];
    int buyPrice;
    int buyIndex;
    int hasActiveBuy;
} Trader;

// Find trader index in array
int findTrader(Trader traders[], int count, char *id) {
    for (int i = 0; i < count; i++) {
        if (strcmp(traders[i].id, id) == 0) {
            return i;
        }
    }
    return -1;
}

int main() {
    int n;
    scanf("%d", &n);

    char type[10], traderId[MAX_ID_LEN];
    int price;

    Trader traders[MAX_TRADERS];
    int traderCount = 0;

    char result[MAX_TRADES][MAX_ID_LEN];
    int resultCount = 0;

    for (int i = 0; i < n; i++) {
        scanf("%s %d %s", type, &price, traderId);

        int idx = findTrader(traders, traderCount, traderId);

        // If trader not found, add new
        if (idx == -1) {
            idx = traderCount++;
            strcpy(traders[idx].id, traderId);
            traders[idx].hasActiveBuy = 0;
        }

        if (strcmp(type, "buy") == 0) {
            traders[idx].buyPrice = price;
            traders[idx].buyIndex = i;
            traders[idx].hasActiveBuy = 1;
        } 
        else if (strcmp(type, "sell") == 0) {
            if (traders[idx].hasActiveBuy) {
                int buyPrice = traders[idx].buyPrice;
                int buyIndex = traders[idx].buyIndex;

                if ((i - buyIndex) <= 3 && price > buyPrice) {
                    strcpy(result[resultCount++], traderId);
                }
            }
        }
    }

    // Print result
    for (int i = 0; i < resultCount; i++) {
        printf("%s\n", result[i]);
    }

    return 0;
}