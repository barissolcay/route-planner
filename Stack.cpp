#include "Stack.h"
#include <iostream>
#include <stdexcept>

// Constructor to initialize an empty stack
Stack::Stack() {
    top = -1; // Top is initialized to -1, indicating the stack is empty
}

// Adds a province to the top of the stack
void Stack::push(int province) {
    if (top >= MAX_SIZE - 1) {
        throw std::overflow_error("Stack overflow: Cannot push more elements.");
    }
    data[++top] = province; // Increment top and add the province
}

// Removes and returns the top province from the stack
int Stack::pop() {
    if (isEmpty()) {
        throw std::underflow_error("Stack underflow: Cannot pop from an empty stack.");
    }
    return data[top--]; // Return the top element and decrement top
}

// Returns the top province without removing it
int Stack::peek() const {
    if (isEmpty()) {
        throw std::underflow_error("Stack is empty: Cannot peek.");
    }
    return data[top]; // Return the top element without modifying the stack
}

// Checks if the stack is empty
bool Stack::isEmpty() const {
    return top == -1; // Stack is empty if top is -1
}

// Function to get the current size of the stack
int Stack::getSize() const {
    return top + 1; // Size is top + 1 because top is 0-based index
}