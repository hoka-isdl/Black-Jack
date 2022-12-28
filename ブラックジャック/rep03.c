/*1116190054 ���@�D�l*/
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


	/* ���������� */
	srand(time(NULL));

	printf("�u���b�N�W���b�N���n�߂܂�\n");
	printf("�u���b�N�W���b�N�����̏ꍇ��1.5�{���l�����܂�\n");


	for (;;)
	{
		if (chip > 0) {
			printf("���݂̃`�b�v��%.2lf�ł�\n", chip);
			printf("�����܂����H������ꍇ�̓`�b�v��u���Ă�������");
			printf("1�ȏ�(�`�b�v�̐�)...������ 0...�I���:");
			scanf("%d", &putchip);
			if (putchip <= 0)break;
			else if (putchip > chip) {
				printf("�`�b�v������܂���I");
				continue;
			}


			/* 1��̃u���b�N�W���b�N���� */
			turn();
		}
		else {
			printf("�`�b�v���Ȃ��Ȃ�܂���\n.�Q�[�����I�����܂�\n");
			break;
		}


		/* �����邩? 
		printf("\n�����܂���? y...������ n ...�I���: ");
		scanf("%s", buf);
		if (buf[0] != 'y')break;*/

	}
	printf("�`�b�v�̎c���%f�ł�.\n", chip);
	printf("�u���b�N�W���b�N���I�����܂��B");
	
	return 0;
}

/* 1��̃u���b�N�W���b�N���� */
void	turn(void)
{
	int	nyou, ncom, you[10], com[10];
	char	buf[3];
	int	sumYou, sumCom;

	/* �����J�[�h�z�z */
	nyou = 2;
	ncom = 2;
	you[0] = rand() % 13 + 1;
	com[0] = rand() % 13 + 1;
	you[1] = rand() % 13 + 1;
	com[1] = rand() % 13 + 1;
	prtCard(0, nyou, you, ncom, com);

	/* �v���C���[�̎�� */
	for (;;)
	{

		sumYou = calcSum( nyou, you);

		if (sumYou > 21)
			break;

		printf("�q�b�g�Ȃ� h �� �X�e�C�Ȃ� s ����͂��Ă��������B\n");
		scanf("%s", buf);
		if (buf[0] == 's')
			break;
		you[nyou] = rand() % 13 + 1;
		nyou++;
		prtCard(0, nyou, you, ncom, com);
	}

	if (sumYou > 21)
	{
		printf("�o�[�X�g! ���Ȃ��̕����ł�.\n");
		chip -= putchip;
		return;
	}

	/* �e�̎�� */
	 printf("\n�e�̔Ԃł�. \n"); 

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
		printf("�e���o�[�X�g! ���Ȃ��̏����ł�.\n");
		if (nyou == 2 && sumYou == 21) {
			chip += (double)putchip*1.5;
		}
		else {
			chip += putchip;
		}
		return;
	}

	/* ���� */
	judge(sumYou, sumCom, nyou, ncom);

}

/* ��̕\�� */
/* flag = 0...�e��1���ڂ̂ݗ��\�� */
void	prtCard(int flag, int nyou, int you[], int ncom, int com[])
{
	int	i;
	char	card[14] = { '*', 'A', '2', '3', '4', '5', '6',
		'7', '8', '9', '0','J', 'Q', 'K' };

	printf("���Ȃ��̎� : ");
	for (i = 0; i < nyou; i++)
		printf("%c ", card[you[i]]);


	printf("�e�̎� : ");
	for (i = 0; i < ncom; i++) {
		if (flag == 0 && i == 0)  printf("%c ", card[0]);
		else printf("%c ", card[com[i]]);
	}
	printf("\n");
}

/* �J�[�h�̍��v�|�C���g�v�Z */
/* flag = 0...1���ڂ����v�ɉ����Ȃ�. */
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




