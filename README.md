# Book Recommender System

## Introduction
The **Book Recommender System** is a command-line application designed to recommend books to users based on their preferences. By analyzing user ratings, the system identifies similar users and suggests highly-rated books. Additionally, the system can display average ratings for all books.

This project demonstrates the use of object-oriented programming principles, efficient data structures, and algorithms for handling recommendations and sorting.

---

## Features
- **Personalized Recommendations**: Suggests books for a user based on similar users' preferences.
- **Average Ratings**: Displays average ratings for all books in the dataset.
- **Command-Line Interaction**: Users can interact with the system using commands like:
  - `recommend <username>`: Provides recommendations for a user.
  - `averages`: Displays average ratings for all books.
  - `quit`: Exits the application.

---

## How It Works
1. **Data Loading**: Reads user-book ratings from an input file where each user's name, book title, and rating are on separate lines.
2. **Recommendation Algorithm**:
   - Identifies similar users based on their ratings using dot-product similarity.
   - Recommends books that highly similar users have rated.
3. **Average Calculation**:
   - Calculates and displays average ratings for each book, sorted in descending order of ratings.

---
