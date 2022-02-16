#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#pragma warning(disable: 4996)
#pragma warning(disable: 6031)

#define LENGTH_OF_STRING 20
#define SCALE_OF_SAVE_DATA 50
#define SCISSORS    1   //Game1
#define ROCK        2   //Game1
#define PAPER       3   //Game1
#define LEFT        75  //Game2
#define RIGHT       77  //Game2
#define UP          72  //Game2
#define DOWN        80  //Game2
#define RANK        100 //Game2
#define EXIT        -1  //Game2

typedef enum _bool
{
    false, true
}bool;

typedef struct _Player
{
    char Name[LENGTH_OF_STRING];
    int Game1_Score;
    int Game2_Score;
    int Game3_Score;
    bool personal_information_hidden;
}Player;

int Home();

void prepare_the_game();
void write_player_name(Player* cu);
void redefine_user_data(Player* cu);
char select_play_game(Player* cu);
void load_data(Player c_u);

void ranking_check();
int ranking_check_Home();

void total_ranking_check();
void Show_total_ranking_list();

void individual_ranking_Home();
void individual_ranking_check(int index);
void Show_individual_ranking_list(int index);

void information_enable_disable();

void game1(Player* cu);

void game2(Player* cu);
int is_ending(int puzzle[][5]);
int get_directionkey();
void print_puzzle(int puzzle[][5], int toggle);
void RANKING();

void game3(Player* cu);

Player* pointer_data_base[SCALE_OF_SAVE_DATA];

typedef struct node
{
    Player linked_User;
    struct node* next;
} Node;

typedef struct list
{
    Node* head;
    Node* tail;
    int size;
} List;

void createlist(List* list)
{
    list->head = (Node*)malloc(sizeof(Node));
    list->tail = (Node*)malloc(sizeof(Node));

    if (list->head == NULL || list->tail == NULL)
        printf("메모리 공간이 부족합니다\n");
    else
    {
        list->head->next = list->tail;
        list->tail->next = list->tail;
        list->size = 0;
    }
}

void addLast(List* list, Player current_user)
{
    Node* last = list->head;

    while (list->tail != last->next)
        last = last->next;

    Node* newNode = (Node*)malloc(sizeof(Node));

    if (newNode == NULL)
        printf("메모리 공간이 부족합니다\n");
    else 
    {
        newNode->linked_User = current_user;

        newNode->next = list->tail;

        last->next = newNode;
        list->size++;
    }
}

/*
Node* searchNode(List* list, Player* address) {
    Node* node = list->head->next;

    while (node != list->tail)
    {
        if (strcmp(node->linked_User.Name , address->Name) == 0)
            return node;

        node = node->next;
    }
    //printf("데이터를 찾지 못했습니다.\n");

    return NULL;
}
*/

void printList(List* list)
{
    Node* node = list->head->next;
    int i = 1;

    while (node != list->tail)
    {
        printf("%d 번째 노드의 구조체 포인터가 가르키는 값들\n", i++);
        printf("Name:%s\t", node->linked_User.Name);
        printf("Game1:%d\t", node->linked_User.Game1_Score);
        printf("Game2:%d\t", node->linked_User.Game2_Score);
        printf("Game3:%d\n\n", node->linked_User.Game3_Score);

        node = node->next;
    }
}

List list;

void test_data_base_list(Player* data_base);

Player* linked_pointer_data_base[2];

int main(void)
{
    //*** 연결리스트 완성시 필요없음 ***
    Player data_base[SCALE_OF_SAVE_DATA] = { 0 };

    //포인터에 DB주소 복사  *** 연결리스트 완성시 필요없음 ***
    for (int i = 0; i < SCALE_OF_SAVE_DATA; i++)   pointer_data_base[i] = &data_base[i];
    
    test_data_base_list(data_base);         //테스트용 데이터

    /*--------여기서부터 연결리스트 항목 시작--------*/ 
    createlist(&list);

    //test_data_base_list의 정보들 list(liked list)에 저장
    int i = 0;
    while(true)
    {
        if (strcmp(data_base[i].Name, "") != 0)
        {
            addLast(&list, data_base[i]);
            i++;
        }
        else
        {
            i = 0;//printf("%d\n", i);      //10(실질적 데이터의 끝)
            break;
        }
    }

    Sleep(1000);
    /*--------여기까지 연결리스트 항목--------*/

    int key_of_menu = 0;

    while (true)
    {
        system("cls");

        key_of_menu = Home();
        switch (key_of_menu)
        {
        case 1:         //플레이어 이름 작성 > 게임 선택 > 게임 실행
            prepare_the_game();
            break;

        case 2:         //랭킹 조회 메뉴
            ranking_check();
            break;

        case 3:         //프로그램 종료
            printf("\n사용자에 의해 프로그램이 종료되었습니다.\n");
            exit(0);
        }
    }
    return 0;
}
void test_data_base_list(Player* data_base)
{
    Player test_data_base[10] = {
        {"test0",80,100,20,false},
        {"test1",60,120,40,true},
        {"test2",60,98,40,true},
        {"test3",40,95,60,false},
        {"test4",80,110,60,true},
        {"test5",100,135,40,false},
        {"test6",40,87,80,true},
        {"test7",20,90,40,true},
        {"test8",20,105,20,false},
        {"test9",80,93,80,true}
    };

    for (int i = 0; i < 10; i++)
    {
        strcpy(data_base[i].Name, test_data_base[i].Name);
        data_base[i].Game1_Score = test_data_base[i].Game1_Score;
        data_base[i].Game2_Score = test_data_base[i].Game2_Score;
        data_base[i].Game3_Score = test_data_base[i].Game3_Score;
        data_base[i].personal_information_hidden = test_data_base[i].personal_information_hidden;
    }
}

