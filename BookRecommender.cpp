#include "BookRecommender.h"

BookRecommender::BookRecommender() {} //creates an empty set for the default constructor

BookRecommender::BookRecommender(string fileName) {
    fstream inFile(fileName);
    if (!inFile) {
        cout << "File not able to open" << endl;
        exit(1);
    }
    
    string userName, bookTitle, rating;
    
    while (std::getline(inFile, userName) &&
        std::getline(inFile, bookTitle) &&
        std::getline(inFile, rating)) {
        if (find(books.begin(), books.end(), bookTitle) == books.end()) { books.push_back(removeNewLine(bookTitle)); }
        if (find(users.begin(), users.end(), userName) == users.end()) { users.push_back(removeNewLine(userName)); }
        onlyRatedBooks[removeNewLine(userName) + "-" + removeNewLine(bookTitle)] = std::stoi(rating);
        bookRatings[removeNewLine(bookTitle)].push_back((std::stoi(rating)));
    }
    
    std::sort(books.begin(), books.end());
    inFile.close();
    
     // Get the iterator to the bookTitle in the averages map
    // Return the average value associated with the bookTitle
    for (const auto& user : users) {
        for (const auto& book : books) {
            string bookuser = user + "-" + book;
            double rating;
            rating = 0.0;
            if (onlyRatedBooks.count(bookuser) > 0) {
                auto bookrating = onlyRatedBooks.find(bookuser);
                rating = bookrating->second;
            }
            if (rating > 0 || rating <0 ) { ratedBooks[user].push_back(rating); }
            else { ratedBooks[user].push_back(0.0); }
        }
    }

    for (const auto& pair : bookRatings) {
        const auto& bookTitle = pair.first;
        const auto& ratings = pair.second;
        double sum = 0.0;
        for (const auto& rating : ratings) { sum += rating; }
        double average = sum / ratings.size();
        averages[bookTitle] = average;
    }

}

//Return the total number of books.
int BookRecommender::getBookCount() { return books.size(); }

//Return the totla number of users.
int BookRecommender::getUserCount() { return users.size(); }

double BookRecommender::getSimilarity(string userName1, string userName2) {
   const vector<double>& user1 = ratedBooks[userName1];
   const vector<double>& user2 = ratedBooks[userName2];
   double similarity = 0.0;
   for (size_t i = 0; i < books.size(); ++i) { similarity += user1[i] * user2[i]; }
   return similarity;
}

double BookRecommender::getUserBooksRating(string userName, string bookTitle) {
   const vector<double>& ratings = ratedBooks[userName];
   for (size_t i = 0; i < books.size(); i++) {
       if (books[i] == bookTitle) { return ratings[i]; }
   }
   return 0.0;
}

string BookRecommender::IsUserFound(string uName) {
   if (find(users.begin(), users.end(), uName) == users.end()) { return "false"; }
   else { return "true"; }
}

string BookRecommender::removeNewLine(string line) {
   if (line[line.length() - 1] == '\r') { line.erase(line.length() - 1); }
   return line;
}


// Get the iterator to the bookTitle in the averages map
// Return the average value associated with the bookTitle
double BookRecommender::getAverage(string bookTitle) {
    if (averages.count(bookTitle) > 0) {
        auto avg = averages.find(bookTitle);
        return avg->second;
    }
    return 0;
}

void BookRecommender::printRecommend(string userName) {
    vector<pair<double, string> > similarities;
    vector<pair<double, string> > recommendations;
    vector<pair<double, string> > avgbookratings;
    
    for (auto& user : ratedBooks) {
        string otherUser = user.first;
        if (otherUser != userName) {
            double similarity = getSimilarity(userName, otherUser);
            similarities.push_back(make_pair(similarity, otherUser));
        }
    }
    
    std::sort(similarities.rbegin(), similarities.rend());
    
    for (size_t i = 0; i < books.size();i++) {
    int ratingsZero = 0;
    double ubRating = 0;
    double tubRating = 0;
    bool bookAlreadyAdded = false; // keeps track of whether the book has already been added or not.
        
    for (size_t j = 0; j < 3;j++) {
        ubRating = getUserBooksRating(similarities[j].second, books[i]);
        if (ubRating != 0) {
            ratingsZero++;
            tubRating = tubRating + ubRating;
        }
    }
    if (ratingsZero > 0) {
        double averageRating = tubRating / ratingsZero;
        // Check if the book has already been added to recommendations with the same score
        for (auto& recommendation : recommendations) {
            if (recommendation.first == averageRating && recommendation.second == books[i]) {
                bookAlreadyAdded = true;
                break;
            }
        }
        // Add the book to recommendations if it hasn't already been added
        if (!bookAlreadyAdded) { recommendations.push_back(make_pair(averageRating, books[i])); }
    }   
}
    
    // Compare by double value
    // Sort in descending order by double value
    // If double values are equal, compare by string value
     // Sort in ascending order by string value
    std::sort(recommendations.begin(), recommendations.end(),
        [](const pair<double, string>& a, const pair<double, string>& b) {
            if (a.first != b.first) { return a.first > b.first; }
            else {
                // if the scores are the same, compare by book title
                if (a.second != b.second) { return a.second < b.second; }
                // if the scores and titles are the same, return false to keep only one copy
                else { return false; }
            }
        });
    
    // Print books based on similarity with the requested username.
    for (auto& recommendation : recommendations) {
        if (recommendation.first > 0) { cout << removeNewLine(recommendation.second) << " " << fixed << setprecision(2) << recommendation.first << std::endl; }
    }
    
}

/* Sort the vector using a custom comparer
Then Compare average ratings in descending order
If the average ratings are the same, compare book titles in alphabetical order
Print the sorted entries*/
void BookRecommender::printAverages() {
   
    for (const string& book : books) {
        double avg = getAverage(book);
        averagesPrint[book] = avg;
     }

    std::vector<std::pair<std::string, double>> entries(averagesPrint.begin(), averagesPrint.end());
    std::sort(entries.begin(), entries.end(), [](const auto& entry1, const auto& entry2) {
        if (entry1.second != entry2.second) { return entry1.second > entry2.second; }
        else { return entry1.first < entry2.first; }
        });

    for (const auto& entry : entries) {
        if (entry.second >= 0) { std::cout << removeNewLine(entry.first) << " " << std::fixed << std::setprecision(2) << entry.second << std::endl; }
        if (entry.second < 0) { std::cout << removeNewLine(entry.first) << " " << std::fixed << std::setprecision(2) << entry.second << std::endl; }
    }
 }
 
