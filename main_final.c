#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char c;
int word_len=0;
char new_input[30];
char queen_word[30];
int queen_analize[64];
char min_iteration[64];
int min_iteration_n[64];
int min_pos=-1;
char exact_iteration[64];
int exact_iteration_n[64];
int exact_pos=-1;
char * sure, * not_in;
int not_in_total[64];
int filter_counter=0;
int vincoli=0;
int malloc_count=0;
//typedef struct nodo {
//    struct nodo * prec;
//    struct nodo * succ[64];
//} lettera;
typedef struct  node {
    //struct node * up;
    struct node * down;
    struct node * right;
    char active[10];
    char c[10];
} letter;

letter * head = NULL, * malloc_pointer=NULL;

int nuova_partita();
void initialize(letter * node, int n);
int insert_tree(); //USA UPPER (FATTO)
//int activator(letter * current, int i, int active_temp, int onoff);
int find_tree();
int stampa_filtrate(); //USA UPPER (FATTO)
int check_word();
//int clear_new_input();
void analize_queen();
/*int tree_no_char(char c);
int tree_yes_char_specific(int k, char ch);
//int tree_no_char_specific_all();
int tree_no_char_specific(int k, char ch);
int tree_min_char(int n);
int tree_exact_char(int n);*/
int down_counter(letter * mark, int start_lvl, int k_pos);//USA UPPER (FATTO?)
int clear_all();//USA UPPER (FATTO?)
int tree_polish();//USA UPPER (FATTO?)
//int tree_polish_check(letter * current, int k, int i, int position);

int stampa_albero();//USA UPPER (FATTO?)

int main() {
    int j=0, d=0, i=0;
    //if(freopen("output_toto_4.txt", "w", stdout)){}
    j=0;
    while((d = getchar_unlocked()) != '\n'){
      word_len = word_len*10+d-48;
      j++;
    }
    sure = malloc((word_len+1) * sizeof(char)); //inserisci dentro quelli certi
    not_in = malloc((word_len * 64 + 1) * sizeof(char)); //inserisci quelli sicuramente no per posizione (no assoluti)
    for (i = 0; i < word_len*64+1; i++) {
    	if(i<word_len){
    		sure[i]=0;
    	}
        not_in[i]=0;
    }
    //if(scanf("%s", new_input)){};
    j=0;
    while((c = getchar_unlocked()) != '\n'){
      new_input[j] = c;
      j++;
    }
    new_input[j] = '\0';
    while (new_input[0]!='+' || new_input[1]!='n') {//finchè non è uguale a +nuova_partita
        if (new_input[0]=='+' && new_input[1]=='i') { //se comando è +inserisci_inizio
            //clear_new_input();
            j = 0;
            while ((c = getchar_unlocked()) != '\n') {
                new_input[j] = c;
                j++;
            }
            new_input[j] = '\0';
            while (new_input[0]!='+' || new_input[1]!='i') { //finchè comando non è +inserisci_fine
                if(new_input[0]=='+' && new_input[1]=='s'){// se comando è +stampa_filtrate
                    stampa_filtrate();
                } else {
                    insert_tree();
                }
                //printf("Parola(+i_i): %s\n", new_input);
                j = 0;
                while ((c = getchar_unlocked()) != '\n') {
                    new_input[j] = c;
                    j++;
                }
                new_input[j] = '\0';
            }
            j = 0;
            while ((c = getchar_unlocked()) != '\n') {
                new_input[j] = c;
                j++;
            }
            new_input[j] = '\0';
        } else if(new_input[0]=='+' && new_input[1]=='s'){ //se comando è +stampa_filtrate
            stampa_filtrate();
            j = 0;
            while ((c = getchar_unlocked()) != '\n') {
                new_input[j] = c;
                j++;
            }
            new_input[j] = '\0';
        } else { // //se comando è una parola da inserire
            //printf("Parola: %s\n", new_input);
            insert_tree();
            //clear_new_input();
            j=0;
            while((c = getchar_unlocked()) != '\n'){
                new_input[j] = c;
                j++;
            }
            new_input[j] = '\0';
        }
    }
    //clear_new_input();
    nuova_partita();
    //printf("Stampa pre clear\n");
    //stampa_albero();
    //clear_all(); ERA ATTIVO
    //printf("Stampa post clear\n");
    //stampa_albero();
    while((c = getchar_unlocked()) != EOF) { //da capire quando termina totalmente il programma
        j=0;
        new_input[j] = c;
        j++;
        while((c = getchar_unlocked()) != '\n'){
          new_input[j] = c;
          j++;
        }
        new_input[j] = '\0';
        if(new_input[0]=='+' && new_input[1]=='s'){// se comando è +stampa_filtrate
            stampa_filtrate();
        } else if (new_input[0]=='+' && new_input[1]=='i'){//se comando è +inserisci_inizio
            //clear_new_input();
            j=0;
            while((c = getchar_unlocked()) != '\n'){
              new_input[j] = c;
              j++;
            }
            new_input[j] = '\0';
            while(new_input[0]!='+' || new_input[1]!='i'){//finchè comando non è +inserisci_fine
                if(new_input[0]=='+' && new_input[1]=='s'){// se comando è +stampa_filtrate
                    stampa_filtrate();
                } else {
                    insert_tree();
                }
                //clear_new_input();
                j=0;
                while((c = getchar_unlocked()) != '\n'){
                  new_input[j] = c;
                  j++;
                }
                new_input[j] = '\0';
            }
        } else if (new_input[0]=='+' && new_input[1]=='n'){ //se comando è +nuova_partita
            //clear_new_input();
            nuova_partita();//occupa una marea di tempo!
            //clear_all(); ERA ATTIVO
            vincoli = 0;
        }
        //clear_new_input();
    }

}

int nuova_partita(){
    int max_tries=0, result=0, j=0, d=0;
    //clear_new_input();
    clear_all();
    j=0;
    vincoli = 1;
    while((c = getchar_unlocked()) != '\n'){
      queen_word[j] = c;
      j++;
    }
    queen_word[j] = '\0';
    analize_queen();
    //printf("PAROLA QUEEN: %s", queen_word);
    j=0;
    while((d = getchar_unlocked()) != '\n'){
      max_tries = max_tries*10+d-48;
      j++;
    }
    for (int i = 0; i < max_tries && result == 0; i++) {
        //clear_new_input();
        j=0;
        while((c = getchar_unlocked()) != '\n'){
          new_input[j] = c;
          //printf("leggo %c", new_input[j]);
          //printf("%d(%c)", j, new_input[j]);
          j++;
        }
        new_input[j] = '\0';
        //printf("\n");
        //printf("Termino parola");
        //printf("tester %s\n", new_input);
        if(new_input[0]=='+' && new_input[1]=='s'){
            stampa_filtrate();
            i--;
        } else if (new_input[0]=='+' && new_input[1]=='i'){
            //clear_new_input();
            j=0;
            while((c = getchar_unlocked()) != '\n'){
              new_input[j] = c;
              j++;
            }
            new_input[j] = '\0';
            while(new_input[0]!='+' || new_input[1]!='i'){
                if(new_input[0]=='+' && new_input[1]=='s'){
                    stampa_filtrate();
                    i--;
                } else {
                    insert_tree();
                }
                //clear_new_input();
                j=0;
                while((c = getchar_unlocked()) != '\n'){
                  new_input[j] = c;
                  j++;
                }
                new_input[j] = '\0';
            }
            i--;
        } else {
            result = check_word();
            if (result == -1){
                result = 0;
                i--;
            }
        }
    }

    if (result == 0) {
        printf("ko\n");
    }
    vincoli=0;
    return 0;
}

void analize_queen(){
    int i=0, position=0;
    for (i = 0; i < 64; ++i)
    {
        queen_analize[i] = 0;
        //printf("%d %d %d %d\n", queen_analize[i], min_iteration[i], exact_iteration[i], not_in_total[i]);
    }
    i=0;
    while(queen_word[i]!='\0'){
        if(queen_word[i] >= 65 && queen_word[i] <= 90){ //lettere
            position = queen_word[i] - 54;
        } else if (queen_word[i] >= 97 && queen_word[i] <= 122){//lettere
            position = queen_word[i] - 59;
        } else if (queen_word[i] >= 48 && queen_word[i] <= 57){ //numeri
            position = queen_word[i] - 47;
        } else if (queen_word[i] == 45){//carattere
            position = 0;
        } else if (queen_word[i] == 95){//carattere
            position = 37;
        }
        queen_analize[position]++;
        i++;
    }
}

