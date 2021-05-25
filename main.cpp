//****************************************************/
/*  Estruturas de dados e algoritmos fundamentais   */
/*             21046->EFOLIO-B                      */
/*      Ana Rita Pinho-> 1800464->LEI               */
/****************************************************/

/****************************************************/
/*                  bibliotecas                     */
/****************************************************/

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <exception>


using namespace std;

/****************************************************/
/*                  classe erros                    */
/****************************************************/
class Erros: public exception{
private:
    string mensagem;
public:
    explicit Erros(int erro) noexcept(false);
    explicit Erros(int erro, int num) noexcept(false);
    const char * what() const noexcept override;
};
//Funcão  Erros:
Erros::Erros(int erro) noexcept(false){
    switch(erro){
        case 1://caso a lista se encontre vazia
            this->mensagem="Arvore vazia!\n";
            break;
        default://outros erros possiveis
            this->mensagem= "Erro Desconhecido\n";
            break;
    }
}

Erros::Erros(int erro, int num) noexcept(false){
    stringstream s;
    s << "Item " << num << " inexistente!\n";
    this->mensagem = s.str();
}

const char * Erros::what() const noexcept{
    return mensagem.c_str();
}

/****************************************************/
/*              (Binary search tree)                */
/****************************************************/


/****************************************************/
/*              classe no de arvore                 */
/****************************************************/
class no{
private:
    int elemento;
    no * direita;
    no * esquerda;
public:
    ~ no();
    no(int elemento) noexcept(false);
    no * get_no_direito();
    no * get_no_esquerdo();
    int get_elemento();
    void set_elemento(int elemento);
    void set_no_direito(no * direita);
    void set_no_esquerdo(no * esquerda);

};
/****************************************************/
/*              Classe Tree (arvore)                */
/****************************************************/
class tree {
private:
    no * root;
    bool antecessor;

public:
    ~tree ();
    tree  ();
    no * get_root();
    void set_root(no * root);
    bool insert (int elemento);
    string print_inorder(no * arvore, no * pai);
    string print(tree * arvore);
    no *  no_vminimo(no * filho );
    no * delete_no(no * root, int elemento);
    bool clear ( );
    void rotate_esquerda(no * no_raiz, no* no_mudar, no* avo);
    void rotate_direita(no * no_raiz, no* no_mudar, no* avo);
    bool possui_elemento(int elemento, no * atual);
    bool rotate(int elemento);
    bool find( int elemento);
};
/****************************************************/
/*              classe comandos                     */
/****************************************************/
//
class comandos {
private:
    string mensagem;// mensagem de erro
    stringstream linha;
public:
    explicit comandos(string & linha);
    ~comandos( );
    void executar_comandos (tree * root);
    bool mensagem_vazia() const;
    string get_mensagem() const;
};

/****************************************************/
/*          funcoes pertencestes a classe no        */
/****************************************************/

// funcao construtora da classe no
no:: no(int elemento) noexcept(false){
    this->direita = nullptr;
    this->esquerda = nullptr;
    this->elemento=elemento;
}

// funcao Destrutor da classe no
no::~no() {
    this->direita= nullptr;
    this->esquerda= nullptr;
    elemento = 0 ;
}


// funcao que obtem no direito
no * no::get_no_direito(){
    return this->direita;
}

//funcao que obtem  no esquerdo
no * no:: get_no_esquerdo(){
    return this->esquerda;
}

// funcao que obtem elemento
int no::get_elemento() {
    return this->elemento;
}

//funcao que atualiza elemento
void no::set_elemento(int elemento ) {
    this->elemento = elemento;
}

//funcao que atualiza no direito
void no:: set_no_direito(no * direita){
    this->direita = direita;
}

//funcao que atualiza no esquerdo
void no:: set_no_esquerdo(no * esquerda){
    this->esquerda = esquerda;
}

/****************************************************/
/*      funcoes  pertencentes  a classe tree        */
/****************************************************/

//funcao destrutor pertencente a classe tree
tree:: ~tree (){
    while(root != nullptr ){
        set_root(delete_no(get_root(),get_root()->get_elemento()));
    }
}