int Home()
{
    int key_of_menu;

    while (true)
    {
        char input = 0;
        printf("\n   *HOME 화면*\n\n");
        printf(" 1. 게임 시작\n");
        printf(" 2. 랭킹 조회\n");
        printf(" 3. 프로그램 종료\n\n");
        printf("메뉴 번호를 입력하세요. >> ");
        scanf(" %c", &input);

        system("cls");

        if (input == '1' || input == '2' || input == '3') {
            key_of_menu = input - '1' + 1;
            break;
        }
        else
            printf("\n 잘못된 접근입니다.\n");
    }

    return key_of_menu;
}

void prepare_the_game()
{
    while (true)
    {
        system("cls");

        Player current_user = { 0 };
        write_player_name(&current_user);                                         //플레이어 이름을 작성

        if (strcmp(current_user.Name, "`") == 0)   break;                         //플레이어 이름을 작성하는 메뉴에서 이전 메뉴(홈 화면)로 이동

        redefine_user_data(&current_user);                                        //기존 데이터와 비교해서 current_user 정보 갱신

        if (strcmp(current_user.Name, "WritePlayerNameAgain") == 0)   continue;   //기존 유저가 있지만 갱신을 하지 않으면 이름을 다시 작성

        while (true)
        {
            /*게임 선택*/
            char select_game = select_play_game(&current_user);            //게임을 선택하라는 문구

            switch (select_game)                        //입력 받은 값을 통해 플레이할 게임 선정
            {
            case '1':                                   //Game 1 실행 - 끝나면 게임 선택 화면으로 이동
                printf("잠시후 1번 게임이 실행됩니다. \n"); Sleep(1000);
                game1(&current_user);
                load_data(current_user);
                break;

            case '2':                                   //Game 2 실행 - 끝나면 게임 선택 화면으로 이동
                printf("잠시후 2번 게임이 실행됩니다. \n"); Sleep(1000);
                game2(&current_user);
                load_data(current_user);
                break;

            case '3':                                   //Game 3 실행 - 끝나면 게임 선택 화면으로 이동
                printf("잠시후 3번 게임이 실행됩니다. \n"); Sleep(1000);
                game3(&current_user);
                load_data(current_user);
                break;
            }
            if (select_game == '`') break;
        }
    }
}

void write_player_name(Player* cu)
{
    printf("\n   **플레이어 이름 작성**\n");
    printf("\n   이전 메뉴로 가기 : `\n");
    printf("\n플레이어 이름을 입력하세요. >> ");
    scanf("%s", cu->Name);
}

