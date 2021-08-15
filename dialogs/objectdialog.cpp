#include "objectdialog.h"
#include "ui_objectdialog.h"


ObjectDialog::ObjectDialog(QWidget *parent, QSqlDatabase *database, const unsigned int objectId)
    : QDialog(parent)
    , m_ui(new Ui::ObjectDialog)
    , m_db(database)
    , m_id(objectId)
    , m_rightAscension(0.00)
    , m_declination(0.00)
{
    m_ui->setupUi(this);

    setWindowIcon(QIcon(":/Ressources/icons/icons8-show-property-96.png"));

    m_db->open();

    QSqlQuery query;

    // Set the query
    query.prepare(
                "SELECT "
                "`objects`.`object_id`, "                   // 0
                "`objects`.`object_name`, "                 // 1
                "`objects`.`object_messier`, "              // 2
                "`objects`.`object_ngc`, "                  // 3
                "`objects`.`object_othername1`, "           // 4
                "`objects`.`object_othername2`, "           // 5
                "`categories`.`category_name`, "            // 6
                "`constellations`.`constellation_name`, "   // 7
                "`objects`.`object_apparent_magnitude`, "   // 8
                "`objects`.`object_secondary_magnitude`, "  // 9
                "`objects`.`object_right_ascension`, "      // 10
                "`objects`.`object_declination`, "          // 11
                "`objects`.`object_appreciation`, "         // 12
                "`objects`.`object_note`, "                 // 13
                "`skymap1`.`skymap1_number`, "              // 14
                "`skymap2`.`skymap2_number`, "              // 15
                "`skymap3`.`skymap3_number`, "              // 16
                "`objects`.`object_distance`, "             // 17
                "`objects`.`object_diameter`"               // 18
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
                "WHERE `objects`.`object_id` = :object_id;"
                );

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
        messierPushButton->setIcon(QIcon(":/Ressources/icons/icons8-lien-externe-96.png"));
        connect(messierPushButton, SIGNAL(clicked()), this, SLOT(on_messierPushButton_clicked()));
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
        ngcPushButton->setIcon(QIcon(":/Ressources/icons/icons8-lien-externe-96.png"));
        connect(ngcPushButton, SIGNAL(clicked()), this, SLOT(on_ngcPushButton_clicked()));
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

    computeGraph();
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


void ObjectDialog::computeGraph()
{
    // Julian days to compute
    /*
    Jan 2451558.50000
    Feb 2451589.50000
    Mar 2451618.50000
    Avr 2451649.50000
    Mai 2451679.50000
    Jun 2451710.50000
    Jul 2451740.50000
    Aug 2451771.50000
    Sep 2451802.50000
    Oct 2451832.50000
    Nov 2451863.50000
    Dec 2451893.50000
    */

    EquatorialPosition test("18h37m56.00s", "38°47'08\".00");
    HorizontalPosition hpTest = test.toHorizontalPosition(14, 8, 2021, 21, 0, 0);
    qDebug() << "Azi : " << hpTest.getAzimuth().getDegreeAngle();
    qDebug() << "Alt : " << hpTest.getAltitude().getDegreeAngle();

    QBarSet *set0 = new QBarSet("Masse d'aire");
    QBarSet *set1 = new QBarSet("Elévation (°)");
    *set0 << 1 << 2 << 3 << 4 << 5 << 6 << 6 << 5 << 4 << 3 << 2 << 1;
    *set1 << 60 << 50 << 40 << 30 << 20 << 10 << 10 << 20 << 30 << 40 << 50 << 60;

    QBarSeries *serie0 = new QBarSeries();
    serie0->append(set0);

    QBarSeries *serie1 = new QBarSeries();
    serie1->append(set1);

    m_chart = new QChart();
    m_chart->addSeries(serie0);
    m_chart->addSeries(serie1);
    m_chart->setTitle("Graphe de visibilité");
    m_chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;
    categories << "Janvier" << "Février" << "Mars" << "Avril" << "Mai" << "Juin" << "Juillet" << "Août" << "Septembre" << "Octobre" << "Novembre" << "Décembre";
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    m_chart->addAxis(axisX, Qt::AlignBottom);
    serie0->attachAxis(axisX);
    serie1->attachAxis(axisX);

    QValueAxis *axisY0 = new QValueAxis();
    axisY0->setRange(0, 10);
    m_chart->addAxis(axisY0, Qt::AlignLeft);
    serie0->attachAxis(axisY0);

    QValueAxis *axisY1 = new QValueAxis();
    axisY1->setRange(0, 90);
    m_chart->addAxis(axisY1, Qt::AlignRight);
    serie1->attachAxis(axisY1);

    m_chart->legend()->setVisible(true);
    m_chart->legend()->setAlignment(Qt::AlignBottom);

    m_chartView = new QChartView(m_chart);
    m_chartView->setRenderHint(QPainter::Antialiasing);

    m_chartView = new QChartView(m_chart);
    m_ui->mainHorizontalLayout->addWidget(m_chartView);
}