void initialize(letter * node, int n){
    int i;
    for (i = 0; i < n; i++) {
      node->c[i] = 0;
      node->active[i] = 1;
    }
    for(;i<10; i++){
        node->c[i] = '\0';
        node->active[i] = 1;
    }
    //node->up = NULL;
    node->down = NULL;
    node->right = NULL;
}

int insert_tree(){
    int i=0, flag=0, active_temp[word_len+1], active_global = 1, k=0, m=0, k_mem=0;
    letter * current, * transpose, * upper[word_len+2];

    for(i=0; i<word_len+1;i++){
        active_temp[i]=1;
    }
    i=0;
    if(vincoli==1) {
        int off, position=0, iteration_temp[64] = {0};
        //printf("%s\n", new_input);
        while (new_input[i] != '\0' && active_global == 1) { //scorro l'input una volta
            if (sure[i] != 0) { //segno su un temp se le lettere sicure corrispondono
                if (sure[i] != new_input[i]) {
                    //printf("active temp 0 (1) per %c\n", new_input[i]);
                    active_temp[i] = 0;
                    //fltr_cntr = 1;
                    active_global = 0;
                    break;
                }
            }
            if (new_input[i] >= 65 && new_input[i] <= 90) { //lettere
                position = new_input[i] - 54;
            } else if (new_input[i] >= 97 && new_input[i] <= 122) { //lettere
                position = new_input[i] - 59;
            } else if (new_input[i] >= 48 && new_input[i] <= 57) { //numeri
                position = new_input[i] - 47;
            } else if (new_input[i] == 45) {
                position = 0;
            } else if (new_input[i] == 95) {
                position = 37;
            }
            iteration_temp[position]++;
            if (not_in_total[position] == 1) { //segno su un temp se le lettere sicuro no corrispondono
                //printf("active temp 0 (2) per %c\n", new_input[i]);
                active_temp[i] = 0;
                //fltr_cntr = 1;
                active_global = 0;
                break;
            }
            /*off = i * 64;
            while (not_in[off] != 0 && active_global == 1) { //segno su un temp se le lettere sicuro no specifiche corrispondono
                //QUI SOPRA POTREBBE ESSERCI ERRORE, NEL CASO IN CUI CI SIA - NELL'ARRAY NOT_IN
                if (new_input[i] == not_in[off]) {
                    //printf("active temp 0 (3) per %c, con %c\n", new_input[i], not_in[off]);
                    active_temp[i] = 0;
                    //fltr_cntr = 1;
                    active_global = 0;
                    break;
                }
                off++;
            }*/
            off = (i * 64)+position;
            if(not_in[off]==new_input[i]){
                active_temp[i] = 0;
                active_global = 0;
                break;
            }
            i++;
        }

        i = 0;
        while (i <= exact_pos && active_global == 1) {
            if (exact_iteration[i] >= 65 && exact_iteration[i] <= 90) { //lettere
                position = exact_iteration[i] - 54;
            } else if (exact_iteration[i] >= 97 && exact_iteration[i] <= 122) { //lettere
                position = exact_iteration[i] - 59;
            } else if (exact_iteration[i] >= 48 && exact_iteration[i] <= 57) { //numeri
                position = exact_iteration[i] - 47; //numeri
            } else if (exact_iteration[i] == 45) {
                position = 0;
            } else if (exact_iteration[i] == 95) {
                position = 37;
            }
            if (iteration_temp[position] != exact_iteration_n[i]) {
                //printf("active temp 0 (3) per exact_iteration %c\n", exact_iteration[i]);
                active_temp[word_len-1] = 0;
                //fltr_cntr = 1;
                active_global = 0;
                break;
            }
            i++;
        }

        i = 0;
        while (i <= min_pos && active_global == 1) {
            if (min_iteration[i] >= 65 && min_iteration[i] <= 90) { //lettere
                position = min_iteration[i] - 54;
            } else if (min_iteration[i] >= 97 && min_iteration[i] <= 122) { //lettere
                position = min_iteration[i] - 59;
            } else if (min_iteration[i] >= 48 && min_iteration[i] <= 57) {//numeri
                position = min_iteration[i] - 47;
            } else if (min_iteration[i] == 45) {
                position = 0;
            } else if (min_iteration[i] == 95) {
                position = 37;
            }
            if (iteration_temp[position] < min_iteration_n[i]) {
                //printf("active temp 0 (3) per min_iteration %c\n", min_iteration[i]);
                active_temp[word_len-1] = 0;
                //fltr_cntr = 1;
                active_global = 0;
                break;
            }
            i++;
        }

        /*for(i=0; i<word_len;i++){
            printf("%d", active_temp[i]);
        }
        i=0;
        printf("\n");*/
    }

    if(active_global==1){
        filter_counter++;
    }

    if(head==NULL){
        malloc_pointer = malloc(4096*sizeof(letter));
        malloc_count = 0;
        head = malloc_pointer + malloc_count;
        initialize(head, 1);
    }
    current = head;
    i=0;
    active_global=1;
    upper[i]=current;
    //ALGORITMO RIFATTO inizio
    while (new_input[i]!='\0' && i < word_len) {
      if(current->down != NULL){
        current = current->down;
        k=0;
        while(flag == 0){
          if(current->c[k]!=new_input[i]){
            if(current->right != NULL){
              if(current->right->c[k] == new_input[i]){
                  current = current->right;
                  if(active_global==1){
                      if(current->active[k]==1){
                          active_global = active_temp[i];
                          current->active[k] = active_temp[i];
                      } else {
                          active_global = 0;
                      }
                      /*if(vincoli==1){
                          printf("%d", active_global);
                      }*/
                  }
                  flag = 1;
                  i++;
                  k++;
                  upper[i]=current;
                  while(current->c[k] != '\0'){
                    if(current->c[k] != new_input[i]){
                      transpose = current;
                      if(malloc_count!=4095){
                          malloc_count++;
                      } else {
                          malloc_pointer = malloc(4096*sizeof(letter));
                          malloc_count = 0;
                      }
                      current = malloc_pointer + malloc_count;
                      initialize(current, word_len-i);
                      current->down = transpose -> down;
                      transpose->down = current;
                      m=0;
                      k_mem = k;
                      while(transpose->c[k] != '\0'){
                        current->c[m]=transpose->c[k];
                        current->active[m]=transpose->active[k];
                        k++;
                        m++;
                      }
                      transpose->c[k_mem] = '\0';
                      current->c[m] = '\0';

                      k=0;
                      flag = 0;
                      break;
                    }
                    if(active_global==1){
                        if(current->active[k]==1){
                            active_global = active_temp[i];
                            current->active[k] = active_temp[i];
                        } else {
                            active_global = 0;
                        }
                        /*if(vincoli==1){
                            printf("%d", active_global);
                        }*/
                    }
                    k++;
                    i++;
                    upper[i]=current;
                  }
                  k=0;
                  if(i==word_len){
                    break;
                  }
                //avanza nella stessa parola, oppure ti sposti sotto (se arriva in fondo break?)
              } else if (current->c[k] < new_input[i] && current->right->c[k] > new_input[i]) {
                transpose = current->right;
                if(malloc_count!=4095){
                    malloc_count++;
                } else {
                    malloc_pointer = malloc(4096*sizeof(letter));
                    malloc_count = 0;
                }
                current->right = malloc_pointer + malloc_count;
                initialize(current->right, word_len-i);
                current = current->right;
                current->right = transpose;
                current->c[k] = new_input[i];
                if(active_global==1){
                    if(current->active[k]==1){
                        active_global = active_temp[i];
                        current->active[k] = active_temp[i];
                    } else {
                        active_global = 0;
                    }
                    /*if(vincoli==1){
                        printf("%d", active_global);
                    }*/
                }
                flag = 1;
                i++;
                k++;
                upper[i]=current;
                while(new_input[i]!='\0' && i < word_len){
                    current->c[k] = new_input[i];
                    if(active_global==1){
                        if(current->active[k]==1){
                            active_global = active_temp[i];
                            current->active[k] = active_temp[i];
                        } else {
                            active_global = 0;
                        }
                        /*if(vincoli==1){
                            printf("%d", active_global);
                        }*/
                    }
                    i++;
                    k++;
                    upper[i]=current;
                }
                current->c[k] = '\0';
                k=0;
                if(i==word_len){
                    break;
                }
                //avanza nella stessa parola fino in fondo (se sono tutti attivi, se no spezzi)
              } else if (current->c[k] > new_input[i]) {
                transpose = current;
                if(malloc_count!=4095){
                    malloc_count++;
                } else {
                    malloc_pointer = malloc(4096*sizeof(letter));
                    malloc_count = 0;
                }
                current = malloc_pointer + malloc_count;
                initialize(current, word_len-i);
                upper[i]->down = current;
                current->right = transpose;
                current->c[k] = new_input[i];
                if(active_global==1){
                    if(current->active[k]==1){
                        active_global = active_temp[i];
                        current->active[k] = active_temp[i];
                    } else {
                        active_global = 0;
                    }
                    /*if(vincoli==1){
                        printf("%d", active_global);
                    }*/
                }
                flag = 1;
                  i++;
                  k++;
                  upper[i]=current;
                  while(new_input[i]!='\0' && i < word_len){
                    current->c[k] = new_input[i];
                    if(active_global==1){
                        if(current->active[k]==1){
                            active_global = active_temp[i];
                            current->active[k] = active_temp[i];
                        } else {
                            active_global = 0;
                        }
                        /*if(vincoli==1){
                            printf("%d", active_global);
                        }*/
                    }
                    i++;
                    k++;
                    upper[i]=current;
                  }
                  current->c[k] = '\0';
                  k=0;
                  if(i==word_len){
                      break;
                  }
                //avanza nella stessa parola fino in fondo (se sono tutti attivi, se no spezzi)
              } else {
                current = current->right;
                k=0;
              }
            } else { //se a destra non ha nulla
              if(current->c[k] > new_input[i]){
                  transpose = current;
                  if(malloc_count!=4095){
                      malloc_count++;
                  } else {
                      malloc_pointer = malloc(4096*sizeof(letter));
                      malloc_count = 0;
                  }
                  current = malloc_pointer + malloc_count;
                  initialize(current, word_len-i);
                  upper[i]->down = current;
                  current->right = transpose;
                  k=0;
                  current->c[k] = new_input[i];
                  if(active_global==1){
                      if(current->active[k]==1){
                          active_global = active_temp[i];
                          current->active[k] = active_temp[i];
                      } else {
                          active_global = 0;
                      }
                      /*if(vincoli==1){
                          printf("%d", active_global);
                      }*/
                  }
                  flag = 1;
                  i++;
                  k++;
                  upper[i]=current;
                  while(new_input[i]!='\0' && i < word_len){
                      if(active_global==1){
                          if(current->active[k]==1){
                              active_global = active_temp[i];
                              current->active[k] = active_temp[i];
                          } else {
                              active_global = 0;
                          }
                          /*if(vincoli==1){
                              printf("%d", active_global);
                          }*/
                      }
                      current->c[k] = new_input[i];
                      i++;
                      k++;
                      upper[i]=current;
                  }
                  current->c[k] = '\0';
                  k=0;
                  if(i==word_len){
                      break;
                  }
                  //avanza nella stessa parola fino in fondo (se sono tutti attivi, se no spezzi)
              } else {
                  if(malloc_count!=4095){
                      malloc_count++;
                  } else {
                      malloc_pointer = malloc(4096*sizeof(letter));
                      malloc_count = 0;
                  }
                  current->right = malloc_pointer + malloc_count;
                  initialize(current->right, word_len-i);
                  current = current->right;
                  current->c[k] = new_input[i];
                  if(active_global==1){
                      if(current->active[k]==1){
                          active_global = active_temp[i];
                          current->active[k] = active_temp[i];
                      } else {
                          active_global = 0;
                      }
                      /*if(vincoli==1){
                          printf("%d", active_global);
                      }*/
                  }
                  flag = 1;
                    i++;
                    k++;
                    upper[i]=current;
                    while(new_input[i]!='\0' && i < word_len){
                      current->c[k] = new_input[i];
                        if(active_global==1){
                            if(current->active[k]==1){
                                active_global = active_temp[i];
                                current->active[k] = active_temp[i];
                            } else {
                                active_global = 0;
                            }
                            /*if(vincoli==1){
                                printf("%d", active_global);
                            }*/
                        }
                      i++;
                      k++;
                      upper[i]=current;
                    }
                    current->c[k] = '\0';
                    k=0;
                  if(i==word_len){
                      break;
                  }
                  //avanza nella stessa parola fino in fondo (se sono tutti attivi, se no spezzi)
              }
            }
          } else { //la lettera corrisponde
              flag = 1;
              if(active_global==1){
                  if(current->active[k]==1){
                      active_global = active_temp[i];
                      current->active[k] = active_temp[i];
                  } else {
                      active_global = 0;
                  }
                  /*if(vincoli==1){
                      printf("%d", active_global);
                  }*/
              }
                i++;
                k++;
                upper[i]=current;
                while(current->c[k] != '\0'){
                  if(current->c[k] != new_input[i]){
                    transpose = current;
                    if(malloc_count!=4095){
                        malloc_count++;
                    } else {
                        malloc_pointer = malloc(4096*sizeof(letter));
                        malloc_count = 0;
                    }
                    current = malloc_pointer+malloc_count;
                    initialize(current, word_len-i);
                    current->down = transpose -> down;
                    transpose->down = current;
                    m=0;
                    k_mem = k;
                    while(transpose->c[k] != '\0'){
                      current->c[m]=transpose->c[k];
                      current->active[m]=transpose->active[k];
                      k++;
                      m++;
                    }
                    transpose->c[k_mem] = '\0';
                    current->c[m] = '\0';
                    k=0;
                    flag = 0;
                    break;
                  }
                  if(active_global==1){
                      if(current->active[k]==1){
                          active_global = active_temp[i];
                          current->active[k] = active_temp[i];
                      } else {
                          active_global = 0;
                      }
                      /*if(vincoli==1){
                          printf("%d", active_global);
                      }*/
                  }
                  k++;
                  i++;
                  upper[i]=current;
                }
                k=0;
                if(i==word_len){
                  break;
                }
              ////avanza nella stessa parola, oppure ti sposti sotto (se arriva in fondo break?)
          }
        }
        flag = 0;
      } else { //non c'è niente andando giù, alloco tutta la parola
          if(malloc_count!=4095){
              malloc_count++;
          } else {
              malloc_pointer = malloc(4096*sizeof(letter));
              malloc_count = 0;
          }
          current->down = malloc_pointer + malloc_count;
          initialize(current->down, word_len-i-1);
          current = current->down;
          current->c[k] = new_input[i];
          if(active_global==1){
              if(current->active[k]==1){
                  active_global = active_temp[i];
                  current->active[k] = active_temp[i];
              } else {
                  active_global = 0;
              }
              /*if(vincoli==1){
                  printf("%d", active_global);
              }*/
          }
          i++;
          k++;
          upper[i]=current;
          while(new_input[i]!='\0' && i < word_len){
              current->c[k] = new_input[i];
              if(active_global==1){
                  if(current->active[k]==1){
                      active_global = active_temp[i];
                      current->active[k] = active_temp[i];
                  } else {
                      active_global = 0;
                  }
                  /*if(vincoli==1){
                      printf("%d", active_global);
                  }*/
              }
              i++;
              k++;
              upper[i]=current;
          }
          current->c[k] = '\0';
          k=0;
          break;
      }
    }

    //ALGORITMO RIFATTO fine

    //printf("\n");

    //printf("Parola inserita: %d\n", find_tree());
    return 0;
}

