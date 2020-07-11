#ifndef OUTLINER_H
#define OUTLINER_H

#include <QObject>
#include <QTreeWidget>

class Outliner : public QTreeWidget
{
    Q_OBJECT
public:
    explicit Outliner(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // OUTLINER_H
