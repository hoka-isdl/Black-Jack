/*1116190054 岡　颯人*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void    turn(void);
void	prtCard(int flag, int nyou, int you[], int ncom, int com[]);
int		calcSum(int n, int p[]);
void	judge(int sumYou, int sumCom, int nyou, int ncom);

double chip = 100.0;
int putchip = 0;


int main(void)
{
	/*char	buf[3];*/


	/* 乱数初期化 */
	srand(time(NULL));

	printf("ブラックジャックを始めます\n");
	printf("ブラックジャック勝ちの場合は1.5倍を獲得します\n");


	for (;;)
	{
		if (chip > 0) {
			printf("現在のチップは%.2lfです\n", chip);
			printf("続けますか？続ける場合はチップを置いてください");
			printf("1以上(チップの数)...続ける 0...終わる:");
			scanf("%d", &putchip);
			if (putchip <= 0)break;
			else if (putchip > chip) {
				printf("チップが足りません！");
				continue;
			}


			/* 1回のブラックジャック勝負 */
			turn();
		}
		else {
			printf("チップがなくなりました\n.ゲームを終了します\n");
			break;
		}


		/* 続けるか? 
		printf("\n続けますか? y...続ける n ...終わる: ");
		scanf("%s", buf);
		if (buf[0] != 'y')break;*/

	}
	printf("チップの残りは%fです.\n", chip);
	printf("ブラックジャックを終了します。");
	
	return 0;
}

/* 1回のブラックジャック勝負 */
void	turn(void)
{
	int	nyou, ncom, you[10], com[10];
	char	buf[3];
	int	sumYou, sumCom;

	/* 初期カード配布 */
	nyou = 2;
	ncom = 2;
	you[0] = rand() % 13 + 1;
	com[0] = rand() % 13 + 1;
	you[1] = rand() % 13 + 1;
	com[1] = rand() % 13 + 1;
	prtCard(0, nyou, you, ncom, com);

	/* プレイヤーの手番 */
	for (;;)
	{

		sumYou = calcSum( nyou, you);

		if (sumYou > 21)
			break;

		printf("ヒットなら h を ステイなら s を入力してください。\n");
		scanf("%s", buf);
		if (buf[0] == 's')
			break;
		you[nyou] = rand() % 13 + 1;
		nyou++;
		prtCard(0, nyou, you, ncom, com);
	}

	if (sumYou > 21)
	{
		printf("バースト! あなたの負けです.\n");
		chip -= putchip;
		return;
	}

	/* 親の手番 */
	 printf("\n親の番です. \n"); 

	for(;;)
	{

		prtCard(1, nyou, you, ncom, com);

		sumCom = calcSum( ncom, com);
		if (17 <= sumCom)
			break;
		com[ncom] = rand() % 13 + 1;
		ncom++;
	}

	if (sumCom > 21)
	{
		printf("親がバースト! あなたの勝ちです.\n");
		if (nyou == 2 && sumYou == 21) {
			chip += (double)putchip*1.5;
		}
		else {
			chip += putchip;
		}
		return;
	}

	/* 勝負 */
	judge(sumYou, sumCom, nyou, ncom);

}

/* 手の表示 */
/* flag = 0...親の1枚目のみ裏表示 */
void	prtCard(int flag, int nyou, int you[], int ncom, int com[])
{
	int	i;
	char	card[14] = { '*', 'A', '2', '3', '4', '5', '6',
		'7', '8', '9', '0','J', 'Q', 'K' };

	printf("あなたの手 : ");
	for (i = 0; i < nyou; i++)
		printf("%c ", card[you[i]]);


	printf("親の手 : ");
	for (i = 0; i < ncom; i++) {
		if (flag == 0 && i == 0)  printf("%c ", card[0]);
		else printf("%c ", card[com[i]]);
	}
	printf("\n");
}

