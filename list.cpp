#include "list.h"
#include "song.h"
    #include <QHeaderView>

///Node

list::Node::Node(){
    next=nullptr ;
    prev=nullptr;
}

list::Node::Node(song& s){
    data=s;
    next=nullptr ;
    prev=nullptr;
}

///List
list::list()
{
    head=nullptr;
    rows=0;
}


list::~list() {
    deleteAll();
    }

void list::setTable(QTableWidget* t){
    table = t;
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    QStringList hLabels;

    table->setColumnCount(table->horizontalHeader()->count() + 3);

    hLabels<<"Nombre"<<"Autor"<<"URL";
    table->setHorizontalHeaderLabels(hLabels);

}

/*void list::copyAll(list l) {
    Node* aux(l.head);
    Node* last(nullptr);
    Node* newNode;

    while(aux!= nullptr) {
        newNode = new Node(aux->data);

        if(last == nullptr)
            head=newNode;
        else
            last->next=newNode;

        last=newNode;
        aux=aux->next;
        }

    }*/
bool list::isValidPos(Node* p) {
    if(!isEmpty()) {
            Node* aux(head);

            do {
                if(aux==p)
                    return true;
                aux=aux->next;
                }
            while(aux!=head);
            }
        return false;
    }






bool list::isEmpty() {
    return head==nullptr;
    }


void list::insertElem(Node* p,song& e) {
   /* if(p!=nullptr && !isValidPos(p))
            return;
*/
    Node* aux = new Node(e);
    if(aux == nullptr)
            return;///Exception
        if(p==nullptr) {

            if(head == nullptr) { //Insertar al principio, no hay mas nodos
                aux->next=aux;
                aux->prev=aux;
                //aux->index = 0;


            }
            else {//Ya hay mas nodos
                aux->prev=head->prev;
                aux->next=head;

                head->prev->next=aux;
                head->prev=aux;

                }
            head=aux;
            }
        else {//Insertar en cualquier lugar
            aux->prev=p;
            aux->next=p->next;

            p->next->prev=aux;
            p->next=aux;
            }
        head=aux;

        //Table

        table->setRowCount(table->verticalHeader()->count()+1);
         QString element;

                 for(int col = 0; col < 3; col++ ) {
                     QTableWidgetItem *newItem = new QTableWidgetItem();
                     switch(col){
                         case 0:
                             element=this->getFirstPos()->data.getName();
                         break;
                         case 1:
                             element=this->getFirstPos()->data.getAuthor();
                         break;
                         case 2:
                             element=this->getFirstPos()->data.getAddress();
                         break;
                     }

                     newItem->setText(element);
                     table->setItem(rows, col, newItem);
                     table->setCurrentItem(newItem);
                      table->setItemSelected(newItem,true);
                 }

                 rows++;
                 table->resizeRowsToContents();

            currentSong = aux;
            ///----------------------------




}


void list::deleteElem(Node* p) {
    if(!isValidPos(p))
            return;///Exception


        p->prev->next=p->next;
        p->next->prev=p->prev;

        if(p==head) {
            if(p->next==p)
                head=nullptr;
            else
                head=head->next;
            }

        delete p;
    }
void list::deleteFirstElem(){
    Node* p=head;
    head=head->next;
    delete p;

    rows--;
    ///Eliminar al principio
    ///table->removeRow(0);
    table->removeRow(table->currentRow());

}

song list::getCurrentSong(){
    return currentSong->data;
}

list::Node* list::getFirstPos() {
    return head;
    }

void list::nextSong(){
    currentSong = currentSong->next;

}

void list::prevSong(){
     currentSong = currentSong->prev;
}

list::Node* list::getLastPos() {
    if(isEmpty())
        return nullptr;

    Node* aux(head);
    while(aux->next!=nullptr)
        aux=aux->next;

    return aux;
    }


list::Node* list::getPrevPos(Node* p) {
    if(!isValidPos(p))
        return nullptr;

    return p->prev;
    }


list::Node* list::getNextPos(Node* p) {
    if(!isValidPos(p))
        return nullptr;

    return p->next;
    }


list::Node* list::findElem(song& e) {
    Node* aux(head);

    while(aux!=nullptr && aux->data!=e)
        aux=aux->next;
    return aux;
    }


///findElemen by Atr

void list::reverse(){

      if(head != NULL) {
        Node* prevNode = head;
        Node* tempNode = head;
        Node* curNode = head->next;


        prevNode->next = prevNode;
        prevNode->prev = prevNode;

        while(curNode != head) {

          tempNode = curNode->next;

          curNode->next = prevNode;
          prevNode->prev = curNode;
          head->next = curNode;
          curNode->prev = head;

          prevNode = curNode;
          curNode = tempNode;
        }


        head = prevNode;

        //Adjust table

        //Table

        Node* aux(head);
         QString element;
            for(int i=0;i<rows;i++){
                 for(int col = 0; col < 3; col++ ) {
                     QTableWidgetItem *newItem = new QTableWidgetItem();
                     switch(col){
                         case 0:
                             element=aux->data.getName();
                         break;
                         case 1:
                             element=aux->data.getAuthor();
                         break;
                         case 2:
                             element=aux->data.getAddress();
                         break;
                     }
                     newItem->setText(element);
                     table->setItem(i, col, newItem);
                 }
                 aux=aux->next;
                 }


                 table->resizeRowsToContents();
            ///----------------------------

    }
}
song list::retrieve(Node* p) {
    if(!isValidPos(p)) {
        throw("Posicion invalida,retrieve");
        }

    return p->data;

    }


void list::deleteAll() {
    Node* aux;

    while(head!=nullptr) {
        aux=head;
        head = head->next;
        delete aux;
        }
    }


/*list& list::operator=(list& l) {
    deleteAll();
    copyAll(l);
    return *this;
    }*/


