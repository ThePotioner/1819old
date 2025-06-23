#include <cstdio>

class legend
{
private:
    /* data */
public:
    legend();
    ~legend();

    void q1();
    void q2();
};

legend::legend()
{
    printf("default create function call\n");
}

legend::~legend()
{
    printf("default delete function call");
}

// 1번 문제
void legend::q1()
{
    for (int i = 4; i >= 0; --i)
    {
        for (int j = 0; j < i; ++j)
        {
            printf(" ");
        }

        for (int k = 0; k < 9 - (i * 2); ++k)
        {
            printf("*");
        }

        printf("\n");
    }
    printf("   |||   \n");
}

// 2번 문제
void legend::q2()
{
    double scoreAvg;
    printf("이번 학기에 받고 싶은 전과목 평균 점수가 무엇인고?\n");
    scanf("%lf", &scoreAvg);

    printf("너의 이번 학기 전과목 평균 점수는 %.1lf점이 될 것이니라~\n", scoreAvg);
}


int main()
{
    legend legeno;

    legeno.q1();
    legeno.q2();
}