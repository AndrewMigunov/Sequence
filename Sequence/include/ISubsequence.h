// ISubsequence.h
#ifndef ISUBSEQUENCE_H
#define ISUBSEQUENCE_H

#include <string>
#include "ISequence.h"

class ISubsequence : public ISequence {
public:
	ISubsequence(const std::string& allowedLetters, const std::string& allowedDigits) :
		ISequence(allowedLetters, allowedDigits) {
	}
	virtual ~ISubsequence() override = default;
	virtual bool isLastSequenceIndex() const = 0;
private:
	ISubsequence() = delete;
};

#endif // ISUBSEQUENCE_H