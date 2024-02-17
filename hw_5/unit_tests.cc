#include <math.h>
#include <float.h> /* defines DBL_EPSILON */
#include <assert.h>
#include "utilities.h"
#include "gtest/gtest.h"
#include <map>
#include <string>

namespace
{
    TEST(occurrenceMapTest, Test_Invalid_Words) {
        std::string text = "This is a sentence. Don't think of wier_d strings as words. Really, 123 is a nice number.";
        TypedArray<TypedArray<double>> matrix;
        TypedArray<double> row;  // Simulating a row with each word as an element

        // Simulate adding each word to the row, for demonstration we use indices instead of words
        // In practice, this requires a different approach as write_matrix_csv expects numerical data
        for (int i = 0; i < text.length(); ++i) {
            row.set(row.size(), static_cast<double>(i));  // Placeholder for actual text handling
        }
        matrix.set(matrix.size(), row);

        // Path to the text file
        std::string path = "quote_1.txt";

        // Write the matrix to the file
        write_matrix_csv(matrix, path);

        auto result = occurrence_map(path);
        std::map<std::string, int> expected = {
            {"this", 2}, {"is", 2}, {"a", 1}, {"sentence", 1}, {"don't", 1}, 
            {"think", 1}, {"of", 1}, {"strings", 1}, {"as", 1}, {"words", 1}, 
            {"really", 1}, {"123", 1}, {"nice", 1}, {"number", 1}
        };

        EXPECT_EQ(result, expected);
    }

    TEST(occurrenceMapTest, TEST_2) {
        std::string text = "'I should use double quotes'";
        //auto result = occurrence_map(text);
        std::map<std::string, int> expected = {
            {"'I should use double quotes'", 1}
        };

        //EXPECT_EQ(result, expected);
    }

    TEST(occurrenceMapTest, TEST_3){
        std::string text = "George Mallory's famous quote: \"My mind is in a state of constant rebellion.\"";
        //auto result = occurrence_map(text);
        std::map<std::string, int> expected = {
            {"george", 1}, {"mallory's", 1}, {"famous", 1}, {"quote", 1}, 
            {"my", 1}, {"mind", 1}, {"is", 1}, {"in", 1}, {"a", 1}, 
            {"state", 1}, {"of", 1}, {"constant", 1}, {"rebellion", 1}
        };

        //EXPECT_EQ(result, expected);
    }

    TEST(occurrenceMapTest, TEST_4) {
        std::string text = "10XGenomics (a biotech company) is quoted as saying \"blah blah blah.\"";
        //auto result = occurrence_map(text);
        std::map<std::string, int> expected = {
            {"10xgenomics", 1}, {"a", 1}, {"biotech", 1}, {"company", 1}, 
            {"is", 1}, {"quoted", 1}, {"as", 1}, {"saying", 1}, {"blah", 3}
        };
        //EXPECT_EQ(result, expected);
    }

    TEST(occurrenceMapTest, TEST_5){
        std::string text = "the)s are no%y6 wo!e4";
        //auto result = occurrence_map(text);
        std::map<std::string, int> expected = {
            {"are", 1}
        };
        //EXPECT_EQ(result, expected);
    }
}