//funcao construtor pertencente a classe tree
tree:: tree (){
    this->root= nullptr;
    this->antecessor = true;
}

//funcao que obtem a root
no * tree:: get_root(){
    return root;
}

//funcao que atualiza a root
void tree:: set_root(no * root){
    this->root = root;
}

//funcao que executa o comando inserir item na arvore
bool tree :: insert (int elemento){
    no * novo_no = new no(elemento);
    // caso a arvore esteja vazia
    if(this->root == nullptr ){
        set_root(novo_no);
        //caso a arvore não esteja vazia
    }else{
        no * pai = nullptr;
        no * atual = root;
        //procura o no onde deve inserir o item
        while (atual != nullptr ) {
            pai = atual;
            if (elemento < pai->get_elemento()) {
                atual = pai->get_no_esquerdo();
            } else {
                atual = pai->get_no_direito();
            }
        }
        //insere o elemento
        if (elemento < pai->get_elemento()){
            pai->set_no_esquerdo(novo_no);
        }else{
            pai->set_no_direito(novo_no);
        }
    }
    return true;
}

// funcao que executa o comando print_inorder
string tree:: print_inorder(no * arvore, no * pai){
    stringstream s;
    if (arvore != nullptr){
        s << print_inorder(arvore->get_no_esquerdo(), arvore);
        s << " " << arvore->get_elemento();
        if (pai != nullptr) {
            s << "(" << pai->get_elemento() << ")";
        }
        s << print_inorder(arvore->get_no_direito(), arvore);
    }
    return s.str();
}
// funcao que imprime os valores de print_inorder
string tree::print(tree * arvore){
    try {
        if (arvore->get_root() == nullptr){
            throw Erros(1);
        }
        return "Arvore=" + print_inorder(arvore->get_root(), nullptr)+"\n";
    }catch (const Erros &e) {
        throw Erros(e);
    }
}

//funcao que retorna o no com menor elemento(filho)
no * tree:: no_vminimo(no * filho ){
    no * atual = filho;
    //verifica se deve procurou no ramo do antecessor
    //em caso positivo, procura no ramo da arvore do antecessor
    if (antecessor== true) {
        atual = atual->get_no_esquerdo();
        while (atual && atual->get_no_direito() != nullptr) {
            atual = atual->get_no_direito();
        }
    }else{
        //em caso nrgativo, procura no ramo da arvore do sucessor
        atual = atual->get_no_direito();
        while (atual && atual->get_no_esquerdo() != nullptr) {
            atual = atual->get_no_esquerdo();
        }
    }
    antecessor = !antecessor;
    return atual;
}

// funcao que executa o comando delete item
no * tree:: delete_no(no * root, int elemento) {
    try {
        if (root == nullptr){
            throw Erros(1);
        }
        if (!find(elemento)){
            throw  Erros(2,elemento);
        }
        //verifica se a arvore esta vazia
        if (root == nullptr) {
            return root;
            //verifica se o elemento que esta na arvore e superior ao elemento e executa recursivamente com o no do ramo esquerdo
        } else if (elemento < root->get_elemento()) {
            root->set_no_esquerdo(delete_no(root->get_no_esquerdo(), elemento));
            //verifica se o elemento que esta na arvore e inferior ao elemento e executa recursivamente com o no do ramo direito
        } else if (elemento > root->get_elemento()) {
            root->set_no_direito(delete_no(root->get_no_direito(), elemento));
        } else {
            //caso contrario vai eliminar
            if (root->get_no_esquerdo() == nullptr) {
                no *temporario = root->get_no_direito();
                delete(root);
                return temporario;
            }else if (root->get_no_direito() == nullptr) {
                no *temporario = root->get_no_esquerdo();
                delete(root);
                return temporario;
            }
            //Caso existam 2 filhos seleciona um deles
            no *temporario = no_vminimo(root);
            root->set_elemento(temporario->get_elemento());
            if(antecessor==false) {
                root->set_no_esquerdo(delete_no(root->get_no_esquerdo(), temporario->get_elemento()));
            }else {
                root->set_no_direito(delete_no(root->get_no_direito(), temporario->get_elemento()));
            }
        }return root;
    }catch (const Erros &e) {
        throw Erros(e);
    }
}

