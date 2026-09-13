
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Activity {
    int start;
    int finish;
};

bool compare(Activity a, Activity b) {
    return a.finish < b.finish;
}

int main() {
    int n;

    cout << "Enter number of activities: ";
    cin >> n;

    vector<Activity> activities(n);

    cout << "Enter start and finish time of each activity:\n";

    for (int i = 0; i < n; i++) {
        cin >> activities[i].start
            >> activities[i].finish;
    }

    // Sort activities by increasing finish time
    sort(activities.begin(), activities.end(), compare);

    int count = 0;
    int lastFinish = -1;

    cout << "Selected activities:\n";

    for (int i = 0; i < n; i++) {
        if (activities[i].start >= lastFinish) {
            cout << "(" << activities[i].start
                 << ", " << activities[i].finish << ")" << endl;

            lastFinish = activities[i].finish;
            count++;
        }
    }

    cout << "Maximum number of activities = "
         << count << endl;

    return 0;
}