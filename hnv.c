#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <mm_malloc.h>
#include <math.h>
#include <locale.h>

unsigned long int comp = 0, moves = 0;
double T;
int s;
//������ �� �����
typedef struct package
{
    double a;
    unsigned long int c;
} p;

struct bin_tree {
    int data;
    struct bin_tree * right, * left;
};
typedef struct bin_tree node;

int interpolationSearch(int a, int n, p *pack) {

    int lo = 0, hi = (n - 1);

    while (lo <= hi && a >= pack[lo].c && a <= pack[hi].c)
    {

        int pos = lo + (((double)(hi-lo) /
                         (pack[hi].c-pack[lo].c))*(a - pack[lo].c));

        if (pack[pos].c == a) {
            comp++;
            return pos;
        }

        if (pack[pos].c < a) {
            lo = pos + 1;
            comp++;
        }

        else {
            hi = pos - 1;
            comp++;
        }

        moves++;

    }
    return -1;
}

void insert(node ** tree, int val) {
    node *temp = NULL;
    if(!(*tree))
    {
        temp = (node *)malloc(sizeof(node));
        temp->left = temp->right = NULL;
        temp->data = val;
        *tree = temp;
        comp++;
        return;
    }

    if(val <= (*tree)->data)
    {
        insert(&(*tree)->left, val);
        comp++;
        moves++;
    }
    else if(val >= (*tree)->data)
    {
        insert(&(*tree)->right, val);
        comp++;
        moves++;
    }

}

void treeIntoArray(node * tree, p *pack) {
    static int i=0;
    if (tree)
    {
        treeIntoArray(tree->left,pack);
        pack[i].c=tree->data;
        i++;
        treeIntoArray(tree->right,pack);
    }

}

void deltree(node * tree) {
    if (tree)
    {
        deltree(tree->left);
        deltree(tree->right);
        free(tree);
    }
}

node* search(node ** tree, int val) {
    if(!(*tree))
    {
        comp++;
        return NULL;
    }

    if(val < (*tree)->data)
    {
        comp++;
        moves++;
        search(&((*tree)->left), val);
    }
    else if(val > (*tree)->data)
    {
        comp++;
        moves++;
        search(&((*tree)->right), val);
    }
    else if(val == (*tree)->data)
    {
        comp++;
        return *tree;
    }

}
//����������
void sort_bubble(unsigned long int n, p *pack) {
    unsigned long int i, j, tmp;
    for (i=0; i<n-1; i++) {
        for (j=0; j<n-(1+i); j++) {
            if(pack[j].c > pack[j+1].c) {
                tmp = pack[j].c;
                pack[j].c = pack[j+1].c;
                pack[j+1].c = tmp;
                comp++;
            }
            moves++;

        }
    }
}

// ���������� ���������
void sort_insertion(unsigned long int n, p *pack) {
    unsigned int newElement;
    int location,i;
    for ( i = 1; i < n; i++) {
        newElement = pack[i].c;
        location = i - 1;
        while(location >= 0 && pack[location].c > newElement){
            pack[location+1].c = pack[location].c;
            location = location - 1;
            moves++;
            comp++;
        }
        pack[location+1].c = newElement;
        moves++;
    }
}

//������� ����������
void sort_quick(p *pack, unsigned long int low, unsigned long int high)
{
    unsigned long int l=low,r=high;
    static unsigned long int i,sred,min,max;
    p temp;
    min=l;
    max=r;
    for (i=l; i<r; ++i)
    {
        if (pack[i].c > pack[max].c) max=i;
        if (pack[i].c < pack[min].c) min=i;
    }
    sred=(pack[max].c + pack[min].c)/2;
    while (l <= r)
    {
        while (pack[l].c < sred)
        {
            ++l;
            moves++;
        }
        while (pack[r].c > sred)
        {
            --r;
            moves++;
        }
        if (l <= r)
        {
            temp=pack[l];
            pack[l]=pack[r];
            pack[r]=temp;
            --r;
            ++l;
            comp++;
        }
        moves++;
    }
    if (low < r){
        sort_quick(pack, low, r);
        comp++;

    }
    if (high > l) {
        sort_quick(pack, l, high);
        comp++;
    }
}



//�����
int linearSearch (unsigned int a, int n, p *pack) {
    int i ;
    unsigned int lol;
    for (i=0; i<n; i++) {
        lol = pack[i].c;
        if (a==lol) {
            comp++;
            return i;
        }
        moves++;
    }
    return -1;
}

