#include "markdownviewer.h"

#include <QFile>
#include <QRegExp>

MarkdownViewer::MarkdownViewer(QWidget *parent, QString filename) :
    QTextEdit(parent),
    isPreBlock(false),
    isListGroup(false),
    isTable(false)
{
    setReadOnly(true);

    readFile(filename);
}

void MarkdownViewer::readFile(QString filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QString parsedHtml;
    while (!file.atEnd()) {
        parsedHtml += parseMarkdown(file.readLine());
    }

    file.close();
    setHtml(parsedHtml);
}

QString MarkdownViewer::parseMarkdown(QByteArray line)
{
    if (line.trimmed().isEmpty() || line.startsWith("--"))
        return "\n";

    QString parsedHtml;

    QRegExp header("^(#+)\\s(.+)$"),
            pre("^\\t(.+)$"),
            list("^(\\-|\\*)\\s(.+)$"),
            table("^.+\\|.+"),
            blockquote("^\\>\\s(.+)$");

    if (pre.indexIn(line) > -1) {
        if (!isPreBlock) {
            isPreBlock = true;
            parsedHtml = "<pre>";
        }

        parsedHtml += QString(line).toHtmlEscaped();

        return parsedHtml;
    } else if (isPreBlock) {
        isPreBlock = false;
        parsedHtml = "</pre>";
    }

    QString formated = parseFormating(parseLink(line.trimmed()));

    if (list.indexIn(formated) > -1) {
        if (!isListGroup) {
            isListGroup = true;
            parsedHtml = "<ul>";
        }

        parsedHtml += QString("<li>%1</li>").arg(list.cap(2));

        return parsedHtml;
    } else if (isListGroup) {
        isListGroup = false;
        parsedHtml = "</ul>";
    }

    if (table.indexIn(line) > -1) {
        QString entity = "td";

        if (!isTable) {
            isTable = true;
            parsedHtml = "<table border=\"1\">";
            entity = "th";
        }

        parsedHtml += QString("<tr><%2>%1</%2></tr>").arg(formated.split('|').join(QString("</%1><%1>").arg(entity)), entity);

        return parsedHtml;
    } else if (isTable) {
        isTable = false;
        parsedHtml = "</table>";
    }

    if (header.indexIn(formated) > -1) {
        int level = header.cap(1).length();

        parsedHtml += QString("<h%1>%2</h%1>").arg(QString::number(level), header.cap(2).trimmed());
    } else if (blockquote.indexIn(formated) > -1) {
        parsedHtml += QString("<blockquote>%1</blockquote>").arg(blockquote.cap(1));
    } else if (!line.startsWith('<')) {
        parsedHtml += QString("<p>%1</p>").arg(QString(formated.trimmed()));
    } else {
        parsedHtml += line.trimmed();
    }

    return parsedHtml;
}

QString MarkdownViewer::parseFormating(QString text)
{
    QRegExp bold("\\*\\*(.+)\\*\\*"),
            code("`(.+)`");

    bold.setMinimal(true);
    code.setMinimal(true);

    return text.replace(bold, "<b>\\1</b>")
               .replace(code, "<code>\\1</code>");
}

QString MarkdownViewer::parseLink(QString text)
{
    QRegExp link("\\[(.+)\\]\\((.+)\\)");
    link.setMinimal(true);

    return text.replace(link, "<a href=\"\\2\">\\1</a>");
}