void redefine_user_data(Player* cu)
{
    Node* node = list.head->next;

    while (node != list.tail)
    {
        if(strcmp(cu->Name, node->linked_User.Name) == 0)
        {
            char input = 0;

            system("cls");
            printf("%s 플레이어의 점수가 기존에 존재합니다.\n", cu->Name);
            printf("\n이름\t게임1\t게임2\t게임3\n");
            printf("%s\t%d\t%d\t%d\n", node->linked_User.Name, node->linked_User.Game1_Score, node->linked_User.Game2_Score, node->linked_User.Game3_Score);

            while (true)
            {
                printf("\n점수를 불러오겠습니까? : (y/n)");
                printf("\n(점수를 불러오지 않으면 다른 플레이어로 간주되며, 이름을 다시 입력해야 합니다.) ");
                scanf(" %c", &input);

                if (input == 'y')
                {
                    strcpy((cu->Name), (node->linked_User.Name));
                    cu->Game1_Score = node->linked_User.Game1_Score;
                    cu->Game2_Score = node->linked_User.Game2_Score;
                    cu->Game3_Score = node->linked_User.Game3_Score;

                    printf("%s의 점수를 불러옵니다", cu->Name);
                    Sleep(600);
                    printf(".");
                    Sleep(600);
                    printf(".");
                    Sleep(600);

                    break;
                }
                else if (input == 'n')
                {
                    strcpy(cu->Name, "WritePlayerNameAgain");
                    break;
                }
                else
                    printf("\n잘못된 접근입니다.\n");
            }
            break;
        }

        node = node->next;
    }
}
//redefine_user_data 원본
/*
void redefine_user_data(Player* cu)
{
    for (int i = 0; i < SCALE_OF_SAVE_DATA; i++)
    {
        if (strcmp(cu->Name, pointer_data_base[i]->Name) == 0)
        {
            char input = 0;

            system("cls");
            printf("%s 플레이어의 점수가 기존에 존재합니다.\n", cu->Name);
            printf("\n이름\t게임1\t게임2\t게임3\n");
            printf("%s\t%d\t%d\t%d\n", pointer_data_base[i]->Name, pointer_data_base[i]->Game1_Score, pointer_data_base[i]->Game2_Score, pointer_data_base[i]->Game3_Score);

            while (true)
            {
                printf("\n점수를 불러오겠습니까? : (y/n)");
                printf("\n(점수를 불러오지 않으면 다른 플레이어로 간주되며, 이름을 다시 입력해야 합니다.) ");
                scanf(" %c", &input);

                if (input == 'y')
                {
                    strcpy((cu->Name), (pointer_data_base[i]->Name));
                    cu->Game1_Score = pointer_data_base[i]->Game1_Score;
                    cu->Game2_Score = pointer_data_base[i]->Game2_Score;
                    cu->Game3_Score = pointer_data_base[i]->Game3_Score;

                    printf("%s의 점수를 불러옵니다", cu->Name);
                    Sleep(600);
                    printf(".");
                    Sleep(600);
                    printf(".");
                    Sleep(600);

                    break;
                }
                else if (input == 'n')
                {
                    strcpy(cu->Name, "WritePlayerNameAgain");
                    break;
                }
                else
                    printf("\n잘못된 접근입니다.\n");
            }
            break;
        }
    }
}
*/