/*int activator(letter * current, int k, int active_temp, int onoff){ //(current, k, 0, 0)
    int active_i=0, g=0;
    active_i = current->active;
    for(g=0; g<k; g++){
        active_i = active_i/10;
    }
    active_i = active_i%2;
    if(onoff==1){
        if(active_i == 0 && active_temp == 1) {
            active_i=1;
            for (g=0; g < k; g++) {
                active_i = active_i * 10;
            }
            current->active = current->active + active_i;
            return 1;
        }
        return 1;
    } else {
        if(active_i == 1 && active_temp == 0) {
            for (g=0; g<k; g++) {
                active_i = active_i * 10;
            }
            current->active = current->active - active_i;
            if(vincoli==1){
                printf("k=%d, active_temp=%d, curr active (post)=%d\n", k, active_temp, current->active);
            }
            return 0;
        } else if (active_i == 0){
            if(vincoli==1){
                printf("k=%d, active_temp=%d, curr active (post)=%d\n", k, active_temp, current->active);
            }
            return 0;
        } else {
            if(vincoli==1){
                printf("k=%d, active_temp=%d, curr active (post)=%d\n", k, active_temp, current->active);
            }
            return 1;
        }
    }
}*/
/*int isactive(letter * current, int k){
    int active_k=0, g=0, m=1;
    active_k = current->active;
    for(g=0; g<k; g++){
        m = m*10;
        //active_k = active_k/10;
    }
    active_k = active_k/m;
    active_k = active_k%2;
    return active_k;
}*/
int stampa_filtrate(){
    letter * current, * upper[word_len+1];
    char to_print[word_len+1];
    int i=0, last_right, k=0, g=0, count2=0;
    to_print[word_len]='\0';

    current = head;
    do{
        do{
            last_right = 0;
            while(i!=word_len && current->active[k]==1){
              if(current->c[k+1]=='\0'){
                //printf("qui\n");
                  upper[i] = current;
                  current = current->down;
                  k=0;
                  i++;
                  upper[i]=current;
                  to_print[i-1]=current->c[k];
                  //printf("c= %c, i= %d, k= %d\n", current->c[k], i, k);
                } else {
                  k++;
                  i++;
                  upper[i]=current;
                  //printf("c=%c\n", current->c[k]);
                  to_print[i-1]=current->c[k];
                  //printf("c= %c, i= %d, k= %d\n", current->c[k], i, k);
                }
            }
            //printf("qui\n");
            if(i==word_len && current->active[k]==1){
                count2++;
                printf("%s\n", to_print);
            }
            //printf("c= %c, i= %d, k= %d, curr right=%p\n", current->c[k], i, k, current->right);
            if(current->right!=NULL && k==0){
                //printf("entra\n");
                current = current->right;
                //printf("c=%c\n", current->c[k]);
                to_print[i-1]=current->c[k];
                last_right = 1;
            }
        }while(i<=word_len && ((current->right!=NULL && k==0) || ((current->down!=NULL || current->c[k+1]!='\0') && current->active[k]==1))); //qui l'ultima parola non entra se accedo dalla penultima di destra (?) di una fila
        if(last_right==1){
            if(i==word_len && current->active[k]==1){
                count2++;
                printf("%s\n", to_print);
            }
            last_right = 0;
        }
        while(i!=1 && (k!=0 || (k==0 && current->right==NULL))){ //POST ULTIMO UP
            while(k>0 && i!=1){
              i--;
              k--;
            }
            if(i!=1 && k==0 && current->right==NULL){
              i--;
              current = upper[i];
              g=0;
              while(current->c[g]!='\0'){
                  g++;
              }
              k=g-1;
            }
        }
        if(i==1 && (k!=0 || (k==0 && current->right==NULL))){
            break;
        } else {
            current = current->right;
            k=0;
            while(current->c[k]!='\0' && current->active[k]==1){ //mi pare pericoloso, da pensare bene
            //printf("c=%c\n", current->c[k]);
            to_print[i-1]=current->c[k];
            upper[i]=current;
            i++;
            k++;
            }
            if(current->active[k-1]==1){
            k--;
            i--;
            }
            //printf("i=%d\n", i);
        }
    } while(i!=1 || current->right!=NULL || current->down!=NULL);

    /*if(filter_counter!=count2){
        exit(1);
    }*/
    //printf("fine stampa filtrate\n");
    return 0;
}