/* ���s���� */
void	judge(int sumYou, int sumCom, int nyou, int ncom)
{
	printf("���Ȃ��� %d �e�� %d ", sumYou, sumCom);

	if (sumCom > sumYou) {
		printf("\n\n���Ȃ��̕����ł�.\n");
		chip -= putchip;
	}
	else if (sumCom < sumYou) {
		if (nyou == 2 && sumYou == 21) {
			printf("�u���b�N�W���b�N ���Ȃ��̏����ł�.");
			chip += (double)putchip*1.5;
		}
		else {
			printf("\n\n���Ȃ��̏����ł�.\n");
			chip += putchip;
		}
	}
	else if (ncom == 2 && sumCom == 21) {
		printf("�u���b�N�W���b�N ���Ȃ��̕����ł�.");
		chip -= putchip;
	}
	else if (sumYou == 21 && (nyou == 2 && ncom != 2)) {
		printf("\n\n���_�ł���,�v���C���[���u���b�N�W���b�N�ł��邽��, ���Ȃ��̏����ł�.\n");
		chip += (double)putchip*1.5;
	}
	else if (sumCom == 21 && (nyou != 2 && ncom == 2)) {
		printf("\n\n���_�ł���, �R���s���[�^���u���b�N�W���b�N�ł��邽��, ���Ȃ��̕����ł�.\n");
		chip -= putchip;
	}
	else {
		printf("���������ł�.\n");
	}


}

/*�u���b�N�W���b�N���n�߂܂�
�u���b�N�W���b�N�����̏ꍇ��1.5�{���l�����܂�
���݂̃`�b�v��100.00�ł�
�����܂����H������ꍇ�̓`�b�v��u���Ă�������1�ȏ�(�`�b�v�̐�)...������ 0...�I���:50
���Ȃ��̎� : K J �e�̎� : * 0
�q�b�g�Ȃ� h �� �X�e�C�Ȃ� s ����͂��Ă��������B
s

�e�̔Ԃł�.
���Ȃ��̎� : K J �e�̎� : 6 0
���Ȃ��̎� : K J �e�̎� : 6 0 2
���Ȃ��� 20 �e�� 18

���Ȃ��̏����ł�.
���݂̃`�b�v��150.00�ł�
�����܂����H������ꍇ�̓`�b�v��u���Ă�������1�ȏ�(�`�b�v�̐�)...������ 0...�I���:50
���Ȃ��̎� : 6 8 �e�̎� : * 8
�q�b�g�Ȃ� h �� �X�e�C�Ȃ� s ����͂��Ă��������B
h
���Ȃ��̎� : 6 8 8 �e�̎� : * 8
�o�[�X�g! ���Ȃ��̕����ł�.
���݂̃`�b�v��100.00�ł�
�����܂����H������ꍇ�̓`�b�v��u���Ă�������1�ȏ�(�`�b�v�̐�)...������ 0...�I���:50
���Ȃ��̎� : 8 A �e�̎� : * A
�q�b�g�Ȃ� h �� �X�e�C�Ȃ� s ����͂��Ă��������B
s

�e�̔Ԃł�.
���Ȃ��̎� : 8 A �e�̎� : A A
���Ȃ��̎� : 8 A �e�̎� : A A J
�e���o�[�X�g! ���Ȃ��̏����ł�.
���݂̃`�b�v��150.00�ł�
�����܂����H������ꍇ�̓`�b�v��u���Ă�������1�ȏ�(�`�b�v�̐�)...������ 0...�I���:50
���Ȃ��̎� : Q A �e�̎� : * J
�q�b�g�Ȃ� h �� �X�e�C�Ȃ� s ����͂��Ă��������B
s

�e�̔Ԃł�.
���Ȃ��̎� : Q A �e�̎� : 5 J
���Ȃ��̎� : Q A �e�̎� : 5 J 3
���Ȃ��� 21 �e�� 18 �u���b�N�W���b�N ���Ȃ��̏����ł�.���݂̃`�b�v��225.00�ł�
�����܂����H������ꍇ�̓`�b�v��u���Ă�������1�ȏ�(�`�b�v�̐�)...������ 0...�I���:0
�`�b�v�̎c���225.000000�ł�.
�u���b�N�W���b�N���I�����܂��B*/

/*���z
�`�b�v�̊|�����̕ϐ��ł���putchip���O���[�o���֐��ɂ��邱�Ƃɂ���Č����悭�ł��܂����B
�u���b�N�W���b�N�̎��Ƀ|�C���g���P�D�T�{����Ƃ���Őe���o�[�X�g�����۔��f���ꂸ��킵��
���H�v���Ĕ��f�����悤�ɂȂ�܂����B���s����̃p�^�[�������������̂ŏ������G�ł����B*/