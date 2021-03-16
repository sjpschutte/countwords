#include <stdio.h>
#include <ctype.h>
#include <Judy.h>

// On Ubuntu/Debian: sudo apt install libjudy-dev
// gcc -O3 -Wall judytree.c -o judytree-c -lJudy
//
// 2021-03-16 SJP Schutte



int main()
{
	Pvoid_t   PJArray = (PWord_t)NULL;  // Judy array.
	PWord_t   PValue;                   // Judy array element.
	Word_t    Bytes;                    // size of JudySL array.

	uint8_t word[101];
	while (scanf("%100s", word) != EOF) {
		for (char* p = (char*)word; *p; p++) {
			*p = tolower(*p);
		}
		JSLI(PValue, PJArray, word);   // store string into array
		if (PValue == PJERR)            // if out of memory?
		{                               // so do something
			printf("Malloc failed -- get more ram\n");
			exit(1);
		}
		++(*PValue);                    // count instances of string
	}

	word[0] = '\0';                    // start with smallest string.
	JSLF(PValue, PJArray, word);       // get first string
	while (PValue != NULL)
	{
		printf("%s %lu\n",word,*PValue);
		JSLN(PValue, PJArray, word);   // get next string
	}
	JSLFA(Bytes, PJArray);              // free array

	fprintf(stderr, "The JudySL array used %lu bytes of memory\n", Bytes);
	return (0);
}

