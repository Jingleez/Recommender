#include "BookRecommender.h"

int main(int argc, char** argv) {
    string fileName = argv[1];
    BookRecommender bookRecommender(fileName);
    string command;
    while (true) {
        cin >> command;
        if (command == "recommend") {
                string userName;
                cin >> userName;
                string boolFound = bookRecommender.IsUserFound(bookRecommender.removeNewLine(userName));
                if (boolFound=="true") { bookRecommender.printRecommend(bookRecommender.removeNewLine(userName)); }
                else { bookRecommender.printAverages(); }
        }
        else if (command == "averages") { bookRecommender.printAverages(); }
        else if (command == "quit") { break; }
    }
    return 0;
}
