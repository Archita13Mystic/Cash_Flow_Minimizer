# Cash Flow Minimizer

A C++ console application that minimizes the number of transactions needed to settle debts among a group of people.

## Problem Statement

When multiple people have transactions between them, the number of payments can get complex. This tool computes the **minimum number of transactions** required to settle all debts completely.

## How It Works

1. Input all transactions between people
2. Compute **net balance** for each person
3. Use a **greedy algorithm** with two priority queues to match creditors with debtors
4. Output the optimized settlement plan

## Algorithm

- Creditors (net positive) stored in a **max-heap**
- Debtors (net negative) stored in a **min-heap**
- Greedily matches the largest creditor with the largest debtor until all balances are zero

## Features

- Transaction matrix visualization
- Custom or default names
- Net balance summary
- Optimized settlement output
- Quick demo mode with preset data

## Usage
```bash
g++ -o cashflow main.cpp
./cashflow
```

Choose option `1` to enter your own data or option `2` to run the quick demo.

### Input Format
```
Transaction: <from> <to> <amount>
Enter -1 -1 -1 to finish
```

## Demo Output
```
Alice pays $395 to Bob
Dari  pays $20  to Bob  
Pluto pays $415 to Bob
```

## Tech Stack

- Language: C++
- STL: `priority_queue`, `vector`, `tuple`
- Concepts: Greedy Algorithm, Heap Data Structure
