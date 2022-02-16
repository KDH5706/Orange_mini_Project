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
        printf("�޸� ������ �����մϴ�\n");
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
        printf("�޸� ������ �����մϴ�\n");
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
    //printf("�����͸� ã�� ���߽��ϴ�.\n");

    return NULL;
}
*/

void printList(List* list)
{
    Node* node = list->head->next;
    int i = 1;

    while (node != list->tail)
    {
        printf("%d ��° ����� ����ü �����Ͱ� ����Ű�� ����\n", i++);
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
    //*** ���Ḯ��Ʈ �ϼ��� �ʿ���� ***
    Player data_base[SCALE_OF_SAVE_DATA] = { 0 };

    //�����Ϳ� DB�ּ� ����  *** ���Ḯ��Ʈ �ϼ��� �ʿ���� ***
    for (int i = 0; i < SCALE_OF_SAVE_DATA; i++)   pointer_data_base[i] = &data_base[i];
    
    test_data_base_list(data_base);         //�׽�Ʈ�� ������

    /*--------���⼭���� ���Ḯ��Ʈ �׸� ����--------*/ 
    createlist(&list);

    //test_data_base_list�� ������ list(liked list)�� ����
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
            i = 0;//printf("%d\n", i);      //10(������ �������� ��)
            break;
        }
    }

    Sleep(1000);
    /*--------������� ���Ḯ��Ʈ �׸�--------*/

    int key_of_menu = 0;

    while (true)
    {
        system("cls");

        key_of_menu = Home();
        switch (key_of_menu)
        {
        case 1:         //�÷��̾� �̸� �ۼ� > ���� ���� > ���� ����
            prepare_the_game();
            break;

        case 2:         //��ŷ ��ȸ �޴�
            ranking_check();
            break;

        case 3:         //���α׷� ����
            printf("\n����ڿ� ���� ���α׷��� ����Ǿ����ϴ�.\n");
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
        printf("\n   *HOME ȭ��*\n\n");
        printf(" 1. ���� ����\n");
        printf(" 2. ��ŷ ��ȸ\n");
        printf(" 3. ���α׷� ����\n\n");
        printf("�޴� ��ȣ�� �Է��ϼ���. >> ");
        scanf(" %c", &input);

        system("cls");

        if (input == '1' || input == '2' || input == '3') {
            key_of_menu = input - '1' + 1;
            break;
        }
        else
            printf("\n �߸��� �����Դϴ�.\n");
    }

    return key_of_menu;
}

