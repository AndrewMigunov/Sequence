// SequenceId.h
#ifndef SEQUENCE_ID_H
#define SEQUENCE_ID_H

#include <string>
#include <vector>
#include <mutex>
#include "ISequence.h"
#include "AlphaNumericSubsequence.h"

class SequenceId : public ISequence {
public:
	SequenceId(const std::string& allowedLetters, const std::string& allowedDigits);
	virtual ~SequenceId() override = default;

	virtual bool setSequence(const std::string& sequense) override;
	virtual std::string getSequence() const override;

	virtual std::string increment() override;
protected:
	virtual bool isValid(const std::string& sequenseId) const override;
private:
	void addGroupSequence();
	std::vector<std::string> split(const std::string& str, char delimiter);
	void generateSequence();
	bool isLastSequenceIndex() const;
	SequenceId() = delete;
private:
	std::vector<AlphaNumericSubsequence> m_alphaNumericSubsequences;
	mutable std::mutex m_mutex;
	static const int MAX_GROUP_LENGTH = 10;
};


#endif // SEQUENCE_ID_H