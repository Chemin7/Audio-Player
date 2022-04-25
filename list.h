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
        int id;
        QTableWidgetItem* itemName;
        QTableWidgetItem* itemAuthor;
        QTableWidgetItem* itemAddress;

    };

        Node* head;

        Node* currentSong;
        QTableWidget* table;

        bool isValidPos(Node*);
        void updateIndexes();
        void copyAll(list);

        int rows;
    public:
        typedef Node* position;

        list();
        ~list();

        int id;

        void setTable(QTableWidget*);

        bool isEmpty();

        void insertElem(Node*, song&);
        void deleteElem(Node*);
        void deleteFirstElem();
        void deleteLastElem();

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
        void modify(int,song);

        song retrieve(Node*);

        std::string toString();

        void deleteAll();

        list& operator = (list&);

};

#endif // LIST_H
