#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define t_len 100 //�e�L�X�g��
#define p_len 10  //�p�^�[����
int next[p_len];  //���炵�\

char getRandomCharLower(void);             //�����_���ȃA���t�@�x�b�g1�����𐶐�����
char *getRandomCharsLower(int length);     //����length�̃����_���ȃA���t�@�x�b�g��������쐬����
void make_next(char p[], int m);           //���炵�\���v�Z����
int kmp(char p[], char t[], int m, int n); //kmp�@�����s����

int main()
{
    unsigned int seed;

    /* ���ݎ��������� seed ������*/
    seed = (unsigned)time(NULL);
    srand(seed);

    //���s
    // clock_t start, end;
    // start = clock();
    printf("\n%d\n", kmp(getRandomCharsLower(p_len), getRandomCharsLower(t_len), p_len, t_len));
    // end = clock();
    // printf("%.2f�b������܂���\n", (double)(end - start) / CLOCKS_PER_SEC);
}

//�����_���ȃA���t�@�x�b�g1�����𐶐�����
char getRandomCharLower(void)
{
    const char CHARS[] = "abcdefghijklmnopqrstuvwxyz";
    int index = rand() % strlen(CHARS);
    char c = CHARS[index];
    return c;
}

//����length�̃����_���ȃA���t�@�x�b�g��������쐬����
char *getRandomCharsLower(int length)
{
    static int count = 0;
    count++;
    char *chars = (char *)malloc(sizeof(char) * (length + 1));

    //�����񐶐�
    for (int i = 0; i < length; i++)
    {
        chars[i] = getRandomCharLower();
    }

    // �e�L�X�g�ƃp�^�[����\��
    if (count == 1)
        printf("text�F");
    else
        printf("pattern�F");
    printf("%s\n", chars);
    return chars;
}

//���炵�\���v�Z����
void make_next(char p[], int m)
{
    int i;
    int j = 0; //�p�^�[��������Ƃ̔�r���_�Œ��O�܂łɉ�������v���Ă�������\��
    next[0] = 1;

    for (i = 1; i < m; i++) //�s�ƍ��̈ʒu
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

    // ���炵�\��\��
    printf("���炵�\�F");
    for (int i = 0; i < m; i++)
        printf("%d ", next[i]);
}

//kmp�@�����s����
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