char select_play_game(Player* cu)
{
    system("cls");
    char select_game = 0;

    while (true)
    {
        printf("\n***게임 선택 메뉴***\n");
        printf("(1)... Game 1 START!!\n");
        printf("(2)... Game 2 START!!\n");
        printf("(3)... Game 3 START!!\n");
        printf("(`)... 이전 메뉴\n\n");
        printf("%s 플레이어가 진행할 게임을 선택하세요. >> ", cu->Name);
        scanf(" %c", &select_game);

        if (select_game == '1' || select_game == '2' || select_game == '3' || select_game == '`')
            break;
        else
        { 
            system("cls");   
            printf("\n 잘못된 접근입니다.\n"); 
        }
    }
    return select_game;
}
/*---------------------------------------------------*/
void game1(Player* cu)
{
    system("cls");
    char rcp[3][10] = { "가위","바위","보" };
    int number_game_EE = 0;

    char change_score[3], cont_game[3];
    int end_game_EE = 0;
    int score = 0, play_num = 5;

    char user = '\0';
    int game_count;

    //게임시작
    while (1)
    {
        game_count = 1;
        int score = 0;         //user 획득 sore
        //char stop_game[3];

        //게임 시작
        printf(" ` (게임 취소)\n");
        srand((unsigned)time(NULL));//난수 뿌리기
        while (game_count <= play_num)
        {

            while (getchar() != '\n');

            int com = rand() % 3 + 1;

            printf("%d 번째 게임\n", game_count);

            printf("가위(1), 바위(2), 보(3)를 입력하세요 : ");
            scanf(" %c", &user);
            if (user == '`')    break;

            //SCISSORS:1    ROCK:2    PAPER:3
            if ((user - '0' != SCISSORS) && (user - '0' != ROCK) && (user - '0' != PAPER))
            {
                printf("\n잘못된 번호입니다. 다시 입력하여 주시기 바랍니다\n");
                continue;
            }

            printf("컴퓨터 : %s\n", rcp[com - 1]);
            printf("user : %s\n", rcp[(int)(user - '1')]);

            if (((com == SCISSORS) && (user - '0' == PAPER)) || ((com == ROCK) && (user - '0' == SCISSORS)) || ((com == PAPER) && (user - '0' == ROCK)))
            {
                printf("\n~º~º~컴퓨터의 승~º~º~\n\n");
            }
            else if (com == user - '0')
            {
                printf("\n~*~*~무승부 입니다.~*~*~\n\n");
            }
            else if (((com == SCISSORS) && (user - '0' == ROCK)) || ((com == ROCK) && (user - '0' == PAPER)) || ((com == PAPER) && (user - '0' == SCISSORS)))
            {
                printf("\n~ˇ~ˇ~당신의 승~ˇ~ˇ~\n\n");
                score++; // 유저 점수
            }

            game_count++; //게임 횟수
        }

        //게임 끝
        //게임 점수 갱신

        if (user != '`')
        {
            while (1)
            {
                printf("총 %d 판 중 %d 번 이겼습니다!\n\n", play_num, score);
                printf("☆★☆기존 점수 : %d 점 || new score : %d 점★☆★\n", cu->Game1_Score, 20 * score);
                printf("\n점수를 갱신하시겠습니까?(y/n) -> ");
                scanf(" %s", &change_score);

                if (change_score[0] == 'y' && change_score[1] == '\0')
                {
                    printf("점수를 갱신합니다!\n");
                    cu->Game1_Score = 20 * score;
                    printf("현재 score -> %d..\n\n", cu->Game1_Score);
                    break;
                }
                else if (change_score[0] == 'n' && change_score[1] == '\0')
                {
                    printf("기존 점수로 기록합니다\n\n");
                    printf("현재 score -> %d...\n\n", cu->Game1_Score);
                    break;
                }
                else
                {
                    printf("\n잘못된 입력입니다. 다시 입력해 주십시오.\n\n");
                }
            }
        }

        //점수 갱신 끝
        //게임 종료

        while (1)
        {
            if (user == '`')
            {
                printf(" 게임을 종료합니다 \n");
                end_game_EE = 1;
                break;
            }

            printf("게임을 다시 하시겠습니까?(y/n) -> ");
            scanf("%s", cont_game);

            if (cont_game[0] == 'y' && cont_game[1] == '\0')
            {
                printf("게임을 다시 시작합니다!\n");
                end_game_EE = 0;
                Sleep(1000);
                system("cls");
                break;
            }
            else if (cont_game[0] == 'n' && cont_game[1] == '\0')
            {
                end_game_EE = 1;
                break;
            }
            else
            {
                printf("잘못된 입력입니다. 다시 입력해 주십시오.\n");
            }
        }

        //찐막찐막
        if (end_game_EE == 1)
        {
            printf("\n……end_gamme NO.1\n\n");
            Sleep(500);
            break;
        }
    }

    printf("플레이어의 게임 실행 후 Game1 스코어 : %d\n", cu->Game1_Score);
    Sleep(1000);

}
/*---------------------------------------------------*/
void game2(Player* cu)
{
    int i = 0;
    int row = 4;
    int col = 4;
    int key = 0;
    int toggle = 0;
    char input = 0;

    do
    {
        int score = 0;
        int puzzle[5][5] = { {1,9,7,5,14},{16,2,8,10,3},{6,11,19,4,15},{13,21,20,24,22}, {17,12,23,18,0} };

        while (!is_ending(puzzle))
        {
            print_puzzle(puzzle, toggle);
            printf("\n%s님의 현재 스코어 : %d\n", cu->Name, 200 - score);
            key = get_directionkey();

            if (key == EXIT)    break;

            switch (key)
            {
            case RIGHT:
                if (col > 0)
                {
                    puzzle[row][col] = puzzle[row][col - 1];
                    puzzle[row][col - 1] = 0;
                    score = score + 1;
                    col--;
                }
                break;

            case LEFT:
                if (col < 5 - 1)
                {
                    puzzle[row][col] = puzzle[row][col + 1];
                    puzzle[row][col + 1] = 0;
                    score = score + 1;
                    col++;
                }
                break;

            case UP:
                if (row < 5 - 1)
                {
                    puzzle[row][col] = puzzle[row + 1][col];
                    puzzle[row + 1][col] = 0;
                    score = score + 1;
                    row++;
                }
                break;

            case DOWN:
                if (row > 0)
                {
                    puzzle[row][col] = puzzle[row - 1][col];
                    puzzle[row - 1][col] = 0;
                    score = score + 1;
                    row--;
                }
                break;

            case RANK:
                toggle = 1 - toggle;
                break;
            }

        }

        if (key == EXIT)    break;

        print_puzzle(puzzle, toggle);
        printf("\n%s의 스코어  : %d", cu->Name, 200 - score);

        char answer;

        do
        {
            printf("\n현재 최고 기록 : %d\n", cu->Game2_Score);
            printf("현재 게임 기록 : %d\n", 200 - score);
            printf("기록을 저장하시겠습니까? Y/N\n");
            scanf(" %c", &answer);
            if (answer == 'Y')
            {
                cu->Game2_Score = 200 - score;
                break;
            }
            else if (answer == 'N')
                break;
            else
                printf("다시 입력\n\n");

        } while (answer != 'Y' && answer != 'N');

        printf("\nContinue? Y/N \n\n");
        scanf(" %c", &input);

    } while (input == 'Y');
}

int is_ending(int puzzle[][5])
{
    int r, c;

    for (r = 0; r < 5; r++)
    {
        for (c = 0; c < 5; c++)
        {
            if (puzzle[r][c] != r * 5 + c + 1)
            {
                return(r == 4) && (c == 4);
            }
        }
    }
    return 0;
}

int get_directionkey()
{
    int key;
    int toggle = 1;

    key = _getch();

    if (key == 224)
        return _getch();
    else if (key == 'R' || key == 'r')
        return RANK;
    else if (key == '`')
        return EXIT;

    return 0;
}

