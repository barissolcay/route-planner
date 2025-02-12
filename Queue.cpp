#include "Queue.h"
#include <iostream>
#include <stdexcept>

// Constructor to initialize an empty queue
Queue::Queue() {
    front = -1;
    rear = -1;
}

// Adds a province to the end of the queue
void Queue::enqueue(int province) {
    if ((rear + 1) % MAX_QUEUE_SIZE == front) {
        throw std::overflow_error("Queue overflow: Cannot enqueue more elements.");
    }

    if (isEmpty()) {
        front = 0;
    }

    rear = (rear + 1) % MAX_QUEUE_SIZE; // Circular increment
    data[rear] = province;
}

// Removes and returns the front province from the queue
int Queue::dequeue() {
    if (isEmpty()) {
        throw std::underflow_error("Queue underflow: Cannot dequeue from an empty queue.");
    }

    int province = data[front];

    if (front == rear) {
        // Queue becomes empty after this operation
        front = -1;
        rear = -1;
    } else {
        front = (front + 1) % MAX_QUEUE_SIZE; // Circular increment
    }

    return province;
}

// Returns the front province without removing it
int Queue::peek() const {
    if (isEmpty()) {
        throw std::underflow_error("Queue is empty: Cannot peek.");
    }
    return data[front];
}

// Checks if the queue is empty
bool Queue::isEmpty() const {
    return front == -1;
}

// Add a priority province
void Queue::enqueuePriority(int province) {
    if ((rear + 1) % MAX_QUEUE_SIZE == front) {
        throw std::overflow_error("Queue overflow: Cannot enqueue more elements.");
    }

    if (isEmpty()) {
        enqueue(province); // Simply enqueue if queue is empty
        return;
    }

    // Shift elements to make room for the priority element
    int currentSize = (rear >= front) ? (rear - front + 1) : (MAX_QUEUE_SIZE - front + rear + 1);

    for (int i = currentSize; i > 0; --i) {
        int index = (front + i) % MAX_QUEUE_SIZE;
        int prevIndex = (front + i - 1) % MAX_QUEUE_SIZE;
        data[index] = data[prevIndex];
    }

    data[front] = province; // Place priority element at the front
    rear = (rear + 1) % MAX_QUEUE_SIZE; // Update rear position
}