int main(int argc,char *argv[])
{
    setlocale(LC_ALL,"RUS");
    node *root = NULL, *min;

    unsigned long int * massive;
    unsigned int key;
    long int k,i;
    double Tstart,Tend;
    int inputinput,inputsortway,inputsearchway, value,see;
    printf("������� ������ �������: ");
    scanf("%i", &s);
    p *pack;
    pack=(struct package*)malloc(s*sizeof(struct package));

    printf("�������� ������ �����:\n 1) ���� ������� � ���������� \n 2) �� �����\n 3) ���������� ������� ���������� �������\n");
    scanf("%d",&inputinput);
    switch (inputinput){
        case 1:{
            printf("��� ������ ���� �������\n");
            massive = (unsigned long int *)malloc(s * sizeof(unsigned long int));
            printf("������� �������� �������:\n");
            for ( i = 0; i < s; i++) {
                scanf("%lu", &massive[i]);
                pack[i].c = massive[i];
                pack[i].a = 1.1;
            }
            break;
        }
        case 2:{
printf("������� ���� �� �����\n ");
massive = (unsigned long int *)malloc(s * sizeof(unsigned long int));
for ( i = 0; i < s; i++) {
massive[i]=0;
pack[i].c = massive[i];
pack[i].a = 1.1;
}
FILE *otcr;

char rz [255];
int b=0;
if(!(otcr=fopen(argv[1],"rb")) || (argc==1)) {
printf("������� ��� �����\n");
scanf("%s",rz);
if (!(otcr=fopen(rz,"rb"))) {
printf("�� ���� ������� ���� ����");
return 0;
}
else
printf ("������ ���� %s\n", rz);
}
else printf("������ ���� %s\n", argv[1]);
fseek(otcr,0,SEEK_SET);

char buffer[128];
char buffer1[128];
char buffer2[128];
//��������� �� ������������ ������ �����
int j;
for (i=0; i<s; i++) {
fgets(buffer, 127, otcr);
//printf("%s", buffer);
strncpy(buffer1,buffer, strcspn(buffer,","));
buffer1[strcspn(buffer,",")+1]='\0';
for (j=strcspn(buffer,",")+1;j<=strlen(buffer);j++)
buffer2[j-strcspn(buffer,",")-1]=buffer[j];
buffer2[strlen(buffer)-strcspn(buffer,",")+1]='\0';
pack[i].a=atof(buffer1);
pack[i].c=atoi(buffer2);
}



//for (i=0; i<s; i++) {
// fscanf(otcr,"%f%s",&pack[i].a);
// fscanf(otcr,"%lu\n",&pack[i].c);
//}
//for (i=0; i<s; i++) {
//fread(&pack[i].a,1,sizeof(double),otcr);
//fread(&pack[i].c,1,sizeof(unsigned long int),otcr);
//}
//fread(pack,sizeof(p),s,otcr);


fclose (otcr);
printf ( "������ ������ �������� ������?:\n 1 ��\n 2 ���\n");
scanf("%d",&see);
switch (see){

case 1: {printf("�������� ������:\n");
for ( i = 0; i < s; i++){
printf("%lu\n", pack[i].c);
}
break; }

case 2: break;
}
break;
}
        case 3:{
            printf("���� ������� ��������� ������� ���������� �������\n");
            massive = (unsigned long int *)malloc(s * sizeof(unsigned long int));
            for ( i = 0; i < s; i++) {
                massive[i]=rand()%10000;
                pack[i].c = massive[i];
                pack[i].a = 1.1;
            }
            printf ( "������� �� �� ������ �������� ������?:\n 1) ��\n 2) ���\n");
            scanf("%d",&see);
            switch (see){

            case 1: {printf("�������� ������:\n");
            for ( i = 0; i < s; i++)
            printf("%lu\n", pack[i].c);
            break; }

            case 2: break;
            }
            break;
            }

        default:{
            printf ("������ �����\n");
            return (0);
            break;
        }
    }

    printf("�������� ������ ����������\n 1) ���������� ���������\n 2) ������� ����������\n 3) ���������� �������� �������\n 4) ���������� ������� �������� ������\n ");
    scanf("%d",&inputsortway);

    switch (inputsortway){

        case 1:{
            Tstart = clock();
            sort_insertion (s, pack);
            Tend=clock();
            T=(Tend-Tstart)/(double)CLOCKS_PER_SEC;
            printf("\n����� ����������� �� ���������� �������:  %lf ���\n",T);
            printf("\n���������� ����������� �� �������: [%lu]", moves);
            printf("\n���������� ��������� [%lu]\n", comp);
            moves=0;
            comp=0;
            T = 0;
            break;
        }
        case 2:{
            Tstart = clock();
            sort_quick(pack, 0, s-1);
            Tend=clock();
            T=(Tend-Tstart)/(double)CLOCKS_PER_SEC;
            printf("\n����� ����������� �� ���������� �������:  %lf ���\n",T);
            printf("\n���������� ����������� �� �������: [%lu]", moves);
            printf("\n���������� ��������� [%lu]\n", comp);
            moves=0;
            comp=0;
            T = 0;
            break;
        }
        case 3:{

            Tstart = clock();
            //����������� ������
            for(k=0; k<s; k++) {
                value = pack[k].c;
                insert(&root, value);
            }
            Tend=clock();
            //���� ������� �� ������
            treeIntoArray(root,pack);
            T=(Tend-Tstart)/(double)CLOCKS_PER_SEC;
            printf("\n����� ����������� �� ���������� �������:  %lf ���\n",T);
            printf("\n���������� ����������� �� �������: [%lu]", moves);
            printf("\n���������� ��������� [%lu]", comp);
            moves=0;
            comp=0;
            T = 0;
            printf("\n������� ������� ��� ������ � ������: ");
            scanf("%d", &key);
            Tstart = clock();
            min = search(&root, key);
            Tend=clock();
            T=(Tend-Tstart)/(double)CLOCKS_PER_SEC;
            if (min) {
                printf("�������� %d �������\n", min->data);
                printf("\n����� ����������� �� ����� �� ������:  %lf ���\n",T);
                printf("\n���������� ����������� �� ������: [%lu]", moves);
                printf("\n���������� ��������� [%lu]\n", comp);
                moves=0;
                comp=0;
                T = 0;
            } else {
                printf("�������� �� �������.\n");
                moves=0;
                comp=0;
                T = 0;
            }

            break;

        }
        case 4:{
            Tstart = clock();
            sort_bubble(s, pack);
            Tend=clock();
            T=(Tend-Tstart)/(double)CLOCKS_PER_SEC;
            printf("\n����� ����������� �� ���������� �������:  %lf ���",T);
            printf("\n���������� ����������� �� �������: [%lu]", moves);
            printf("\n���������� ��������� [%lu]\n", comp);
            moves=0;
            comp=0;
            T = 0;
            break;
        }
        default:{
            printf("������ �����\n");

            break;

        }

    }
    printf ( "������� �� �� ������� ��������������� ������?:\n 1) ��\n 2) ���\n");
    scanf("%d",&see);
   switch (see){

    case 1: {printf("��������������� ������:\n");
    for ( i = 0; i < s; i++)
            printf("%lu\n", pack[i].c);
      break; }

case 2: break;
}

       printf("������� �������� ��� ������:\n");
        scanf("%d",&key);
        printf("�������� ������:\n 1) �������� �����\n 2) ���������������� �����\n ");
        scanf("%d",&inputsearchway);
        switch(inputsearchway){
            case 1:
            {
                Tstart = clock();
                k = linearSearch(key, s, pack);
                Tend=clock();
                T=(Tend-Tstart)/(double)CLOCKS_PER_SEC;
                if (k != -1) {
                    printf("������ �������� �������� %ld\n", k);
                    printf("\n����� ����������� �� �����:  %lf ���\n",T);
                    printf("\n���������� ����������� �� �������: [%lu]", moves);
                    printf("\n���������� ��������� [%lu]", comp);
                    moves=0;
                    comp=0;
                    T = 0;
                }
                else
                {
                    printf("������� �� ������!\n");
                    moves=0;
                    comp=0;
                    T = 0;
                }
                break;
            }
            case 2:
            {
                Tstart = clock();
                value = interpolationSearch(key,s,pack);
                Tend=clock();
                T=(Tend-Tstart)/(double)CLOCKS_PER_SEC;
                if (value != -1) {
                    printf("������ �������� �������� %ld\n", value);
                    printf("����� ����������� �� �����:  %lf ���\n",T);
                    printf("���������� ����������� �� �������: [%lu]\n", moves);
                    printf("���������� ��������� [%lu]", comp);
                    moves=0;
                    comp=0;
                    T = 0;
                }
                else
                    printf("������� �� ������.");
                    break;
            }
            default:{
                printf("������ �����\n");
                return 0;
                break;
            }
        }
    return 0;
}
