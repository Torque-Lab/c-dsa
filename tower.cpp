#include <iostream>
#include <string>

/**
 * @brief Solves the Tower of Hanoi problem recursively and prints the steps.
 * * @param n The number of disks to move.
 * @param source The name of the source peg (e.g., "A").
 * @param destination The name of the destination peg (e.g., "C").
 * @param auxiliary The name of the auxiliary/spare peg (e.g., "B").
 */
void towerOfHanoi(int n, const std::string& source, 
                  const std::string& destination, const std::string& auxiliary) {
    
    // 1. Base Case: If only 1 disk remains, move it directly.
    if (n == 1) {
        std::cout << "Move disk 1 from " << source << " to " << destination << std::endl;
        return;
    }

    // 2. Recursive Step 1: Move n-1 disks from Source to Auxiliary, using Destination as spare.
    towerOfHanoi(n - 1, source, auxiliary, destination);

    // 3. Move the nth (largest) disk from Source to Destination.
    std::cout << "Move disk " << n << " from " << source << " to " << destination << std::endl;

    // 4. Recursive Step 2: Move n-1 disks from Auxiliary to Destination, using Source as spare.
    towerOfHanoi(n - 1, auxiliary, destination, source);
}

int main() {
    int num_disks = 7; // Change this value to solve for a different number of disks.
    
    std::cout << "--- Tower of Hanoi Solver for " << num_disks << " Disks ---" << std::endl;
    
    // Start the recursive process with Pegs A, B, and C
    towerOfHanoi(num_disks, "Peg A (Source)", "Peg C (Destination)", "Peg B (Auxiliary)");
    
    // The total number of moves will be 2^n - 1
    // For 3 disks: 2^3 - 1 = 7 moves.
    std::cout << "--- Total Moves: " << (1 << num_disks) - 1 << " ---" << std::endl;

    return 0;
}