//funcao que executa o comando clear
bool tree:: clear ( ) {
    try {
        if (root== nullptr){
            throw Erros(1);
        }
        while (root != nullptr) {
            set_root(delete_no(get_root(), get_root()->get_elemento()));
        }
    }catch (const Erros &e) {
        throw Erros(e);
    }
    return true;
}

// funcao que efetua a rotacao a esquerda
void tree::rotate_esquerda(no * no_raiz, no* no_mudar, no* avo){
    //verifica se o no que vai ser rodado possui filhos esquerdos
    if(no_mudar->get_no_esquerdo()!= nullptr){
        no_raiz->set_no_direito(no_mudar->get_no_esquerdo());
        no_mudar->set_no_esquerdo(nullptr);
    } else {
        no_raiz->set_no_direito(nullptr);
    }
    //verifica se o no que vai ser substituido e o root(raiz) da arvore
    if(avo == nullptr){
        root = no_mudar;
        //verifica se o no que vai ser substituido e o filho esquerdo
    } else if(avo->get_no_esquerdo() == no_raiz){
        avo->set_no_esquerdo(no_mudar);
        //verifica se o no que vai ser substituido e o filho direito
    } else{
        avo->set_no_direito(no_mudar);
    }
    //roda os valores
    if (no_mudar->get_no_esquerdo() != nullptr) {
        no_raiz->set_no_direito(no_mudar->get_no_direito());
    }
    no_mudar->set_no_esquerdo(no_raiz);
}

//funcao que efetua a rotacao para a direita
void tree:: rotate_direita(no * no_raiz, no* no_mudar, no* avo) {
    //verifica se o no que vai ser rodado possui filhos direitos
    if (no_mudar->get_no_direito() != nullptr) {
        no_raiz->set_no_esquerdo(no_mudar->get_no_direito());
        no_mudar->set_no_direito(nullptr);
    } else{
        no_raiz->set_no_esquerdo(nullptr);
    }
    //verifica se o no que vai ser substituido e o root(raiz) da arvore
    if (avo == nullptr) {
        root = no_mudar;
        //verifica se o no que vai ser substituido e o filho direito
    } else if (avo->get_no_direito() == no_raiz) {
        avo->set_no_direito(no_mudar);
        //verifica se o no que vai ser substituido e o filho esquerdo
    } else {
        avo->set_no_esquerdo(no_mudar);
    }
    //roda os valores
    if (no_mudar->get_no_direito() != nullptr) {
        no_raiz->set_no_esquerdo(no_mudar->get_no_esquerdo());
    }
    no_mudar->set_no_direito(no_raiz);
}

//funcao que executa o comando rotate
bool tree:: rotate(int elemento){
    try {
        if (this->root == nullptr) {
            throw Erros(1);
        }
        if (!find(elemento)) {
            throw Erros(2, elemento);
        }
        //verifica se o no que roda nao e a raiz(root)
        if (elemento != root->get_elemento()) {
            no *atual = root;
            no * pai = nullptr;
            //procura o no a rodar
            while(!possui_elemento(elemento, atual)){
                pai=atual;
                if(atual->get_elemento() > elemento){
                    atual = atual->get_no_esquerdo();
                } else {
                    atual= atual->get_no_direito();
                }
            }
            //executa as operacoes de rodar
            if (atual->get_elemento() < elemento){
                rotate_esquerda(atual, atual->get_no_direito(), pai);
            }else{
                rotate_direita(atual, atual->get_no_esquerdo(), pai);
            }
        }
        return false;
    }catch (const Erros &e) {
        throw Erros(e);
    }
}


// função que verifica se algum dos nos filhos possui elemento
bool tree:: possui_elemento(int elemento, no * atual){
    if(atual->get_elemento() < elemento){
        if (atual->get_no_direito()->get_elemento()== elemento){
            return true;
        }
        else {
            return false;
        }
    } else{
        if (atual->get_no_esquerdo()->get_elemento()== elemento){
            return true;
        }
        else {
            return false;
        }
    }
    return false;
}

