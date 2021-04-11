#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define t_len 100 //テキスト長
#define p_len 10  //パターン長
int next[p_len];  //ずらし表

char getRandomCharLower(void);             //ランダムなアルファベット1文字を生成する
char *getRandomCharsLower(int length);     //長さlengthのランダムなアルファベット文字列を作成する
void make_next(char p[], int m);           //ずらし表を計算する
int kmp(char p[], char t[], int m, int n); //kmp法を実行する

int main()
{
    unsigned int seed;

    /* 現在時刻を元に seed を決定*/
    seed = (unsigned)time(NULL);
    srand(seed);

    //実行
    // clock_t start, end;
    // start = clock();
    printf("\n%d\n", kmp(getRandomCharsLower(p_len), getRandomCharsLower(t_len), p_len, t_len));
    // end = clock();
    // printf("%.2f秒かかりました\n", (double)(end - start) / CLOCKS_PER_SEC);
}

//ランダムなアルファベット1文字を生成する
char getRandomCharLower(void)
{
    const char CHARS[] = "abcdefghijklmnopqrstuvwxyz";
    int index = rand() % strlen(CHARS);
    char c = CHARS[index];
    return c;
}

//長さlengthのランダムなアルファベット文字列を作成する
char *getRandomCharsLower(int length)
{
    static int count = 0;
    count++;
    char *chars = (char *)malloc(sizeof(char) * (length + 1));

    //文字列生成
    for (int i = 0; i < length; i++)
    {
        chars[i] = getRandomCharLower();
    }

    // テキストとパターンを表示
    if (count == 1)
        printf("text：");
    else
        printf("pattern：");
    printf("%s\n", chars);
    return chars;
}

//ずらし表を計算する
void make_next(char p[], int m)
{
    int i;
    int j = 0; //パターン文字列との比較時点で直前までに何文字一致していたかを表す
    next[0] = 1;

    for (i = 1; i < m; i++) //不照合の位置
    {
        if (p[i] == p[j])
        {
            next[i] = i - j;
            j++;
        }
        else
        {
            next[i] = i - j;
            j = 0;
        }
    }

    // ずらし表を表示
    printf("ずらし表：");
    for (int i = 0; i < m; i++)
        printf("%d ", next[i]);
}

//kmp法を実行する
int kmp(char p[], char t[], int m, int n)
{
    int i, j;

    make_next(p, m);

    for (i = j = 0; i < n && j < m;)
    {
        if (t[i] == p[j])
        {
            i++;
            j++;
        }
        else
        {
            j -= next[j];
            if (j < 0)
            {
                i++;
                j++;
            }
        }
    }
    if (j == m)
        return i - m;
    else
        return -1;
}

// https://algoful.com/Archive/Algorithm/KMPSearch
// https://qiita.com/ohwada/items/08af887748aa6a034c47