/**
 * Created on Tue Jul 31 2021
 *
 * Copyright (c) 2021 - Mathéo G - All Right Reserved
 *
 * Licensed under the Apache License, Version 2.0
 * Available on GitHub at https://github.com/Paracetamol56/Observeur2 */

#include "objectdialog.h"
#include "ui_objectdialog.h"

ObjectDialog::ObjectDialog(QWidget *parent, QSqlDatabase *database, const unsigned int objectId)
    : QDialog(parent), m_ui(new Ui::ObjectDialog), m_db(database), m_id(objectId), m_rightAscension(0.00), m_declination(0.00)
{
    m_ui->setupUi(this);

    setWindowIcon(QIcon(":/res/icons/icons8-show-property-96.png"));

    m_db->open();

    QSqlQuery query;

    // Set the query
    query.prepare(
        "SELECT "
        "`objects`.`object_id`, "                  // 0
        "`objects`.`object_name`, "                // 1
        "`objects`.`object_messier`, "             // 2
        "`objects`.`object_ngc`, "                 // 3
        "`objects`.`object_othername1`, "          // 4
        "`objects`.`object_othername2`, "          // 5
        "`categories`.`category_name`, "           // 6
        "`constellations`.`constellation_name`, "  // 7
        "`objects`.`object_apparent_magnitude`, "  // 8
        "`objects`.`object_secondary_magnitude`, " // 9
        "`objects`.`object_right_ascension`, "     // 10
        "`objects`.`object_declination`, "         // 11
        "`objects`.`object_appreciation`, "        // 12
        "`objects`.`object_note`, "                // 13
        "`skymap1`.`skymap1_number`, "             // 14
        "`skymap2`.`skymap2_number`, "             // 15
        "`skymap3`.`skymap3_number`, "             // 16
        "`objects`.`object_distance`, "            // 17
        "`objects`.`object_diameter`"              // 18
        "FROM `objects` "
        "INNER JOIN categories "
        "ON categories.`category_id` = objects.`object_category` "
        "INNER JOIN constellations "
        "ON constellations.`constellation_id` = objects.`object_constellation` "
        "INNER JOIN skymap1 "
        "ON skymap1.`skymap1_id` = objects.`object_skymap1_id` "
        "INNER JOIN skymap2 "
        "ON skymap2.`skymap2_id` = objects.`object_skymap2_id` "
        "INNER JOIN skymap3 "
        "ON skymap3.`skymap3_id` = objects.`object_skymap3_id` "
        "WHERE `objects`.`object_id` = :object_id;");

    query.bindValue(":object_id", QString::number(objectId));

    if (query.exec() == false)
    {
        SqlError sqlError(ErrorPriority::Critical, "Impossible de selectionner l'objet", &query);
        sqlError.printMessage();
    }

    query.next();

    // Name
    {
        QLineEdit *nameEdit = new QLineEdit(query.value(1).toString(), this);
        nameEdit->setReadOnly(true);
        m_ui->formLayout->addRow("Nom", nameEdit);
    }

    // Messier
    if (query.value(2).toString() != "")
    {
        QHBoxLayout *messierLayout = new QHBoxLayout();
        m_messierEdit = new QLineEdit(query.value(2).toString(), this);
        m_messierEdit->setReadOnly(true);
        QPushButton *messierPushButton = new QPushButton(this);
        messierPushButton->setText("Simbad");
        messierPushButton->setIcon(QIcon(":/res/icons/icons8-lien-externe-96.png"));
        connect(messierPushButton, &QPushButton::released, this, &ObjectDialog::on_messierPushButton_clicked);
        messierLayout->addWidget(m_messierEdit);
        messierLayout->addWidget(messierPushButton);
        m_ui->formLayout->addRow("Messier", messierLayout);
    }

    // NGC
    if (query.value(3).toString() != "")
    {
        QHBoxLayout *ngcLayout = new QHBoxLayout();
        m_ngcEdit = new QLineEdit(query.value(3).toString(), this);
        m_ngcEdit->setReadOnly(true);
        QPushButton *ngcPushButton = new QPushButton(this);
        ngcPushButton->setText("Simbad");
        ngcPushButton->setIcon(QIcon(":/res/icons/icons8-lien-externe-96.png"));
        connect(ngcPushButton, &QPushButton::released, this, &ObjectDialog::on_ngcPushButton_clicked);
        ngcLayout->addWidget(m_ngcEdit);
        ngcLayout->addWidget(ngcPushButton);
        m_ui->formLayout->addRow("NGC", ngcLayout);
    }

    // Other name(s)
    if (query.value(4).toString() != "")
    {
        QLineEdit *othernameEdit_1 = new QLineEdit(query.value(4).toString(), this);
        othernameEdit_1->setReadOnly(true);
        m_ui->formLayout->addRow("Autre nom", othernameEdit_1);
        if (query.value(5).toString() != "")
        {
            QLineEdit *othernameEdit_2 = new QLineEdit(query.value(5).toString(), this);
            othernameEdit_2->setReadOnly(true);
            m_ui->formLayout->addRow("", othernameEdit_2);
        }
    }

    // Type
    if (query.value(6).toString() != "")
    {
        QLineEdit *typeEdit = new QLineEdit(query.value(6).toString(), this);
        typeEdit->setReadOnly(true);
        m_ui->formLayout->addRow("Type", typeEdit);
    }

    // Constellation
    if (query.value(7).toString() != "")
    {
        QLineEdit *constellationEdit = new QLineEdit(query.value(7).toString(), this);
        constellationEdit->setReadOnly(true);
        m_ui->formLayout->addRow("Constellation", constellationEdit);
    }

    // Apparent magnitude(s)
    if (query.value(8).toString() != "")
    {
        QLineEdit *magnitudeEdit_1 = new QLineEdit(query.value(8).toString(), this);
        magnitudeEdit_1->setReadOnly(true);
        m_ui->formLayout->addRow("Magnitude apparente", magnitudeEdit_1);
        if (query.value(9).toString() != "")
        {
            QLineEdit *magnitudeEdit_2 = new QLineEdit(query.value(8).toString(), this);
            magnitudeEdit_2->setReadOnly(true);
            m_ui->formLayout->addRow("", magnitudeEdit_2);
        }
    }

    // Distance
    if (query.value(17).toString() != "")
    {
        QLineEdit *distanceEdit = new QLineEdit(query.value(17).toString(), this);
        distanceEdit->setReadOnly(true);
        m_ui->formLayout->addRow("Distance", distanceEdit);
    }

    // Diameter
    if (query.value(18).toString() != "")
    {
        QLineEdit *diameterEdit = new QLineEdit(query.value(18).toString(), this);
        diameterEdit->setReadOnly(true);
        m_ui->formLayout->addRow("Diamètre", diameterEdit);
    }

    // Right ascension
    if (query.value(10).toString() != "")
    {
        m_rightAscension = Angle(query.value(10).toString());
        QLineEdit *rightAscensionEdit = new QLineEdit(query.value(10).toString(), this);
        rightAscensionEdit->setReadOnly(true);
        m_ui->formLayout->addRow("Ascention droite", rightAscensionEdit);
    }

    // Declination
    if (query.value(11).toString() != "")
    {
        m_declination = Angle(query.value(11).toString());
        QLineEdit *declinationEdit = new QLineEdit(query.value(11).toString(), this);
        declinationEdit->setReadOnly(true);
        m_ui->formLayout->addRow("Déclinaison", declinationEdit);
    }

    // Skymap 1
    if (query.value(14).toString() != "")
    {
        QLineEdit *skymap1Edit = new QLineEdit(query.value(14).toString(), this);
        skymap1Edit->setReadOnly(true);
        m_ui->formLayout->addRow("Carte niveau 1", skymap1Edit);
    }

    // Skymap 2
    if (query.value(15).toString() != "")
    {
        QLineEdit *skymap2Edit = new QLineEdit(query.value(15).toString(), this);
        skymap2Edit->setReadOnly(true);
        m_ui->formLayout->addRow("Carte niveau 2", skymap2Edit);
    }

    // Skymap 3
    if (query.value(16).toString() != "")
    {
        QLineEdit *skymap3Edit = new QLineEdit(query.value(16).toString(), this);
        skymap3Edit->setReadOnly(true);
        m_ui->formLayout->addRow("Carte niveau 3", skymap3Edit);
    }

    // Note
    {
        QLineEdit *noteEdit = new QLineEdit(query.value(13).toString() + "/10", this);
        noteEdit->setReadOnly(true);
        m_ui->formLayout->addRow("Note", noteEdit);
    }

    // Appreciation
    if (query.value(12).toString() != "")
    {
        QTextBrowser *appreciationEdit = new QTextBrowser(this);
        appreciationEdit->setReadOnly(true);
        appreciationEdit->setMarkdown(query.value(12).toString());
        m_ui->formLayout->addRow("Appreciation", appreciationEdit);
    }

    m_db->close();

    // Chart
    m_chartView = new QChartView();
    computeYearGraph();
    m_chartView->setRenderHint(QPainter::Antialiasing);
    m_ui->chartVerticalLayout->addWidget(m_chartView);

    QDate currentDate = QDate::currentDate();
    m_ui->dateEdit->setDate(currentDate);
    m_ui->dayDateGroupBox->hide();
}

