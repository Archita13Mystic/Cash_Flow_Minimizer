#include <bits/stdc++.h>
using namespace std;

class CashFlowVisualizer {
private:
    int n;
    vector<string> names;
    vector<vector<int>> transactions;
    vector<tuple<string, string, int>> optimizedTransactions;
    vector<int> amounts;

    void displayTransactionMatrix() {
        cout << "\n" << string(60, '=') << "\n";
        cout << "            TRANSACTION  MATRIX\n";
        cout << string(60, '=') << "\n";
        
        cout << setw(12) << " ";
        for(int i = 0; i < n; i++) {
            cout << setw(10) << names[i];
        }
        cout << "\n" << string(12 + n*10, '-') << "\n";
        

        for(int i = 0; i < n; i++) {
            cout << setw(12) << names[i];
            for(int j = 0; j < n; j++) {
                cout << setw(10) << transactions[i][j];
            }
            cout << "\n";
        }
        cout << string(60, '=') << "\n";
        cout << "Matrix[i][j] = amount person i pays to person j\n\n";
    }

    void calculateNetAmounts() {
        amounts.assign(n, 0);  
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                amounts[i] += transactions[j][i] - transactions[i][j];
            }
        }
    }

    void minimizeTransactions() {
        optimizedTransactions.clear();

        priority_queue<pair<int, int>> creditors;
        priority_queue<pair<int, int>, vector<pair<int,int>>, greater<pair<int,int>>> debtors;

        for(int i = 0; i < n; i++) {
            if(amounts[i] > 0) {
                creditors.push({amounts[i], i});
            } else if(amounts[i] < 0) {
                debtors.push({amounts[i], i});
            }
        }

        while(!creditors.empty() && !debtors.empty()) {
            auto creditor = creditors.top(); creditors.pop();
            auto debtor = debtors.top(); debtors.pop();

            int creditAmount = creditor.first;
            int debitAmount = -debtor.first;
            int creditorId = creditor.second;
            int debtorId = debtor.second;

            int transferAmount = min(creditAmount, debitAmount);

            optimizedTransactions.push_back(make_tuple(
                names[debtorId], 
                names[creditorId], 
                transferAmount
            ));

            if(creditAmount > transferAmount) {
                creditors.push({creditAmount - transferAmount, creditorId});
            }
            if(debitAmount > transferAmount) {
                debtors.push({-(debitAmount - transferAmount), debtorId});
            }
        }
    }


public:
    void run() {
        cout << "\nNumber of people: ";
        cin >> n;

        names.resize(n);
        transactions.resize(n, vector<int>(n, 0));
        amounts.resize(n, 0);

        cout << "Use default names? (y/n): ";
        char choice;
        cin >> choice;

        if(choice == 'y' || choice == 'Y') {
            for(int i = 0; i < n; i++) {
                names[i] = "Person" + to_string(i+1);
            }
        } else {
            cout << "Enter names:\n";
            for(int i = 0; i < n; i++) {
                cout << "Name " << (i+1) << ": ";
                cin >> names[i];
            }
        }

        cout << "Transaction entry (from to amount)\n";
        cout << "Type -1 -1 -1 to finish:\n";

        int from, to, amount;
        while(true) {
            cout << "Transaction: ";
            cin >> from >> to >> amount;

            if(from == -1) break;

            if(from < 1 || from > n || to < 1 || to > n || from == to) {
                cout << "Invalid!\n";
                continue;
            }

            transactions[from-1][to-1] += amount;
            cout << "Added Transaction\n";
        }


        displayTransactionMatrix();

        calculateNetAmounts();
        
        cout << "NET AMOUNTS (+ means receives, - means owes):\n";
        cout << string(40, '-') << "\n";
        for(int i = 0; i < n; i++) {
            cout << setw(12) << names[i] << ": ";
            if(amounts[i] >= 0) cout << "+";
            cout << amounts[i] << "\n";
        }
        cout << "\n";

        minimizeTransactions();

        cout << "OPTIMIZED TRANSACTIONS:\n";
        cout << string(40, '-') << "\n";
        if(optimizedTransactions.empty()) {
            cout << "No transactions needed!\n";
        } else {
            for(const auto& t : optimizedTransactions) {
                cout << get<0>(t) << " pays $" << get<2>(t) 
                     << " to " << get<1>(t) << "\n";
            }
        }

    }

    void quickDemo() {
        cout << "QUICK DEMO\n";

        n = 4;
        names = {"Alice", "Bob", "Dari", "Pluto"};
        transactions = {
            {0, 100, 0, 0},
            {0, 0, 291, 505}, 
            {20, 0, 0, 0},
            {0, 90, 0, 0}
        };
        amounts.resize(n, 0);

        displayTransactionMatrix();

        calculateNetAmounts();
        
        cout << "NET AMOUNTS:\n";
        cout << string(20, '-') << "\n";
        for(int i = 0; i < n; i++) {
            cout << setw(12) << names[i] << ": " << (amounts[i] >= 0 ? "+" : "") << amounts[i] << "\n";
        }
        cout << "\n";

        minimizeTransactions();

        cout << "OPTIMIZED TRANSACTIONS:\n";
        cout << string(30, '-') << "\n";
        for(const auto& t : optimizedTransactions) {
            cout << get<0>(t) << " pays $" << get<2>(t) 
                 << " to " << get<1>(t) << "\n";
        }
        
    }
};

int main() {
    cout << "CASH FLOW MINIMIZER\n";

    cout << "1. Enter Data\n";
    cout << "2. Quick Demo\n";
    cout << "Choose: ";

    int choice;
    cin >> choice;

    CashFlowVisualizer app;

    if(choice == 2) {
        app.quickDemo();
    } else {
        app.run();
    }

    return 0;
}
