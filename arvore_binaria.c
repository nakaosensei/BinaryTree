#include "arvore_binaria.h"


/**************************************
* DADOS
**************************************/

struct no{
  TipoElemento dado;
  struct no *esq, *dir;
};

struct paiFilho{
  int posicaoFilho;//0=esquerda,1=direita,-1=pai nulo
  struct no *pai, *target;
};

struct familia{
  struct no *raiz,*paiDoFilhoExtremaDireita, *filhoExtremaDireita;
};

/**************************************
* FUNÇÕES AUXILIARES
**************************************/
No* novoNo(TipoElemento item){
    No* novo= (No*)malloc(sizeof(No));
    novo->dado=item;
    novo->esq=NULL;
    novo->dir=NULL;
    return novo;
}

//Busca por um node, se existir retorna o pai e o filho
PaiFilho* ab_consulta_util(No* raiz, TipoElemento elemento){
	if(raiz==NULL) return NULL;    
    No* atual = raiz;    
    No* pai;
    int lastOperation=-1;
    while(atual!=NULL){
        if (elemento==atual->dado){
            PaiFilho* ret = (PaiFilho*)malloc(sizeof(PaiFilho));
            ret->posicaoFilho=lastOperation;
            ret->pai=pai;
            ret->target=atual;
            return ret;
        }
        if(elemento<atual->dado){
            pai=atual;   
            atual=atual->esq;             
            lastOperation=0;      
            continue;
        }
        pai=atual;
        atual=atual->dir;           
        lastOperation=1;       
    }     
    return NULL;
}

//A partir de um node, busca-se o filho a extrema direita do seu filho da esquerda
//Pensa que seu filho votou no Lula, mas seu neto votou no Bolsonaro, esse metodo vai buscar o neto(ok isso foi ruim)
Familia* ab_filho_extrema_direita(No* node){
	if(node==NULL||node->esq==NULL) return NULL;    
    No* atual = node->esq;
    No* raiz=node;
    No *pai=node;
    while(atual->dir!=NULL){        
        pai=atual;
        atual=atual->dir;       
    }     
    Familia *familiaTreta = (Familia*)calloc(1, sizeof(Familia));
    familiaTreta->raiz=raiz;
    familiaTreta->paiDoFilhoExtremaDireita=pai;
    familiaTreta->filhoExtremaDireita=atual;
    return familiaTreta;
}

bool isFolha(No *node){
    if (node->dir==NULL&&node->esq==NULL){
        return true;
    }
    return false;
}

bool contemApenasDirBranch(No *node){
    if (node->dir!=NULL&&node->esq==NULL){
        return true;
    }
    return false;
}

bool contemEsqBranch(No *node){
    if (node->esq!=NULL){
        return true;
    }
    return false;
}


/**************************************
* IMPLEMENTAÇÃO
**************************************/


void ab_destruir(No **enderecoRaiz){
    if(*enderecoRaiz==NULL) return;    
    int lenAtuais=1;
    int qtdeProximos=1;
    No** atuais = (No**)calloc(2,sizeof(No*));    
    atuais[0]=*enderecoRaiz;    
    while(qtdeProximos>0){
        qtdeProximos=0;
        No** proximos = (No**)calloc(lenAtuais*2, sizeof(No*));
        for(int i = 0;i<lenAtuais;i++){
            if (atuais[i]==NULL) continue;            
            if(atuais[i]->esq!=NULL){
                proximos[qtdeProximos]=atuais[i]->esq;
                qtdeProximos++;
            }
            if(atuais[i]->dir!=NULL){
                proximos[qtdeProximos]=atuais[i]->dir;
                qtdeProximos++;
            }          
        }        
        for(int i = 0;i<lenAtuais;i++){
            free(atuais[i]);
        }
        free(atuais);
        atuais = proximos;
        lenAtuais=qtdeProximos;
    }
    free(*enderecoRaiz);
    *enderecoRaiz=NULL;
}

bool ab_inserir(No **enderecoRaiz, TipoElemento elemento){
    if(*enderecoRaiz==NULL){
        No *tmp = novoNo(elemento);
        *enderecoRaiz=tmp;
        return true;
    }
    No* atual = *enderecoRaiz;
    No *pai;
    int lastOperation=0;
    while(atual!=NULL){
        pai=atual;
        if(elemento<atual->dado){
            atual=atual->esq;
            lastOperation=0;
            continue;
        }
        atual=atual->dir;   
        lastOperation=1;     
    }
    atual = novoNo(elemento);
    if(lastOperation==0){
        pai->esq=atual;
    }else{
        pai->dir=atual;
    }    
    return true;
}

void ab_imprime(No** enderecoRaiz){
    if(*enderecoRaiz==NULL) return;    
    int lenAtuais=1;
    int qtdeProximos=1;
    No** atuais = (No**)calloc(2,sizeof(No*));    
    atuais[0]=*enderecoRaiz;
    printf("\n");
    while(qtdeProximos>0){
        qtdeProximos=0;
        No** proximos = (No**)calloc(lenAtuais*2, sizeof(No*));
        for(int i = 0;i<lenAtuais;i++){
            if (atuais[i]==NULL) continue;
            printf("%d ",atuais[i]->dado);
            if(atuais[i]->esq!=NULL){
                proximos[qtdeProximos]=atuais[i]->esq;
                qtdeProximos++;
            }
            if(atuais[i]->dir!=NULL){
                proximos[qtdeProximos]=atuais[i]->dir;
                qtdeProximos++;
            }          
        }
        printf("\n");
        free(atuais);
        atuais = proximos;
        lenAtuais=qtdeProximos;
    }   
}

