#include "song.h"

song::song()
{

}
void song::copyAll(song& s) {
    this->name = s.name;
    this->author = s.author;

    this->address = s.address;
    }


song::song(song& s) {
    copyAll(s);

    }

song song::operator=(song& s) {
    copyAll(s);

    return *this;
    }


QString song::getName() {
    return name;
    }

QString song::getAuthor() {
    return author;
    }


QString song::getAddress()
    {
        return address;
    }


void song::setName(const QString n) {
    name = n;
    }

void song::setAuthor(const QString a) {
    author = a;
    }



void song::setAddress(const QString a) {
    address=a;
    }
bool song::operator == (song& s) {
    return name.compare(s.name) == 0;

    }

bool song::operator!=(song& s) {
    return !(*this == s);
    }

bool song::operator>(song& s) {
    return name.compare(s.name) > 0;
    }

bool song::operator>=(song& s) {
    return *this > s && *this == s;
    }

bool song::operator<(song&  s) {
    return !(*this >= s);
    }

bool song::operator<=(song& s) {
    return *this < s && *this == s;
    }
