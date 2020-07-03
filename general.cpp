#include "general.h"
#include <QApplication>
#include <QDesktopWidget>

General *General::getInstance()
{
    static General ins;
    return &ins;
}

QSize General::getScreenSize(int index)
{
    int current = index == -1?QApplication::desktop()->primaryScreen():index;
    return QApplication::desktop()->screenGeometry(current).size();
}

int General::getScreenNum()
{
    return QApplication::desktop()->screenCount();
}
