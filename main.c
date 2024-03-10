#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

//provera za kucicu
//obrada kad se bira nova figura ili postojeca da odigra(nesto zajebava izbaci novu u svakom slucaju)
//slucaj kad je figurica pojedena
//ns talonu kucicu oznaci posebnim slovima, moze tako provera, tj. polje gde krece kucica, a ovo ostalo recimo -
//ovako kao gore da vrsimo proveru
//da se istestira jos funkcija za pomeranje


typedef struct listNode {
    int info;
    struct listNode *prev;
    struct listNode *next;
} ListNode;

typedef struct listHeader {
    struct listNode *head;
    struct listNode *tail;
    int numElem;
} ListHeader;

struct listHeader* createHeader(int player) {
    struct listHeader *newNode = (struct listHeader*)malloc(sizeof(struct listHeader));
    int firstInfo;
    if (player == 1){
        firstInfo = 14;
    }
    else if (player == 2){
        firstInfo = 24;
    }
    else if (player == 3){
        firstInfo = 34;
    }
    else{
        firstInfo = 44;
    }
    newNode->head=NULL;
    newNode->tail=NULL;
    newNode->numElem=0;
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(-1);
    }
    struct listNode* new=(struct listNode*)malloc(sizeof(struct listNode));
    newNode->head= new;
    newNode->tail=new;
    newNode->head->info=firstInfo;
    newNode->numElem= 1;
    newNode->head->prev=NULL;
    newNode->head->next=NULL;

    return newNode;
}


struct listNode* addNodeToFront(int player, ListHeader* info) {
    struct listNode *newNode = (struct listNode*)malloc(sizeof(struct listNode));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(-1);
    }

    newNode->info = player;
    newNode->next = info->head;

    if (info->head == NULL) {
        newNode->prev = NULL;
        info->head = newNode;
        info->tail = newNode;
    } else {
        newNode->prev = NULL;
        info->head->prev = newNode;
        info->head = newNode;
    }

    info->numElem++;
    return newNode;
}

int PopLastNode(ListHeader* info) {
    struct listNode* lastNode = info->tail;
    int nodeVal = lastNode->info;

    if (lastNode->prev == NULL) {
        free(lastNode);
        info->head = NULL;
        info->tail = NULL;
    } else {
        info->tail = lastNode->prev;
        info->tail->next = NULL;
        free(lastNode);
    }

    info->numElem--;

    return nodeVal;
}

struct listNode* addNodeToBack(int player, ListHeader* info) {
    struct listNode *newNode = (struct listNode*)malloc(sizeof(struct listNode));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(-1);
    }

    newNode->info = player;
    newNode->next = NULL;

    if (info->head == NULL) {
        newNode->prev = NULL;
        info->head = newNode;
        info->tail = newNode;
    } else {
        newNode->prev = info->tail;
        info->tail->next = newNode;
        info->tail = newNode;
    }
    info->numElem++;
    return newNode;
}

void printList(ListHeader* info) {
    struct listNode* current = info->head;
    while (current != NULL) {
        printf("%d -> ", current->info);
        current = current->next;
    }
    printf("NULL\n");
}

int getCurNumOfElements(ListHeader* info) {
    return info->numElem;
}

unsigned int generisi_seed() {
    unsigned int seed = (unsigned int)time(NULL);
    return seed;
}

int LCGgenerator(unsigned int x, int a, int c,unsigned int m) {
    x = (a * x + c) % m;
    return x;
}

int bacanjeKockice() {
    return LCGgenerator(generisi_seed(), 1103515245, 12345, 2147483648) % 6 + 1;
}

void kreirajTalon(int m, int n,int talon[m][n]) {
    for (int i=0; i < m; i++){
        for (int j=0; j < n; j++){
            talon[i][j] = 0;
        }
    }
}

void ispisiTalon(int m, int n, int talon[m][n]) {
    for (int i = 0; i < m; i++) {
        printf("\n");
        for (int j = 0; j < n; j++) {
            printf("%d ", talon[i][j]);
        }
    }
    printf("\n");
}

void kreirajCSC(int n, int cscTalon[n][3]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 3; j++) {
            cscTalon[i][j] = 0;
        }
    }
}

void updateCSC(int m, int n, int talon[m][n], int cscTalon[n][3]) {
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < m; i++) {
            if (talon[i][j] != 0) {
                cscTalon[j][0] += 1;
                cscTalon[j][1] = i;
                cscTalon[j][2] = talon[i][j];
            }
        }
    }
}

