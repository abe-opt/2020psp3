#include <stdio.h>
#include <string.h>
#define DEBUG

#define ALPHABET_LEN    255

char StrOriginal[] = "On a dark deseart highway, cool wind in my hair.";
char StrKey[] = "wind";

char* ForceSearch(char text[], char key[])
{
    //  ここを実装する
    int pos, start, key_len, text_len;
    char *res;
    text_len = strlen(text);
    key_len = strlen(key);

    for(start = 0; (start + key_len) <= text_len; start++){
        for(pos =0; pos < key_len; pos++){
            if(text[start + pos] != key[pos]){
                break;
            }else{
                res = &text[start];
            }
        }

        if(pos == key_len){
            return res;
            break;
        }
    }

    return NULL;
}

char* BMSearch(char text[], char key[])
{
    //  ここを実装する
    int text_index, key_index, text_len, key_len, i;
    int table[256];
    key_len = strlen(key);
    text_len = strlen(text);
    typedef unsigned char UnChar;

    for(i = 0; i < 256; i++){
        table[i] = key_len;
    }

    for(i = 0; i < key_len - 1; i++){
        table[(UnChar)key[i]] =  key_len - i - 1;   
    }

    for(text_index = key_len - 1; text_index < text_len;){
        key_index = key_len - 1;
        while(text[text_index] == key[key_index]){
            if(key_index == 0){
                return &text[text_index];
            }

            text_index--;
            key_index--;
        }

        if(key_len - key_index > table[(UnChar) text[text_index]]){
            text_index += key_len - key_index;
        }else{
            text_index +=table[(UnChar) text[text_index]];
        }
    }

    return NULL;

}

int main(void)
{
    char*   str;
    str = ForceSearch(StrOriginal, StrKey);
    printf("Force Search. Find keyword at:%s\n", str);

    str = BMSearch(StrOriginal, StrKey);
    printf("BM Search. Find keyword at:%s\n", str);

    return 0;
}