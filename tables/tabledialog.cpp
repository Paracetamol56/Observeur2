/**
 * Created on Tue Jul 31 2021
 * 
 * Copyright (c) 2021 - Mathéo G - All Right Reserved
 * 
 * Licensed under the Apache License, Version 2.0
 * Available on GitHub at https://github.com/Paracetamol56/Observeur2 */

#include "tabledialog.h"
#include "ui_tabledialog.h"

TableDialog::TableDialog(QWidget *parent, QSqlDatabase *database)
    : QDialog(parent)
    , m_ui(new Ui::TableDialog)
    , m_db(database)
{
    // ########################## Setup the UI ######################### //

    m_ui->setupUi(this);
}


TableDialog::~TableDialog()
{
    delete m_ui;
}


void TableDialog::generatePdf()
{
    QAbstractItemModel *model = m_ui->tableView->model();

    // Set the document HTML
    QString html =
    "<!DOCTYPE html>"
    "<html>"
    "<head>"
    "    <meta charset=\"utf-8\">"
    "    <style>"
    "        body {"
    "            font-family: sans-serif;"
    "        }"
    "        table {"
    "            border-collapse: collapse;"
    "            font-size: .8rem;"
    "            margin-left: auto;"
    "            margin-right: auto;"
    "            table-layout: fixed;"
    "            width: 100%;"
    "        }"
    "        th {"
    "            border: 1px solid #021624;"
    "            background-color: #A2CDEA;"
    "            padding: 7px;"
    "            text-align: center;"
    "            font-size: .9rem;"
    "            font-weight: bold;"
    "        }"
    "        td {"
    "            border: 1px solid #021624;"
    "            background-color: #C7DBE8;"
    "            padding: 5px;"
    "            margin: 0px;"
    "            text-align: justify;"
    "        }"
    "        footer {"
    "            position: absolute;"
    "            bottom: 20px;"
    "            text-align: center;"
    "            margin-left: auto;"
    "            margin-right: auto;"
    "            left: 0;"
    "            right: 0;"
    "        }"
    "    </style>"
    "</head>"
    "<body style=\"font-family: sans-serif;\">"
    "    <table>"
    "        <thead>"
    "            <tr>";

    for (int i = 0; i < model->columnCount(); i++)
    {
        html += ("<th>" + model->headerData(i, Qt::Horizontal).toString() + "</th>");
    }

    html +=
    "            </tr>"
    "        </thead>"
    "        </tbody>";

    for (int i = 0; i < model->rowCount(); i++)
    {
        html +=
        "<tr>";
        for (int j = 0; j < model->columnCount(); j++)
        {
            html += QString("<td>" + model->index(i, j).data().toString() + "</td>");
        }
        html +=
        "</tr>";
    }
    html +=
    "        </tbody>"
    "    </table>"
    "    <footer>"
    "        <p>Document générer par l'Observeur2 - Créé par Mathéo Galuba © 2021 - Tous droits réservés - Apache License 2.0"
    "        </p>"
    "    </footer>"
    "</body>"
    "</html>";

    qDebug() << html;

    // Ask file location
    QString filename = QFileDialog::getSaveFileName(0, QString::fromUtf8("Générer le PDF"), "Document.pdf", "*.pdf");

    // Settup the printer
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPageOrientation(QPageLayout::Landscape);
    printer.setPageSize(QPageSize::A4);
    printer.setPageMargins(QMargins(0, 0, 0, 0));
    printer.setOutputFileName(filename);

    // Print the document with the printer
    QTextDocument document;
    document.setHtml(html);
    document.print(&printer);
}


void TableDialog::on_ClosePushButton_clicked()
{
    close();
}


void TableDialog::on_PrintPushButton_clicked()
{
    generatePdf();
}