void ispisiCSC(int n, int cscTalon[n][3]) {
    for (int i = 0; i < n; i++) {
        printf("\n");
        for (int j = 0; j < 3; j++) {
            printf("%d ", cscTalon[i][j]);
        }
    }
    printf("\n");
}

ListHeader *inicijalizujIgraca(int Player){
    ListHeader* head = createHeader(Player);

    if (Player == 1){
        addNodeToBack(13, head);
        addNodeToBack(12, head);
        addNodeToBack(11, head);
    }
    else if (Player == 2){
        addNodeToBack(23, head);
        addNodeToBack(22, head);
        addNodeToBack(21, head);
    }
    else if (Player == 3){
        addNodeToBack(33, head);
        addNodeToBack(32, head);
        addNodeToBack(31, head);
    }
    else if (Player == 4){
        addNodeToBack(43, head);
        addNodeToBack(42, head);
        addNodeToBack(41, head);
    }

    return head;

}

void dodajFiguruNaStart (int m, int n, int curIgrac, int talon[m][n], struct listHeader* head){
    int Figura = PopLastNode(head);
    if (curIgrac == 1){
        talon[m-1][0] = Figura;
    }
    else if (curIgrac == 2){
        talon[0][0] = Figura;
    }
    else if (curIgrac == 3){
        talon[0][n-1] = Figura;
    }
    else if (curIgrac == 4){
        talon[m-1][n-1] = Figura;
    }
}

void pomeriFiguricu(int m, int n, int curposI, int curposJ, int pomeraj, int talon[m][n], int Figura){

    //izbrisi staru poziciju figure na talonu
    talon[curposI][curposJ] = 0;

    //prvi red
    if(curposI==0 && curposJ+pomeraj<n-1){
        talon[curposI][curposJ+pomeraj]=Figura;
    }

        //poslednja kolona
    else if (curposJ==n-1 && curposI+pomeraj+1<m){
        talon[curposI+pomeraj][curposJ]=Figura;
    }

        //poslednji red
    else if (curposI==m-1 && curposJ-pomeraj>=0){
        talon[curposI][curposJ-pomeraj]=Figura;
    }

        //prva kolona
    else if (curposJ==0 && curposI-pomeraj>=0){
        talon[curposI-pomeraj][curposJ]=Figura;
    }

        //iz prvog reda u poslednju kolonu
    else if(curposI==0 && curposJ+pomeraj>n-1){
        int ostatak=pomeraj - (n-1-curposJ);
        talon[ostatak][n-1] = Figura;
    }
        //iz poslednje kolone u poslednji red
    else if(curposJ==n-1 && curposI+pomeraj>m-1){
        int ostatak=pomeraj - (m-1-curposI);
        talon[m-1][n-ostatak] = Figura;
    }


        //iz poslednjeg reda u prvu kolonu
    else if(curposI==m-1 && curposJ-pomeraj<0){
        int ostatak=pomeraj - (m-1-curposI);
        talon[m-1-ostatak][0] = Figura;
    }

        //iz prve kolone u prvi red
    else if(curposJ==0 && curposJ-pomeraj<0){
        int ostatak=pomeraj - (n-1-curposJ);
        talon[0][ostatak] = Figura;
    }



}

void nadjiDostupneFigure (int m, int n, int curIgrac, int talon[m][n]){
    int dostupneFigure[4];
    int counter = 0;

    for (int i = 0; i < m; i++){
        for (int j = 0;j < n; j++){
            if (talon[i][j] / 10 == curIgrac){
                dostupneFigure[counter] = talon[i][j];
                counter++;
            }
        }
    }

    printf("Dostupne figure su: \n");
    for (int i = 0; i < counter; i++){
        printf("%d ", dostupneFigure[i]);
    }
    printf("\n");
}

int nadjiFiguricuI (int m, int n, int talon[m][n], int Figura){
    int resi;
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            if (talon[i][j] == Figura){
                resi=i;
            }
        }
    }
    return resi;
}

int nadjiFiguricuJ (int m, int n, int talon[m][n], int Figura){
    int resj;
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            if (talon[i][j] == Figura){
                resj= j;
            }
        }
    }
    return resj;
}

