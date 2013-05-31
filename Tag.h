#ifndef TAG_H
#define TAG_H

#include <QString>

class Tag
{
public:
    Tag(QString name);
    QString getName();
    //friend bool operator==(const Tag& tag, const Tag& right);
private:
    QString name;
};

#endif // TAG_H