int stampa_albero(){
    letter * current, * upper[word_len+2];
    int i=0, last_right, k=0, g=0, tot=0;
    char to_print[word_len+1];
    to_print[word_len]='\0';
    printf("stampo albero\n");
    current = head;
    do{
        do{
            //printf("entro in loop(1)\n");
            last_right = 0;
            while(i!=word_len){
              if(current->c[k+1]=='\0'){
                //printf("qui\n");
                  upper[i]=current;
                  current = current->down;
                  k=0;
                  i++;
                  upper[i]=current;
                  to_print[i-1]=current->c[k];
                  printf("lettera(1):%c (%d), up: %p, down: %p, right: %p\n", current->c[k], current->active[k], upper[i-1], current->down, current->right);
                } else {
                //printf("là\n");
                  k++;
                  i++;
                  upper[i]=current;
                  to_print[i-1]=current->c[k];
                  printf("lettera(2):%c (%d), up: %p, down: %p, right: %p\n", current->c[k], current->active[k], upper[i-1], current->down, current->right);
                }
            }
            if(i==word_len){
                printf("Parola(1) %s\n", to_print);
                tot++;
            }
            if(current->right!=NULL && k==0){
                current = current->right;
                to_print[i-1]=current->c[k];
                printf("lettera(3):%c (%d), up: %p, down: %p, right: %p\n", current->c[k], current->active[k], upper[i-1], current->down, current->right);
                last_right = 1;
            }
        }while(i<=word_len && ((current->right!=NULL && k==0) || (current->down!=NULL || current->c[k+1]!='\0'))); //qui l'ultima parola non entra se accedo dalla penultima di destra (?) di una fila
        if(last_right==1){
            if(i==word_len){
                printf("Parola(2) %s\n", to_print);
                tot++;
            }
            last_right = 0;
        }
        while(i!=1 && (k!=0 || (k==0 && current->right==NULL))){ //POST ULTIMO UP
        	//printf("entro in loop(2), k=%d, curr->c=%c\n", k, current->c[k]);
            while(k>0 && i!=1){
            //printf("entro in loop(3), k=%d, curr->c=%c, curr prec=%c\n", k, current->c[k], current->c[k-1]);
              i--;
              k--;
            }
            if(i!=1 && (k==0 && current->right==NULL)){
            	//printf("entro in if, curr->c=%c, right=%p\n", current->c[k], current->right);
              i--;
              current=upper[i];
                g=0;
                while(current->c[g]!='\0'){
                    g++;
                }
                k=g-1;
              //printf("esco da if, curr->c=%c, right=%p\n", current->c[k], current->right);
            }
        }
        //printf("uscito\n");
        if(i==1 && (k!=0 || (k==0 && current->right==NULL))){
            break;
        } else {
            current = current->right;
            k=0;
            while(current->c[k]!='\0'){
                to_print[i-1]=current->c[k];
            printf("lettera(4):%c (%d), up: %p, down: %p, right: %p\n", current->c[k], current->active[k], upper[i-1], current->down, current->right);
            i++;
            k++;
            upper[i]=current;
            }
            k--;
            i--;
            //printf("i=%d\n", i);
        }
    } while(i!=1 || current->right!=NULL || current->down!=NULL);
    
    printf("Stampa albero fine (tot=%d\n", tot);
    return 0;
}

