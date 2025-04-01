// AlphaNumericSubsequence.h
#ifndef ALPHA_NUMERIC_SUBSEQUENCE_H
#define ALPHA_NUMERIC_SUBSEQUENCE_H

#include <string>
#include "ISubsequence.h"

class AlphaNumericSubsequence : public ISubsequence {
public:
	AlphaNumericSubsequence(const std::string& allowedLetters, const std::string& allowedDigits);
	virtual ~AlphaNumericSubsequence() override = default;

	virtual bool setSequence(const std::string& sequense) override;
	virtual std::string getSequence() const override;

	virtual std::string increment() override;
	virtual bool isLastSequenceIndex() const override;
protected:
	virtual bool isValid(const std::string& sequenseId) const override;
private:
	char incrementLetter();
	char incrementDigit();
	bool isLastSequenceIndex(size_t index, const std::string& sequence) const;

	AlphaNumericSubsequence() = delete;

	static char incrementSequence(size_t& index, const std::string& sequense, bool isLast);
private:
	size_t m_letterIndex;
	size_t m_digetIndex;
};


#endif // ALPHA_NUMERIC_SUBSEQUENCE_H