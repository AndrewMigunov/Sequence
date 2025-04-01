#include "SequenceId.h"
#include <regex>
#include <sstream>

SequenceId::SequenceId(const std::string& allowedLetters, const std::string& allowedDigits) :
	ISequence(allowedLetters, allowedDigits),
	m_mutex(),
	m_alphaNumericSubsequences() {
	if (isConfiguratedSequence) {
		m_alphaNumericSubsequences.push_back(AlphaNumericSubsequence(m_allowedLetters, m_allowedDigits));
		generateSequence();
	}
}

bool SequenceId::setSequence(const std::string& secuenceId) {
	const std::lock_guard<std::mutex> lock(m_mutex);
	bool result = false;
	if (isConfiguratedSequence && isValid(secuenceId)) {
		std::vector<std::string> subsequences = split(secuenceId, '-');
		if (!subsequences.empty()) {
			m_alphaNumericSubsequences.clear();
			m_alphaNumericSubsequences.reserve(subsequences.size());
			for (auto it = subsequences.begin(); it != subsequences.end(); ++it) {
				AlphaNumericSubsequence alphaNumericSubsequence(m_allowedLetters, m_allowedDigits);
				alphaNumericSubsequence.setSequence(*it);
				m_alphaNumericSubsequences.push_back(alphaNumericSubsequence);
				result = true;
			}
			generateSequence();
		}
	}
	return result;
}

std::string SequenceId::getSequence() const {
	const std::lock_guard<std::mutex> lock(m_mutex);
	return m_sequence;
}

std::string SequenceId::increment() {
	const std::lock_guard<std::mutex> lock(m_mutex);
	if (isConfiguratedSequence) {
		size_t length = m_alphaNumericSubsequences.size();
		bool isLastSequenceId = isLastSequenceIndex();
		for (size_t i = length; i > 0; --i) {
			bool incrementPreviousElement = false;
			if (m_alphaNumericSubsequences[i - 1].isLastSequenceIndex()) {
				incrementPreviousElement = true;
			}
			m_alphaNumericSubsequences[i - 1].increment();
			if (!incrementPreviousElement) {
				break;
			}
		}
		if (isLastSequenceId) {
			if (length < MAX_GROUP_LENGTH) {
				addGroupSequence();
			}
			else {
				// TODO: Maybe throw an exception if the maximum value is exceeded?
				m_alphaNumericSubsequences.clear();
				m_alphaNumericSubsequences.push_back(AlphaNumericSubsequence(m_allowedLetters, m_allowedDigits));
			}
		}
		generateSequence();
	}
	return m_sequence;
}

bool SequenceId::isLastSequenceIndex() const {
	bool result = true;
	for (const auto& value : m_alphaNumericSubsequences) {
		if (!value.isLastSequenceIndex()) {
			result = false;
			break;
		}
	}
	return result;
}

bool SequenceId::isValid(const std::string& sequenseId) const {
	std::regex pattern("^[" + m_allowedLetters + "][" + m_allowedDigits + "](?:-[" + m_allowedLetters + "][" + m_allowedDigits + "]){0," + std::to_string(MAX_GROUP_LENGTH - 1) + "}$");
	return std::regex_match(sequenseId, pattern);
}

void SequenceId::addGroupSequence() {
	m_alphaNumericSubsequences.push_back(AlphaNumericSubsequence(m_allowedLetters, m_allowedDigits));
}

std::vector<std::string> SequenceId::split(const std::string& str, char delimiter) {
	std::vector<std::string> tokens;
	std::istringstream iss(str);
	std::string token;

	while (std::getline(iss, token, delimiter)) {
		tokens.push_back(token);
	}
	return tokens;
}

void SequenceId::generateSequence() {
	m_sequence.clear();
	for (auto it = m_alphaNumericSubsequences.begin(); it != m_alphaNumericSubsequences.end(); ++it) {
		m_sequence += it->getSequence();
		if (it + 1 != m_alphaNumericSubsequences.end()) {
			m_sequence += '-';
		}
	}
}