ObjectDialog::~ObjectDialog()
{
    delete m_ui;
}

void ObjectDialog::on_messierPushButton_clicked()
{
    QDesktopServices::openUrl(QUrl("https://simbad.u-strasbg.fr/simbad/sim-basic?Ident=m" + m_messierEdit->text() + "&submit=SIMBAD+search"));
}

void ObjectDialog::on_ngcPushButton_clicked()
{
    QDesktopServices::openUrl(QUrl("https://simbad.u-strasbg.fr/simbad/sim-basic?Ident=ngc" + m_ngcEdit->text() + "&submit=SIMBAD+search"));
}

void ObjectDialog::on_ModifyPushButton_clicked()
{
    ObjectForm *modifyObjectWindow = new ObjectForm(nullptr, m_db, m_id);
    close();
    modifyObjectWindow->show();
}

void ObjectDialog::on_ClosePushButton_clicked()
{
    this->close();
}

void ObjectDialog::computeYearGraph()
{
    EquatorialPosition objectPosition(m_rightAscension, m_declination);

    QBarSet *set0 = new QBarSet("Masse d'aire");
    QBarSet *set1 = new QBarSet("Elévation (°)");

    // Populate sets
    // Static variables for each value
    unsigned int dayOfMonth = m_ui->daySpinBox->value();
    unsigned int hour = m_ui->hourSpinBox->value();
    unsigned int minute = m_ui->minuteSpinBox->value();
    //
    for (int i = 1; i <= 12; ++i)
    {
        Date date(dayOfMonth, i, 2000, hour, minute, 0);

        HorizontalPosition ObjectHorizontalPosition = objectPosition.toHorizontalPosition(date);
        // Elevation angle
        Angle elevation = ObjectHorizontalPosition.getAltitude();
        // Airmass
        if (elevation <= Angle(5.0))
        {
            *set0 << 0.00;
        }
        else
        {
            *set0 << (1 / cos((PI / 2) - elevation.getTotalRadian()));
        }
        // Elevation
        *set1 << elevation.getTotalDegree();
    }

    QBarSeries *serie0 = new QBarSeries();
    serie0->append(set0);

    QBarSeries *serie1 = new QBarSeries();
    serie1->append(set1);

    QChart *chart = new QChart();
    chart->addSeries(serie0);
    chart->addSeries(serie1);
    chart->setTitle("Graphe de visibilité");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;
    categories << "Janvier"
               << "Février"
               << "Mars"
               << "Avril"
               << "Mai"
               << "Juin"
               << "Juillet"
               << "Août"
               << "Septembre"
               << "Octobre"
               << "Novembre"
               << "Décembre";
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    serie0->attachAxis(axisX);
    serie1->attachAxis(axisX);

    QValueAxis *axisY0 = new QValueAxis();
    axisY0->setRange(0, 40);
    chart->addAxis(axisY0, Qt::AlignLeft);
    serie0->attachAxis(axisY0);

    QValueAxis *axisY1 = new QValueAxis();
    axisY1->setRange(0, 90);
    chart->addAxis(axisY1, Qt::AlignRight);
    serie1->attachAxis(axisY1);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    m_chartView->setChart(chart);
}