void print_puzzle(int puzzle[][5], int toggle)
{
    int r, c;
    system("cls");
    for (r = 0; r < 5; r++)
    {
        for (c = 0; c < 5; c++)
        {
            if (puzzle[r][c])
                printf("%3d", puzzle[r][c]);
            else
                printf("   ");
        }
        printf("\n");
    }

    printf("\n>>방향키 선택\n");
    printf("랭킹 보기 'R'\n");
    printf("게임 종료 '`'\n");

    if (toggle == 1)
        RANKING();

}

void RANKING()
{
    for (int i = 0; i < SCALE_OF_SAVE_DATA - 1; i++)
    {
        for (int j = 0; j < SCALE_OF_SAVE_DATA - (i + 1); j++)
        {
            if (pointer_data_base[j]->Game2_Score < pointer_data_base[j + 1]->Game2_Score)
            {
                Player* Temp = pointer_data_base[j];
                pointer_data_base[j] = pointer_data_base[j + 1];
                pointer_data_base[j + 1] = Temp;
            }
        }
    }

    printf("\n1st : %d", pointer_data_base[0]->Game2_Score);
    printf("\n2nd : %d", pointer_data_base[1]->Game2_Score);
    printf("\n3rd : %d\n", pointer_data_base[2]->Game2_Score);
}
/*---------------------------------------------------*/
void game3(Player* cu)
{
    system("cls");
    printf("게임 실행 전 유저 데이터\n");
    printf("플레이어 이름 : %s\n", cu->Name);
    printf("플레이어의 게임 실행 전 Game3 스코어 : %d\n", cu->Game3_Score);
    printf("-----------------------------\n");
    printf("User: %s님이 3번게임 홀짝을 선택했습니다.\n", cu->Name);

    while (1)
    {
        int Player_win = 1;
        int score = 0;
        int com = 0;
        char sel = 0;
        int end_game3 = 0;
        char change_score[3];
        char cont_game[3];

        srand((unsigned)time(NULL));

        while (Player_win > 0)
        {
            Player_win = 0;
            printf("=홀짝게임=\n");
            printf("홀 : 1\n짝 : 2\n");
            printf("----------\n");
            printf("숫자를 선택하세요 ->");
            scanf(" %c", &sel);

            com = rand() % 2 + 1;

            if (com == (sel - '1' + 1))
            {
                Player_win = 1;
                score++;
                printf("이겼습니다. 계속 진행해주세요.\n");
            }
            else if (com != (sel - '1' + 1))
            {
                printf("졌습니다.\n");
                //system("pause");
            }
            else
            {
                Player_win = 1;
                printf("입력이 잘못됐습니다.\n");
            }
        }
        printf("Score : %d점입니다.\n", 20 * score);

        while (1)
        {
            printf("기존점수 : %d점\n새로운점수 : %d점\n", cu->Game3_Score, 20 * score);
            printf("점수 갱신하겠습니까?(y/n)\n");
            scanf("%s", change_score);

            if (change_score[0] == 'y' && change_score[1] == '\0')
            {
                printf("점수를 갱신합니다.\n");
                cu->Game3_Score = 20 * score;
                printf("현재 점수는 %d점입니다. \n\n", cu->Game3_Score);
                break;
            }
            else if (change_score[0] == 'n' && change_score[1] == '\0')
            {
                printf("기존 점수로 보존합니다.\n");
                printf("현재 점수는 %d점입니다. \n\n", cu->Game3_Score);
                break;
            }
        }

        while (1)
        {
            printf("게임을 다시 하겠습니까?(y/n)");
            scanf("%s", cont_game);
            printf("%s\n", cont_game);

            if (cont_game[0] == 'y' && cont_game[1] == '\0')
            {
                printf("게임을 다시 시작합니다.\n");
                end_game3 = 0;
                system("cls");
                break;
            }
            else if (cont_game[0] == 'n' && cont_game[1] == '\0')
            {
                printf("\n게임을 종료합니다.\n");
                end_game3 = 1;

                break;
            }
            else
            {
                printf("잘못된 입력입니다. 다시 입력해주세요.\n");
            }
        }
        if (end_game3 == 1)
        {
            printf("게임 끝\n\n");
            break;
        }
    }

    printf("플레이어의 게임 실행 후 Game3 스코어 : %d\n", cu->Game3_Score);
}
/*---------------------------------------------------*/

