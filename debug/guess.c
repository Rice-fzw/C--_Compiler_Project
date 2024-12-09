//guess number

int main() {
    int random = 57;  // answer
    int guess[1];     // store guessing
    int guessCount = 0;  // record guess count 
    int gameState = 1;   // Game state: positive number for continue; 0 for end
    
    // Print Game, Start!
    putch(71);  // 'G'
    putch(97);  // 'a'
    putch(109); // 'm'
    putch(101); // 'e'
    putch(32);  // ' '
    putch(83);  // 'S'
    putch(116); // 't'
    putch(97);  // 'a'
    putch(114); // 'r'
    putch(116); // 't'
    putch(33);  // '!'
    putch(10);  // '\n'
    
    while (gameState) {
        guess[0] = getint();  // input
        guessCount = guessCount + 1;
        
        if (guess[0] == random) {
            // right answer
            putch(67);  // 'C'
            putch(111); // 'o'
            putch(114); // 'r'
            putch(114); // 'r'
            putch(101); // 'e'
            putch(99);  // 'c'
            putch(116); // 't'
            putch(33);  // '!'
            putch(10);  // '\n'
            
            putch(84);  // 'T'
            putch(114); // 'r'
            putch(105); // 'i'
            putch(101); // 'e'
            putch(115); // 's'
            putch(58);  // ':'
            putch(32);  // ' '
            putint(guessCount);
            putch(10);  // '\n'
            
            gameState = 0;
        } else if (guess[0] < random) {
            // guess a smaller number
            putch(84);  // 'T'
            putch(111); // 'o'
            putch(111); // 'o'
            putch(32);  // ' '
            putch(108); // 'l'
            putch(111); // 'o'
            putch(119); // 'w'
            putch(33);  // '!'
            putch(10);  // '\n'
        } else {
            // guess a bigger number
            putch(84);  // 'T'
            putch(111); // 'o'
            putch(111); // 'o'
            putch(32);  // ' '
            putch(104); // 'h'
            putch(105); // 'i'
            putch(103); // 'g'
            putch(104); // 'h'
            putch(33);  // '!'
            putch(10);  // '\n'
        }
    }
    return 0;
}