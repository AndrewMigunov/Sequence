#include "AlphaNumericSubsequence.h"
#include <regex>

AlphaNumericSubsequence::AlphaNumericSubsequence(const std::string& allowedLetters, const std::string& allowedDigits) :
	ISubsequence(allowedLetters, allowedDigits),
	m_letterIndex(0),
	m_digetIndex(0) {
	if (isConfiguratedSequence) {
		m_sequence += m_allowedLetters[m_letterIndex];
		m_sequence += m_allowedDigits[m_digetIndex];
	}
}

bool AlphaNumericSubsequence::setSequence(const std::string& sequense) {
	bool result = false;
	if (isConfiguratedSequence && isValid(sequense)) {
		size_t index = m_allowedLetters.find(sequense[0]);
		if (index != std::string::npos) {
			m_letterIndex = index;
		}
		index = m_allowedDigits.find(sequense[1]);
		if (index != std::string::npos) {
			m_digetIndex = index;
		}
		m_sequence = sequense;
		result = true;
	}
	return result;
}

std::string AlphaNumericSubsequence::getSequence() const {
	return m_sequence;
}

std::string AlphaNumericSubsequence::increment() {
	if (isConfiguratedSequence) {
		if (isLastSequenceIndex(m_digetIndex, m_allowedDigits)) {
			m_sequence[0] = incrementLetter();
		}
		m_sequence[1] = incrementDigit();
	}
	return m_sequence;
}

bool AlphaNumericSubsequence::isLastSequenceIndex() const {
	return isLastSequenceIndex(m_letterIndex, m_allowedLetters) && isLastSequenceIndex(m_digetIndex, m_allowedDigits);
}

bool AlphaNumericSubsequence::isValid(const std::string& sequenseId) const {
	std::regex pattern("^[" + m_allowedLetters + "][" + m_allowedDigits + "]$");
	return std::regex_match(sequenseId, pattern);
}

char AlphaNumericSubsequence::incrementLetter() {
	return incrementSequence(m_letterIndex, m_allowedLetters, isLastSequenceIndex(m_letterIndex, m_allowedLetters));
}

char AlphaNumericSubsequence::incrementDigit() {
	return incrementSequence(m_digetIndex, m_allowedDigits, isLastSequenceIndex(m_digetIndex, m_allowedDigits));
}

bool AlphaNumericSubsequence::isLastSequenceIndex(size_t index, const std::string& sequence) const {
	bool result = false;
	size_t lastIndex = 0;
	if (!sequence.empty()) {
		lastIndex = sequence.length() - 1;
	}
	if (index == lastIndex) {
		result = true;
	}
	return result;
}

char AlphaNumericSubsequence::incrementSequence(size_t& index, const std::string& sequense, bool isLast) {
	if (isLast) {
		index = 0;
	}
	else {
		index++;
	}
	return sequense[index];
}
