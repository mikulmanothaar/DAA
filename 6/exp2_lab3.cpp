#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Item {
    int value;
    int weight;
    double ratio;
};

bool compare(Item a, Item b) {
    return a.ratio > b.ratio;
}

int main() {
    int n, capacity;

    cout << "Enter number of items: ";
    cin >> n;

    vector<Item> items(n);

    cout << "Enter value and weight of each item:\n";

    for (int i = 0; i < n; i++) {
        cin >> items[i].value >> items[i].weight;
        items[i].ratio =
            (double)items[i].value / items[i].weight;
    }

    cout << "Enter knapsack capacity: ";
    cin >> capacity;

    // Sort items by value/weight ratio
    sort(items.begin(), items.end(), compare);

    double maxProfit = 0;

    for (int i = 0; i < n; i++) {

        if (capacity >= items[i].weight) {
            // Take the complete item
            capacity -= items[i].weight;
            maxProfit += items[i].value;
        }
        else {
            // Take fraction of the item
            maxProfit += items[i].ratio * capacity;
            capacity = 0;
            break;
        }
    }

    cout << "Maximum Profit = " << maxProfit << endl;

    return 0;
}