void ObjectDialog::computeDayGraph()
{
    EquatorialPosition objectPosition(m_rightAscension, m_declination);

    QLineSeries *serie0 = new QLineSeries();
    QLineSeries *serie1 = new QLineSeries();

    serie0->setName("Elévation (°)");
    serie1->setName("Horizon");

    // Populate sets
    // Static variables for each value
    QDate editedDate = m_ui->dateEdit->date();
    Date date(editedDate.day(), editedDate.month(), editedDate.year(), 0, 0, 0);
    //
    for (float i = 0; i <= 24.0; i += 0.5f)
    {
        date.m_hour = std::trunc(i);
        date.m_minute = (i - date.m_hour) * 60;

        HorizontalPosition ObjectHorizontalPosition = objectPosition.toHorizontalPosition(date);
        // Elevation angle
        Angle elevation = ObjectHorizontalPosition.getAltitude();
        // Elevation
        *serie0 << QPointF(i, elevation.getTotalDegree());
    }

    // Horizon
    *serie1 << QPointF(0.0, 0.0) << QPointF(24.0, 0.0);

    QChart *chart = new QChart();
    chart->addSeries(serie0);
    chart->addSeries(serie1);

    QValueAxis *axisY0 = new QValueAxis();
    axisY0->setRange(-90.0, 90.0);
    chart->addAxis(axisY0, Qt::AlignLeft);
    serie0->attachAxis(axisY0);
    serie1->attachAxis(axisY0);

    QValueAxis *axisX0 = new QValueAxis();
    axisX0->setRange(0, 24);
    axisX0->setTickCount(13);
    chart->addAxis(axisX0, Qt::AlignBottom);
    serie0->attachAxis(axisX0);
    serie1->attachAxis(axisX0);

    chart->setTitle("Graphe de visibilité");

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    m_chartView->setChart(chart);
}

void ObjectDialog::on_typeChange()
{
    if (m_ui->yearSamplingRadioButton->isChecked())
    {
        // Update ui
        m_ui->yearDateGroupBox->show();
        m_ui->dayDateGroupBox->hide();
        computeYearGraph();
    }
    else if (m_ui->daySamplingRadioButton->isChecked())
    {
        // Update ui
        m_ui->yearDateGroupBox->hide();
        m_ui->dayDateGroupBox->show();
        computeDayGraph();
    }
}

void ObjectDialog::on_dateChange()
{
    if (m_ui->yearSamplingRadioButton->isChecked())
    {
        computeYearGraph();
    }
    else if (m_ui->daySamplingRadioButton->isChecked())
    {
        computeDayGraph();
    }
}
