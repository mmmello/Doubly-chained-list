#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Knot Knot;

struct Knot{
    int data;
    Knot *next;
    Knot *previous;
}*start=NULL, *end=NULL;

int menu(){
    int op;
    printf("Choose: \n1 - Insert. \n2 - Show. \n3 - Search. \n4 - Change. \n5 - Delete 1 element. \n6 - Delete all. \n0 - Finish. \nOption: ");
    scanf("%d", &op);
    return op;
}

void insert(int num){
    Knot *new;
    new = (Knot*) malloc(sizeof(Knot));
    new->data = num;

    if(start==NULL){
        new->next = start;
        new->previous = end;
        start = end = new;
    }else{
        new->next = end;
        new->previous = NULL;
        new->next->previous = new;
        end = new;
    }
    printf("\nNUMBER SUCCESSFULLY ENTERED.\n\n");
}

void show(){
    Knot *aux = start;
    
    printf("\n+----------------------------------------------------------------------+\n| List:");
    while (aux != NULL){
        printf(" %d ", aux->data);
        aux = aux->previous;
    }
    printf("\n+----------------------------------------------------------------------+\n\n");
}

Knot * search(int search){
    Knot *aux_start = start;
    Knot *aux_end = end;
    Knot *retorno=NULL;

    if(start!=NULL)
        do{
            if(aux_start->data==search){
                retorno = aux_start;
                break;
            }else if(aux_end->data==search){
                retorno = aux_end;
                break;
            }else{
                aux_start=aux_start->previous;
                aux_end=aux_end->next;
            }
        }while (aux_start->next!=aux_end->previous && aux_start->next!=aux_end);
    return retorno;
}

void change_list(int target, int num_change){
    Knot *aux;
    aux = search(target);
    if(aux!=NULL){
        aux->data = num_change;
        printf("\n\nTHE NUMBER WAS SUCCESSFULLY CHANGED, CHECK THE UPDATED LIST.");
    }else
        printf("\nERROR. ENTERED NUMBER NOT FOUND.\n\n");
}

void delete_1(int target){
    Knot *aux;
    aux = search(target);
    if(aux!=NULL){
        if (aux->next == NULL){ // if the next one is NULL then it is at the beginning
            start = aux->previous;
            start->next = NULL;
        }else if(aux->previous == NULL){ // if the previous one equals NULL then it is at the end
            end = aux->next;
            end->previous = NULL;
        }else{
            aux->next->previous = aux->previous;
            aux->previous->next = aux->next;
        }
        free(aux);
        printf("\n\nTHE NUMBER WAS SUCCESSFULLY DELETED, CHECK THE UPDATED LIST.");
    }else
        printf("\nERROR. ENTERED NUMBER NOT FOUND.\n\n");
}

void delete_all(){
    do{
        if(start->previous == end->next || start->previous == end){
            free(start->previous);
            end = start = NULL;
        }else{
            start = start->previous;
            end = end->next;
            free(start->next);
            free(end->previous);
            start->next = end->previous = NULL;
        }
    }while (start != NULL && end !=NULL);
}

int check_list(){
    if(start)
        return 1;
    else{
        printf("\nEMPTY LIST.\nInsert at least one element for this option.\n\n");
        return 0;
    }
}

int main(){
    system("cls");
    int op, num;
    do{
        op = menu();
        switch (op){
        case 1: // INSERTS INTO THE LIST
            printf("\nEnter a number to be inserted in the list: ");
            scanf("%d", &num);
            insert(num);
        break;
        case 2: // PRINTS THE LIST
            if(check_list())
                show();
        break;
        case 3: { // SEEK A VALUE
            if(check_list()){
                int num_search;
                printf("\nEnter the number you wish to search: ");
                scanf("%d", &num_search);

                Knot * obj = search(num_search);

                if(obj!=NULL)
                    printf("\nSEARCHED NUMBER: %d\n\n", obj->data);
                else
                    printf("\nERROR. ENTERED NUMBER NOT FOUND.\n\n");
            }
            break;
        }case 4: { // CHANGE LIST
            if(check_list()){
                int num_change, target;
                printf("\nObserve the current situation of the list.\n\n");

                show();
                sleep(2);

                printf("\nEnter the number of the list you wish to REPLACE: ");
                scanf("%d", &target);

                printf("\nNow, enter the value that will REPLACE the number %d: ", num_change);
                scanf("%d", &num_change);
                change_list(target, num_change);
                show();
                sleep(2);
            }
            break;
        }case 5:{ // DELETE 1
            if(check_list()){
                int num_delete;
                printf("\nObserve the current situation of the list.\n\n");

                show();
                sleep(2);

                printf("\nEnter the number of the list you wish to EXCLUDE: ");
                scanf("%d", &num_delete);

                delete_1(num_delete);
                show();
                sleep(2);
            }
            break;
        }case 6: // DELETE ALL
            if(check_list()){
                delete_all();
                if(start == NULL && end == NULL)
                    printf("\nLIST SUCCESSFULLY DELETED.\n\n");
                else
                    printf("\nERROR WHEN DELETING.\nList still filled.\n");
            }
            break;
        case 0: // EXIT THE SYSTEM
            printf("\n+-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-+\n");
            printf("|         EXITING THE SYSTEM          |\n");
            printf("+-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-+\n\n");
            sleep(2);
            break;
        default:
            printf("\n+-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-+\n");
            printf("|           INVALID OPTION            |\n");
            printf("|   ENTER AN OPTION BETWEEN 0 AND 6   |\n");
            printf("+-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-+\n\n");
            break;
        }
    }while(op);
}