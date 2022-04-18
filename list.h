#ifndef LIST_H
#define LIST_H
#include "song.h"
#include <QTableWidget>
#include <QTableWidgetItem>

class list
{
private:
    class Node{
    public:
        Node();
        Node(song&);

        song data;
        Node* next;
        Node* prev;

    };

        Node* head;
        Node* currentSong;
        QTableWidget* table;

        bool isValidPos(Node*);
        void copyAll(list);

        int rows;
    public:
        typedef Node* position;

        list();
        ~list();

        void setTable(QTableWidget*);

        bool isEmpty();

        void insertElem(Node*, song&);
        void deleteElem(Node*);
        void deleteFirstElem();

        song getCurrentSong();

        void nextSong();
        void prevSong();

        Node* getFirstPos();
        Node* getLastPos();
        Node* getPrevPos(Node*);
        Node* getNextPos(Node*);

        Node* findElem(song&);
        Node* findElemByAtribute(std::string, int);
        void reverse();

        song retrieve(Node*);

        std::string toString();

        void deleteAll();

        list& operator = (list&);

};

#endif // LIST_H
