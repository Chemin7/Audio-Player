#ifndef SONG_H
#define SONG_H
#include <QString>

class song
{
            QString name;
            QString author ;
            QString address;

           void copyAll(song&);

       public:
           song();


           song(song&);
           song operator = (song&);

            QString getName();
            QString getAuthor();
            QString getAddress();

           void setName(const QString);
           void setAuthor(const QString );
           void setAddress(const QString);

           bool operator == (song&);
                 bool operator != (song&);
                 bool operator > (song&);
                 bool operator >= (song&);
                 bool operator < (song&);
                 bool operator <= (song&);


};

#endif // SONG_H
