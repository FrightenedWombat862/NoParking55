#include "PatienceSortDate.h"

/**
 * Heapify down algorithm for a min heap (cardStacks). Uses the license plate number of the top element
 * of each stack as the key.
 * @param cardStacks
 * @param elementToHeapify
 */
void PatienceSortDate::heapifyDown(std::vector<std::list<std::unique_ptr<Citation>>> &cardStacks, std::size_t elementToHeapify) {
    for (std::size_t currentElement = elementToHeapify; currentElement < cardStacks.size();) {
        std::size_t leftChild = currentElement * 2 + 1;
        std::size_t rightChild = currentElement * 2 + 2;
        if (leftChild < cardStacks.size() && cardStacks.at(currentElement).front()->dateTime->getDateTimeString() > cardStacks.at(leftChild).front()->dateTime->getDateTimeString()) {
            // Left child is less than current element.
            if (rightChild >= cardStacks.size() ||
                cardStacks.at(leftChild).front()->dateTime->getDateTimeString() < cardStacks.at(rightChild).front()->dateTime->getDateTimeString()) {
                // Left child is less than rightChild. Prioritize that one.
                std::swap(cardStacks.at(leftChild), cardStacks.at(currentElement));
                currentElement = leftChild;  // Heapify again for the left child.
            }
            else {
                // Either they are equal or right child is less. Prioritize the right child.
                std::swap(cardStacks.at(rightChild), cardStacks.at(currentElement));
                currentElement = rightChild;  // Heapify again for the right child.
            }
        }
        else if (rightChild < cardStacks.size() &&
                cardStacks.at(currentElement).front()->dateTime->getDateTimeString() > cardStacks.at(rightChild).front()->dateTime->getDateTimeString()) {
            // Right child is less than current element.
            std::swap(cardStacks.at(rightChild), cardStacks.at(currentElement));
            currentElement = rightChild;  // Heapify again for the right child.
        }
        else {
            // Everything is in the right place, so we're done.
            break;
        }
    }
}

void PatienceSortDate::patienceSort(std::vector<std::unique_ptr<Citation>>& citations) {
    std::vector<std::list<std::unique_ptr<Citation>>> cardStacks;

    for (auto citationIter = citations.end(); citationIter != citations.begin();) {
        std::unique_ptr<Citation>& citationPtr = *(--citationIter);

        // Binary search for the right stack to put the card in
        std::size_t rangeLeft = 0;  // Left side of the search range
        std::size_t rangeRight = cardStacks.size() - 1;  // Right side of the search range
        std::size_t currentStack = (rangeLeft + rangeRight) / 2;  // Stack that we are currently searching

        std::size_t stackToInsertIn = (std::size_t) -1;  // "-1" means not found
        while (rangeRight != (std::size_t) -1 && rangeLeft <= rangeRight) {
            if (citationPtr->dateTime->getDateTimeString() <= cardStacks.at(currentStack).front()->dateTime->getDateTimeString()) {
                // This stack is valid, but we want to look left for another valid stack.
                stackToInsertIn = currentStack;
                if (currentStack == 0) {
                    // We're at the beginning of the array and can't go left anymore.
                    break;
                }
                else {
                    rangeRight = currentStack - 1;
                    currentStack = (rangeLeft + rangeRight) / 2;
                }
            }
            else if (citationPtr->dateTime->getDateTimeString() > cardStacks.at(currentStack).front()->dateTime->getDateTimeString()) {
                // This stack is not valid. Look right for another stack.
                if (currentStack == cardStacks.size() - 1) {
                    // We're at the end of the array and can't go right anymore.
                    break;
                }
                else {
                    rangeLeft = currentStack + 1;
                    currentStack = (rangeLeft + rangeRight) / 2;
                }
            }
            else {
                // We're done, as this is guaranteed not to mess up the order.
                stackToInsertIn = currentStack;
                break;
            }

            currentStack = (rangeLeft + rangeRight) / 2;
        }

        if (stackToInsertIn == (std::size_t) -1) {
            // No stack was suitable to insert this card.
            // Create a new stack and insert an element in it.
            cardStacks.emplace_back();  // Construct a forward_list at the end of cardStacks
            cardStacks.back().push_front(std::make_unique<Citation>(*citationPtr));
        }
        else {
            // We found a suitable stack. Place the Citation on top of the stack
            cardStacks.at(stackToInsertIn).push_front(std::make_unique<Citation>(*citationPtr));
        }

        /*
        bool placedInStack = false;  // Whether the card has been put into a stack
        for (std::list<std::unique_ptr<Citation>>& cardStack : cardStacks) {
            if (citationPtr->dateTime->getDateTimeString() <= cardStack.front()->dateTime->getDateTimeString()) {
                // We found a suitable stack. Place the Citation on top of the stack
                cardStack.push_front(std::make_unique<Citation>(*citationPtr));
                placedInStack = true;
                break;
            }
        }
         */
    }

    // Now all the cards have been dealt into the stacks, each in a sorted order.

    std::size_t originalIndex = 0;  // The index in the original vector we are inserting into
    while (!cardStacks.empty()) {
        // We know for sure that the first element is the smallest because of the heap invariant.
        auto smallestCardStack = cardStacks.begin();
        citations.at(originalIndex) = std::make_unique<Citation>(*(smallestCardStack->front()));

        // Remove the smallest element from the stack.
        smallestCardStack->pop_front();

        // Remove the stack if it becomes empty.
        if (smallestCardStack->empty()) {
            // Move the now-empty smallestCardStack to the back and remove it
            std::swap(cardStacks.front(), cardStacks.back());
            cardStacks.pop_back();
        }
        heapifyDown(cardStacks, 0);  // Re-heapify from the top.
        ++originalIndex;
    }
}