void load_data(Player c_u)
{

    Node* node = list.head->next;
    bool Same_name = false;

    while (node != list.tail)
    {
        if (strcmp(c_u.Name, node->linked_User.Name) == 0)
        {
            node->linked_User.Game1_Score = c_u.Game1_Score;
            node->linked_User.Game2_Score = c_u.Game2_Score;
            node->linked_User.Game3_Score = c_u.Game3_Score;
            node->linked_User.personal_information_hidden = c_u.personal_information_hidden;

            printf("\n기존의 데이터가 갱신되었습니다.");
            Same_name = true;
        }

        node = node->next;
    }

    if (Same_name == false)
    {
        addLast(&list, c_u);
        printf("\n신규 데이터가 저장되었습니다.");
    }

    Sleep(1200);
}
//load_data 원본
/*
void load_data(Player* c_u)
{
    bool Same_name = false;
    //같은 이름 찾아서 데이터 갱신
    for (int i = 0; i < SCALE_OF_SAVE_DATA; i++)
    {
        if (strcmp(c_u->Name, pointer_data_base[i]->Name) == 0)
        {
            pointer_data_base[i]->Game1_Score = c_u->Game1_Score;
            pointer_data_base[i]->Game2_Score = c_u->Game2_Score;
            pointer_data_base[i]->Game3_Score = c_u->Game3_Score;

            Same_name = true;
            printf("\n기존의 데이터가 갱신되었습니다.");
            break;
        }
    }
    //DB에 없는 이름 -> DB의 공석에 저장
    if (Same_name == false)
    {
        for (int i = 0; i < SCALE_OF_SAVE_DATA; i++)
        {
            if (strcmp(pointer_data_base[i]->Name, "") == 0)      //공석 찾기
            {
                strcpy(pointer_data_base[i]->Name, c_u->Name);
                pointer_data_base[i]->Game1_Score = c_u->Game1_Score;
                pointer_data_base[i]->Game2_Score = c_u->Game2_Score;
                pointer_data_base[i]->Game3_Score = c_u->Game3_Score;

                printf("\n신규 데이터가 저장되었습니다.");
                break;
            }
        }
    }
    Sleep(1200);
}
*/

void ranking_check()
{
    int key_of_menu = 0;
    while (true)
    {
        system("cls");
        key_of_menu = ranking_check_Home();

        switch (key_of_menu)
        {
        case 1:               //종합 랭킹 조회(합 점수 기준 랭킹) & 이름으로 개인 종합 랭킹 검색
            total_ranking_check();
            break;
        case 2:               //게임 별 랭킹 조회 & 이름으로 개인 랭킹 검색
            individual_ranking_Home();
            break;
        case 3:               //개인 정보 숨김/표시 설정 (이름 입력해서 숨김<->표시 전환)
            information_enable_disable();
            break;
        }

        if (key_of_menu == EXIT) break;
    }
}

int ranking_check_Home()
{
    int key_of_menu;
    char input = 0;

    while (true)
    {
        printf("\n ** 랭킹 조회 메뉴 **\n\n");
        printf(" 1. 종합 랭킹 조회\n");
        printf(" 2. 게임 별 랭킹 조회\n");
        printf(" 3. 개인 정보 숨김/표시 설정\n");
        printf("\n   이전 메뉴로 가기 : `\n\n");
        printf("메뉴 번호를 입력하세요. >> ");

        scanf(" %c", &input);

        system("cls");

        if (input == '1' || input == '2' || input == '3' || input == '`')
            break;
        else
            printf("\n 잘못된 접근입니다.\n");
    }

    if (input == '`')
        key_of_menu = EXIT;
    else
        key_of_menu = input - '1' + 1;

    return key_of_menu;
}

void total_ranking_check()
{
    char search_name[LENGTH_OF_STRING] = { 0 };

    for (int i = 0; i < SCALE_OF_SAVE_DATA - 1; i++)
    {
        for (int j = 0; j < SCALE_OF_SAVE_DATA - i - 1; j++)
        {
            if (pointer_data_base[j]->Game1_Score + pointer_data_base[j]->Game2_Score + pointer_data_base[j]->Game3_Score < pointer_data_base[j + 1]->Game1_Score + pointer_data_base[j + 1]->Game2_Score + pointer_data_base[j + 1]->Game3_Score)
            {
                Player* Temp = pointer_data_base[j + 1];
                pointer_data_base[j + 1] = pointer_data_base[j];
                pointer_data_base[j] = Temp;
            }
        }
    }

    Show_total_ranking_list();

    while (true)
    {
        printf("\n\t이전 메뉴로 가기 : `\n");
        printf("\n검색할 유저의 이름을 입력하세요. >> ");
        scanf("%s", &search_name);

        if (strcmp(search_name, "`") == 0) break;

        int check = 0;

        for (int i = 0; i < SCALE_OF_SAVE_DATA; i++)
        {
            if (strcmp(search_name, pointer_data_base[i]->Name) != 0)
            {
                check++;
                continue;
            }

            system("cls");
            printf("\n검색된 결과는 다음과 같습니다.\n");
            printf("\n랭킹\t이름\t게임1\t게임2\t게임3\t합계\n");

            printf("%d위\t", i + 1);

            if (pointer_data_base[i]->personal_information_hidden == false)
                printf("%s\t", pointer_data_base[i]->Name);               //숨김처리를 안한 데이터
            else
                printf("****\t");                           //숨김처리를 한 데이터

            printf("%d\t", pointer_data_base[i]->Game1_Score);
            printf("%d\t", pointer_data_base[i]->Game2_Score);
            printf("%d\t", pointer_data_base[i]->Game3_Score);
            printf("%d\n", pointer_data_base[i]->Game1_Score + pointer_data_base[i]->Game2_Score + pointer_data_base[i]->Game3_Score);

            break;
        }
        if (check == SCALE_OF_SAVE_DATA)   printf("\n검색된 결과가 없습니다. \n");
    }
}