int check_word(){
    int i=0, k, position=0, slash_count[64]={0}, off, new_input_analize[64] = {0}, found_analize[64] = {0}, found;
    char final[word_len+1];
    for (i = 0; i < word_len; i++) {
        final[i]=0;
    }
    i=0;
    //final = malloc((word_len+1) * sizeof(char)); //inserisci i + / |
    if(find_tree() == -1){ //La parola non appartiene all'albero
        printf("not_exists\n");
        return -1;
    } else if (strcmp(new_input, queen_word)==0){
        printf("ok\n");
        return 1;
    }

    //printf("Analizzo: %s\n", new_input);

    while(new_input[i] != '\0'){ //scorre tutta la parola e segna le lettere che corrispondono con i + e si segna anche quante iterazioni di ogni lettera sono presenti
        //printf("(%c-%c)", new_input[i], queen_word[i]);
        if(new_input[i] >= 65 && new_input[i] <= 90){ //lettere
            position = new_input[i] - 54;
        } else if (new_input[i] >= 97 && new_input[i] <= 122){ //lettere
            position = new_input[i] - 59;
        } else if (new_input[i] >= 48 && new_input[i] <= 57){ //numeri
            position = new_input[i] - 47;
        } else if (new_input[i] == 45){
            position = 0;
        } else if (new_input[i] == 95){
            position = 37;
        }
        new_input_analize[position]++; //aumenta di 1 il counter delle lettere presenti;
        if(new_input[i] == queen_word[i]){ // segna con + le corrispondenti e segna quelle sicure in memoria e conteggia le sicure
            //printf("entra ()%c %c)", new_input[i], queen_word[i]);
            final[i] = '+';
            sure[i] = new_input[i];
            //printf("Entro in yes char\n");
            //tree_yes_char_specific(i+1, new_input[i]);
            found_analize[position]++;
        }
        i++;
    }
    i=0; //ricomincia dall'inizio
    while(new_input[i] != '\0'){ //fino a fine stringa
        if(new_input[i] >= 65 && new_input[i] <= 90){ //lettere
            position = new_input[i] - 54;
        } else if (new_input[i] >= 97 && new_input[i] <= 122){ //lettere
            position = new_input[i] - 59;
        } else if (new_input[i] >= 48 && new_input[i] <= 57){//numeri
            position = new_input[i] - 47;
        } else if (new_input[i] == 45){
            position = 0;
        } else if (new_input[i] == 95){
            position = 37;
        }
        if(final[i]!='+'){ //se una lettera NON è già segnata
            //printf("Analizzo (%c)", new_input[i]);
            off = (i * 64) + position; //determina la posizione per la matrice dei non presenti nella posizione specifica
            if (queen_analize[position] - found_analize[position] > 0) { //se differenza tra quante lettera in queen e quante lettera trovate è >0
                final[i] = '|'; //segno che ne ho ancora disponibili
                /*while (not_in[off]!=new_input[i] && not_in[off] !=0) { //con while e successiva segno la lettera non presente in quella posizione
                    off++;
                }*/
                not_in[off] = new_input[i];
                /*if(filter_counter==1){
                    printf("Aggiungo in posizione i (da 0)=%d la lettera %c\n", i, new_input[i]);
                }*/
                //printf("Tolgo tutti quelli che hanno (1) %c in %d\n", new_input[k], k+1);
                //printf("Entro in no char specific (2)\n");
                //tree_no_char_specific(k+1, new_input[k]);
                found_analize[position]++;//aumento di 1 il conteggio delle found (non ne ho trovata un'altra ma almeno tengo il conto)
            } else {
                //printf("Entro con %c di posizione %d", new_input[k], k);
                //printf("Entra / per (%c)", new_input[k]);
                final[i] = '/'; //segno che NON ne ho più disponibili
                slash_count[position]++; //conto quante barre ho messo per questa lettera
                /*while (not_in[off]!=new_input[i] && not_in[off] != 0) { //con while e successiva segno la lettera non presente in quella posizione
                    off++;
                }*/
                not_in[off] = new_input[i];
                /*if(filter_counter==1){
                    printf("Aggiungo in posizione i (da 0)=%d la lettera %c\n", i, new_input[i]);
                }*/
                //printf("Tolgo tutti quelli che hanno (2) %c in %d\n", new_input[k], k+1);
                //printf("Entro in no char specific (3)\n");
                //tree_no_char_specific(k+1, new_input[k]);
                //printf("%d\n", filter_counter);
            }
        }
        printf("%c", final[i]);
        i++;
    }

    i=0;
    //printf("Check minimi di %s:\n", new_input);
    while(new_input[i] != '\0'){
        if(new_input[i] >= 65 && new_input[i] <= 90){ //lettere
            position = new_input[i] - 54;
        } else if (new_input[i] >= 97 && new_input[i] <= 122){ //lettere
            position = new_input[i] - 59;
        } else if (new_input[i] >= 48 && new_input[i] <= 57){ //numeri
            position = new_input[i] - 47;
        } else if (new_input[i] == 45){
            position = 0;
        } else if (new_input[i] == 95){
            position = 37;
        }
        if(slash_count[position] == new_input_analize[position]){
          //printf("(not in) Slash count (%d) == new input analize (%d), del carattere %c\n", slash_count[position], new_input_analize[position], new_input[i]);
            not_in_total[position]=1;
            //printf("Tolgo tutti quelli che hanno %c\n", new_input[i]);
            //printf("Entro in no char\n");
            //tree_no_char(new_input[i]);
            //printf("%d\n", filter_counter);
        } else if(slash_count[position] < new_input_analize[position] && slash_count[position]!=0){
          //printf("(exact) Slash count (%d) < new input analize (%d) (e slash != 0), del carattere %c\n", slash_count[position], new_input_analize[position], new_input[i]);
            k=0;
            found=0;
            while(k<=exact_pos && found==0){
                if(new_input[i]==exact_iteration[k]){
                    found=1;
                }
                k++;
            }
            if(found==0){
                k=0;
                while(k<=min_pos && found==0){
                  if (min_iteration[k]==new_input[i]){
                    while(k<min_pos){
                      min_iteration[k]=min_iteration[k+1];
                      min_iteration_n[k]=min_iteration_n[k+1];
                      k++;
                    }
                    min_pos--;
                    found = 1;
                    break;
                  }
                  k++;
                }
                exact_pos++;
                exact_iteration[exact_pos] = new_input[i];
                exact_iteration_n[exact_pos] = new_input_analize[position]-slash_count[position];
            }
            //printf("Entro in exact (2)\n");
            //tree_exact_char(position);
        } else {
          //printf("(min) Slash count (%d) < new input analize (%d) (e slash == 0), del carattere %c\n", slash_count[position], new_input_analize[position], new_input[i]);
            k=0;
            found=0;
            while(k<=exact_pos && found==0){
                if(new_input[i]==exact_iteration[k]){
                    found=1;
                }
                k++;
            }
            if(found==0) {
                k=0;
                while (k <= min_pos && found == 0) {
                    if (new_input[i] == min_iteration[k]) {
                        if(min_iteration_n[k]<new_input_analize[position]){
                            min_iteration_n[k] = new_input_analize[position];
                        }
                        found = 1;
                    }
                    k++;
                }
                if (found == 0) {
                    min_pos++;
                    min_iteration[min_pos] = new_input[i];
                    min_iteration_n[min_pos] = new_input_analize[position];
                }
            }
            //printf("Tolgo tutti quelli che hanno meno di %d %c\n",min_iteration[position], new_input[i]);
            //printf("Entro in min char\n");
            //tree_min_char(position); //QUESTO NON FUNZIONA BENE!!
            //printf("%d\n", filter_counter);
        }
        i++;
    }

    final[i] = '\0';
    sure[i] = '\0';
    i = 0;
    tree_polish();
    printf("\n");
    printf("%d\n", filter_counter);
    /*if(filter_counter<1){
        exit(1);
    }*/
    return 0;
}

int find_tree(){
    int i=0, not_found=0, k=0, flag=0;
    letter * current;
    current = head;
    while (new_input[i]!='\0' && i < word_len && not_found==0) {
        current = current->down;
        k=0;
        flag = 0;
        while(flag==0 && not_found==0){
		if (new_input[i] != current->c[k]) {
		    while(current->right!=NULL && new_input[i] != current->c[k]){
		    	current=current->right;
		    }
		    if(new_input[i] != current->c[k]){
		    	not_found=1;
		    }
		} else {
		  i++;
		  k++;
		  while(current->c[k]!='\0' && not_found==0){
		    if(current->c[k]!=new_input[i]){
		      not_found = 1;
		    }
		    i++;
		    k++;
		  }
		  flag = 1;
		}
        }
    }
    if (not_found == 1){
        return -1;
    } else {
        return 1;
    }
}

int down_counter(letter * mark, int start_lvl, int k_pos){
    letter * current=mark, * upper[word_len+2];
    //printf("Partendo da %c, al livello %d\n", mark->c, start_lvl);
    if(mark->c[k_pos+1]=='\0' && mark->down==NULL){
        filter_counter--;
        //printf("Diminuisco (1)\n");
        //printf("Counter (1) --\n");
        //printf("Termino %c, al livello %d\n", mark->c, start_lvl);
        return 0;
    }
    int i=0, last_right, k=0, g=0;
    k = k_pos;
    do{
        do{
            last_right = 0;
            while(i!=word_len-start_lvl && current->active[k]==1){
            //printf("i= %d diversa da %d\n", i, word_len-start_lvl);
            //printf("%c\n", current->c[k]);
                if(current->c[k+1]=='\0'){
                //printf("qui\n");
                  upper[i]=current;
                  current = current->down;
                  k=0;
                  i++;
                  upper[i]=current;
                } else {
                //printf("là\n");
                  k++;
                  i++;
                  upper[i]=current;
                }
            }
            //printf("eccoci\n");
            if(i==word_len-start_lvl && current->active[k]==1){
                filter_counter--;
                //printf("Diminuisco (2)\n");
                //printf("Counter (2) --\n");
                //printf("Parola che termina con %c\n", current->c);
            }
            if(current->right!=NULL && k==0){ //NON SOLO ULTIMO CARATTERE MA DEV'ESSERCI CONDIZIONE NON USCITA
            	//printf("qui dubito\n");
                current = current->right;
                last_right = 1;
            }
        }while(i<=word_len-start_lvl && ((current->right!=NULL && k==0) || ((current->down!=NULL || current->c[k+1]!='\0') && current->active[k]==1)));
        if(last_right==1){
            if(i==word_len-start_lvl && current->active[k]==1){
                filter_counter--;
                //printf("Diminuisco (3)\n");
                //printf("Counter (2) --\n");
                //printf("Parola che termina con %c\n", current->c);
            }
            last_right = 0;
        }
        while(i!=1 && (k!=0 || (k==0 && current->right==NULL))){ //POST ULTIMO UP
            while(k>0 && i!=1){
              i--;
              k--;
              //printf("I=%d\n", i);
            }
            if(i!=1 && (k==0 && current->right==NULL)){
              i--;
              current=upper[i];
                g=0;
                while(current->c[g]!='\0'){
                    g++;
                }
                k=g-1;
              //printf("I(2)=%d\n", i);
            }
        }
        if(i==1 && (k!=0 || (k==0 && current->right==NULL))){
            break;
        } else {
            //printf("I(2)=%d\n", i);
            current = current->right;
            k=0;
            while(current->c[k]!='\0' && current->active[k]==1){
            upper[i]=current;
              i++;
              k++;
            }
            if(current->active[k-1]==1){
            k--;
            i--;
            }
        }
    } while(i!=1 || current->right!=NULL || current->down!=NULL);

    //printf("Termino %c, al livello %d\n", mark->c, start_lvl);

    return 0;
}

