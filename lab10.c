#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{	
    struct Trie* next[26];
    int isWord;
};

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie* myTrie = (struct Trie*)malloc(sizeof(struct Trie));
    myTrie->isWord = 0;
    for (int i = 0; i < 26; i++) {
		myTrie->next[i] = NULL;
	}
    return myTrie;
}

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
	int len = strlen(word);
    for (int i = 0; i < len; i++) {
		int idx = word[i] - 'a';
		if (pTrie->next[idx] == NULL) pTrie->next[idx] = createTrie();
		pTrie = pTrie->next[idx];
	}
	pTrie->isWord += 1;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
	int len = strlen(word);

	for (int i = 0; i < len; i++) {
		int idx = word[i] - 'a';
		if (pTrie->next[idx] == NULL) return 0;
		pTrie = pTrie->next[idx];
	}

	return pTrie->isWord;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
	for (int i = 0; i < 26; i++) {
		if (pTrie->next[i] != NULL) {
			pTrie->next[i] = deallocateTrie(pTrie->next[i]);
		}
	}
	free(pTrie);
	return NULL;
}



// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
	FILE* infile = fopen(filename, "r");
	int len;
	
	fscanf(infile, "%d", &len);
	
	for (int i = 0; i < len; i++) {
		char word[256];
		fscanf(infile, "%s", word);
		pInWords[i] = strdup(word);
	}

	return len;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}