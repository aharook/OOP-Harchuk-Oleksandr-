#include <iostream>
#include <stdexcept>
#include <gtest/gtest.h>

class AgeCalculator {
public:
    int Year;
    int curent_Year;

    AgeCalculator(int Year, int curent_Year) : Year(Year), curent_Year(curent_Year) {
        if (Year > curent_Year) {
            throw std::invalid_argument("Рік народження не може бути більшим за поточний рік!");
        }
        if (Year < 0 || curent_Year < 0) {
            throw std::invalid_argument("Роки не можуть бути від'ємними!");
        }
    }

    int CalculateAge() {
        return curent_Year - Year;
    }

    bool IsAdult() {
        return (curent_Year - Year >= 18);
    }
};


// Звичайні тести (Аналог Fact )


TEST(AgeCalculatorFactTests, CalculatesCorrectAge) {
    AgeCalculator calc(2000, 2026);
    EXPECT_EQ(calc.CalculateAge(), 26);
}

TEST(AgeCalculatorFactTests, BornInCurrentYear_ReturnsZero) {
    AgeCalculator calc(2026, 2026);
    EXPECT_EQ(calc.CalculateAge(), 0);
}

TEST(AgeCalculatorFactTests, VeryOldPerson_CalculatesCorrectly) {
    AgeCalculator calc(1900, 2026);
    EXPECT_EQ(calc.CalculateAge(), 126);
}

TEST(AgeCalculatorFactTests, FutureBirthYear_ThrowsException) {
    EXPECT_THROW(AgeCalculator(2050, 2026), std::invalid_argument);
}

TEST(AgeCalculatorFactTests, NegativeYear_ThrowsException) {
    EXPECT_THROW(AgeCalculator(-5, 2026), std::invalid_argument);
}


//Параметризовані тести (Аналог Theory)


// Структура для зберігання параметрів
struct AdultTestData {
    int birthYear;
    int currentYear;
    bool expectedIsAdult;
};

class AgeCalculatorTheoryTests : public ::testing::TestWithParam<AdultTestData> {};

TEST_P(AgeCalculatorTheoryTests, ChecksIfAdultCorrectly) {
    AdultTestData data = GetParam();
    AgeCalculator calc(data.birthYear, data.currentYear);
    EXPECT_EQ(calc.IsAdult(), data.expectedIsAdult);
}

INSTANTIATE_TEST_SUITE_P(
    AdultTestsVariations,
    AgeCalculatorTheoryTests,
    ::testing::Values(
        AdultTestData{ 2000, 2026, true  },  
        AdultTestData{ 2015, 2026, false },  
        AdultTestData{ 2008, 2026, true  }, 
        AdultTestData{ 2009, 2026, false },  
        AdultTestData{ 1950, 2026, true  }  
    )
);

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}