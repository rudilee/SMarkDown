#ifndef MARKDOWNVIEWER_H
#define MARKDOWNVIEWER_H

#include <QTextEdit>

class MarkdownViewer : public QTextEdit
{
    Q_OBJECT
public:
    explicit MarkdownViewer(QWidget *parent = 0, QString filename = "");

private:
    bool isPreBlock, isListGroup, isTable;

    void readFile(QString filename);
    QString parseMarkdown(QByteArray line);
    QString parseFormating(QString text);
    QString parseLink(QString text);
};

#endif // MARKDOWNVIEWER_H
