# Greedy Knapsack Problem
This project provides C++ implementations of the Binary (0/1) Knapsack and Fractional Knapsack algorithms. The goal is to study the computational complexity of each solution approach and evaluate their time efficiency under various conditions.

## Problem Overview
The Knapsack Problem is a well-known optimization problem that comes in two main forms:

Binary (0/1) Knapsack: Given a set of items, each with a weight and value, and a maximum weight capacity, determine the maximum value achievable by selecting items such that each item is either taken or left (binary choice), and the total weight does not exceed the capacity.
Fractional Knapsack: Similar to the binary knapsack, but allows fractional parts of items to be taken. The solution uses a greedy approach, selecting items or portions of items based on their value-to-weight ratio.
Features
Binary Knapsack Solution:

Implemented using a greedy approach. Items are sorted by value-to-weight ratio, achieving a time complexity of O(n log n) for sorting and O(n) for item selection.
This approach provides an efficient and optimal solution for fractional item selection scenarios.
Performance Analysis
The project includes benchmarks to analyze the time complexity and performance of each algorithm on various input sizes and capacities

## Getting Started
Clone the repository and compile the provided C++ files to experiment with each knapsack solution. Sample inputs and benchmark scripts are provided to facilitate testing and evaluation.

This project serves as a valuable tool for understanding different algorithmic approaches to the knapsack problem and provides insights into their real-world efficiency.
