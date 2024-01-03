#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char* txt;
    size_t maxSize;
} varchar;

varchar create_varchar(size_t max_size);
void scan_varchar(varchar *ptr_varchar);
int isIdentical(const char *string, const char *word);
int find_word(const varchar *const text, const char *word, int n);
void replace_word(varchar *const text, const char *word1,const char *word2, int n);

int main(int argc, char *argv[]) {

    if (argc < 5) {
        printf("usage: %s <max_size> <word to find> <word to replace> <occurence>\n", argv[0]);
        return 1;
    }

    int max_size = atoi(argv[1]);
    char* word1 = argv[2];
    char* word2 = argv[3];
    int occurence = atoi(argv[4]);

    varchar text = create_varchar(20);
    scan_varchar(&text);
    printf("text: %s\n", text.txt);

    int index = find_word(&text, word1, occurence);
    printf("index: %d\n", index);

    replace_word(&text, word1, word2, occurence);
    printf("text: %s\n", text.txt);
    
}

varchar create_varchar(size_t max_size) {
    varchar text;

    text.maxSize = max_size;
    text.txt = malloc(sizeof(char) * 0);

    return text;
};

void scan_varchar(varchar *text) {
    char* string = malloc(sizeof(char) * 255);

    printf("enter text: ");
    scanf("%254[^\n]s", string);
    
    size_t allocated_size = strlen(string) + 1 > text->maxSize ? text->maxSize : strlen(string) + 1;

    text->txt = realloc(text->txt, sizeof(char) * allocated_size);

    for (int i = 0; i < allocated_size; i++)
    {
        text->txt[i] = string[i];
    }

    text->txt[allocated_size] = '\0';
    
}

int find_word(const varchar *const text, const char *word, int n) {
    int actual_occurence = 0;
    for (int i = 0; i < strlen(text->txt); i++)
    {
        if (text->txt[i] == word[0]) {
            if (isIdentical(&text->txt[i], word)) {
                actual_occurence++;
                // if ((i == 0 || text->txt[i - 1] == ' ') && text->txt[strlen(text->txt) + i] == ' ') 
                //     actual_occurence++;
            }
            if (actual_occurence == n) return i;
        }
    }
    
    
    return -1;
}

int isIdentical(const char *string, const char *word) {
    if (strlen(word) > strlen(string)) return 0;
    for (int i = 0; i < strlen(word); i++) {
        if (string[i] != word[i]) return 0;
    }
    return 1;
}

void replace_word(varchar *const text, const char *word1,const char *word2, int n) {
    int oldSize = strlen(text->txt);
    int newSize = oldSize - strlen(word1) + strlen(word2);
    int index = find_word(text, word1, n);

    size_t allocated_size = newSize > text->maxSize ? text->maxSize : newSize + 1;

    
    char* newTxt = malloc(sizeof(char) * allocated_size);


    for (int i = 0; i < allocated_size; i++)
    {
        if (i >= index && i < i + strlen(word2)) 
        {
            newTxt[i] = word2[i - index];
        }
        else if (i >= i + strlen(word2)) 
        {
            newTxt[i] = text->txt[i - strlen(word2) + 1];
        }
        else {
            newTxt[i] = text->txt[i];
        } 
    }

    text->txt = newTxt;
}