int clear_all(){
    int i=0, last_right, k=0, g=0;
    letter * current, * upper[word_len+2];
    //clear_new_input();
    for (i = 0; i < 30; i++) {
        queen_word[i]=0;
    }
    for (i = 0; i < word_len; i++) {
        sure[i]=0;
    }
    for (i = 0; i < word_len*64; i++) {
        not_in[i]=0;
    }
    //printf("new_input: %s, queen_word: %s, sure: %s, not_in: %s\n", new_input, queen_word, sure, not_in);
    //printf("not in: %d\n", word_len*64);
    //for (i = 0; i < word_len*64; ++i)
    //{
    //printf("%d", not_in[i]);
    //}
    //printf("\nQueen min exact not_in_total\n");
    for (i = 0; i < 64; ++i)
    {
        queen_analize[i] = 0;
        not_in_total[i] = 0;
        //printf("%d %d %d %d\n", queen_analize[i], min_iteration[i], exact_iteration[i], not_in_total[i]);
    }
    for (i = 0; i < min_pos; ++i) {
        min_iteration[i] = 0;
        min_iteration_n[i] = 0;
    }
    min_pos = -1;
    for (i = 0; i < exact_pos; ++i) {
        exact_iteration[i] = 0;
        exact_iteration_n[i] = 0;
    }
    exact_pos = -1;
    //printf("\n\n");
    filter_counter=0;

    i = 0;
    current = head;
    do{
        do{
            last_right = 0;
            while(i!=word_len){
                if(current->c[k+1]=='\0'){
                //printf("qui\n");
                  upper[i]=current;
                  //if(isactive(current, k)==0){
                    current->active[k] = 1;
                    //printf("DOWN: %c RIATTIVATA\n", current->c);
                  //}
                  current = current->down;
                  k=0;
                  i++;
                  //if(isactive(current, k)==0){
                        current->active[k] = 1;
                      //printf("DOWN: %c RIATTIVATA\n", current->c);
                  //}
                  upper[i]=current;
                } else {
                //printf("là\n");
                  k++;
                  i++;
                  //if(isactive(current, k)==0){
                    current->active[k] = 1;
                        //printf("DOWN: %c RIATTIVATA\n", current->c);
                  //}
                  upper[i]=current;
                }
                //printf("DOWN(1): %c\n", current->c);
            }
            if(i==word_len){
                filter_counter++;
            }
            if(current->right!=NULL && k==0){
                current = current->right;
                k=0;
                //printf("DOWN(2): %c\n", current->c);
                //if(isactive(current, k)==0){
                current->active[k] = 1;
                    //printf("DOWN: %c RIATTIVATA\n", current->c);
                //}
                last_right = 1;
            }
        }while(i<=word_len && ((current->right!=NULL && k==0) || (current->down!=NULL || current->c[k+1]!='\0')));
        if(last_right==1){
            if(i==word_len){
                filter_counter++;
            }
            last_right = 0;
        }
        while(i!=1 && (k!=0 || (k==0 && current->right==NULL))){
            while(k>0 && i!=1){
              i--;
              k--;
            }
            if(i!=1 && (k==0 && current->right==NULL)){
              i--;
              current = upper[i];
                g=0;
                while(current->c[g]!='\0'){
                    g++;
                }
                k=g-1;
            }
        }
        if(i==1 && (k!=0 || (k==0 && current->right==NULL))){
            break;
        } else {
            current = current->right;
            k=0;
            while(current->c[k]!='\0'){
            upper[i]=current;
            //if(isactive(current, k)==0){
                current->active[k] = 1;
                    //printf("DOWN: %c RIATTIVATA\n", current->c);
            //}
            i++;
            k++;
            }
            k--;
            i--;
            //printf("DOWN(3): %c\n", current->c);
        }
    } while(i!=1 || current->right!=NULL || current->down!=NULL);

    return 0;
}