void Show_total_ranking_list()
{
    system("cls");
    printf("\n랭킹\t이름\t게임1\t게임2\t게임3\t합계\n");

    for (int i = 0; i < SCALE_OF_SAVE_DATA; i++)
    {
        if (strcmp(pointer_data_base[i]->Name, "") != 0)
        {
            printf("%d위\t", i + 1);
            if (pointer_data_base[i]->personal_information_hidden == false)
                printf("%s\t", pointer_data_base[i]->Name);
            else
                printf("****\t");

            printf("%d\t", pointer_data_base[i]->Game1_Score);
            printf("%d\t", pointer_data_base[i]->Game2_Score);
            printf("%d\t", pointer_data_base[i]->Game3_Score);
            printf("%d\n", pointer_data_base[i]->Game1_Score + pointer_data_base[i]->Game2_Score + pointer_data_base[i]->Game3_Score);

        }
    }
}

void individual_ranking_Home()
{
    char input;
    int index = 0;

    while (true)
    {
        system("cls");

        while (true)
        {
            printf("\n ** 개별 랭킹 조회 메뉴 **\n\n");
            printf(" 1. Game1 랭킹 조회\n");
            printf(" 2. Game2 랭킹 조회\n");
            printf(" 3. Game3 랭킹 조회\n");
            printf("\n   이전 메뉴로 가기 : `\n\n");
            printf("랭킹 조회할 게임을 선택하세요. >> ");

            scanf(" %c", &input);

            system("cls");
            if (input != '1' && input != '2' && input != '3' && input != '`')
                printf("\n 잘못된 접근 입니다.\n");
            else
                break;
        }

        if (input == '`')   break;

        index = input - '1' + 1;

        individual_ranking_check(index);
    }
}

void individual_ranking_check(int index)
{
    char search_name[LENGTH_OF_STRING] = { 0 };

    //구조체 포인터 배열을 상황에 맞게 재 정렬
    switch (index)
    {
    case 1:
        for (int i = SCALE_OF_SAVE_DATA - 1; i > 0; i--)
        {
            for (int j = 0; j < i; j++)
            {
                if (pointer_data_base[j]->Game1_Score < pointer_data_base[j + 1]->Game1_Score)
                {
                    Player* temp = pointer_data_base[j];
                    pointer_data_base[j] = pointer_data_base[j + 1];
                    pointer_data_base[j + 1] = temp;
                }
            }
        }
        break;

    case 2:
        for (int i = SCALE_OF_SAVE_DATA - 1; i > 0; i--)
        {
            for (int j = 0; j < i; j++)
            {
                if (pointer_data_base[j]->Game2_Score < pointer_data_base[j + 1]->Game2_Score)
                {
                    Player* temp = pointer_data_base[j];
                    pointer_data_base[j] = pointer_data_base[j + 1];
                    pointer_data_base[j + 1] = temp;
                }
            }
        }
        break;

    case 3:
        for (int i = SCALE_OF_SAVE_DATA - 1; i > 0; i--)
        {
            for (int j = 0; j < i; j++)
            {
                if (pointer_data_base[j]->Game3_Score < pointer_data_base[j + 1]->Game3_Score)
                {
                    Player* temp = pointer_data_base[j];
                    pointer_data_base[j] = pointer_data_base[j + 1];
                    pointer_data_base[j + 1] = temp;
                }
            }
        }
        break;
    }

    Show_individual_ranking_list(index);            //정렬된 구조체 포인터 배열을 이용하여 index게임의 랭킹 출력

    //검색할 유저 입력 > 해당 유저 index게임의 랭킹 출력
    while (true)
    {
        printf("\n\t이전 메뉴로 가기 : `\n");
        printf("\n검색할 유저의 이름을 입력하세요. >> ");
        scanf("%s", &search_name);

        if (strcmp(search_name, "`") == 0) break;

        int check = 0;
        
        for (int i = 0; i < SCALE_OF_SAVE_DATA; i++)
        {
            if (strcmp(search_name, pointer_data_base[i]->Name) != 0)
            {
                check++;
                continue;
            }

            system("cls");
            printf("\n검색된 결과는 다음과 같습니다.\n");
            printf("\n랭킹\t이름\t게임%d\n", index);

            printf("%d위\t", i + 1);

            if (pointer_data_base[i]->personal_information_hidden == false)
                printf("%s\t", pointer_data_base[i]->Name);               //숨김처리를 안한 데이터
            else
                printf("****\t");                           //숨김처리를 한 데이터

            switch (index)
            {
            case 1:
                printf("%d\n", pointer_data_base[i]->Game1_Score);
                break;
            case 2:
                printf("%d\n", pointer_data_base[i]->Game2_Score);
                break;
            case 3:
                printf("%d\n", pointer_data_base[i]->Game3_Score);
                break;
            }

            break;
        }
        if (check == SCALE_OF_SAVE_DATA) printf("\n검색된 결과가 없습니다. \n");
    }
}

