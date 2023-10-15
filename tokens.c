#include "header_shell_files.h"

/**
 * tokenizeString - This splits a string into words
 * using the specified delimiters
 * @str: This is the input string
 * @delimiters: This is the delimiter string
 * Return: This returns a pointer to an array of strings,
 * or NULL on failure
 */
char **tokenizeString(char *str, char *delimiters)
{
	int wordIndex, charIndex, wordLength, charCount, numWords = 0;
	char **tokens;

	if (str == NULL || str[0] == '\0')
		return (NULL);
	if (!delimiters)
		delimiters = " ";
	for (wordIndex = 0; str[wordIndex] != '\0'; wordIndex++)
		if (isDelimiter(str[wordIndex], delimiters)
				&& (isDelimiter(str[wordIndex + 1], delimiters)
					|| str[wordIndex + 1] == '\0'))
			numWords++;
	if (numWords == 0)
		return (NULL);
	tokens = malloc((numWords + 1) * sizeof(char *));
	if (!tokens)
		return (NULL);
	for (wordIndex = 0, charIndex = 0; charIndex < numWords; charIndex++)
	{
		while (isDelimiter(str[wordIndex], delimiters))
			wordIndex++;
		wordLength = 0;
		while (!isDelimiter(str[wordIndex + wordLength], delimiters)
				&& str[wordIndex + wordLength] != '\0')
			wordLength++;
		tokens[charIndex] = malloc((wordLength + 1) * sizeof(char));
		if (!tokens[charIndex])
		{
			for (wordLength = 0; wordLength < charIndex; wordLength++)
				free(tokens[wordLength]);
			free(tokens);
			return (NULL);
		}
		for (charCount = 0; charCount < wordLength; charCount++)
			tokens[charIndex][charCount] = str[wordIndex++];
		tokens[charIndex][charCount] = '\0';
	}
	tokens[charIndex] = NULL;
	return (tokens);
}

/**
 * tokenizeStringByChar - This splits a string into words
 * using the specified delimiter character
 * @str: This is the input string
 * @delimiter: This is the delimiter character
 * Return: This returns a pointer to an array of strings, or NULL on failure
 */

char **tokenizeStringByChar(char *str, char delimiter)
{
	int word_Index, char_Index, word_Length, char_Count, num_Words = 0;
	char **token;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (word_Index = 0; str[word_Index] != '\0'; word_Index++)
		if ((str[word_Index] != delimiter && str[word_Index + 1] == delimiter) ||
		    (str[word_Index] != delimiter && !str[word_Index + 1])
		    || str[word_Index + 1] == delimiter)
			num_Words++;
	if (num_Words == 0)
		return (NULL);
	token = malloc((1 + num_Words) * sizeof(char *));
	if (!token)
		return (NULL);
	for (word_Index = 0, char_Index = 0; char_Index < num_Words; char_Index++)
	{
		while (str[word_Index] == delimiter && str[word_Index] != delimiter)
			word_Index++;
		word_Length = 0;
		while (str[word_Index + word_Length] != delimiter
				&& str[word_Index + word_Length]
				&& str[word_Index + word_Length] != delimiter)
			word_Length++;
		token[char_Index] = malloc((word_Length + 1) * sizeof(char));
		if (!token[char_Index])
		{
			for (word_Length = 0; word_Length < char_Index; word_Length++)
				free(token[word_Length]);
			free(token);
			return (NULL);
		}
		for (char_Count = 0; char_Count < word_Length; char_Count++)
			token[char_Index][char_Count] = str[word_Index++];
		token[char_Index][char_Count] = 0;
	}
	token[char_Index] = NULL;
	return (token);
}