bool ab_remover(No** enderecoRaiz, TipoElemento dado){
    PaiFilho *pesq = ab_consulta_util(*enderecoRaiz,dado);//alvo=pesq->target, pai do alvo = pesq->pai
    if (pesq==NULL) return false;    
    if (isFolha(pesq->target)){//Caso o node encontrado seja uma folha...
        if (pesq->posicaoFilho==0){//filho a esquerda
            pesq->pai->esq=NULL;
            free(pesq->target);
            return true;
        }else if(pesq->posicaoFilho==1){//filho a direita
            pesq->pai->dir=NULL;
            free(pesq->target);
            return true;
        }else{//na busca, nao foi encontrado um no pai do node encontrado, sendo ele raiz e folha ao mesmo tempo
            free(pesq->target);
            return true;
        }        
    }
    if (contemApenasDirBranch(pesq->target)){//caso tenha apenas filho da direita
        if (pesq->posicaoFilho==0){//filho a esquerda
            pesq->pai->esq=pesq->target->dir;
            free(pesq->target);
            return true;
        }else if(pesq->posicaoFilho==1){//filho a direita
            pesq->pai->dir=pesq->target->dir;
            free(pesq->target);
            return true;
        }else{//na busca, nao foi encontrado um no pai do node encontrado
            *enderecoRaiz=pesq->target->dir;
            free(pesq->target);
            return true;
        }
    }    
    if(contemEsqBranch(pesq->target)){//caso tenha filho da esquerda                   
        Familia *family = ab_filho_extrema_direita(pesq->target);                
        if (family==NULL) return false;  
        if (family->paiDoFilhoExtremaDireita!=pesq->target)
            family->paiDoFilhoExtremaDireita->dir=family->filhoExtremaDireita->esq;
        family->filhoExtremaDireita->esq=pesq->target->esq;                  
        family->filhoExtremaDireita->dir=pesq->target->dir;               
        if (family->filhoExtremaDireita==family->filhoExtremaDireita->esq) family->filhoExtremaDireita->esq=NULL;
        if (family->filhoExtremaDireita==family->filhoExtremaDireita->dir) family->filhoExtremaDireita->dir=NULL; 
        if(pesq->target==*enderecoRaiz)//se o node a ser removido = raiz, a nova raiz passa a ser o filho de extrema direita a partir do no da esquerda da raiz
            *enderecoRaiz=family->filhoExtremaDireita;
        if (pesq->posicaoFilho==0){//filho a esquerda
            pesq->pai->esq=family->filhoExtremaDireita;            
        }else if(pesq->posicaoFilho==1){//filho a direita
            pesq->pai->dir=family->filhoExtremaDireita;            
        }
        free(pesq->target);
        return true;
    }
    return false;
}

void ab_pre_ordem(No* raiz){
     if (raiz != NULL){
        printf("%d ", raiz->dado);
        ab_pre_ordem(raiz->esq);
        ab_pre_ordem(raiz->dir);
    }
}

void ab_em_ordem(No* raiz){
    if (raiz != NULL){
        ab_em_ordem(raiz->esq);
        printf("%d ", raiz->dado);
        ab_em_ordem(raiz->dir);
    }
}

void ab_pos_ordem(No* raiz){
    if (raiz != NULL){
        ab_pos_ordem(raiz->esq);
        ab_pos_ordem(raiz->dir);
        printf("%d ", raiz->dado);
    }
}

int ab_altura(No *enderecoRaiz){
    if(enderecoRaiz==NULL) return -1;    
    int lenAtuais=1;
    int qtdeProximos=1;
    No** atuais = (No**)calloc(2,sizeof(No*));    
    atuais[0]=enderecoRaiz;
    int altura=0;
    while(qtdeProximos>0){
        altura+=1;
        qtdeProximos=0;
        No** proximos = (No**)calloc(lenAtuais*2, sizeof(No*));
        for(int i = 0;i<lenAtuais;i++){
            if (atuais[i]==NULL) continue;
            if(atuais[i]->esq!=NULL){
                proximos[qtdeProximos]=atuais[i]->esq;
                qtdeProximos++;
            }
            if(atuais[i]->dir!=NULL){
                proximos[qtdeProximos]=atuais[i]->dir;
                qtdeProximos++;
            }          
        }
        free(atuais);
        atuais = proximos;
        lenAtuais=qtdeProximos;
    }
    return altura;
}

int ab_total_vertices(No *enderecoRaiz){
	if(enderecoRaiz==NULL) return -1;    
    int lenAtuais=1;
    int qtdeProximos=1;
    No** atuais = (No**)calloc(2,sizeof(No*));    
    atuais[0]=enderecoRaiz;
    int total=0;
    while(qtdeProximos>0){        
        qtdeProximos=0;
        No** proximos = (No**)calloc(lenAtuais*2, sizeof(No*));
        for(int i = 0;i<lenAtuais;i++){
            if (atuais[i]==NULL) continue;
            total+=1;
            if(atuais[i]->esq!=NULL){
                proximos[qtdeProximos]=atuais[i]->esq;
                qtdeProximos++;
            }
            if(atuais[i]->dir!=NULL){
                proximos[qtdeProximos]=atuais[i]->dir;
                qtdeProximos++;
            }          
        }
        free(atuais);
        atuais = proximos;
        lenAtuais=qtdeProximos;
    }
    return total;
}

bool ab_consulta(No* raiz, TipoElemento elemento){
	if(raiz==NULL) return false;    
    No* atual = raiz;    
    while(atual!=NULL){
        if (elemento==atual->dado) return true;
        if(elemento<atual->dado){
            atual=atual->esq;            
            continue;
        }
        atual=atual->dir;          
    }     
    return false;
}