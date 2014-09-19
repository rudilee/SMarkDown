SMarkDown
=========

Ridiculously simple Markdown document viewer.

##Background
I built this in an evening when need a way to read [Laravel's Markdown documentation](https://github.com/laravel/docs) but didn't have Internet conectivity at the time to looking for a decent viewer for it.
So think I can slap a simple Qt app as a viewer for the documents, so this is it.
Most of what it did is just simply parse the Markdown format and convert it to HTML fragments and display it in QTextEdit, Qt's QString & QRegExp do all the heavy lifting.
