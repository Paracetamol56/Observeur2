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
    "<html>"
    "<head>"
    "    <meta charset=\"utf-8\">"
    "    <style>"
    "        body {"
    "            font-family: Helvetica, Arial,sans-serif;"
    "        }"
    "        table {"
    "            border-collapse: collapse;"
    "            border: 2px solid rgb(200, 200, 200);"
    "            letter-spacing: 1px;"
    "            font-family: sans-serif;"
    "            font-size: .8rem;"
    "        }"
    "        td,"
    "        th {"
    "            border: 1px solid #3a3a3a;"
    "            padding: 5px;"
    "            text-align: center;"
    "        }"
    "        tr:nth-child(even) {"
    "            background-color: #eeeeee;"
    "        }"
    "    </style>"
    "</head>"
    "<body style=\"font-family: Helvetica,Arial,sans-serif;\">"
    "    <table>"
    "        <tr>";

    for (int i = 0; i < model->columnCount(); i++)
    {
        html += QString("<th>" + model->headerData(i, Qt::Horizontal).toString() + "</th>");
    }

    html =+
    "        </tr>";

    for (int i = 0; i < model->rowCount(); i++)
    {
        html +=
        "        <tr>";
        for (int j = 0; j < model->columnCount(); j++)
        {
            html += QString("<th>" + model->index(i, j).data().toString() + "</th>");
        }
        html +=
        "        </tr>";
    }
    html +=
    "    </table>"
    "    <footer style=\"margin: auto;\">"
    "        <p>Document générer par l'Observeur2 - Créé par Mathéo Galuba © 2021 - Tous droits réservés - Apache License 2.0</p>"
    "    </footer>"
    "</body>"
    "</html>";

    // Ask file location
    QString filename = QFileDialog::getSaveFileName(0, QString::fromUtf8("Générer le PDF"), QCoreApplication::applicationDirPath(), ".pdf");

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
