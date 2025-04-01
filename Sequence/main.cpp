#include <iostream>
#include "SequenceId.h"
#include "SimpleUnitTests.h"

const std::string LETTERS_SEQUEBNCE = "ABCEHIKLNOPRSTUWXYZ";
const std::string DIGINT_SEQUEBNCE = "123456789";

TEST_CASE(InvalidInitializationTest) {
    SequenceId sequenceId("", DIGINT_SEQUEBNCE);
    ASSERT(sequenceId.getSequence() == "");
    ASSERT(!sequenceId.setSequence("A1"));
    ASSERT(sequenceId.getSequence() == "");
    ASSERT(sequenceId.increment() == "");

    SequenceId sequenceId2(LETTERS_SEQUEBNCE, "");
    ASSERT(sequenceId2.getSequence() == "");
    ASSERT(!sequenceId2.setSequence("A1"));
    ASSERT(sequenceId2.getSequence() == "");
    ASSERT(sequenceId2.increment() == "");
}

TEST_CASE(FirstElementTest) {
    SequenceId sequenceId(LETTERS_SEQUEBNCE, DIGINT_SEQUEBNCE);
    ASSERT(sequenceId.getSequence() == "A1");
}

TEST_CASE(FirstIncrementTest) {
    SequenceId sequenceId(LETTERS_SEQUEBNCE, DIGINT_SEQUEBNCE);
    ASSERT(sequenceId.increment() == "A2");
}

TEST_CASE(ForbiddenValuesSetTest) {
    SequenceId sequenceId(LETTERS_SEQUEBNCE, DIGINT_SEQUEBNCE);
    ASSERT(!sequenceId.setSequence("`2"));
    ASSERT(!sequenceId.setSequence("A`"));
    ASSERT(!sequenceId.setSequence("a1"));
    ASSERT(!sequenceId.setSequence("D1"));
    ASSERT(!sequenceId.setSequence("F1"));
    ASSERT(!sequenceId.setSequence("G1"));
    ASSERT(!sequenceId.setSequence("J1"));
    ASSERT(!sequenceId.setSequence("M1"));
    ASSERT(!sequenceId.setSequence("Q1"));
    ASSERT(!sequenceId.setSequence("V1"));
    ASSERT(!sequenceId.setSequence("A0"));
    ASSERT(!sequenceId.setSequence("A11"));

    ASSERT(!sequenceId.setSequence("A1-"));
    ASSERT(!sequenceId.setSequence("A1-A"));
    ASSERT(!sequenceId.setSequence("A1-F0"));
    ASSERT(!sequenceId.setSequence("A1-F1"));
    ASSERT(!sequenceId.setSequence("A1-F1-A1"));
}

TEST_CASE(SomeIncrementsTest) {
    SequenceId sequenceId(LETTERS_SEQUEBNCE, DIGINT_SEQUEBNCE);
    ASSERT(sequenceId.increment() == "A2");
    ASSERT(sequenceId.increment() == "A3");
    ASSERT(sequenceId.getSequence() == "A3");
    ASSERT(sequenceId.increment() == "A4");

    ASSERT(sequenceId.setSequence("A9"));
    ASSERT(sequenceId.increment() == "B1");

    ASSERT(sequenceId.setSequence("Z9"));
    ASSERT(sequenceId.increment() == "A1-A1");
    ASSERT(sequenceId.increment() == "A1-A2");

    ASSERT(sequenceId.setSequence("A1-Z9"));
    ASSERT(sequenceId.increment() == "A2-A1");

    ASSERT(sequenceId.setSequence("Z9-Z9"));
    ASSERT(sequenceId.increment() == "A1-A1-A1");

    ASSERT(sequenceId.setSequence("Z9-Z9-Z9"));
    ASSERT(sequenceId.increment() == "A1-A1-A1-A1");

    ASSERT(sequenceId.setSequence("Z9-Z9-Z9-Z9"));
    ASSERT(sequenceId.increment() == "A1-A1-A1-A1-A1");

    ASSERT(sequenceId.setSequence("Z9-Z9-Z9-Z9-Z9"));
    ASSERT(sequenceId.increment() == "A1-A1-A1-A1-A1-A1");

    ASSERT(sequenceId.setSequence("Z9-Z9-Z9-Z9-Z9-Z9"));
    ASSERT(sequenceId.increment() == "A1-A1-A1-A1-A1-A1-A1");

    ASSERT(sequenceId.setSequence("Z9-Z9-Z9-Z9-Z9-Z9-Z9"));
    ASSERT(sequenceId.increment() == "A1-A1-A1-A1-A1-A1-A1-A1");

    ASSERT(sequenceId.setSequence("Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9"));
    ASSERT(sequenceId.increment() == "A1-A1-A1-A1-A1-A1-A1-A1-A1");

    ASSERT(sequenceId.setSequence("Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9"));
    ASSERT(sequenceId.increment() == "A1-A1-A1-A1-A1-A1-A1-A1-A1-A1");

    ASSERT(sequenceId.setSequence("Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z8"));
    ASSERT(sequenceId.increment() == "Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9");
}

TEST_CASE(AdditionalIncrementsTest) {
    SequenceId sequenceId(LETTERS_SEQUEBNCE, DIGINT_SEQUEBNCE);
    ASSERT(sequenceId.setSequence("B4-X9-C8"));
    ASSERT(sequenceId.increment() == "B4-X9-C9");
    ASSERT(sequenceId.increment() == "B4-X9-E1");

    ASSERT(sequenceId.setSequence("B4-X9-Z9"));
    ASSERT(sequenceId.increment() == "B4-Y1-A1");

    ASSERT(sequenceId.setSequence("B4-Z9-Z9"));
    ASSERT(sequenceId.increment() == "B5-A1-A1");
}

TEST_CASE(IncrementAfterMaxValueTest) {
    // This case is beyond the scope of this task and can be reworked.
    SequenceId sequenceId(LETTERS_SEQUEBNCE, DIGINT_SEQUEBNCE);
    ASSERT(sequenceId.setSequence("Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9"));
    ASSERT(sequenceId.increment() == "A1");
}


int main()
{
    return UnitTest::RunTests();
}