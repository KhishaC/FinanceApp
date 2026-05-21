#ifndef TOPIC_H
#define TOPIC_H

#include <QString>


////PARENT CLASS

class Topic
{
protected:
    QString englishTitle;
    QString frenchTitle;

public:
    Topic(QString en, QString fr)
    {
        englishTitle = en;
        frenchTitle = fr;
    }

    QString getTitle(QString lang)
    {
        if (lang == "fr")
            return frenchTitle;

        return englishTitle;
    }
};

//// CHILD CLASS


class FinanceTopic : public Topic
{
public:
    FinanceTopic(QString en, QString fr)
        : Topic(en, fr)
    {
    }
};

#endif