void prepare_the_game()
{
    while (true)
    {
        system("cls");

        Player current_user = { 0 };
        write_player_name(&current_user);                                         //�÷��̾� �̸��� �ۼ�

        if (strcmp(current_user.Name, "`") == 0)   break;                         //�÷��̾� �̸��� �ۼ��ϴ� �޴����� ���� �޴�(Ȩ ȭ��)�� �̵�

        redefine_user_data(&current_user);                                        //���� �����Ϳ� ���ؼ� current_user ���� ����

        if (strcmp(current_user.Name, "WritePlayerNameAgain") == 0)   continue;   //���� ������ ������ ������ ���� ������ �̸��� �ٽ� �ۼ�

        while (true)
        {
            /*���� ����*/
            char select_game = select_play_game(&current_user);            //������ �����϶�� ����

            switch (select_game)                        //�Է� ���� ���� ���� �÷����� ���� ����
            {
            case '1':                                   //Game 1 ���� - ������ ���� ���� ȭ������ �̵�
                printf("����� 1�� ������ ����˴ϴ�. \n"); Sleep(1000);
                game1(&current_user);
                load_data(current_user);
                break;

            case '2':                                   //Game 2 ���� - ������ ���� ���� ȭ������ �̵�
                printf("����� 2�� ������ ����˴ϴ�. \n"); Sleep(1000);
                game2(&current_user);
                load_data(current_user);
                break;

            case '3':                                   //Game 3 ���� - ������ ���� ���� ȭ������ �̵�
                printf("����� 3�� ������ ����˴ϴ�. \n"); Sleep(1000);
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
    printf("\n   **�÷��̾� �̸� �ۼ�**\n");
    printf("\n   ���� �޴��� ���� : `\n");
    printf("\n�÷��̾� �̸��� �Է��ϼ���. >> ");
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
            printf("%s �÷��̾��� ������ ������ �����մϴ�.\n", cu->Name);
            printf("\n�̸�\t����1\t����2\t����3\n");
            printf("%s\t%d\t%d\t%d\n", node->linked_User.Name, node->linked_User.Game1_Score, node->linked_User.Game2_Score, node->linked_User.Game3_Score);

            while (true)
            {
                printf("\n������ �ҷ����ڽ��ϱ�? : (y/n)");
                printf("\n(������ �ҷ����� ������ �ٸ� �÷��̾�� ���ֵǸ�, �̸��� �ٽ� �Է��ؾ� �մϴ�.) ");
                scanf(" %c", &input);

                if (input == 'y')
                {
                    strcpy((cu->Name), (node->linked_User.Name));
                    cu->Game1_Score = node->linked_User.Game1_Score;
                    cu->Game2_Score = node->linked_User.Game2_Score;
                    cu->Game3_Score = node->linked_User.Game3_Score;

                    printf("%s�� ������ �ҷ��ɴϴ�", cu->Name);
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
                    printf("\n�߸��� �����Դϴ�.\n");
            }
            break;
        }

        node = node->next;
    }
}
//redefine_user_data ����
/*
void redefine_user_data(Player* cu)
{
    for (int i = 0; i < SCALE_OF_SAVE_DATA; i++)
    {
        if (strcmp(cu->Name, pointer_data_base[i]->Name) == 0)
        {
            char input = 0;

            system("cls");
            printf("%s �÷��̾��� ������ ������ �����մϴ�.\n", cu->Name);
            printf("\n�̸�\t����1\t����2\t����3\n");
            printf("%s\t%d\t%d\t%d\n", pointer_data_base[i]->Name, pointer_data_base[i]->Game1_Score, pointer_data_base[i]->Game2_Score, pointer_data_base[i]->Game3_Score);

            while (true)
            {
                printf("\n������ �ҷ����ڽ��ϱ�? : (y/n)");
                printf("\n(������ �ҷ����� ������ �ٸ� �÷��̾�� ���ֵǸ�, �̸��� �ٽ� �Է��ؾ� �մϴ�.) ");
                scanf(" %c", &input);

                if (input == 'y')
                {
                    strcpy((cu->Name), (pointer_data_base[i]->Name));
                    cu->Game1_Score = pointer_data_base[i]->Game1_Score;
                    cu->Game2_Score = pointer_data_base[i]->Game2_Score;
                    cu->Game3_Score = pointer_data_base[i]->Game3_Score;

                    printf("%s�� ������ �ҷ��ɴϴ�", cu->Name);
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
                    printf("\n�߸��� �����Դϴ�.\n");
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
        printf("\n***���� ���� �޴�***\n");
        printf("(1)... Game 1 START!!\n");
        printf("(2)... Game 2 START!!\n");
        printf("(3)... Game 3 START!!\n");
        printf("(`)... ���� �޴�\n\n");
        printf("%s �÷��̾ ������ ������ �����ϼ���. >> ", cu->Name);
        scanf(" %c", &select_game);

        if (select_game == '1' || select_game == '2' || select_game == '3' || select_game == '`')
            break;
        else
        { 
            system("cls");   
            printf("\n �߸��� �����Դϴ�.\n"); 
        }
    }
    return select_game;
}
/*---------------------------------------------------*/
void game1(Player* cu)
{
    system("cls");
    char rcp[3][10] = { "����","����","��" };
    int number_game_EE = 0;

    char change_score[3], cont_game[3];
    int end_game_EE = 0;
    int score = 0, play_num = 5;

    char user = '\0';
    int game_count;

    //���ӽ���
    while (1)
    {
        game_count = 1;
        int score = 0;         //user ȹ�� sore
        //char stop_game[3];

        //���� ����
        printf(" ` (���� ���)\n");
        srand((unsigned)time(NULL));//���� �Ѹ���
        while (game_count <= play_num)
        {

            while (getchar() != '\n');

            int com = rand() % 3 + 1;

            printf("%d ��° ����\n", game_count);

            printf("����(1), ����(2), ��(3)�� �Է��ϼ��� : ");
            scanf(" %c", &user);
            if (user == '`')    break;

            //SCISSORS:1    ROCK:2    PAPER:3
            if ((user - '0' != SCISSORS) && (user - '0' != ROCK) && (user - '0' != PAPER))
            {
                printf("\n�߸��� ��ȣ�Դϴ�. �ٽ� �Է��Ͽ� �ֽñ� �ٶ��ϴ�\n");
                continue;
            }

            printf("��ǻ�� : %s\n", rcp[com - 1]);
            printf("user : %s\n", rcp[(int)(user - '1')]);

            if (((com == SCISSORS) && (user - '0' == PAPER)) || ((com == ROCK) && (user - '0' == SCISSORS)) || ((com == PAPER) && (user - '0' == ROCK)))
            {
                printf("\n~��~��~��ǻ���� ��~��~��~\n\n");
            }
            else if (com == user - '0')
            {
                printf("\n~*~*~���º� �Դϴ�.~*~*~\n\n");
            }
            else if (((com == SCISSORS) && (user - '0' == ROCK)) || ((com == ROCK) && (user - '0' == PAPER)) || ((com == PAPER) && (user - '0' == SCISSORS)))
            {
                printf("\n~��~��~����� ��~��~��~\n\n");
                score++; // ���� ����
            }

            game_count++; //���� Ƚ��
        }

        //���� ��
        //���� ���� ����

        if (user != '`')
        {
            while (1)
            {
                printf("�� %d �� �� %d �� �̰���ϴ�!\n\n", play_num, score);
                printf("�١ڡٱ��� ���� : %d �� || new score : %d ���ڡ١�\n", cu->Game1_Score, 20 * score);
                printf("\n������ �����Ͻðڽ��ϱ�?(y/n) -> ");
                scanf(" %s", &change_score);

                if (change_score[0] == 'y' && change_score[1] == '\0')
                {
                    printf("������ �����մϴ�!\n");
                    cu->Game1_Score = 20 * score;
                    printf("���� score -> %d..\n\n", cu->Game1_Score);
                    break;
                }
                else if (change_score[0] == 'n' && change_score[1] == '\0')
                {
                    printf("���� ������ ����մϴ�\n\n");
                    printf("���� score -> %d...\n\n", cu->Game1_Score);
                    break;
                }
                else
                {
                    printf("\n�߸��� �Է��Դϴ�. �ٽ� �Է��� �ֽʽÿ�.\n\n");
                }
            }
        }

        //���� ���� ��
        //���� ����

        while (1)
        {
            if (user == '`')
            {
                printf(" ������ �����մϴ� \n");
                end_game_EE = 1;
                break;
            }

            printf("������ �ٽ� �Ͻðڽ��ϱ�?(y/n) -> ");
            scanf("%s", cont_game);

            if (cont_game[0] == 'y' && cont_game[1] == '\0')
            {
                printf("������ �ٽ� �����մϴ�!\n");
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
                printf("�߸��� �Է��Դϴ�. �ٽ� �Է��� �ֽʽÿ�.\n");
            }
        }

        //����
        if (end_game_EE == 1)
        {
            printf("\n����end_gamme NO.1\n\n");
            Sleep(500);
            break;
        }
    }

    printf("�÷��̾��� ���� ���� �� Game1 ���ھ� : %d\n", cu->Game1_Score);
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
            printf("\n%s���� ���� ���ھ� : %d\n", cu->Name, 200 - score);
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
        printf("\n%s�� ���ھ�  : %d", cu->Name, 200 - score);

        char answer;

        do
        {
            printf("\n���� �ְ� ��� : %d\n", cu->Game2_Score);
            printf("���� ���� ��� : %d\n", 200 - score);
            printf("����� �����Ͻðڽ��ϱ�? Y/N\n");
            scanf(" %c", &answer);
            if (answer == 'Y')
            {
                cu->Game2_Score = 200 - score;
                break;
            }
            else if (answer == 'N')
                break;
            else
                printf("�ٽ� �Է�\n\n");

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

    printf("\n>>����Ű ����\n");
    printf("��ŷ ���� 'R'\n");
    printf("���� ���� '`'\n");

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
    printf("���� ���� �� ���� ������\n");
    printf("�÷��̾� �̸� : %s\n", cu->Name);
    printf("�÷��̾��� ���� ���� �� Game3 ���ھ� : %d\n", cu->Game3_Score);
    printf("-----------------------------\n");
    printf("User: %s���� 3������ Ȧ¦�� �����߽��ϴ�.\n", cu->Name);

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
            printf("=Ȧ¦����=\n");
            printf("Ȧ : 1\n¦ : 2\n");
            printf("----------\n");
            printf("���ڸ� �����ϼ��� ->");
            scanf(" %c", &sel);

            com = rand() % 2 + 1;

            if (com == (sel - '1' + 1))
            {
                Player_win = 1;
                score++;
                printf("�̰���ϴ�. ��� �������ּ���.\n");
            }
            else if (com != (sel - '1' + 1))
            {
                printf("�����ϴ�.\n");
                //system("pause");
            }
            else
            {
                Player_win = 1;
                printf("�Է��� �߸��ƽ��ϴ�.\n");
            }
        }
        printf("Score : %d���Դϴ�.\n", 20 * score);

        while (1)
        {
            printf("�������� : %d��\n���ο����� : %d��\n", cu->Game3_Score, 20 * score);
            printf("���� �����ϰڽ��ϱ�?(y/n)\n");
            scanf("%s", change_score);

            if (change_score[0] == 'y' && change_score[1] == '\0')
            {
                printf("������ �����մϴ�.\n");
                cu->Game3_Score = 20 * score;
                printf("���� ������ %d���Դϴ�. \n\n", cu->Game3_Score);
                break;
            }
            else if (change_score[0] == 'n' && change_score[1] == '\0')
            {
                printf("���� ������ �����մϴ�.\n");
                printf("���� ������ %d���Դϴ�. \n\n", cu->Game3_Score);
                break;
            }
        }

        while (1)
        {
            printf("������ �ٽ� �ϰڽ��ϱ�?(y/n)");
            scanf("%s", cont_game);
            printf("%s\n", cont_game);

            if (cont_game[0] == 'y' && cont_game[1] == '\0')
            {
                printf("������ �ٽ� �����մϴ�.\n");
                end_game3 = 0;
                system("cls");
                break;
            }
            else if (cont_game[0] == 'n' && cont_game[1] == '\0')
            {
                printf("\n������ �����մϴ�.\n");
                end_game3 = 1;

                break;
            }
            else
            {
                printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.\n");
            }
        }
        if (end_game3 == 1)
        {
            printf("���� ��\n\n");
            break;
        }
    }

    printf("�÷��̾��� ���� ���� �� Game3 ���ھ� : %d\n", cu->Game3_Score);
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

            printf("\n������ �����Ͱ� ���ŵǾ����ϴ�.");
            Same_name = true;
        }

        node = node->next;
    }

    if (Same_name == false)
    {
        addLast(&list, c_u);
        printf("\n�ű� �����Ͱ� ����Ǿ����ϴ�.");
    }

    Sleep(1200);
}
//load_data ����
/*
void load_data(Player* c_u)
{
    bool Same_name = false;
    //���� �̸� ã�Ƽ� ������ ����
    for (int i = 0; i < SCALE_OF_SAVE_DATA; i++)
    {
        if (strcmp(c_u->Name, pointer_data_base[i]->Name) == 0)
        {
            pointer_data_base[i]->Game1_Score = c_u->Game1_Score;
            pointer_data_base[i]->Game2_Score = c_u->Game2_Score;
            pointer_data_base[i]->Game3_Score = c_u->Game3_Score;

            Same_name = true;
            printf("\n������ �����Ͱ� ���ŵǾ����ϴ�.");
            break;
        }
    }
    //DB�� ���� �̸� -> DB�� ������ ����
    if (Same_name == false)
    {
        for (int i = 0; i < SCALE_OF_SAVE_DATA; i++)
        {
            if (strcmp(pointer_data_base[i]->Name, "") == 0)      //���� ã��
            {
                strcpy(pointer_data_base[i]->Name, c_u->Name);
                pointer_data_base[i]->Game1_Score = c_u->Game1_Score;
                pointer_data_base[i]->Game2_Score = c_u->Game2_Score;
                pointer_data_base[i]->Game3_Score = c_u->Game3_Score;

                printf("\n�ű� �����Ͱ� ����Ǿ����ϴ�.");
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
        case 1:               //���� ��ŷ ��ȸ(�� ���� ���� ��ŷ) & �̸����� ���� ���� ��ŷ �˻�
            total_ranking_check();
            break;
        case 2:               //���� �� ��ŷ ��ȸ & �̸����� ���� ��ŷ �˻�
            individual_ranking_Home();
            break;
        case 3:               //���� ���� ����/ǥ�� ���� (�̸� �Է��ؼ� ����<->ǥ�� ��ȯ)
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
        printf("\n ** ��ŷ ��ȸ �޴� **\n\n");
        printf(" 1. ���� ��ŷ ��ȸ\n");
        printf(" 2. ���� �� ��ŷ ��ȸ\n");
        printf(" 3. ���� ���� ����/ǥ�� ����\n");
        printf("\n   ���� �޴��� ���� : `\n\n");
        printf("�޴� ��ȣ�� �Է��ϼ���. >> ");

        scanf(" %c", &input);

        system("cls");

        if (input == '1' || input == '2' || input == '3' || input == '`')
            break;
        else
            printf("\n �߸��� �����Դϴ�.\n");
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
        printf("\n\t���� �޴��� ���� : `\n");
        printf("\n�˻��� ������ �̸��� �Է��ϼ���. >> ");
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
            printf("\n�˻��� ����� ������ �����ϴ�.\n");
            printf("\n��ŷ\t�̸�\t����1\t����2\t����3\t�հ�\n");

            printf("%d��\t", i + 1);

            if (pointer_data_base[i]->personal_information_hidden == false)
                printf("%s\t", pointer_data_base[i]->Name);               //����ó���� ���� ������
            else
                printf("****\t");                           //����ó���� �� ������

            printf("%d\t", pointer_data_base[i]->Game1_Score);
            printf("%d\t", pointer_data_base[i]->Game2_Score);
            printf("%d\t", pointer_data_base[i]->Game3_Score);
            printf("%d\n", pointer_data_base[i]->Game1_Score + pointer_data_base[i]->Game2_Score + pointer_data_base[i]->Game3_Score);

            break;
        }
        if (check == SCALE_OF_SAVE_DATA)   printf("\n�˻��� ����� �����ϴ�. \n");
    }
}

void Show_total_ranking_list()
{
    system("cls");
    printf("\n��ŷ\t�̸�\t����1\t����2\t����3\t�հ�\n");

    for (int i = 0; i < SCALE_OF_SAVE_DATA; i++)
    {
        if (strcmp(pointer_data_base[i]->Name, "") != 0)
        {
            printf("%d��\t", i + 1);
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
            printf("\n ** ���� ��ŷ ��ȸ �޴� **\n\n");
            printf(" 1. Game1 ��ŷ ��ȸ\n");
            printf(" 2. Game2 ��ŷ ��ȸ\n");
            printf(" 3. Game3 ��ŷ ��ȸ\n");
            printf("\n   ���� �޴��� ���� : `\n\n");
            printf("��ŷ ��ȸ�� ������ �����ϼ���. >> ");

            scanf(" %c", &input);

            system("cls");
            if (input != '1' && input != '2' && input != '3' && input != '`')
                printf("\n �߸��� ���� �Դϴ�.\n");
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

    //����ü ������ �迭�� ��Ȳ�� �°� �� ����
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

    Show_individual_ranking_list(index);            //���ĵ� ����ü ������ �迭�� �̿��Ͽ� index������ ��ŷ ���

    //�˻��� ���� �Է� > �ش� ���� index������ ��ŷ ���
    while (true)
    {
        printf("\n\t���� �޴��� ���� : `\n");
        printf("\n�˻��� ������ �̸��� �Է��ϼ���. >> ");
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
            printf("\n�˻��� ����� ������ �����ϴ�.\n");
            printf("\n��ŷ\t�̸�\t����%d\n", index);

            printf("%d��\t", i + 1);

            if (pointer_data_base[i]->personal_information_hidden == false)
                printf("%s\t", pointer_data_base[i]->Name);               //����ó���� ���� ������
            else
                printf("****\t");                           //����ó���� �� ������

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
        if (check == SCALE_OF_SAVE_DATA) printf("\n�˻��� ����� �����ϴ�. \n");
    }
}

void Show_individual_ranking_list(int index)
{
    system("cls");
    printf("\n��ŷ\t�̸�\t����%d\n", index);

    switch (index)
    {
    case 1:
        for (int i = 0; i < SCALE_OF_SAVE_DATA; i++)
        {
            if (strcmp(pointer_data_base[i]->Name, "") != 0)
            {
                printf("%d��\t", i + 1);

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
                printf("%d��\t", i + 1);

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
                printf("%d��\t", i + 1);

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
        printf("�̸�\t���迩��\n");
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

        printf("\n\t���� �޴��� ���� : `\n");
        printf("\n�˻��� ������ �̸��� �Է��ϼ���. >> ");
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
            printf("\n�̸�\t���迩��\n");

            if (pointer_data_base[index]->personal_information_hidden == false)
                printf("%s\tfalse\n", pointer_data_base[index]->Name);
            else
                printf("%s\ttrue\n", pointer_data_base[index]->Name);

            break;
        }

        if (check == SCALE_OF_SAVE_DATA)   printf("\n�˻��� ����� �����ϴ�. \n");
        else
        {
            char input = 0;

            while (true)
            {
                if (pointer_data_base[index]->personal_information_hidden == false)
                    printf("\n%s �÷��̾��� �������� �������� ��Ȱ��ȭ �Ǿ��ֽ��ϴ�.\nȰ��ȭ �Ͻðڽ��ϱ�?(y/n) ", pointer_data_base[index]->Name);
                else
                    printf("\n%s �÷��̾��� �������� �������� Ȱ��ȭ �Ǿ��ֽ��ϴ�.\n��Ȱ��ȭ �Ͻðڽ��ϱ�?(y/n) ", pointer_data_base[index]->Name);

                scanf(" %c", &input);

                if (input == 'y')
                {
                    pointer_data_base[index]->personal_information_hidden = 1 - pointer_data_base[index]->personal_information_hidden;
                    printf("\n����Ǿ����ϴ�.\n");
                    break;
                }
                else if (input == 'n')
                {
                    printf("\n������ ����Ͽ����ϴ�.\n");
                    break;
                }
                else
                    printf("\n �߸��� �����Դϴ�.\n");
            }
        }
        Sleep(1000);
    }
}