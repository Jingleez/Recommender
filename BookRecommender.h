#ifndef BOOKRECOMMENDER_H
#define BOOKRECOMMENDER_H
#include <iostream>
#include <map>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <set>
#include <string>
using namespace std;

class BookRecommender {
    private:
            vector <string> books;
            vector <string> users;
            map <string, double> onlyRatedBooks;
            map <string, vector<double> > ratedBooks;
            map <string, vector<double> > bookRatings;
            map <string, double> averages;
            map <string, double> averagesPrint;
    public:
            BookRecommender();
            BookRecommender(string fileName);
            string IsUserFound(string uName);
            string removeNewLine(string line);
            void printRecommend(string userName);
            void printAverages();
            double getAverage(string bookTitle);
            double getSimilarity(string userName1, string userName2);
            int getBookCount();
            int getUserCount();
            double getUserBooksRating(string userName, string bookTitle);
 };
#endif
