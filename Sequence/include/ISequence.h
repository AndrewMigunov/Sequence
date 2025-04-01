// ISequence.h
#ifndef ISEQUENCE_H
#define ISEQUENCE_H

#include <string>
#include <mutex>

class ISequence {
public:
	ISequence(const std::string& allowedLetters, const std::string& allowedDigits) :
		isConfiguratedSequence(false),
		m_sequence(),
		m_allowedLetters(allowedLetters),
		m_allowedDigits(allowedDigits) {
		if (!m_allowedLetters.empty() && !m_allowedDigits.empty()) {
			isConfiguratedSequence = true;
		}
		else {
			isConfiguratedSequence = false;
		}
	}
	virtual ~ISequence() = default;

	virtual bool setSequence(const std::string& sequense) = 0;
	virtual std::string getSequence() const = 0;

	virtual std::string increment() = 0;
protected:
	virtual bool isValid(const std::string& sequense) const = 0;
private:
	ISequence() = delete;
protected:
	bool isConfiguratedSequence;
	std::string m_sequence;
	const std::string m_allowedLetters;
	const std::string m_allowedDigits;
};

#endif // ISEQUENCE_H