void Show_individual_ranking_list(int index)
{
    system("cls");
    printf("\n랭킹\t이름\t게임%d\n", index);

    switch (index)
    {
    case 1:
        for (int i = 0; i < SCALE_OF_SAVE_DATA; i++)
        {
            if (strcmp(pointer_data_base[i]->Name, "") != 0)
            {
                printf("%d위\t", i + 1);

                if (pointer_data_base[i]->personal_information_hidden == false)
                {
                    printf("%s\t", pointer_data_base[i]->Name);
                }
                else
                {
                    printf("****\t");
                }
                printf("%d\n", pointer_data_base[i]->Game1_Score);
            }
        }
        break;

    case 2:
        for (int i = 0; i < SCALE_OF_SAVE_DATA; i++)
        {
            if (strcmp(pointer_data_base[i]->Name, "") != 0)
            {
                printf("%d위\t", i + 1);

                if (pointer_data_base[i]->personal_information_hidden == false)
                {
                    printf("%s\t", pointer_data_base[i]->Name);
                }
                else
                {
                    printf("****\t");
                }
                printf("%d\n", pointer_data_base[i]->Game2_Score);
            }
        }
        break;

    case 3:
        for (int i = 0; i < SCALE_OF_SAVE_DATA; i++)
        {
            if (strcmp(pointer_data_base[i]->Name, "") != 0)
            {
                printf("%d위\t", i + 1);

                if (pointer_data_base[i]->personal_information_hidden == false)
                {
                    printf("%s\t", pointer_data_base[i]->Name);
                }
                else
                {
                    printf("****\t");
                }
                printf("%d\n", pointer_data_base[i]->Game3_Score);
            }
        }
        break;
    }
}

void information_enable_disable()
{
    char search_name[LENGTH_OF_STRING] = { 0 };

    while (true)
    {
        system("cls");
        printf("이름\t숨김여부\n");
        for (int i = 0; i < SCALE_OF_SAVE_DATA; i++)
        {
            if (strcmp(pointer_data_base[i]->Name, "") != 0)
            {
                if (pointer_data_base[i]->personal_information_hidden == false)
                    printf("%s\tfalse\n", pointer_data_base[i]->Name);
                else
                    printf("%s\ttrue\n", pointer_data_base[i]->Name);
            }
        }

        printf("\n\t이전 메뉴로 가기 : `\n");
        printf("\n검색할 유저의 이름을 입력하세요. >> ");
        scanf("%s", &search_name);

        if (strcmp(search_name, "`") == 0) break;

        int check = 0;
        int index = 0;

        for (index = 0; index < SCALE_OF_SAVE_DATA; index++)
        {
            if (strcmp(search_name, pointer_data_base[index]->Name) != 0)
            {
                check++;
                continue;
            }

            system("cls");
            printf("\n이름\t숨김여부\n");

            if (pointer_data_base[index]->personal_information_hidden == false)
                printf("%s\tfalse\n", pointer_data_base[index]->Name);
            else
                printf("%s\ttrue\n", pointer_data_base[index]->Name);

            break;
        }

        if (check == SCALE_OF_SAVE_DATA)   printf("\n검색된 결과가 없습니다. \n");
        else
        {
            char input = 0;

            while (true)
            {
                if (pointer_data_base[index]->personal_information_hidden == false)
                    printf("\n%s 플레이어의 개인정보 숨김기능은 비활성화 되어있습니다.\n활성화 하시겠습니까?(y/n) ", pointer_data_base[index]->Name);
                else
                    printf("\n%s 플레이어의 개인정보 숨김기능은 활성화 되어있습니다.\n비활성화 하시겠습니까?(y/n) ", pointer_data_base[index]->Name);

                scanf(" %c", &input);

                if (input == 'y')
                {
                    pointer_data_base[index]->personal_information_hidden = 1 - pointer_data_base[index]->personal_information_hidden;
                    printf("\n변경되었습니다.\n");
                    break;
                }
                else if (input == 'n')
                {
                    printf("\n변경을 취소하였습니다.\n");
                    break;
                }
                else
                    printf("\n 잘못된 접근입니다.\n");
            }
        }
        Sleep(1000);
    }
}