int tree_polish(){ //DA AGGIUNGERE LE SCISSIONI QUANDO VENGONO DISATTIVATI e DA SISTEMARE filter_counter
    letter * current, * upper[word_len+2];
    int i=0, position=0, position_b=0, last_right=0, j=0, k=0, g=0, active_now=0, off=0;
    int iteration_temp[64] = {0};
    //char to_print[word_len+1];

    //to_print[word_len]='\0';

    current = head;
    active_now = current->active[k];
    do{
        do{
            last_right = 0;
            if(active_now == 1) {
                while (i != word_len) {
                    //printf("qui entra, i=%d, e current active=%d e current->c=%c\n", i, current->active, current->c[k]);
                    if (current->c[k + 1] == '\0') {
                        upper[i] = current;
                        current = current->down;
                        k = 0;
                        i++;
                        active_now = current->active[k];
                        upper[i] = current;
                    } else {
                        k++;
                        i++;
                        active_now = current->active[k];
                        upper[i] = current;
                    }
                    //printf("c=%c (1), i=%d\n", current->c[k], i);
                    if (current->c[k] >= 65 && current->c[k] <= 90) { //lettere
                        position = current->c[k] - 54;
                    } else if (current->c[k] >= 97 && current->c[k] <= 122) { //lettere
                        position = current->c[k] - 59;
                    } else if (current->c[k] >= 48 && current->c[k] <= 57) { //numeri
                        position = current->c[k] - 47;
                    } else if (current->c[k] == 45) {
                        position = 0;
                    } else if (current->c[k] == 95) {
                        position = 37;
                    }
                    //printf("entra qui\n");
                    //PARTE VARIABILE INIZIO
                    //INIZIO NO CHAR
                    if(not_in_total[position]==1 && active_now==1){
                        //printf("Non può esserci il carattere %c\n", current->c[k]);
                        /*if(filter_counter<=1)
                        printf("Ingresso counter (1)\n");*/
                        down_counter(current, i, k); //ultimo i placeholder
                        current->active[k] = 0;
                        active_now=0;
                    }
                    //FINE NO CHAR
                    //INIZIO YES CHAR SPECIFIC
                    //printf("c=%c (BOH), sure=%c, i=%d\n", current->c[k], sure[i-1], i);
                    if(current->c[k]!=sure[i-1] && sure[i-1]!=0 && active_now==1){
                        //printf("Deve esserci il carattere %c al posto che %c\n", sure[i-1], current->c);
                        /*if(filter_counter<=1)
                        printf("Ingresso counter (2)\n");*/
                        down_counter(current, i, k); //ultimo i placeholder
                        current->active[k] = 0;
                        active_now=0;
                    }
                    //FINE YES CHAR SPECIFIC
                    //INIZIO NO CHAR SPECIFIC
                    off = ((i-1)*64)+position;
                    /*if(filter_counter<=1) {
                        printf("entro\n");
                    }*/
                    /*if(filter_counter<=1) {
                        printf("Lettere per i=%d", i);
                    }*/
                    if(active_now==1){
                        /*while (not_in[off] != 0) {*/
                            /*if(filter_counter<=1) {
                                printf("%c ", not_in[off]);
                            }*/
                            if (current->c[k] == not_in[off]) {
                                //printf("\n");
                                /*if(filter_counter<=1){
                                    printf("Non può esserci il carattere %c QUI (i=%d)\n", current->c[k], i);
                                    printf("Ingresso counter (3)\n");
                                }*/
                                down_counter(current, i, k); //ultimo i placeholder
                                current->active[k] = 0;
                                active_now=0;
                                break;
                            }
                            /*off++;
                        }*/
                    }
                    //FINE NO CHAR SPECIFIC
                    //PARTE VARIABILE FINE
                    upper[i] = current;
                    //INIZIO MIN E EXACT CHAR
                    if (active_now == 1) {
                        iteration_temp[position]++;
                        //to_print[i-1]=current->c[k];
                        //printf("%c incremento (1)\n", current->c[k]);
                    } else {
                        break;
                    }
                }
            }
            active_now = current->active[k];
            if(i==word_len && active_now==1){
                //printf("La parola attuale è: %s\n", to_print);
                j=0;
                while (j <= exact_pos) {
                    //printf("iterazioni esatte di: %c\n", exact_iteration[j]);
                    if (exact_iteration[j] >= 65 && exact_iteration[j] <= 90) { //lettere
                        position_b = exact_iteration[j] - 54;
                    } else if (exact_iteration[j] >= 97 && exact_iteration[j] <= 122) { //lettere
                        position_b = exact_iteration[j] - 59;
                    } else if (exact_iteration[j] >= 48 && exact_iteration[j] <= 57) { //numeri
                        position_b = exact_iteration[j] - 47;
                    } else if (exact_iteration[j] == 45) {
                        position_b = 0;
                    } else if (exact_iteration[j] == 95) {
                        position_b = 37;
                    }
                    //printf("Carattere %c, ho %d e %d esatti\n", exact_iteration[j], iteration_temp[position_b], exact_iteration_n[j]);
                    if (iteration_temp[position_b] != exact_iteration_n[j]) {
                        //printf("Carattere %c, ho %d e %d esatti\n", exact_iteration[j], iteration_temp[position_b], exact_iteration_n[j]);
                        /*if(filter_counter<=1)
                        printf("Ingresso counter (4)\n");*/
                        filter_counter--;
                        current->active[k] = 0;
                        active_now=0;
                        break;
                    }
                    j++;
                }
                j=0;
                if(active_now == 1) {
                    while (j <= min_pos) {
                        //printf("iterazioni minime di: %c\n", min_iteration[j]);
                        if (min_iteration[j] >= 65 && min_iteration[j] <= 90) { //lettere
                            position_b = min_iteration[j] - 54;
                        } else if (min_iteration[j] >= 97 && min_iteration[j] <= 122) { //lettere
                            position_b = min_iteration[j] - 59;
                        } else if (min_iteration[j] >= 48 && min_iteration[j] <= 57) { //numeri
                            position_b = min_iteration[j] - 47;
                        } else if (min_iteration[j] == 45) {
                            position_b = 0;
                        } else if (min_iteration[j] == 95) {
                            position_b = 37;
                        }
                        //printf("Carattere %c, ho %d e %d min\n", min_iteration[j], iteration_temp[position_b], min_iteration_n[j]);
                        if (iteration_temp[position_b] < min_iteration_n[j]) {
                            //printf("Carattere %c, ho %d e %d min\n", min_iteration[j], iteration_temp[position_b], min_iteration_n[j]);
                            /*if(filter_counter<=1)
                            printf("Ingresso counter (5)\n");*/
                            filter_counter--;
                            current->active[k] = 0;
                            active_now=0;
                            break;
                        }
                        j++;
                    }
                }
                if(active_now==0){
               	    if(min_iteration[j] >= 65 && min_iteration[j] <= 90){ //lettere
                    position_b = min_iteration[j] - 54;
                    } else if (min_iteration[j] >= 97 && min_iteration[j] <= 122){//lettere
                    position_b = min_iteration[j] - 59;
                    } else if (min_iteration[j] >= 48 && min_iteration[j] <= 57){ //numeri
                        position_b = min_iteration[j] - 47;
                    } else if (min_iteration[j] == 45){
                    position_b = 0;
                    } else if (min_iteration[j] == 95){
                    position_b = 37;
                    }
                    iteration_temp[position]--;
                    //printf("%c decremento(1)\n", current->c[k]);
                }
            }
            if(current->right!=NULL && k==0){
            	if(active_now==1){
            		iteration_temp[position]--;
            		//printf("%c decremento(2)\n", current->c[k]);
            	}
                current = current->right;
                last_right = 1;
                //printf("entra anche qua\n");
                //printf("c=%c (2)\n", current->c[k]);
                if(current->c[k] >= 65 && current->c[k] <= 90){ //lettere
                    position = current->c[k] - 54;
                } else if (current->c[k] >= 97 && current->c[k] <= 122){ //lettere
                    position = current->c[k] - 59;
                } else if (current->c[k] >= 48 && current->c[k] <= 57){ //numeri
                    position = current->c[k] - 47;
                } else if (current->c[k] == 45){
                    position = 0;
                } else if (current->c[k] == 95){
                    position = 37;
                }
                //PARTE VARIABILE INIZIO
                active_now = current->active[k];
                //INIZIO NO CHAR
                if(not_in_total[position]==1 && active_now==1){
                    //printf("Non può esserci il carattere %c\n", current->c[k]);
                    /*if(filter_counter<=1)
                    printf("Ingresso counter (1)\n");*/
                    down_counter(current, i, k); //ultimo i placeholder
                    current->active[k] = 0;
                    active_now=0;
                }
                //FINE NO CHAR
                //INIZIO YES CHAR SPECIFIC
                //printf("c=%c (BOH), sure=%c, i=%d\n", current->c[k], sure[i-1], i);
                if(current->c[k]!=sure[i-1] && sure[i-1]!=0 && active_now==1){
                    //printf("Deve esserci il carattere %c al posto che %c\n", sure[i-1], current->c);
                    /*if(filter_counter<=1)
                    printf("Ingresso counter (2)\n");*/
                    down_counter(current, i, k); //ultimo i placeholder
                    current->active[k] = 0;
                    active_now=0;
                }
                //FINE YES CHAR SPECIFIC
                //INIZIO NO CHAR SPECIFIC
                off = ((i-1)*64)+position;
                /*if(filter_counter<=1) {
                    printf("entro\n");
                }*/
                /*if(filter_counter<=1) {
                    printf("Lettere per i=%d", i);
                }*/
                if(active_now==1){
                    /*while (not_in[off] != 0) {*/
                    /*if(filter_counter<=1) {
                        printf("%c ", not_in[off]);
                    }*/
                    if (current->c[k] == not_in[off]) {
                        //printf("\n");
                        /*if(filter_counter<=1){
                            printf("Non può esserci il carattere %c QUI (i=%d)\n", current->c[k], i);
                            printf("Ingresso counter (3)\n");
                        }*/
                        down_counter(current, i, k); //ultimo i placeholder
                        current->active[k] = 0;
                        active_now=0;
                        break;
                    }
                    /*off++;
                }*/
                }
                //FINE NO CHAR SPECIFIC
                //PARTE VARIABILE FINE
                upper[i]=current;
                //INIZIO MIN E EXACT CHAR
                if(active_now==1){
                    iteration_temp[position]++;
                    //to_print[i-1]=current->c[k];
                    //printf("%c incremento (2)\n", current->c[k]);
                }
            }
            //printf("qui c'è, e curr right:%p e i=%d\n", current->right, i);
        }while(i<=word_len && ((current->right!=NULL && k==0) || ((current->down!=NULL || current->c[k+1]!='\0') && active_now==1)));
        //printf("superato primo while, current k+1=%c\n", current->c[k+1]);
        if(last_right==1){
            if(i==word_len && active_now==1){
                //printf("La parola attuale è: %s\n", to_print);
                j=0;
                while(j<=exact_pos){
                  //printf("iterazioni esatte di: %c\n", exact_iteration[j]);
                    if(exact_iteration[j] >= 65 && exact_iteration[j] <= 90){ //lettere
                        position_b = exact_iteration[j] - 54;
                    } else if (exact_iteration[j] >= 97 && exact_iteration[j] <= 122){ //lettere
                        position_b = exact_iteration[j] - 59;
                    } else if (exact_iteration[j] >= 48 && exact_iteration[j] <= 57){ //numeri
                        position_b = exact_iteration[j] - 47;
                    } else if (exact_iteration[j] == 45){
                        position_b = 0;
                    } else if (exact_iteration[j] == 95){
                        position_b = 37;
                    }
                    //printf("Carattere %c, ho %d e %d esatti\n", exact_iteration[j], iteration_temp[position_b], exact_iteration_n[j]);
                    if(iteration_temp[position_b]!=exact_iteration_n[j]){
                    //printf("Carattere %c, ho %d e %d esatti\n", exact_iteration[j], iteration_temp[position_b], exact_iteration_n[j]);
                        /*if(filter_counter<=1)
                        printf("Ingresso counter (9)\n");*/
                        filter_counter--;
                        current->active[k] = 0;
                        active_now=0;
                        break;
                    }
                    j++;
                }
                j=0;
                if(active_now == 1) {
                    while (j <= min_pos) {
                        //printf("iterazioni minime di: %c\n", min_iteration[j]);
                        if (min_iteration[j] >= 65 && min_iteration[j] <= 90) { //lettere
                            position_b = min_iteration[j] - 54;
                        } else if (min_iteration[j] >= 97 && min_iteration[j] <= 122) { //lettere
                            position_b = min_iteration[j] - 59;
                        } else if (min_iteration[j] >= 48 && min_iteration[j] <= 57) { //numeri
                            position_b = min_iteration[j] - 47;
                        } else if (min_iteration[j] == 45) {
                            position_b = 0;
                        } else if (min_iteration[j] == 95) {
                            position_b = 37;
                        }
                        //printf("Carattere %c, ho %d e %d minimi\n", min_iteration[j], iteration_temp[position_b], min_iteration_n[j]);
                        if (iteration_temp[position_b] < min_iteration_n[j]) {
                            //printf("Carattere %c, ho %d e %d minimi\n", min_iteration[j], iteration_temp[position_b], min_iteration_n[j]);
                            /*if(filter_counter<=1)
                            printf("Ingresso counter (10)\n");*/
                            filter_counter--;
                            current->active[k] = 0;
                            active_now=0;
                            break;
                        }
                        j++;
                    }
                }
                if(active_now==0){
                	iteration_temp[position]--;
                	//printf("%c decremento(3)\n", current->c[k]);
                }
            }
            last_right=0;
        }
        while(i!=1 && (k!=0 || (k==0 && current->right==NULL))){
            while(k!=0 && i!=1){
            //printf("entra sopra con c=%c\n", current->c[k]);
              //printf("dentro(4)(risalita), i=%d e current=%c\n", i, current->c[k]);
              if(current->c[k] >= 65 && current->c[k] <= 90){ //lettere
                  position = current->c[k] - 54;
              } else if (current->c[k] >= 97 && current->c[k] <= 122){ //lettere
                  position = current->c[k] - 59;
              } else if (current->c[k] >= 48 && current->c[k] <= 57){ //numeri
                  position = current->c[k] - 47; //numeri
              } else if (current->c[k] == 45){
                  position = 0;
              } else if (current->c[k] == 95){
                  position = 37;
              }
              if(active_now==1){
                  iteration_temp[position]--;
                  //printf("%c decremento(4), i=%d, k=%d\n", current->c[k], i, k);
              }
              i--;
              k--;
              active_now = current->active[k];
            }
            if(i!=1 && (k==0 && current->right==NULL)){
              //printf("entra sotto con c=%c\n", current->c[k]);
              if(current->c[k] >= 65 && current->c[k] <= 90){ //lettere
                  position = current->c[k] - 54;
              } else if (current->c[k] >= 97 && current->c[k] <= 122){ //lettere
                  position = current->c[k] - 59;
              } else if (current->c[k] >= 48 && current->c[k] <= 57){ //numeri
                  position = current->c[k] - 47; //numeri
              } else if (current->c[k] == 45){
                  position = 0;
              } else if (current->c[k] == 95){
                  position = 37;
              }
              if(active_now==1){
              	iteration_temp[position]--;
              	//printf("%c decremento(5), i=%d, k=%d\n", current->c[k], i, k);
              }
              i--;
              current=upper[i];
              g=0;
              while(current->c[g]!='\0'){
                  g++;
              }
              k=g-1;
              active_now = current->active[k];
            }
        }
        if(i==1 && (k!=0 || (k==0 && current->right==NULL))){
            break;
        } else {
            //printf("entra proprio qua\n");
              if(current->c[k] >= 65 && current->c[k] <= 90){ //lettere
                  position = current->c[k] - 54;
              } else if (current->c[k] >= 97 && current->c[k] <= 122){ //lettere
                  position = current->c[k] - 59;
              } else if (current->c[k] >= 48 && current->c[k] <= 57){ //numeri
                  position = current->c[k] - 47; //numeri
              } else if (current->c[k] == 45){
                  position = 0;
              } else if (current->c[k] == 95){
                  position = 37;
              }
              if(active_now==1){
                iteration_temp[position]--;
                //printf("%c decremento(6), i=%d, k=%d\n", current->c[k], i, k);
              }
              current = current->right;
            k=0;
            active_now = current->active[k];
            //printf("qui ci passa come previsto\n");
            while(current->c[k]!='\0' && active_now==1){
            //printf("dentro(7), i=%d e current=%c\n", i, current->c[k]);
              //printf("c=%c (3)\n", current->c[k]);
                if(current->c[k] >= 65 && current->c[k] <= 90){ //lettere
                    position = current->c[k] - 54;
                } else if (current->c[k] >= 97 && current->c[k] <= 122){ //lettere
                    position = current->c[k] - 59;
                } else if (current->c[k] >= 48 && current->c[k] <= 57){ //numeri
                    position = current->c[k] - 47; //numeri
                } else if (current->c[k] == 45){
                    position = 0;
                } else if (current->c[k] == 95){
                    position = 37;
                }
                //PARTE VARIABILE INIZIO
                //INIZIO NO CHAR
                if(not_in_total[position]==1 && active_now==1){
                    //printf("Non può esserci il carattere %c\n", current->c[k]);
                    /*if(filter_counter<=1)
                    printf("Ingresso counter (1)\n");*/
                    down_counter(current, i, k); //ultimo i placeholder
                    current->active[k] = 0;
                    active_now=0;
                }
                //FINE NO CHAR
                //INIZIO YES CHAR SPECIFIC
                //printf("c=%c (BOH), sure=%c, i=%d\n", current->c[k], sure[i-1], i);
                if(current->c[k]!=sure[i-1] && sure[i-1]!=0 && active_now==1){
                    //printf("Deve esserci il carattere %c al posto che %c\n", sure[i-1], current->c);
                    /*if(filter_counter<=1)
                    printf("Ingresso counter (2)\n");*/
                    down_counter(current, i, k); //ultimo i placeholder
                    current->active[k] = 0;
                    active_now=0;
                }
                //FINE YES CHAR SPECIFIC
                //INIZIO NO CHAR SPECIFIC
                off = ((i-1)*64)+position;
                /*if(filter_counter<=1) {
                    printf("entro\n");
                }*/
                /*if(filter_counter<=1) {
                    printf("Lettere per i=%d", i);
                }*/
                if(active_now==1){
                    /*while (not_in[off] != 0) {*/
                    /*if(filter_counter<=1) {
                        printf("%c ", not_in[off]);
                    }*/
                    if (current->c[k] == not_in[off]) {
                        //printf("\n");
                        /*if(filter_counter<=1){
                            printf("Non può esserci il carattere %c QUI (i=%d)\n", current->c[k], i);
                            printf("Ingresso counter (3)\n");
                        }*/
                        down_counter(current, i, k); //ultimo i placeholder
                        current->active[k] = 0;
                        active_now=0;
                        break;
                    }
                    /*off++;
                }*/
                }
                //FINE NO CHAR SPECIFIC
                //PARTE VARIABILE FINE
                //INIZIO MIN E EXACT CHAR
                if(active_now==1){
                    iteration_temp[position]++;
                    //to_print[i-1]=current->c[k];
                    //printf("%c incremento (3), i=%d\n", current->c[k], i);
                    upper[i]=current;
                    i++;
            	    k++;
                    active_now = current->active[k];
                }
                //FINE MIN E EXACT CHAR
            //printf("active = %d, i=%d\n", current->active, i);
            }
            if(current->active[k-1]==1){
              k--;
              i--;
              active_now = current->active[k];
            }
        }
    } while(i!=1 || current->right!=NULL || current->down!=NULL);
    //printf("right=%p, down=%p, i=%d", current->right, current->down, i);
    return 0;
}

