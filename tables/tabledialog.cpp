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
    "</head>"
    "<body>"
    "    <table>"
    //"        <thead>"
    "            <tr>";

    for (int i = 0; i < model->columnCount(); i++)
    {
        html += QString("                <th>" + model->headerData(i, Qt::Horizontal).toString() + "</th>");
    }

    html =+
    "            </tr>";
    //"        </thead>"
    //"        </tbody>";

    for (int i = 0; i < model->rowCount(); i++)
    {
        html +=
        "            <tr>";
        for (int j = 0; j < model->columnCount(); j++)
        {
            html += QString("                <td>" + model->index(i, j).data().toString() + "</td>");
        }
        html +=
        "            </tr>";
    }
    html +=
    //"        </tbody>"
    "    </table>"
    "    <footer>"
    "        <p>Document générer par l'Observeur2 - Créé par Mathéo Galuba © 2021 - Tous droits réservés - Apache License 2.0</p>"
    "    </footer>"
    "</body>"
    "</html>";

    QString style =
    "body {"
    "font-family: sans-serif;"
    "}"
    "table {"
    "border: 2px solid #021624;"
    "font-size: .8rem;"
    "margin: auto;"
    "}"
    "td,"
    "th {"
    "border: 1px solid #021624;"
    "padding: 5px;"
    "margin: 0px"
    "text-align: center;"
    "background-color: #E8EDF1;"
    "}"
    "th {"
    "background-color: #E8EDF1;"
    "border: 1px solid #021624;"
    "color: #eeeeee"
    "}";

    // Ask file location
    QString filename = QFileDialog::getSaveFileName(0, QString::fromUtf8("Générer le PDF"), "D:/DOCUMENTS UTILISATEUR/Desktop/test.pdf", "*.pdf");

    // Settup the printer
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPageOrientation(QPageLayout::Landscape);
    printer.setPageSize(QPageSize::A4);
    printer.setPageMargins(QMargins(0, 0, 0, 0));
    printer.setOutputFileName(filename);

    // Print the document with the printer
    QTextDocument document;
    document.setDefaultStyleSheet(style);
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
