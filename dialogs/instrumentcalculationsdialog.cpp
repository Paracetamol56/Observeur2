#include "instrumentcalculationsdialog.h"
#include "ui_instrumentcalculationsdialog.h"


InstrumentCalculationsDialog::InstrumentCalculationsDialog(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::InstrumentCalculationsDialog)
{
    m_ui->setupUi(this);

    // Set table size policy
    m_ui->editableEyepiecesTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    // Set table edition delegation
    m_ui->editableEyepiecesTableWidget->setItemDelegate(new Delegate);
    // Sort by default
    m_ui->editableEyepiecesTableWidget->setSortingEnabled(true);
    m_ui->editableEyepiecesTableWidget->sortByColumn(0, Qt::AscendingOrder);
}


InstrumentCalculationsDialog::~InstrumentCalculationsDialog()
{
    delete m_ui;
}


bool InstrumentCalculationsDialog::checkInput()
{
    if (m_ui->brandLineEdit->text() == "")
    {
        throw MissingInputError(ErrorPriority::BadInput, "Vous devez specifier une marque d'instrument");
        return false;
    }

    if (m_ui->modelLineEdit->text() == "")
    {
        throw MissingInputError(ErrorPriority::BadInput, "Vous devez specifier un modèle d'instrument");
        return false;
    }

    if (m_ui->focalDoubleSpinBox->value() == 0.00)
    {
        throw MissingInputError(ErrorPriority::BadInput, "Vous devez specifier la distance focal de l'instrument");
        return false;
    }

    if (m_ui->diameterDoubleSpinBox->value() == 0.00)
    {
        throw MissingInputError(ErrorPriority::BadInput, "Vous devez specifier le diamètre de l'instrument");
        return false;
    }

    return true;
}


void InstrumentCalculationsDialog::on_computePushButton_clicked()
{
    try
    {
        if (checkInput())
        {
            double focal = m_ui->focalDoubleSpinBox->value();
            if (m_ui->focalComboBox->currentIndex() == 1)
                focal *= 25.4;

            double diameter = m_ui->diameterDoubleSpinBox->value();
            if (m_ui->focalComboBox->currentIndex() == 1)
                diameter *= 25.4;

            QString markdown =
                "**" + m_ui->brandLineEdit->text() + "**\n\n"
                + m_ui->modelLineEdit->text() + "\n\n"
                "Disatance focale : " + QString::number(focal, 'f', 2) + "mm\n\n"
                + "Diamètre : " + QString::number(diameter, 'f', 2) + "mm\n\n"
                + "Rapport F/D : " + QString::number(focal / diameter, 'f', 2)
                + "\n\n---\n\n"
                "Magnitude limite théorique : " + QString::number(5.0 * log10(diameter) + 2.1, 'f', 1) + "\n\n"
                "Pouvoir séparateur théorique : " + QString::number(120 / diameter, 'f', 1) + "s d'arc\n\n"
                "Ce qui correspond à une pièce de 1€ vue à " + QString::number((23.25 / tan(((120 / diameter) * PI / 180) / 3600)) / 1000000, 'f', 2)
                + " km ou à des détails de " + QString::number(tan(((120 / diameter) * PI / 180) / 3600) * 384000, 'f', 2)
                + " km sur la Lune.";

            m_ui->textBrowser->setMarkdown(markdown);
        }
    }
    catch (Error &e)
    {
        e.printMessage();
    }
}


void InstrumentCalculationsDialog::on_addPushButton_clicked()
{
    // New row
    m_ui->editableEyepiecesTableWidget->insertRow ( m_ui->editableEyepiecesTableWidget->rowCount() );
    // Focal column
    m_ui->editableEyepiecesTableWidget->setItem( m_ui->editableEyepiecesTableWidget->rowCount() - 1 , 0 , new QTableWidgetItem(0.00));
    // Field column
    m_ui->editableEyepiecesTableWidget->setItem( m_ui->editableEyepiecesTableWidget->rowCount() - 1 , 1 , new QTableWidgetItem(0.00));
    // Edit the new item by default
    m_ui->editableEyepiecesTableWidget->editItem( m_ui->editableEyepiecesTableWidget->itemAt(m_ui->editableEyepiecesTableWidget->rowCount() - 1, 0) );
}


void InstrumentCalculationsDialog::on_removePushButton_clicked()
{
    if (m_ui->editableEyepiecesTableWidget->selectedItems().count() != 0)
        m_ui->editableEyepiecesTableWidget->removeRow(m_ui->editableEyepiecesTableWidget->selectedItems().first()->row());
}