/*int tree_polish_check(letter * current, int k, int i, int position){ //forse k
	int off=0, active_now;
	//PARTE VARIABILE INIZIO
    active_now = isactive(current, k);
    //INIZIO NO CHAR
    if(not_in_total[position]==1 && active_now==1){
        //printf("Non può esserci il carattere %c\n", current->c[k]);
        down_counter(current, i, k); //ultimo i placeholder
        activator(current, k, 0, 0);
        active_now=0;
    }
    //FINE NO CHAR
    //INIZIO YES CHAR SPECIFIC
    //printf("c=%c (BOH), sure=%c, i=%d\n", current->c[k], sure[i-1], i);
    if(current->c[k]!=sure[i-1] && sure[i-1]!=0 && active_now==1){
        //printf("Deve esserci il carattere %c al posto che %c\n", sure[i-1], current->c);
        down_counter(current, i, k); //ultimo i placeholder
        activator(current, k, 0, 0);
        active_now=0;
    }
    //FINE YES CHAR SPECIFIC
    //INIZIO NO CHAR SPECIFIC
    off = (i-1)*64;
    if(active_now==1){
        while (not_in[off] != 0) {
            if (current->c[k] == not_in[off]) {
                //printf("\n");
                down_counter(current, i, k); //ultimo i placeholder
                activator(current, k, 0, 0);
                active_now=0;
                break;
            }
            off++;
        }
    }
    //FINE NO CHAR SPECIFIC
    //PARTE VARIABILE FINE
    return active_now;
}*/