//funcao que procura se o elemento existe na arvore
bool tree:: find( int elemento){
    no * atual = root;
    while(atual != nullptr){
        if (atual->get_elemento()== elemento){
            return true;
        } else if(atual->get_elemento() < elemento ){
            atual= atual->get_no_direito();
        }else if( atual->get_elemento()> elemento){
            atual = atual->get_no_esquerdo();
        }
    }
    return false;
}

/****************************************************/
/*      funcoes pertencentes a  classe  Comandos    */
/****************************************************/

//funcao contrutora da classe comandos
comandos:: comandos (string & linha){
    this->mensagem= "";
    this->linha.str(linha);
}

//funcao destrutora da classe comandos
comandos:: ~comandos ( ){
    this->mensagem =  "";
    this->linha.str("");
}

//funcao que verifica se a string esta vazia
bool comandos::mensagem_vazia() const{
    return this->mensagem.empty();
}
// funcao que obtem(neste caso retorna) uma mensagem
string  comandos::get_mensagem() const{
    return mensagem;
}

//funcao que trata dos outputs (interface->que executa os comandos)
void comandos :: executar_comandos (tree * root ) {
    string texto;
    this->linha >> texto;
    if (texto == "insert") {
        while (!this->linha.eof()) {//enquanto a linha nao chegue ao final
            this->linha >> texto;
            int elemento_lista = stoi(texto);
            if (root->insert(elemento_lista)) {//chama a funcao insert
                this->mensagem = "";
            }
        }
    } else if (texto == "print_inorder") {
        try {
            this->mensagem = root->print(root);
        } catch (const Erros &e) {
            this->mensagem = "Comando print_inorder: ";
            this->mensagem.append(e.what());
        }
    } else if (texto == "delete") {
        try {
            while (!this->linha.eof()) {//enquanto a linha nao chegue ao final
                this->linha >> texto;
                int elemento_lista = stoi(texto);
                root->set_root(root->delete_no(root->get_root(), elemento_lista));//chama a funcao delete
                this->mensagem = "";
            }
        }catch (const Erros &e) {
            this->mensagem = "Comando delete: ";
            this->mensagem.append(e.what());
        }
    } else if (texto == "clear") {
        try {
            if (root->clear()) {
                this->mensagem = "";
            }
        } catch (const Erros &e) {
            this->mensagem = "Comando clear: ";
            this->mensagem.append(e.what());
        }
    }else if (texto == "rotate") {
        try {
            while (!this->linha.eof()) {//enquanto a linha nao chegue ao final
                this->linha >> texto;
                int elemento_lista = stoi(texto);
                root->rotate(elemento_lista);//chama a funcao rotate
                this->mensagem = "";
            }
        } catch (const Erros &e) {
            this->mensagem = "Comando rotate: ";
            this->mensagem.append(e.what());
        }
    }
}
/****************************************************/
/*                  funcao principal                */
/****************************************************/
/*
int main() {
    string linha;
    auto * root = new tree();
    while(getline(cin,linha)){ //Ler ficheiro
        if(linha.substr(0,1)!= "#" || linha.empty()){//caso encontre um # ignora a linha
            auto * novo_comando = new comandos(linha);
            novo_comando->executar_comandos(root);
            if(!novo_comando->mensagem_vazia()){//caso a execucao do novo_comando gere alguma mensagem
                cout << novo_comando->get_mensagem();
            }
            delete(novo_comando);
        }
    }
    delete(root);
    return 0;
}*/

int main() {
    string linha;
    auto * root = new tree();
    fstream file;
    file.open("cmd.txt", ios::in);
    while(getline(file,linha)){ //Ler ficheiro
        if(linha.substr(0,1)!= "#" || linha.empty()){
            auto * novo_comando = new comandos(linha);
            novo_comando->executar_comandos(root);
            if(!novo_comando->mensagem_vazia()){
                cout << novo_comando->get_mensagem();
            }
            delete(novo_comando);
        }
    }
    file.close();
    delete(root);
    return 0;
}