void PotezPomeranje(int curIgrac, int m, int n, int talon[m][n], int curKockica){
    int Figura;
    int curposI;
    int curposJ;

    ispisiTalon(m,n,talon);

    nadjiDostupneFigure(m,n, curIgrac, talon);
    printf("Unesi trazenu figuru: \n");
    scanf("%d", &Figura);

    curposI = nadjiFiguricuI(m, n, talon, Figura);
    curposJ = nadjiFiguricuJ(m, n, talon, Figura);

    pomeriFiguricu(m, n, curposI, curposJ, curKockica, talon, Figura);


}

void Potez(int curIgrac, struct listHeader* head, int m, int n, int talon[m][n]){
    char potezOpcija;
    int brojFigura = getCurNumOfElements(head);
    int curKockica = bacanjeKockice();
    printf("Trenutni igrac: %d \n", curIgrac);
    printf("Bacanje kockice: %d.\n", curKockica);

    if (brojFigura == 4) {
        int brojPokusaja = 0;

        curKockica = bacanjeKockice();
        while(brojPokusaja<3) {
            if (curKockica == 6){
                dodajFiguruNaStart(m, n, curIgrac, talon, head);
                break;
            }
            else {
                if (brojPokusaja == 2){
                    printf("Nije dobijen broj 6\n");
                    break;
                }
                else{
                    printf("Nije dobijen broj 6. Ponovno bacanje\n");
                }

                sleep(1);
                curKockica = bacanjeKockice();
                printf("Bacanje kockice: %d\n", curKockica);
                brojPokusaja++;
            }
        }
    }

    else if (brojFigura < 4){
        curKockica = bacanjeKockice();
        if (curKockica == 6){
            printf("Da li zelite da dodate novu figuru ili pomerite figuru?\n");
            printf("a. Dodaj novu figuru \nb. Pomeri postojecu figuru\n");
            scanf(" %c", &potezOpcija);
            switch(potezOpcija) {
                case 'a':
                    dodajFiguruNaStart(m, n, curIgrac, talon, head);
                    break;
                case 'b':
                    PotezPomeranje(curIgrac, m, n, talon, curKockica);
                    break;
                default:
                    printf("Nepoznata opcija, unesi ponovo\n");
            }
        }
        else{
            PotezPomeranje(curIgrac, m, n, talon, curKockica);
        }
    }


}

//test


int main() {
    ListHeader *head1=NULL;
    ListHeader *head2, *head3, *head4;
    char opcija;
    int m, n;
    int talon[100][100];
    int cscTalon[100][3];
    int curIgrac = 1;
    inicijalizujIgraca(1);
    inicijalizujIgraca(2);
    inicijalizujIgraca(3);
    inicijalizujIgraca(4);
    int test;
    printf("Ne ljuti se covece!\n\n");
    do {
        printf("Meni: \n");
        printf("a - Kreiraj prazan talon\n");
        printf("b - Ispis talona\n");
        printf("c - Odigraj potez\n");
        printf("d - Ispisi CSC\n");
        printf("e - Izlaz\n");
        scanf(" %c", &opcija);

        switch (opcija) {
            case 'a':
                printf("Unesite dimenzije talona:\n");
                scanf("%d%d", &m, &n);
                kreirajTalon(m, n, talon);
                kreirajCSC(n, cscTalon);
                head1=inicijalizujIgraca(1);
                head2=inicijalizujIgraca(2);
                head3=inicijalizujIgraca(3);
                head4=inicijalizujIgraca(4);
                break;
            case 'b':
                printf("Ispis talona:\n");
                ispisiTalon(m, n, talon);
                break;
            case 'c':

                if (curIgrac == 1){
                    Potez(curIgrac, head1, m, n, talon);
                    curIgrac = 2;
                    printList(head1);
                }
                else if (curIgrac == 2){
                    Potez(curIgrac, head2, m, n, talon);
                    curIgrac = 3;
                    printList(head2);
                }
                else if (curIgrac == 3){
                    Potez(curIgrac, head3, m, n, talon);
                    curIgrac = 4;
                    printList(head3);
                }
                else if (curIgrac == 4){
                    Potez(curIgrac, head4, m, n, talon);
                    curIgrac = 1;
                    printList(head4);
                }
                break;
            case 'd':
                updateCSC(m, n, talon, cscTalon);
                ispisiCSC(n, cscTalon);
            case 'e':
                printf("Izlaz\n");
                break;
            default:
                printf("Nepoznata opcija\n");
        }
    } while (opcija != 'e');

    return 0;
}