/* カードの合計ポイント計算 */
/* flag = 0...1枚目を合計に加えない. */
int	calcSum( int n, int p[])
{
	int	i, sum = 0,A;

	for (i = 0; i < n; i++) {
		if (p[i] >= 10) {
			sum += 10;
		}
		else if (p[i] == 1&& sum <= 10) {
			sum += 11;
		}
		else {
			sum += p[i];
		}
	}
		return  sum;
}


	/*for (i = 0; i < n; i++)
	{
		sum += p[i];
	}
	return sum;*/




/* 勝敗判定 */
void	judge(int sumYou, int sumCom, int nyou, int ncom)
{
	printf("あなたは %d 親は %d ", sumYou, sumCom);

	if (sumCom > sumYou) {
		printf("\n\nあなたの負けです.\n");
		chip -= putchip;
	}
	else if (sumCom < sumYou) {
		if (nyou == 2 && sumYou == 21) {
			printf("ブラックジャック あなたの勝ちです.");
			chip += (double)putchip*1.5;
		}
		else {
			printf("\n\nあなたの勝ちです.\n");
			chip += putchip;
		}
	}
	else if (ncom == 2 && sumCom == 21) {
		printf("ブラックジャック あなたの負けです.");
		chip -= putchip;
	}
	else if (sumYou == 21 && (nyou == 2 && ncom != 2)) {
		printf("\n\n同点ですが,プレイヤーがブラックジャックであるため, あなたの勝ちです.\n");
		chip += (double)putchip*1.5;
	}
	else if (sumCom == 21 && (nyou != 2 && ncom == 2)) {
		printf("\n\n同点ですが, コンピュータがブラックジャックであるため, あなたの負けです.\n");
		chip -= putchip;
	}
	else {
		printf("引き分けです.\n");
	}


}

/*ブラックジャックを始めます
ブラックジャック勝ちの場合は1.5倍を獲得します
現在のチップは100.00です
続けますか？続ける場合はチップを置いてください1以上(チップの数)...続ける 0...終わる:50
あなたの手 : K J 親の手 : * 0
ヒットなら h を ステイなら s を入力してください。
s

親の番です.
あなたの手 : K J 親の手 : 6 0
あなたの手 : K J 親の手 : 6 0 2
あなたは 20 親は 18

あなたの勝ちです.
現在のチップは150.00です
続けますか？続ける場合はチップを置いてください1以上(チップの数)...続ける 0...終わる:50
あなたの手 : 6 8 親の手 : * 8
ヒットなら h を ステイなら s を入力してください。
h
あなたの手 : 6 8 8 親の手 : * 8
バースト! あなたの負けです.
現在のチップは100.00です
続けますか？続ける場合はチップを置いてください1以上(チップの数)...続ける 0...終わる:50
あなたの手 : 8 A 親の手 : * A
ヒットなら h を ステイなら s を入力してください。
s

親の番です.
あなたの手 : 8 A 親の手 : A A
あなたの手 : 8 A 親の手 : A A J
親がバースト! あなたの勝ちです.
現在のチップは150.00です
続けますか？続ける場合はチップを置いてください1以上(チップの数)...続ける 0...終わる:50
あなたの手 : Q A 親の手 : * J
ヒットなら h を ステイなら s を入力してください。
s

親の番です.
あなたの手 : Q A 親の手 : 5 J
あなたの手 : Q A 親の手 : 5 J 3
あなたは 21 親は 18 ブラックジャック あなたの勝ちです.現在のチップは225.00です
続けますか？続ける場合はチップを置いてください1以上(チップの数)...続ける 0...終わる:0
チップの残りは225.000000です.
ブラックジャックを終了します。*/

/*感想
チップの掛け金の変数であるputchipをグローバル関数にすることによって効率よくできました。
ブラックジャックの時にポイントが１．５倍するところで親がバーストした際反映されず苦戦した
が工夫して反映されるようになりました。勝敗判定のパターンが多かったので少し複雑でした。*/