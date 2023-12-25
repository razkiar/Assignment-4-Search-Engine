#ifndef document_H
#define document_H

#include <string>

// Using a namespace in header files can cause conflicts when included in different contexts.
// It's better practice to use the std:: prefix where needed.

class document {
public:
    // Constructor with optional parameters allows for creating an empty or fully initialized Document
    document(std::string title = "", std::string id = "", std::string pubDate = "", 
             std::string author = "", std::string text = "", int score = 0)
    : title(title), identifier(id), publicationDate(pubDate), 
      authorName(author), content(text), relevanceScore(score) {}

    // Public member variables 
    std::string title;            // Title of the document
    std::string identifier;       // Unique identifier for the document
    std::string publicationDate;  // Date when the document was published
    std::string authorName;       // Name of the document's author
    std::string content;          // Text content of the document
    int relevanceScore = 0;       // Relevance score indicating the importance or ranking of the document

    // Operator overloads for comparison
    // Compares two Document objects for equality
    bool operator==(const document &other) const {
        return title == other.title && identifier == other.identifier &&
               publicationDate == other.publicationDate && authorName == other.authorName &&
               relevanceScore == other.relevanceScore && content == other.content;
    }

    // Compares the relevance score of two Document objects for less-than relationship
    bool operator<(const document &other) const {
        return relevanceScore < other.relevanceScore;
    }

    // Compares the relevance score of two Document objects for greater-than relationship
    bool operator>(const document &other) const {
        return relevanceScore > other.relevanceScore;
    }
};

#endif // document_H
